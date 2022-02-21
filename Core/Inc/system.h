#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define enableSysTickIntr() SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk)
#define disableSysTickIntr() CLEAR_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk)    

void initSystem(void);
void initSysClock(void);
void activateWatchdog(void);
void refreshWatchdog(void);
void delayMs(int ms);
void reboot(void);
void enterStopMode(void);
void setPriorityIrq(int irq, uint32_t priority);
void enableIrq(int irq);
uint32_t getSysTickCount(void);
uint32_t getSysClockFreq(void);
uint16_t getRstReason(void);
void disableSwd(void);

#endif
