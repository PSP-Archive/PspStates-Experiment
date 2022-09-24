// PspStates Experiment v2 for PSP SLIM by Dark-Alex
// Reversed by plum

// header
#include "pspstates.h"

// info
PSP_MODULE_INFO("pspSleepMode_test", PSP_MODULE_KERNEL | PSP_MODULE_SINGLE_LOAD | PSP_MODULE_SINGLE_START, 1, 1);

// extras.S
u32 power_jump_addr;		// 0x0D90
u32 ctrl_jump_addr[10];		// 0x0DEC

// global
char umdid[10];				// 0x2F9C
u32 power_addr;				// 0x2F8C
u32 restore_data[2];		// 0x2FB4 - 0x2FB8
SceUID sema_ctrl_id;		// 0x2F98
SceUID second_sema_id;		// 0x2F84
SceUID load_thid;			// 0x2F4C
STMOD_HANDLER previous;		// 0x2F90

// extern
extern int is_running;				// 0x2FA8
extern PspSysEventHandler events;	// 0x2EF0

// sub_0000076C
int OnModuleStart(SceModule2 *module)
{
	int i, n;
	SceUID fd, memid;
	char *sector_buffer, *filename, *filename_tail;

	if(strcmp(module->modname, "sceKernelLibrary") == 0)
	{
		if(sceKernelBootFrom() == PSP_BOOT_DISC)
		{
			memid = 0;

			if(sceIoDevctl("umd0:", 0x01E28035, NULL, 0, &sector_buffer, 4) < 0)
			{
				memid = sceKernelAllocPartitionMemory(8, "PVD", 0x800, PSP_SMEM_High, NULL);

				if(memid > 0)
				{
					sector_buffer = sceKernelGetBlockHeadAddr(memid);

					fd = sceIoOpen("umd0:", PSP_O_RDONLY, 0);

					if(fd > 0)
					{
						sceIoLseek(fd, 0x10, PSP_SEEK_SET);
						sceIoRead(fd, sector_buffer, 1);
						sceIoClose(fd);
					}
				}
			}

			if(sector_buffer != NULL)
			{
				for(i = 0, n = 0; i < 10; i++)
				{
					if(sector_buffer[0x373 + i] != '-')
						umdid[n++] = sector_buffer[0x373 + i];
				}

				umdid[9] = '\0';
			}

			if(memid > 0)
				sceKernelFreePartitionMemory(memid);
		}
		else if(sceKernelBootFrom() == PSP_BOOT_MS)
		{
			filename = sceKernelInitFileName();

			if(filename != NULL)
			{
				filename_tail = strrchr(filename, '/');
				filename_tail[0] = '\0';

				strncpy(umdid, strrchr(filename, '/') + 1, 9);

				umdid[9] = '\0';
				filename_tail[0] = '/';
			}
		}
	}

	if(sceKernelInitKeyConfig() == PSP_INIT_KEYCONFIG_GAME)
	{
		if(strcmp(module->modname, "sceImpose_Driver") == 0)
		{
			MAKE_STUB(module->text_addr + 0x7E74, sceCtrlPeekBufferPositivePatched);
			ClearCaches();
		}
	}

	return previous ? previous(module) : 0;
}

// module_start
int module_start(SceSize args, void *argp)
{
	SceUID thid;
	SceModule2 *power_module;

	if(sceKernelGetModel() != PSP_MODEL_SLIM_AND_LITE || sceKernelInitKeyConfig() != PSP_INIT_KEYCONFIG_GAME)
		return 1;

	thid = sceKernelCreateThread("InOutThread", InOutThread, 16, 0x5000, 0, NULL);

	if(thid < 0)
		return thid;

	sema_ctrl_id = sceKernelCreateSema("SemaController", 0, 0, 1, NULL);

	if(sema_ctrl_id < 0)
		return sema_ctrl_id;

	second_sema_id = sceKernelCreateSema("SecondarySema", 0, 0, 1, NULL);

	if(second_sema_id < 0)
		return second_sema_id;

	sceKernelStartThread(thid, 0, NULL);

	load_thid = sceKernelCreateThread("load_thread", load_thread, 16, 0x1000, 0, NULL);

	if(load_thid < 0)
		return load_thid;

	sceKernelStartThread(load_thid, 0, NULL);

	sceKernelRegisterSysEventHandler(&events);

	previous = sctrlHENSetStartModuleHandler(OnModuleStart);

	power_module = sceKernelFindModuleByName("scePower_Service");

	power_jump_addr = power_module->text_addr + 0x25A8;

	restore_data[0] = _lw(power_module->text_addr + 0x25A0);
	restore_data[1] = _lw(power_module->text_addr + 0x25A4);

	power_addr = power_module->text_addr + 0x25A0;

	ClearCaches();
	return 0;
}

// module_stop
int module_stop(SceSize args, void *argp)
{
	is_running = 1;

	sceKernelSignalSema(sema_ctrl_id, 1);
	sceKernelDelayThread(50000);

	return 0;
}

