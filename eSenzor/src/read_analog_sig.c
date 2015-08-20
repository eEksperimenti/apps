#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "rp.h"
#include "read_analog_sig.h"

int APP_running = 1;
pthread_mutex_t rp_analog_sig_mutex = PTHREAD_MUTEX_INITIALIZER;

int rp_start_API(void)
{
	/* Print error, if rp_Init() function failed */
	if(rp_Init() != RP_OK)
	{
    fprintf(stderr, "Rp api init failed!n");
  }

  pthread_t thread0;
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  
  pthread_mutex_lock(&rp_analog_sig_mutex);

  APP_running = 1;
  if( pthread_create(&thread0, &attr, reading_analog_sig, NULL) != 0 )
  {
    fprintf(stderr, "Error creating thread\n");
    return -3;
  }
  
  return 0;
}

int rp_stop_API(void)
{
  APP_running = 0;
  pthread_mutex_unlock(&rp_analog_sig_mutex);
  rp_Release();

  return 0;
}

void *reading_analog_sig( void *ptr )
{
	while(APP_running != 0)
	{
      pthread_mutex_lock(&rp_analog_sig_mutex);
	    rp_ApinGetValue(RP_AIN0, rp_ain0_val);
	   	rp_ApinGetValue(RP_AIN1, rp_ain1_val);
	   	rp_ApinGetValue(RP_AIN2, rp_ain2_val);
	   	rp_ApinGetValue(RP_AIN3, rp_ain3_val);
      pthread_mutex_unlock(&rp_analog_sig_mutex);
	}

    return NULL;
}