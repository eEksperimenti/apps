#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#include "rp.h"
#include "read_element.h"

int rp_init_API(void)
{
	/* Print error, if rp_Init() function failed */
	if(rp_Init() != RP_OK)
	{
    fprintf(stderr, "Rp api init failed!\n");
    return -1;
  }

  rp_DpinSetDirection(RP_DIO0_P, RP_OUT);
  rp_DpinSetDirection(RP_DIO1_P, RP_OUT);
  rp_DpinSetDirection(RP_DIO2_P, RP_OUT);
  rp_DpinSetDirection(RP_DIO3_P, RP_OUT);

  rp_DpinSetState(RP_DIO0_P,  RP_HIGH);

  /* Default reading from R = 000 on extension board */
  rp_DpinSetState(RP_DIO1_P,  RP_LOW);
  rp_DpinSetState(RP_DIO2_P,  RP_LOW);
  rp_DpinSetState(RP_DIO3_P,  RP_LOW);

  return 0;
}

/*int rp_start_API(void)
{
  ptime = (float*)calloc(SIG_LENGTH, sizeof(*ptime));

  int i;

  for( i = 0; i < SIG_LENGTH; ++i)
  {
    ptime[i] = i;
  }

  panalog_signals = (float*)calloc(NUM_ANA_SIG * NUM_ANA_SIG_LEN, sizeof(*panalog_signals));
  ana_sig_array = panalog_signals;

  return 0;
}*/

int rp_stop_API(void)
{
  rp_Release();
  return 0;
}

/*int rp_copy_analog_signals(float ***signals, int *sig_idx)
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
}*/

void read_element(void)
{
  if( *pread_ele == 0 )
  {
    rp_DpinSetState(RP_DIO1_P,  RP_LOW);
    rp_DpinSetState(RP_DIO2_P,  RP_LOW);
    rp_DpinSetState(RP_DIO3_P,  RP_LOW);
  }
  else if( *pread_ele == 1 )
  {
    rp_DpinSetState(RP_DIO1_P,  RP_HIGH);
    rp_DpinSetState(RP_DIO2_P,  RP_LOW);
    rp_DpinSetState(RP_DIO3_P,  RP_LOW);
  }
  else if( *pread_ele == 2 )
  {
    rp_DpinSetState(RP_DIO1_P,  RP_LOW);
    rp_DpinSetState(RP_DIO2_P,  RP_HIGH);
    rp_DpinSetState(RP_DIO3_P,  RP_LOW);
  }
  else if( *pread_ele == 3 )
  {
    rp_DpinSetState(RP_DIO1_P,  RP_HIGH);
    rp_DpinSetState(RP_DIO2_P,  RP_HIGH);
    rp_DpinSetState(RP_DIO3_P,  RP_LOW);
  }
  else if( *pread_ele == 4 )
  {
    rp_DpinSetState(RP_DIO1_P,  RP_LOW);
    rp_DpinSetState(RP_DIO2_P,  RP_LOW);
    rp_DpinSetState(RP_DIO3_P,  RP_HIGH);
  }
  else if( *pread_ele == 5 )
  {
    rp_DpinSetState(RP_DIO1_P,  RP_HIGH);
    rp_DpinSetState(RP_DIO2_P,  RP_LOW);
    rp_DpinSetState(RP_DIO3_P,  RP_HIGH);
  }
  else if( *pread_ele == 6 )
  {
    rp_DpinSetState(RP_DIO1_P,  RP_LOW);
    rp_DpinSetState(RP_DIO2_P,  RP_HIGH);
    rp_DpinSetState(RP_DIO3_P,  RP_HIGH);
  }
  else if( *pread_ele == 7 )
  {
    rp_DpinSetState(RP_DIO1_P,  RP_HIGH);
    rp_DpinSetState(RP_DIO2_P,  RP_HIGH);
    rp_DpinSetState(RP_DIO3_P,  RP_HIGH);
  }
}