
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "house_kp.h"

/* Global variables */
house_t *house_reg = NULL;
int house_fd = -1;

int house_init(void){

	if(house_release() < -1){
		printf("Mapping resources failed.");
		return -1;
	}

	void *page_ptr;
	long page_addr, page_off, page_size = sysconf(_SC_PAGESIZE);

	/* OPEN THE DEVICE */
	house_fd = open("/dev/mem", O_RDWR | O_SYNC);

	if(house_fd  < -1){
		printf("Error opening /dev/mem\n");
		return -1;
	}

	/* Calculate page correct addresses */
	page_addr = HK_BASE_ADDR & (~(page_size - 1));

	page_off = HK_BASE_ADDR - page_addr;

	/* mmap physical memory */
	page_ptr = mmap(NULL, HK_BASE_SIZE, PROT_READ | 
		PROT_WRITE, MAP_SHARED, house_fd, page_addr);

	if((void *)page_ptr == MAP_FAILED){
		printf("Mapping failed.\n");
		return -1;
	}

	house_reg = page_ptr + page_off;

	return 0;

}

int house_release(void){
	 
	if(house_reg){
		if(munmap(house_reg, HK_BASE_SIZE) < 0){
			printf("Unmapping failed.\n");
			return -1;
		}
		if(house_fd >= 1){
			close(house_fd);
			house_fd = -1;
		}
	}
	return 0;
}

int set_led(int led){
	house_reg->led_control |= 1 << led;
	return 0; 
}

int unset_led(int led){
	house_reg->led_control &= ~(1 << led);
	return 0;
}
