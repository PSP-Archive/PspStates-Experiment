// PspStates Experiment v1 for PSP SLIM by Dark-Alex
// Reversed by plum

// header
#include "pspstates.h"

// info
PSP_MODULE_INFO("pspSleepMode_test", PSP_MODULE_KERNEL | PSP_MODULE_SINGLE_LOAD | PSP_MODULE_SINGLE_START, 1, 1);

// extras.S
u32 power_jump_addr;		// 0x0B68
u32 ctrl_jump_addr[3];		// 0x0BC4

// global
u32 power_addr;				// 0x2C88
u32 restore_data[2];		// 0x2CA4 - 0x2CA8
SceUID sema_ctrl_id;		// 0x2C94
SceUID second_sema_id;		// 0x2C80
STMOD_HANDLER previous;		// 0x2C8C

// extern
extern int is_running;				// 0x2C98
extern PspSysEventHandler events;	// 0x2C1C

// sub_000004E4
int OnModuleStart(SceModule2 *module)
{
	u32 orgaddr;

	if(sceKernelInitKeyConfig() == PSP_INIT_KEYCONFIG_GAME)
	{
		if(strcmp(module->modname, "sceImpose_Driver") == 0)
		{
			MAKE_STUB(module->text_addr + 0x7E74, sceCtrlPeekBufferPositivePatched);
			ClearCaches();
		}
	}
	else
	{
		// ƒQ[ƒ€ê—p‚È‚Ì‚Å‚±‚Á‚¿‚ÍŒÄ‚Î‚ê‚È‚¢

		if(strcmp(module->modname, "vsh_module") == 0)
		{
			// sceCtrlReadBufferPositive
			orgaddr = sctrlHENFindFunction("sceController_Service", "sceCtrl_driver", 0x1F803938);

			if(orgaddr != 0)
			{
				MAKE_STUB(orgaddr, sceCtrlReadBufferPositiveHijackFunc);

				ctrl_jump_addr[0] = orgaddr + 8;

				ClearCaches();
			}
		}
	}

	return previous ? previous(module) : 0;
}

// module_start
int module_start(SceSize args, void *argp)
{
	SceUID thid;
	SceModule2 *power_module;

	if(sceKernelGetModel() == PSP_MODEL_SLIM_AND_LITE && sceKernelInitKeyConfig() == PSP_INIT_KEYCONFIG_GAME)
	{
		thid = sceKernelCreateThread("InOutThread", InOutThread, 16, 0x6000, 0, NULL);

		if(thid < 0)
			return thid;

		sema_ctrl_id = sceKernelCreateSema("SemaController", 0, 0, 1, NULL);

		if(sema_ctrl_id < 0)
			return sema_ctrl_id;

		second_sema_id = sceKernelCreateSema("SecondarySema", 0, 0, 1, NULL);

		if(second_sema_id < 0)
			return second_sema_id;

		sceKernelStartThread(thid, 0, NULL);

		sceKernelRegisterSysEventHandler(&events);

		previous = sctrlHENSetStartModuleHandler(OnModuleStart);

		power_module = sceKernelFindModuleByName("scePower_Service");

		power_jump_addr = power_module->text_addr + 0x25A8;

		restore_data[0] = _lw(power_module->text_addr + 0x25A0);
		restore_data[1] = _lw(power_module->text_addr + 0x25A4);

		power_addr = power_module->text_addr + 0x25A0;

		ClearCaches();
	}

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

