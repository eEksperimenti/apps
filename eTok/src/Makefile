CC=$(CROSS_COMPILE)gcc
#dosent work with -std=gnu99
#-g for debugging
CFLAGS= -Wall  -fPIC 
OFLAGS= -Wall -Werror 
LDFLAGS=-shared
CROSS_COMPILE=arm-linux-gnueabi-

IDIR=../include/
LDIR=../lib/

OBJECTS=main.o fpga.o worker.o calib.o fpga_awg.o generate.o load_save_params.o read_element.o

#Define header includes
RP_PATH_INCLUDE=-I $(IDIR)

#Define library includes
RP_LIB_INCLUDE=-L $(LDIR) -lm -lpthread -lrp

OUT_DIR=../
C_OUT_NAME=$(OUT_DIR)controller.so

all: $(OBJECTS)
	$(CC) -o $(C_OUT_NAME) $(OBJECTS) $(OFLAGS) $(RP_LIB_INCLUDE) $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(RP_PATH_INCLUDE) $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(C_OUT_NAME)