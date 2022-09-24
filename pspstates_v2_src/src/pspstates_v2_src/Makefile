TARGET = pspstates
OBJS = main.o lslibrary.o utils.o save_processing_data.o load_processing_data.o extras.o stub.o exports.o

USE_KERNEL_LIBC = 1
USE_KERNEL_LIBS = 1

BUILD_PRX = 1
PRX_EXPORTS = exports.exp

INCDIR = 
CFLAGS = -O2 -G0 -Wall -fno-builtin-printf
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = 
LIBS = -lpspkernel -lc -lpspuser -lpspsystemctrl_kernel -lpsppower -lpsprtc

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

