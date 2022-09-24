// PspStates Experiment v1 for PSP SLIM by Dark-Alex
// Reversed by plum

// header
#include "pspstates.h"

// event_handler
PspSysEventHandler events =
{
	sizeof(PspSysEventHandler),
	"ProcessSignals",
	0x00FFFF00,
	ProcessSignals,
}; // 0x2C1C

// path
char bin_path[] = "ms0:/seplugins/SAVESTATE/globalstate_X.bin";	// 0x2C18

// global
int unk_var;			// 0x2C90
int unregister_res;		// 0x2C70
u64 global_tick;		// 0x2C68

// extern
extern int global_number;		// 0x2C78
extern int is_running;			// 0x2C98
extern int state_flag;			// 0x2C7C
extern int save_flag;			// 0x2CA0
extern int load_flag;			// 0x2C84
extern int set_alarm_flag;		// 0x2C60
extern int driver_flag;			// 0x2C9C
extern u32 power_addr;			// 0x2C88
extern u32 restore_data[2];		// 0x2CA4 - 0x2CA8
extern SceUID sema_ctrl_id;		// 0x2C94
extern SceUID second_sema_id;	// 0x2C80

// sub_00000124
void ClearCaches(void)
{
	sceKernelDcacheWritebackAll();
	sceKernelIcacheClearAll();
}

// sub_00000BD0
u64 SetAlarmTick(u64 *tick)
{
	sceRtcSetAlarmTick(tick);
	return (u64)*tick;
}

// 0x00000BFC
u64 AddAlarmTick(u64 add_tick)
{
	sceRtcGetAlarmTick(&global_tick);
	sceRtcTickAddTicks(&global_tick, &global_tick, add_tick);
	sceRtcSetAlarmTick(&global_tick);

	return global_tick;
}

// 0x00000C54
int RtcUnregisterCallback(void)
{
	unregister_res = sceRtcUnregisterCallback(0);
	return unregister_res;
}

// 0x00000C84
int RtcRegisterCallback(SceUID cbid)
{
	return sceRtcRegisterCallback(0, cbid);
}

// sub_00000828
int ProcessSignals(int ev_id, char *ev_name, void *param, int *result)
{
	u64 cur_tick;
	PspIoDrv *lflash, *flashfat;

	if(ev_id == PSP_SYSEVENT_KERNEL_POWER_LOCK_PHASE1)
	{
		if(set_alarm_flag == -1)
		{
			sceRtcGetCurrentTick(&cur_tick);
			sceRtcTickAddSeconds(&cur_tick, &cur_tick, 2);
			SetAlarmTick(&cur_tick);

			set_alarm_flag = 1;
		}
	}
	else if(ev_id == PSP_SYSEVENT_RESUME_COMPLETED)
	{
		state_flag = 0;

		if(driver_flag != 0)
		{
			if(_lw(0x8A000008) == -1)
			{
				save_flag = 0;

				lflash = sctrlHENFindDriver("lflash");
				flashfat = sctrlHENFindDriver("flashfat");

				sceIoUnassign("flash0:");
				sceIoUnassign("flash1:");

				sceIoDelDrv("lflash");
				sceIoDelDrv("flashfat");

				sceIoAddDrv(lflash);
				sceIoAddDrv(flashfat);

				sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", IOASSIGN_RDONLY, NULL, 0);
				sceIoAssign("flash1:", "lflash0:0,1", "flashfat1:", IOASSIGN_RDWR, NULL, 0);
			}

			sceKernelSignalSema(sema_ctrl_id, 1);
			driver_flag = 0;
		}
	}

	return 0;
}

// sub_00000238
int ReadFile(const char *filename, void *data, SceSize size)
{
	SceUID fd;
	int read_size;

	fd = sceIoOpen(filename, PSP_O_RDONLY, 0);

	if(fd < 0)
		return fd;

	read_size = sceIoRead(fd, data, size);

	sceIoClose(fd);
	return read_size;
}

// sub_000002A8
int WriteFile(const char *filename, void *data, SceSize size)
{
	SceUID fd;
	int write_size;

	fd = sceIoOpen(filename, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

	if(fd < 0)
		return fd;

	write_size = sceIoWrite(fd, data, size);

	sceIoClose(fd);
	return write_size;
}

// sub_000009B0
int InOutThread(SceSize args, void *argp)
{
	while(!is_running)
	{
		sceKernelWaitSema(sema_ctrl_id, 1, NULL);

		bin_path[37] = (char)global_number;

		if(load_flag)
		{
			ReadFile(bin_path, (void *)0x8A000000, 0x1C00000);

			load_flag = 0;
			sceKernelSignalSema(second_sema_id, 1);
		}
		else
		{
			_sw(restore_data[0], power_addr + 0);
			_sw(restore_data[1], power_addr + 4);

			ClearCaches();

			if(save_flag)
			{
				if(_lw(0x8A000000) == 0xDADADADA && _lw(0x8A000004) == 0x33333333)
				{
					sceKernelChangeThreadPriority(sceKernelGetThreadId(), 4);
					sceKernelDelayThread(600000);

					WriteFile(bin_path, (void *)0x8A000000, _lw(0x8A000014) + _lw(0x8A000018));

					sceKernelChangeThreadPriority(sceKernelGetThreadId(), 16);
				}

				save_flag = 0;
			}

			if(is_running != 0)
				break;

			unk_var = 0;
		}
	}

	return sceKernelExitDeleteThread(0);
}

