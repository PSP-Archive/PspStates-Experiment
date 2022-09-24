// PspStates Experiment v2 for PSP SLIM by Dark-Alex
// Reversed by plum

// header
#include "pspstates.h"

// global
int global_number;		// 0x2F48
int is_running;			// 0x2FA8
int state_flag;			// 0x2F50
int save_flag;			// 0x2FB0
int load_flag;			// 0x2F88
int set_alarm_flag;		// 0x2F30
int driver_flag;		// 0x2FAC
char bin_path[48];		// 0x2F54

// extern
extern u8 save_processing_data[];	// 0x15E4
extern u8 load_processing_data[];	// 0x2A08
extern char umdid[10];				// 0x2F9C
extern u32 power_addr;				// 0x2F8C
extern SceUID sema_ctrl_id;			// 0x2F98
extern SceUID second_sema_id;		// 0x2F84
extern SceUID load_thid;			// 0x2F4C

// sub_00000194
void BuildPath(int global_flag)
{
	sprintf(bin_path, "ms0:/seplugins/SAVESTATE/%s_%c.bin", (global_flag) ? "globalstate" : umdid, (char)global_number);
	return;
}

// sub_00000288
void SaveProcessing(void)
{
	void (*SaveProcessingFunc)(void);

	memset((void *)0x40E0000, 0, 0x10000);
	memcpy((void *)0x40E0000, save_processing_data, 0xC70);

	SaveProcessingFunc = (void *)0x40E0000;
	driver_flag = 1;

	ClearCaches();

	SaveProcessingFunc();

	ClearCaches();
	return;
}

// sub_00000214
void LoadProcessing(void)
{
	void (*LoadProcessingFunc)(void);

	memset((void *)0x40E0000, 0, 0x10000);
	memcpy((void *)0x40E0000, load_processing_data, 0x964);

	LoadProcessingFunc = (void *)0x40E0000;

	ClearCaches();

	LoadProcessingFunc();

	while(1);
	return;
}

// loc_00000D94
void HijackPowerModuleForLoadState(void)
{
	LoadProcessing();
	return;
}

// PspLsLibrary_C118AA99
void PspSaveState(int number, int global_flag)
{
	global_number = number;
	save_flag = 1;

	BuildPath(global_flag);

	MAKE_STUB(power_addr, HijackPowerModuleForSaveState);
	ClearCaches();

	set_alarm_flag = -1;

	scePowerRequestSuspend();
	return;
}

// PspLsLibrary_E34921F7
void PspLoadState(int number, int global_flag)
{
	global_number = number;

	BuildPath(global_flag);

	sceKernelWakeupThread(load_thid);
	return;
}

// sub_00000000
void GetButtons(SceCtrlData *pad_data, u32 *get_buttons, int *get_number)
{
	if(pad_data->Buttons & PSP_CTRL_LEFT)
	{
		*get_buttons = PSP_CTRL_LEFT;
		*get_number = 'l';
	}
	else if(pad_data->Buttons & PSP_CTRL_UP)
	{
		*get_buttons = PSP_CTRL_UP;
		*get_number = 'u';
	}
	else if(pad_data->Buttons & PSP_CTRL_DOWN)
	{
		*get_buttons = PSP_CTRL_DOWN;
		*get_number = 'd';
	}
	else if(pad_data->Buttons & PSP_CTRL_RIGHT)
	{
		*get_buttons = PSP_CTRL_RIGHT;
		*get_number = 'r';
	}
	else if(pad_data->Buttons & PSP_CTRL_SQUARE)
	{
		*get_buttons = PSP_CTRL_SQUARE;
		*get_number = 'q';
	}
	else if(pad_data->Buttons & PSP_CTRL_TRIANGLE)
	{
		*get_buttons = PSP_CTRL_TRIANGLE;
		*get_number = 't';
	}
	else if(pad_data->Buttons & PSP_CTRL_CROSS)
	{
		*get_buttons = PSP_CTRL_CROSS;
		*get_number = 'x';
	}
	else if(pad_data->Buttons & PSP_CTRL_CIRCLE)
	{
		*get_buttons = PSP_CTRL_CIRCLE;
		*get_number = 'c';
	}
	else if(pad_data->Buttons & PSP_CTRL_START)
	{
		*get_buttons = PSP_CTRL_START;
		*get_number = 's';
	}

	return;
}

// sub_000003F8
void PspLsLibraryLauncher(SceCtrlData *pad_data)
{
	u32 buttons = 0;
	int number = -1;

	if(!state_flag)
	{
		if(pad_data->Buttons & PSP_CTRL_RTRIGGER)
		{
			GetButtons(pad_data, &buttons, &number);

			if(number != -1)
			{
				if(pad_data->Buttons & PSP_CTRL_SELECT)
				{
					PspSaveState(number, 1);
					buttons |= PSP_CTRL_SELECT;
				}
				else
				{
					PspSaveState(number, 0);
				}

				pad_data->Buttons &= ~(buttons | PSP_CTRL_RTRIGGER);
				state_flag = 1;
			}
		}
		else if(pad_data->Buttons & PSP_CTRL_LTRIGGER)
		{
			GetButtons(pad_data, &buttons, &number);

			if(number != -1)
			{
				if(pad_data->Buttons & PSP_CTRL_SELECT)
				{
					PspLoadState(number, 1);
					buttons |= PSP_CTRL_SELECT;
				}
				else
				{
					PspLoadState(number, 0);
				}

				pad_data->Buttons &= ~(buttons | PSP_CTRL_LTRIGGER);
				state_flag = 1;
			}
		}
	}

	return;
}

// sub_0000059C
int sceCtrlPeekBufferPositivePatched(SceCtrlData *pad_data, int count)
{
	int res = sceCtrlPeekBufferPositive(pad_data, count);

	PspLsLibraryLauncher(pad_data);

	return res;
}

// sub_00000514
int sceCtrlReadBufferPositivePatched(SceCtrlData *pad_data, int count)
{
	// ¦v1‚ÌŽž‚ÌŽcŠ[‚ÅŽg‚í‚ê‚Ä‚¢‚È‚¢

	// ˆø”‚Ìcount‚ÍsceCtrlReadBufferPositive‚Ì•Ô‚è’l‚ª“n‚³‚ê‚Ä‚¢‚é
	// ¦FW4.01‚Ìctrl.prx‚ÌsceCtrlReadBufferPositive‚ÆCtrlFuncLauncher‚ðŽQÆ

	int k1 = pspSdkSetK1(0);

	if(pad_data->Buttons & PSP_CTRL_HOME)
	{
		PspLsLibraryLauncher(pad_data);

		if(state_flag)
			pad_data->Buttons &= ~PSP_CTRL_HOME;
	}

	pspSdkSetK1(k1);
	return count;
}

