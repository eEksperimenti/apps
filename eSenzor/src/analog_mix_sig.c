
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "analog_mix_sig.h"

/* Global variables */
analog_mixed_sig_t *analog_mixed_sig_reg = NULL;
int analog_mixed_sig_fd = -1;

int analog_mixed_sig_init(void){

	if(analog_mixed_sig_release() < -1){
		printf("Mapping resources failed.");
		return -1;
	}

	void *page_ptr;
	long page_addr, page_off, page_size = sysconf(_SC_PAGESIZE);

	/* OPEN THE DEVICE */
	analog_mixed_sig_fd = open("/dev/mem", O_RDWR | O_SYNC);

	if(analog_mixed_sig_fd  < -1){
		printf("Error opening /dev/mem\n");
		return -1;
	}

	/* Calculate page correct addresses */
	page_addr = ANALOG_MIXED_SIG_ADDR & (~(page_size - 1));

	page_off = ANALOG_MIXED_SIG_ADDR - page_addr;

	/* mmap physical memory */
	page_ptr = mmap(NULL, ANALOG_MIXED_SIG_SIZE, PROT_READ | 
		PROT_WRITE, MAP_SHARED, analog_mixed_sig_fd, page_addr);

	if((void *)page_ptr == MAP_FAILED){
		printf("Mapping failed.\n");
		return -1;
	}

	analog_mixed_sig_reg = page_ptr + page_off;

	return 0;

}

int analog_mixed_sig_release(void)
{
	 
	if(analog_mixed_sig_reg)
	{
		if(munmap(analog_mixed_sig_reg, ANALOG_MIXED_SIG_SIZE) < 0)
		{
			printf("Unmapping failed.\n");
			return -1;
		}
		if(analog_mixed_sig_fd >= 1)
		{
			close(analog_mixed_sig_fd);
			analog_mixed_sig_fd = -1;
		}
	}
	return 0;
}