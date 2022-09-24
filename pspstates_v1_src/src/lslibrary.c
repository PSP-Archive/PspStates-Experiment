// PspStates Experiment v1 for PSP SLIM by Dark-Alex
// Reversed by plum

// header
#include "pspstates.h"

// global
int global_number;		// 0x2C78
int is_running;			// 0x2C98
int state_flag;			// 0x2C7C
int save_flag;			// 0x2CA0
int load_flag;			// 0x2C84
int set_alarm_flag;		// 0x2C60
int driver_flag;		// 0x2C9C

// extern
extern u8 save_processing_data[];	// 0x130C
extern u8 load_processing_data[];	// 0x2730
extern u32 power_addr;				// 0x2C88
extern SceUID sema_ctrl_id;			// 0x2C94
extern SceUID second_sema_id;		// 0x2C80

// sub_000001B4
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

// sub_00000140
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

// loc_00000B6C
void HijackPowerModuleForLoadState(void)
{
	LoadProcessing();
	return;
}

// PspLsLibrary_C118AA99
void PspSaveState(int number)
{
	global_number = number;

	MAKE_STUB(power_addr, HijackPowerModuleForSaveState);
	ClearCaches();

	save_flag = 1;
	set_alarm_flag = -1;

	scePowerRequestSuspend();
	return;
}

// PspLsLibrary_E34921F7
void PspLoadState(int number)
{
	global_number = number;

	load_flag = 1;
	sceKernelSignalSema(sema_ctrl_id, 1);

	sceKernelWaitSema(second_sema_id, 1, NULL);

	MAKE_STUB(power_addr, HijackPowerModuleForLoadState);
	ClearCaches();

	set_alarm_flag = -1;

	scePowerRequestSuspend();
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

// sub_00000694
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
				PspSaveState(number);

				pad_data->Buttons &= ~(buttons | PSP_CTRL_RTRIGGER);
				state_flag = 1;
			}
		}
		else if(pad_data->Buttons & PSP_CTRL_LTRIGGER)
		{
			GetButtons(pad_data, &buttons, &number);

			if(number != -1)
			{
				PspLoadState(number);

				pad_data->Buttons &= ~(buttons | PSP_CTRL_LTRIGGER);
				state_flag = 1;
			}
		}
	}

	return;
}

// sub_000007EC
int sceCtrlPeekBufferPositivePatched(SceCtrlData *pad_data, int count)
{
	int res = sceCtrlPeekBufferPositive(pad_data, count);

	PspLsLibraryLauncher(pad_data);

	return res;
}

// sub_00000764
int sceCtrlReadBufferPositivePatched(SceCtrlData *pad_data, int count)
{
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

