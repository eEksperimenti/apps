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
int last_ind = 511;

pthread_mutex_t rp_analog_sig_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread0;

float *ana_sig_array = NULL;
float *ptime = NULL;
float *panalog_signals = NULL;

unsigned int sleep_delta_T;
unsigned int num_of_meas;

FILE *fd = NULL;

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

  char *mode = "w";
  char *file_path = NULL;
  file_path = (char*)malloc(sizeof(char)*512);

  if( file_path == NULL )
      return 1;

  file_path[0] = '\0';
  strcpy(file_path, DEBUG_PATH);

  fd = fopen(file_path, mode);

  int i;
  for( i = 0; i < SIG_LENGTH; ++i)
  {
    ptime[i] = i;
  }

  panalog_signals = (float*)calloc(NUM_ANA_SIG * NUM_ANA_SIG_LEN, sizeof(*panalog_signals));
  ana_sig_array = panalog_signals;

  fprintf(fd, "ptime addr:%p\tpanalog_signals addr:%p\n", ptime, panalog_signals);
  
  api_running = 1;
  if( pthread_create(&thread0, &attr, read_analog_sig, NULL) != 0 )
  {
    fprintf(stderr, "Error creating thread\n");
    return -3;
  }
  
  return 0;
}

int rp_stop_API(void)
{
  api_running = 0;
  //pthread_cancel(thread0);
  rp_Release();
  free(ptime);
  free(panalog_signals);
  fclose(fd);
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

  memcpy(&s[0][0], ptime, sizeof(float) * SIG_LENGTH);
  memcpy(&s[1][0], ana_sig_array, sizeof(float) * SIG_LENGTH);
  memcpy(&s[2][0], &ana_sig_array[SIG_LENGTH], sizeof(float) * SIG_LENGTH);

  return 0;
}

void *read_analog_sig(void *ptr)
{
  unsigned int i;
  int send_ms = 0;
  
  float *panalog_sig0 = panalog_signals;
  float *panalog_sig1 = &panalog_signals[NUM_ANA_SIG_LEN];
  float *panalog_sig2 = &panalog_signals[(NUM_ANA_SIG_LEN*2)];
  float *panalog_sig3 = &panalog_signals[(NUM_ANA_SIG_LEN*3)];

 /* fprintf(fd, "panalog_sig0 addr:%p\npanalog_sig1 addr:%p\npanalog_sig2 addr:%p\n\
panalog_sig3 addr:%p\n", panalog_sig0, panalog_sig1, panalog_sig2, panalog_sig3);*/

  //fflush(fd);

  float *pcurr_sig0 = NULL;
  float *pcurr_sig1 = NULL;
  float *pcurr_sig2 = NULL;
  float *pcurr_sig3 = NULL;

  while(api_running)
  {
     while( *pdelta_T == -1 && *pnum_of_meas == -1 )
       usleep(2000);

    sleep_delta_T = ((unsigned int)((*pdelta_T) * 1000));
    num_of_meas = (unsigned int)(*pnum_of_meas);

    i = 0;

    while(num_of_meas > 0)
    {

      if( *pmeas_control == 3 )
      {
          *pdelta_T = -1;
          *pnum_of_meas = -1;
          break;
      }

      while( *pmeas_control == 1 )
        usleep(2000);

      pcurr_sig0 = panalog_sig0;
      pcurr_sig1 = panalog_sig1;
      pcurr_sig2 = panalog_sig2;
      pcurr_sig3 = panalog_sig3;

      for( i = 0; i < NUM_ANA_SIG_LEN; ++i )
      {
        if( num_of_meas == 0)
        {
          //n = last_ind;

          for( ; i < NUM_ANA_SIG_LEN; ++i)
          {
            *pcurr_sig0 = -100;
            *pcurr_sig1 = -100;
            *pcurr_sig2 = -100;
            *pcurr_sig3 = -100;

            ++pcurr_sig0;
            ++pcurr_sig1;
            ++pcurr_sig2;
            ++pcurr_sig3;
          }
          break;
        }

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

        usleep(sleep_delta_T);
        send_ms += *pdelta_T;

        if( send_ms >= SEND_MS )
        {
          ++i;
          for( ; i < NUM_ANA_SIG_LEN; ++i)
          {
            *pcurr_sig0 = -100;
            *pcurr_sig1 = -100;
            *pcurr_sig2 = -100;
            *pcurr_sig3 = -100;

            ++pcurr_sig0;
            ++pcurr_sig1;
            ++pcurr_sig2;
            ++pcurr_sig3;
          }
          last_ind = 511;
          send_ms = 0;
          break;
        }
      }

      send_ms = 0;

      if( num_of_meas <= 0)
      {
        *pdelta_T = -1;
        *pnum_of_meas = -1;
        last_ind = 511;
        //usleep(50);
      }
      
      ++(*pchange);
      
    
      if( *pchange == 100e3 )
        *pchange = 1;

      //n = last_ind;
      while( last_ind == 511 )
        usleep(2000);   
    }

  }
  return NULL;
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