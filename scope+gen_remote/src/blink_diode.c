#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rp.h"
#include "blink_diode.h"

#define Istrue(e) ((e) != 0) //Helper function. Int > 0 is true, else == 0 is false



void *diode(void *ptr){

	/* Print error, if rp_Init() function failed */
	if(rp_Init() != RP_OK){
		fprintf(stderr, "Rp api init failed!\n");
	}

	/* Set rp_dpin_t to led 1 */
	rp_dpin_t pin1 = RP_LED1;
	rp_dpin_t pin2 = RP_LED2;
	rp_dpin_t pin3 = RP_LED3;
	rp_dpin_t pin4 = RP_LED4;

	rp_DpinSetState(pin1, RP_HIGH);
	sleep(1);
	rp_DpinSetState(pin1, RP_LOW);

	rp_DpinSetState(pin2, RP_HIGH);
	sleep(1);
	rp_DpinSetState(pin2, RP_LOW);

	rp_DpinSetState(pin3, RP_HIGH);
	sleep(1);
	rp_DpinSetState(pin3, RP_LOW);

	rp_DpinSetState(pin4, RP_HIGH);
	sleep(1);
	rp_DpinSetState(pin4, RP_LOW);
	
	/* Releasing resources */
	rp_Release();
	printf("SUCCSESFULLY RAN PROGRAM BLINK DIODE.\n");
	diods_running = 0;
	return NULL;
}