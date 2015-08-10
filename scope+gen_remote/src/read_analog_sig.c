#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include "rp.h"
#include "read_analog_sig.h"
void *reading_analog_sig( void *ptr )
{
 
    /* Print error, if rp_Init() function failed */
    if(rp_Init() != RP_OK){
        fprintf(stderr, "Rp api init failed!n");
    }
    rp_ApinGetValue(RP_AIN0, &rp_ain0_val);
    /*printf("Volts: %fn", volts);
 
    rp_dpin_t led_pin = 0;
 
    float p = volts*(100/3.3);
 
    int i;
    for(i = 1; i < 7; i++){
        if(p >= (100/7) * i)
            rp_DpinSetState(led_pin + i, RP_HIGH);
        else
            rp_DpinSetState(led_pin + i, RP_LOW);
        
    }*/
    rp_Release();
    /* the sleep was for testing purposes*/
    /*sleep(3);*/
    --read_analog_sig;
    return 0;
}