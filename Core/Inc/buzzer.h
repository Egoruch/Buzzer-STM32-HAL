#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#endif /* INC_BUZZER_H_ */

/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Active buzzer for GPIO control
 * Passive buzzer need PWM */
#define USE_PASSIVE_BUZZER 0 /* 0 - Active buzzer; 1 - Passive buzzer (uses timer) */


/* External BEGIN */
#if(USE_PASSIVE_BUZZER)
extern TIM_HandleTypeDef htim11;
#endif
/* External END  */

/* Defines BEGIN */
#if(USE_PASSIVE_BUZZER)
#define TIM_BUZZER_HANDLE &htim11
#endif
/* Defines END */

/* HOW TO USE? BEGIN */
/*
 * 1) Set any GPIO pin as output and set default level low or high, depending on and write label BUZZER
 * 2) Insert into SysTick handler callback function (in file stm32xxxx_it.h)
 * 3) Include "buzzer.h" in main.c
 * 4) Thats all, now you can test it:
 * BUZZER_Go(TBUZ_100, TICK_4);
 */

	/* e x a m p l e */
//	void SysTick_Handler(void)
//{
//  /* USER CODE BEGIN SysTick_IRQn 0 */
//  HAL_SYSTICK_Callback();
//  /* USER CODE END SysTick_IRQn 0 */
//  HAL_IncTick();
//  /* USER CODE BEGIN SysTick_IRQn 1 */
//
//  /* USER CODE END SysTick_IRQn 1 */
//}


///* USER CODE BEGIN 4 */
//
///*** SYSTICK (T = 1ms) ***/
///**
//  * @brief  SYSTICK callback.
//  * @retval None
//  */
//void HAL_SYSTICK_Callback(void)
//{
//	BUZZER_Handler();
//}
//
///* USER CODE END 4 */

/* HOW TO USE? END */


/* USER CODE BEGIN PTD */
typedef enum BuzzerTime
{
	TBUZ_20 = 20,
	TBUZ_50 = 50,
	TBUZ_100 = 100,
	TBUZ_200 = 200,
	TBUZ_300 = 300,
	TBUZ_400 = 400,
	TBUZ_500 = 500,
	TBUZ_600 = 600,
	TBUZ_800 = 800,
	TBUZ_900 = 900,
	TBUZ_1000 = 1000,
}buztime_t;

typedef enum BuzzerTicks
{
	TICK_1 = 2-1,
	TICK_2 = 4-1,
	TICK_4 = 8-1,
	TICK_6 = 12-1,
	TICK_8 = 16-1,
	TICK_10 = 20-1,
	TICK_12 = 24-1,
}buztick_t;
/* USER CODE END PTD */


/* USER CODE BEGIN PFP */
void BUZZER_On(void);
void BUZZER_Off(void);
void BUZZER_Go(buztime_t period, buztick_t ticks);
void BUZZER_Handler(void);
/* USER CODE END PFP */
