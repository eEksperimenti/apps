#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#include "rp.h"
#include "read_analog_sig.h"

int api_running = 1;
int api_wait = 0;
pthread_mutex_t rp_analog_sig_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread0;
float *ana_sig_array = NULL;
float *ptime = NULL;
float *panalog_signals = NULL;


int rp_init_API(void)
{
	/* Print error, if rp_Init() function failed */
	if(rp_Init() != RP_OK)
	{
    fprintf(stderr, "Rp api init failed!n");
  }

  return 0;
}

int rp_start_API(void)
{
 
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  pthread_mutex_lock(&rp_analog_sig_mutex);
  ptime = (float*)calloc(SIG_LENGTH, sizeof(*ptime));
  panalog_signals = (float*)malloc(sizeof(float) * NUM_ANA_SIG * NUM_ANA_SIG_LEN);
  ana_sig_array = panalog_signals;
  
  api_running = 1;
  if( pthread_create(&thread0, &attr, read_analog_sig3, NULL) != 0 )
  {
    fprintf(stderr, "Error creating thread\n");
    return -3;
  }

  //read_analog_sig(NULL);
  
  return 0;
}

int rp_stop_API(void)
{
  api_running = 0;
  //pthread_cancel(thread0);
  rp_Release();
  free(ptime);
  free(panalog_signals);
  //usleep(50);
  //pthread_join(thread0, NULL);
  return 0;
}

void rp_copy_analog_signals(float ***signals)
{
  float **s = *signals;
  //memcpy(&s[0][0], ptime, sizeof(float) * NUM_ANA_SIG_LEN * 2);
  memcpy(&s[1][0], ana_sig_array, sizeof(float) * NUM_ANA_SIG_LEN * 2);
  memcpy(&s[2][0], &ana_sig_array[NUM_ANA_SIG_LEN * 2], sizeof(float) * NUM_ANA_SIG_LEN * 2);
}

void *read_analog_sig(void *ptr)
{
  int i;

  int sleep_delta_T;
  int num_of_meas;

  while(api_running)
  {

    pthread_mutex_lock(&rp_analog_sig_mutex);
    api_wait = 0;

    sleep_delta_T = (int)(*pdelta_T);
    num_of_meas = (int)(*pnum_of_meas);

    for( i = 0;i < num_of_meas; ++i)
    {
      ++(*pchange);
      sleep(sleep_delta_T);
    }

    *ptrig_mode = 2;

    api_wait = 1;
    pthread_mutex_unlock(&rp_analog_sig_mutex);       
  }

  return NULL;
}

void *read_analog_sig3(void *ptr)
{
  int i;

  unsigned int sleep_delta_T;
  unsigned int num_of_meas;

  
  float *panalog_sig0 = panalog_signals;
  float *panalog_sig1 = &panalog_signals[NUM_ANA_SIG_LEN];
  float *panalog_sig2 = &panalog_signals[NUM_ANA_SIG_LEN*2];
  float *panalog_sig3 = &panalog_signals[NUM_ANA_SIG_LEN*3];

  float *pcurr_sig0 = NULL;
  float *pcurr_sig1 = NULL;
  float *pcurr_sig2 = NULL;
  float *pcurr_sig3 = NULL;

  /**ptrig_mode = 2;*/
  while(api_running)
  {

    //if( api_wait == 1 )


    pcurr_sig0 = panalog_sig0;
    pcurr_sig1 = panalog_sig1;
    pcurr_sig2 = panalog_sig2;
    pcurr_sig3 = panalog_sig3;

    /*pthread_mutex_lock(&rp_analog_sig_mutex);
    api_wait = 0;*/

    sleep_delta_T = (int)(*pdelta_T) * 1e6;
    num_of_meas = (int)(*pnum_of_meas);

    for( i = 0;i < *pnum_of_meas; ++i)
    {
      rp_ApinGetValue(RP_AIN0, pcurr_sig0);
      rp_ApinGetValue(RP_AIN1, pcurr_sig1);
      rp_ApinGetValue(RP_AIN2, pcurr_sig2);
      rp_ApinGetValue(RP_AIN3, pcurr_sig3);

      ++pcurr_sig0;
      ++pcurr_sig1;
      ++pcurr_sig2;
      ++pcurr_sig3;

      //usleep(1e2);

      //pthread_mutex_lock(&rp_main_params_mutex);
      ++(*pchange);
      //pthread_mutex_unlock(&rp_main_params_mutex);
      //system("echo sleep_delta_T >> /opt/www/apps/eSenzor/my.txt");
      //pthread_mutex_lock(&rp_analog_write);
      //sleep(1);
      
      //pthread_mutex_unlock(&rp_analog_write);

    }
    
    
    /**ptrig_mode = 2;*/
    api_wait = 1;
    //pthread_mutex_unlock(&rp_analog_sig_mutex);

    //--api_running;
  }

  
  return NULL;
}

/*void *read_analog_sig2( void *ptr )
{     
  char *path = (char*)malloc(sizeof(char)*PATH_LEN);
  path[0] = '\0';
  getcwd( path, PATH_LEN);
  strcat( path, "/analog_sig.txt");

  FILE *filestream = fopen( path, "w");

  float val0;
  float val1;
  float val2;
  float val3;

  float sum0 = 0;
  float sum1 = 0;
  float sum2 = 0;
  float sum3 = 0;

  int i = 0;

  clock_t start, end;
  double cpu_time_used;

  start = clock();

  for( i = 0; i < 10e6 ; ++i )
  {
    rp_ApinGetValue(RP_AIN0, &val0);
    rp_ApinGetValue(RP_AIN1, &val1);
    rp_ApinGetValue(RP_AIN2, &val2);
    rp_ApinGetValue(RP_AIN3, &val3);

    sum0 += val0;
    sum1 += val1;
    sum2 += val2;
    sum3 += val3;

    fprintf( filestream, "%3.10f %3.10f %3.10f %3.10f\n", val0, val1, val2, val3);
  }

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  fprintf( filestream, "%3.10f %3.10f %3.10f %3.10f\n", sum0, sum1, sum2, sum3);
  fprintf( filestream, "%3.10f %3.10f %3.10f %3.10f\n", sum0/10e6, sum1/10e6, sum2/10e6, sum3/10e6);
  fprintf( filestream, "CPU_time_used:%2.66f\n", cpu_time_used);
  fprintf( filestream, "CLOCKS_PER_SEC:%li\n", CLOCKS_PER_SEC);

  free(path);
  fclose(filestream);
  return NULL;
}*/