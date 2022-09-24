PSPDEV=$(shell psp-config --pspsdk-path)
INCLUDES=-I $(PSPDEV)/include

all:	a.bin

a.bin: 
	C:/pspsdk/bin/psp-gcc $(INCLUDES) -W -Wall -G0 -O3 -fno-pic -mno-abicalls -w -S main.c -o main.s
	C:/pspsdk/bin/psp-gcc $(INCLUDES) -W -Wall -G0 -O3 -fno-pic -mno-abicalls -w -S fastlz_compress.c -o fastlz.s
	C:/pspsdk/bin/psp-as fastlz.s -o fastlz.o
	C:/pspsdk/bin/psp-as main.s -o main.o
	C:/pspsdk/bin/psp-ld -T linkfile.l main.o fastlz.o -o main.elf
	C:/pspsdk/bin/psp-strip -s main.elf
	C:/pspsdk/bin/psp-objcopy -O binary main.elf save_processing_data.bin
	C:/pspsdk/bin/bin2c save_processing_data.bin save_processing_data.c save_processing_data

clean:
	rm -rf *~ *.o *.elf *.bin *.bin

