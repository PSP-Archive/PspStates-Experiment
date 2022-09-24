#ifndef __PSPSTATES_V1_H__
#define __PSPSTATES_V1_H__

// header
#include <pspkernel.h>
#include <systemctrl.h>
#include <pspsysevent.h>
#include <pspsysmem_kernel.h>
#include <pspiofilemgr_kernel.h>
#include <psppower.h>
#include <pspctrl.h>
#include <pspinit.h>
#include <psprtc.h>
#include <string.h>

// define
#define MAKE_STUB(a, f) _sw(0x08000000 | (((u32)(f) & 0x0FFFFFFC) >> 2), a); _sw(0, a + 4);

// event_id
#define PSP_SYSEVENT_KERNEL_POWER_LOCK_PHASE1	0x401
#define PSP_SYSEVENT_RESUME_COMPLETED			0x400000

// stub.S(sceRtc)
int sceRtcRegisterCallback(int slot, SceUID cbid);
int sceRtcUnregisterCallback(int slot);

// stub.S(sceRtc_driver)
int sceRtcGetAlarmTick(u64 *tick);
int sceRtcSetAlarmTick(u64 *tick);

// extras.S
void HijackPowerModuleForSaveState(void);
int sceCtrlReadBufferPositiveHijackFunc(SceCtrlData *pad_data, int count);
int CtrlFuncLauncher(void);

// main.c
int OnModuleStart(SceModule2 *module);
int module_start(SceSize args, void *argp);
int module_stop(SceSize args, void *argp);

// lslibrary.c
void SaveProcessing(void);
void LoadProcessing(void);
void HijackPowerModuleForLoadState(void);
void PspSaveState(int number);
void PspLoadState(int number);
void GetButtons(SceCtrlData *pad_data, u32 *get_buttons, int *get_number);
void PspLsLibraryLauncher(SceCtrlData *pad_data);
int sceCtrlPeekBufferPositivePatched(SceCtrlData *pad_data, int count);
int sceCtrlReadBufferPositivePatched(SceCtrlData *pad_data, int count);

// utils.c
void ClearCaches(void);
u64 SetAlarmTick(u64 *tick);
u64 AddAlarmTick(u64 add_tick);
int RtcUnregisterCallback(void);
int RtcRegisterCallback(SceUID cbid);
int ProcessSignals(int ev_id, char *ev_name, void *param, int *result);
int ReadFile(const char *filename, void *data, SceSize size);
int WriteFile(const char *filename, void *data, SceSize size);
int InOutThread(SceSize args, void *argp);

#endif

