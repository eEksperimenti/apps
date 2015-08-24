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
  
  api_running = 1;
  if( pthread_create(&thread0, &attr, read_analog_sig, NULL) != 0 )
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
  //usleep(50);
  //pthread_join(thread0, NULL);
  return 0;
}

void *read_analog_sig3(void *ptr)
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
      rp_ApinGetValue(RP_AIN0, rp_ain0_val);
      rp_ApinGetValue(RP_AIN1, rp_ain1_val);
      rp_ApinGetValue(RP_AIN2, rp_ain2_val);
      rp_ApinGetValue(RP_AIN3, rp_ain3_val);
      ++(*pchange);
      sleep(sleep_delta_T);
    }

    *ptrig_mode = 2;

    api_wait = 1;
    pthread_mutex_unlock(&rp_analog_sig_mutex);       
  }

  return NULL;
}


void *read_analog_sig(void *ptr)
{
	while( api_running != 0)
	{
     // pthread_mutex_lock(&rp_analog_sig_mutex);
	    rp_ApinGetValue(RP_AIN0, rp_ain0_val);
	   	rp_ApinGetValue(RP_AIN1, rp_ain1_val);
	   	rp_ApinGetValue(RP_AIN2, rp_ain2_val);
	   	rp_ApinGetValue(RP_AIN3, rp_ain3_val);
      //sleep(1);
      --api_running;
     // pthread_mutex_unlock(&rp_analog_sig_mutex);
	}

    return NULL;
}

void *read_analog_sig2(void *ptr)
{
  /*float *ptab = (float*)malloc(sizeof(*ptab)*NUM_ANA_SIG * NUM_ANA_SIG_LEN);
  float *pcurr = ptab;

  float *pend = &ptab[(NUM_ANA_SIG * NUM_ANA_SIG_LEN) - 1];*/

  int i;
  /*float val0;
  float val1;
  float val2;
  float val3;

  float sum0 = 0;
  float sum1 = 0;
  float sum2 = 0;
  float sum3 = 0;*/

  int sleep_delta_T;
  int num_of_meas;

  /*clock_t start, end;
  double cpu_time_used;

  time_t startTime, endTime;*/
 
  /* *ptrig_mode = 2;*/
  while(api_running)
  {

    pthread_mutex_lock(&rp_analog_sig_mutex);
    api_wait = 0;

    sleep_delta_T = (int)(*pdelta_T);
    num_of_meas = (int)(*pnum_of_meas);

    /*if( app_running == 0)
      break;
    time(&startTime);
    start = clock();*/
    /*for( ; i < *pnum_of_meas; ++i)
    {*/
      /*rp_ApinGetValue(RP_AIN0, pcurr);
      ++pcurr;
      rp_ApinGetValue(RP_AIN1, pcurr);
      ++pcurr;
      rp_ApinGetValue(RP_AIN2, pcurr);
      ++pcurr;
      rp_ApinGetValue(RP_AIN3, pcurr);
      ++pcurr;*/

      /*rp_ApinGetValue(RP_AIN0, &val0);
      rp_ApinGetValue(RP_AIN1, &val1);
      rp_ApinGetValue(RP_AIN2, &val2);
      rp_ApinGetValue(RP_AIN3, &val3);*/

     /* sum0 += val0;
      sum1 += val1;
      sum2 += val2;
      sum3 += val3;*/
    /*}*/

    /**rp_ain0_val = sum0/(*pnum_of_meas);
    *rp_ain1_val = sum1/(*pnum_of_meas);
    *rp_ain2_val = sum2/(*pnum_of_meas);
    *rp_ain3_val = sum3/(*pnum_of_meas);*/

    for( i = 0;i < num_of_meas; ++i)
    {
      rp_ApinGetValue(RP_AIN0, rp_ain0_val);
      rp_ApinGetValue(RP_AIN1, rp_ain1_val);
      rp_ApinGetValue(RP_AIN2, rp_ain2_val);
      rp_ApinGetValue(RP_AIN3, rp_ain3_val);
      ++(*pchange);
      sleep(sleep_delta_T);
    }


    *ptrig_mode = 2;

    api_wait = 1;
    pthread_mutex_unlock(&rp_analog_sig_mutex);      
  
     /*end = clock();
     time(&endTime);*/
     /*cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;*/
     /*cpu_time_used = ((double) (end - start));
     *rp_ain2_val = cpu_time_used;

     *rp_ain3_val = difftime(endTime, startTime);*/
  }

  /*free(ptab);*/
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