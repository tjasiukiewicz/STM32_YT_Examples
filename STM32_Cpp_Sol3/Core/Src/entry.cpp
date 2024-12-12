/*
 * entry.cpp
 */
#include <cstdio>
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "entry.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_LPUART1_UART_Init(void);

#ifdef __cplusplus
} // End extern "C"
#endif

template<uint8_t MaxValue>
void showCounter() {
	static uint8_t counter = 0U;
	char buffer[64];

	size_t size = sprintf(buffer,
			"\e[H\e[2J"			// clear screen
			"\e[1;31m"			// red foreground
			"Counter: "
			"\e[1;32;44m"		// blue bckg. green fg.
			" %03d "
			"\e[0m"				// reset attributes
			"\r\n", counter);

	++counter;

	if (counter > MaxValue) {
		counter = 0U;
	}

#ifdef LL_LPUART_ISR_TXE_TXFNF
	const uint8_t * ptr_buff = (uint8_t *)buffer;
	while(size--) {
		while(! (LPUART1->ISR & LL_LPUART_ISR_TXE_TXFNF)) {}
		LL_LPUART_TransmitData8(LPUART1, *(ptr_buff++));
	}
#else
	HAL_UART_Transmit(&hlpuart1, (uint8_t *)buffer, size, HAL_MAX_DELAY);
#endif

}

template<uint8_t Count>
void blinkLed() {
	static uint8_t counter = 0U;
	if (counter > Count) {
#ifndef LL_GPIO_PIN_5
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
#else
	LL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
#endif
		counter = 0U;
	}
	++counter;
}


#ifdef __cplusplus
extern "C" {
#endif

int main(void) {

#ifdef USE_HAL_DRIVER
	HAL_Init();
#else
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	LL_PWR_DisableUCPDDeadBattery();
#endif

	SystemClock_Config();

	MX_GPIO_Init();
	MX_LPUART1_UART_Init();


	auto displayCounter = showCounter<100>;
	auto displayLed = blinkLed<5>;

	while (1) {
		displayCounter();
		displayLed();

#ifdef USE_HAL_DRIVER
		HAL_Delay(200);
#else
		LL_mDelay(200);
#endif

	}
}

#ifdef __cplusplus
} // End extern "C"
#endif