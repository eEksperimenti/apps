
/* Housekeeping header */

#include <stdint.h>

#ifndef __ANALOG_MIXED_SIG
#define __ANALOG_MIXED_SIG


#define ANALOG_MIXED_SIG_ADDR 0x40400000
#define ANALOG_MIXED_SIG_SIZE 0xFFFFF

#define RP_AMS_AIN0 xadc_aif0

/* Map the memory */

typedef struct analog_mix_sig_t{
	uint32_t xadc_aif0; //0x0
	uint32_t xadc_aif1; //0x4
	uint32_t xadc_aif2; //0x8
	uint32_t xadc_aif3; //0xC
	uint32_t xadc_aif4; //0x10
	uint32_t reserved1; //0x14
	uint32_t reserved2; //0x18
	uint32_t reserved3; //0x1C
	uint32_t pwm_dac0; //0x20
	uint32_t pwm_dac1; //0x24
	uint32_t pwm_dac2; //0x28
	uint32_t pwm_dac3; //0x2C
	uint32_t xadc_temperature; //0x30
	uint32_t xadc_vccpint; //0x34
	uint32_t xadc_vccpaux; //0x38
	uint32_t xadc_vccbram; //0x3c
	uint32_t xadc_vccint; //0x40
	uint32_t xadc_vccaux; //0x44
	uint32_t xadc_vccddr; //0x48
} analog_mix_sig_t;



int analog_mixed_sig_init(void);
int analog_mixed_sig_release(void);

#endif // ANALOG_MIXED_SIG


