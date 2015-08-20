#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "analog_mixed_sig.h"

/* Global variables */
analog_mixed_sig_t *analog_mixed_sig_reg = NULL;
int analog_mixed_sig_fd = -1;
/*int logfile = -1;*/

int analog_mixed_sig_init(void){

	/*logfile = open("/opt/www/apps/scope+gen_remote/logfile.txt", O_RDWR | O_SYNC | O_CREAT | O_APPEND);*/
	/*if( logfile < -1){
		printf("Error opening logfile\n");
		return -1;
	}

	write(logfile, "Log opened\n", strlen("Log opened\n"));*/

	if(analog_mixed_sig_release() < -1){
		/*char *e1 = "Mapping resources failed.\n";
		write(logfile, e1, strlen(e1));*/
		return -1;
	}

	void *page_ptr;
	long page_addr, page_off, page_size = sysconf(_SC_PAGESIZE);

	/* OPEN THE DEVICE */
	analog_mixed_sig_fd = open("/dev/mem", O_RDWR | O_SYNC);

	if(analog_mixed_sig_fd  < -1){
		/*char *e2 = "Error opening /dev/mem\n";
		write(logfile, e2, strlen(e2));*/
		return -1;
	}

	/*write(logfile, "Opened /dev/mem\n", strlen("Opened /dev/mem\n"));*/

	/* Calculate page correct addresses */
	page_addr = ANALOG_MIXED_SIG_ADDR & (~(page_size - 1));

	page_off = ANALOG_MIXED_SIG_ADDR - page_addr;

	/* mmap physical memory */
	page_ptr = mmap(NULL, ANALOG_MIXED_SIG_SIZE, PROT_READ | 
		PROT_WRITE, MAP_SHARED, analog_mixed_sig_fd, page_addr);

	if((void *)page_ptr == MAP_FAILED){
		/*char *e3 = "Mapping failed.\n";
		write(logfile, e3, strlen(e3));*/
		return -1;
	}

	/*write(logfile, "Mapped the addresses\n", strlen("Mapped the addresses\n"));*/

	analog_mixed_sig_reg = page_ptr + page_off;

	return 0;

}

int analog_mixed_sig_release(void)
{
	 
	if(analog_mixed_sig_reg != NULL)
	{
		if(munmap(analog_mixed_sig_reg, ANALOG_MIXED_SIG_SIZE) < 0)
		{
			/*har *e4 = "Unmapping failed.\n";
			write(logfile, e4, strlen(e4));*/
			return -1;
		}
		if(analog_mixed_sig_fd >= 1)
		{
			close(analog_mixed_sig_fd);
			analog_mixed_sig_fd = -1;
		}
	}
	/*write(logfile, "Clossing logfile.txt\n\n", strlen("Clossing logfile.txt\n"));
	close(logfile);*/
	return 0;
}

void rp_ams_ApinGetValue( int val ,float *value )
{
	 /**value = analog_mixed_sig_reg->xadc_aif0 & 0x00000fff; */
	 switch(val)
	 {
	 	case RP_AMS_AIN0:
	 		*value = analog_mixed_sig_reg->xadc_aif0;
	 		break;
	 	case RP_AMS_AIN1:
	 		*value = analog_mixed_sig_reg->xadc_aif1;
	 		break;
	 	case RP_AMS_AIN2:
	 		*value = analog_mixed_sig_reg->xadc_aif2;
	 		break;
	 	case RP_AMS_AIN3:
	 		*value = analog_mixed_sig_reg->xadc_aif3;
	 		break;
	 	default:
	 		*value = -1;
	 }
	  *value = ((int)*value) & 0x00000fff;
	  *value /= DIVISON_FACTOR; 
}