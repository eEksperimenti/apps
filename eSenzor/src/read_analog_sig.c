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
int last_ind = 0;


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

  int i;

  for( i = 0; i < SIG_LENGTH; ++i)
  {
    ptime[i] = i;
  }

  panalog_signals = (float*)malloc(sizeof(float) * NUM_ANA_SIG * NUM_ANA_SIG_LEN);
  ana_sig_array = panalog_signals;
  
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
  free(ptime);
  free(panalog_signals);
  //rp_DpinSetState(RP_LED4, RP_LOW);
  //usleep(50);
  //pthread_join(thread0, NULL);
  return 0;
}

int rp_copy_analog_signals(float ***signals, int *sig_idx)
{
  float **s = *signals;

  if( last_ind < 511 )
  {
    *sig_idx = 1;
    return -1;
  }
  else
  {
    *sig_idx = SIG_LENGTH - 1;
    last_ind = 0;
  }

  memcpy(&s[0][0], ptime, sizeof(float) * NUM_ANA_SIG_LEN * 2);
  memcpy(&s[1][0], ana_sig_array, sizeof(float) * NUM_ANA_SIG_LEN * 2);
  memcpy(&s[2][0], &ana_sig_array[NUM_ANA_SIG_LEN * 2], sizeof(float) * NUM_ANA_SIG_LEN * 2);

  return 0;
}

void *read_analog_sig2(void *ptr)
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

void *read_analog_sig(void *ptr)
{
  unsigned int i;
  unsigned int j;

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

  while(api_running)
  {
    pcurr_sig0 = panalog_sig0;
    pcurr_sig1 = panalog_sig1;
    pcurr_sig2 = panalog_sig2;
    pcurr_sig3 = panalog_sig3;

    /*while( *pdelta_T != -1 && *pnum_of_meas != -1 )
      usleep(100);

    sleep_delta_T = (int)(*pdelta_T) * 1e6;
    num_of_meas = (int)(*pnum_of_meas);*/

   
    //for( ; num_of_meas > 0; )
    //{
      for( i = 0;i < NUM_ANA_SIG_LEN; ++i)
      {
        rp_ApinGetValue(RP_AIN0, pcurr_sig0);
        rp_ApinGetValue(RP_AIN1, pcurr_sig1);
        rp_ApinGetValue(RP_AIN2, pcurr_sig2);
        rp_ApinGetValue(RP_AIN3, pcurr_sig3);

        ++pcurr_sig0;
        ++pcurr_sig1;
        ++pcurr_sig2;
        ++pcurr_sig3;

        ++last_ind;
        --num_of_meas;

        /*if( num_of_meas == 0)
        {
          break;
        }*/

        //usleep(sleep_delta_T);
        usleep(10);
      }

      while( last_ind == 511)
        usleep(100);
      //*pN = last_ind;
      ++(*pchange);
    //}

  }
  return NULL;
}