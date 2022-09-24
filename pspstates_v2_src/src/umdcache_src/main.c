// umdcache_dummy by Dark-Alex
// Reversed by plum

// header
#include <pspkernel.h>
#include <pspsysmem_kernel.h>
#include <pspinit.h>

// info
PSP_MODULE_INFO("pspUmdCache_Dummy", PSP_MODULE_KERNEL | PSP_MODULE_SINGLE_LOAD | PSP_MODULE_SINGLE_START, 1, 1);
PSP_NO_CREATE_MAIN_THREAD();

// module_start
int module_start(SceSize args, void *argp)
{
	u32 addr;

	if(sceKernelGetModel() == PSP_MODEL_SLIM_AND_LITE && sceKernelInitKeyConfig() == PSP_INIT_KEYCONFIG_GAME && sceKernelBootFrom() == PSP_BOOT_MS)
	{
		for(addr = 0xBC000040; addr < 0xBC000080; addr += 4)
		{
			_sw(-1, addr);
		}
	}

	return 1;
}

