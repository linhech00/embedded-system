#include "stm32f4xx_hal.h"
#include "system.h"

static volatile uint32_t sysTickCount = 0;
static uint16_t resetReason = 0;

void initSystem(void) {
    resetReason = RCC->CSR >> 23;
    RCC->CSR |= 0x01000000; //clear flag
    
#ifndef USE_HAL_DRIVER
    while (SysTick_Config(SystemCoreClock / (1000U)) > 0);
    NVIC_SetPriority(SysTick_IRQn, 0);
    
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    NVIC_SetPriority(PendSV_IRQn, 3);
    
    initSysClock();
#endif
}

void initSysClock(void) {
#ifndef USE_HAL_DRIVER
    //    /* HSI clock */
    //    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HSI) || \
    //        ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSI))) { 
    //    }
    //    else {
    //        __HAL_RCC_HSI_ENABLE();
    //        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET);
    //    }
    //    __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_HSICALIBRATION_DEFAULT);
    //
    //    /* LSI clock */
    //    __HAL_RCC_LSI_ENABLE();
    //    while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET);
    //    
    //    /* HSI14 clock */
    //    __HAL_RCC_HSI14ADC_DISABLE();
    //    __HAL_RCC_HSI14_ENABLE();
    //    while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSI14RDY) == RESET);
    //    __HAL_RCC_HSI14_CALIBRATIONVALUE_ADJUST(16);
    //    
    //    /* PLL clock */
    //    __HAL_RCC_PLL_DISABLE();
    //    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY)  != RESET);
    //#ifdef STM32F070xB
    //    __HAL_RCC_PLL_CONFIG(RCC_PLLSOURCE_HSI, RCC_PREDIV_DIV1, RCC_PLL_MUL6);
    //#else
    //    __HAL_RCC_PLL_CONFIG(RCC_PLLSOURCE_HSI, RCC_PREDIV_DIV1, RCC_PLL_MUL12);
    //#endif
    //    __HAL_RCC_PLL_ENABLE();
    //    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY)  == RESET);
    //    
    //    /* Initializes the CPU, AHB and APB buses clocks */
    //    if (FLASH_LATENCY_1 > __HAL_FLASH_GET_LATENCY())
    //        __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);
    //
    //    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, RCC_HCLK_DIV16);
    //    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_HCLK_DIV1);
    //    
    //    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET);
    //    __HAL_RCC_SYSCLK_CONFIG(RCC_SYSCLKSOURCE_PLLCLK);
    //    while (__HAL_RCC_GET_SYSCLK_SOURCE() != (RCC_SYSCLKSOURCE_PLLCLK << RCC_CFGR_SWS_Pos));
    //
    //    if(FLASH_LATENCY_1 < __HAL_FLASH_GET_LATENCY()) {
    //        __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);
    //        while (__HAL_FLASH_GET_LATENCY() != FLASH_LATENCY_1);
    //    }
    //
    //    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, RCC_HCLK_DIV1);
    //
    //    /* Update system core clock and timebase */
    //    SystemCoreClock = getSysClockFreq();
    //    while (SysTick_Config(SystemCoreClock / (1000U)) > 0);
    //    NVIC_SetPriority(SysTick_IRQn, 0);
#endif
}

void activateWatchdog(void) {
    //	WRITE_REG(IWDG->KR, IWDG_KEY_ENABLE);
    //	WRITE_REG(IWDG->KR, IWDG_KEY_WRITE_ACCESS_ENABLE);
    //	IWDG->PR = IWDG_PRESCALER_256;
    //	IWDG->RLR = 3200;
    //	while (IWDG->SR != 0x00u);
    //	if (IWDG->WINR != 4095)
    //		IWDG->WINR = 4095;
    //	else
    //		WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD);
}

void refreshWatchdog(void) {
    //	WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD);
}

void delayMs(int ms) {
    //	uint32_t tick = sysTickCount;
    //	while ((uint32_t)(sysTickCount - tick) < ms);
    uint32_t tick = HAL_GetTick();
    while ((uint32_t)(HAL_GetTick() - tick) < ms);
}

void reboot(void) {
    NVIC_SystemReset();
}

void enterStopMode(void) {
    //    PWR->CR &= (uint32_t)~(PWR_CR_PDDS | PWR_CR_LPDS);
    //    PWR->CR |= PWR_LOWPOWERREGULATOR_ON;
    //    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    //    __WFI();
    //    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

void setPriorityIrq(int irq, uint32_t priority) {
    //    NVIC_SetPriority((IRQn_Type)IRQn, priority);
}

void enableIrq(int irq) {
    //    NVIC_EnableIRQ((IRQn_Type)irq);
}

uint32_t getSysTickCount(void) {
    //	return sysTickCount;
    return HAL_GetTick();
}

uint16_t getRstReason(void) {
    return resetReason;
}

void disableSwd(void) {
}

//static uint32_t getSysClockFreq(void) {
//    uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
//    uint8_t aPLLMULFactorTable[16] = { 2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U, 10U, 11U, 12U, 13U, 14U, 15U, 16U, 16U};
//    uint32_t pllmul = aPLLMULFactorTable[(uint32_t)(RCC->CFGR & RCC_CFGR_PLLMUL) >> RCC_CFGR_PLLMUL_BITNUMBER];
//#ifdef STM32F070xB
//    uint8_t aPredivFactorTable[16] = { 1U, 2U,  3U,  4U,  5U,  6U,  7U,  8U, 9U, 10U, 11U, 12U, 13U, 14U, 15U, 16U};  
//    uint32_t prediv = aPredivFactorTable[(uint32_t)(RCC->CFGR2 & RCC_CFGR2_PREDIV) >> RCC_CFGR2_PREDIV_BITNUMBER];
//    uint32_t freq = ((uint64_t)HSI_VALUE / (uint64_t)(prediv)) * ((uint64_t)pllmul);
//#else
//    uint32_t freq = ((uint64_t)(HSI_VALUE >> 1U) * ((uint64_t) pllmul));
//#endif
//    return (freq >> AHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE)>> RCC_CFGR_HPRE_BITNUMBER]);
//}
//
//void NMI_Handler(void) {
//}
//
//void HardFault_Handler(void) {
//    NVIC_SystemReset();
//}
//
//void SVC_Handler(void) {
//}
//
//void PendSV_Handler(void) {
//}
//
//void SysTick_Handler(void) {
//	sysTickCount++;
//}
