
# Buzzer-STM32-HAL
![Config pin as input and set gpio label](/Images/buzzer_library.svg)
Simple library to generate pulses with predefined  time and period, that can be used for control piezoelectronic buzzer with oscillator circuit – active, or without – passive. It useful for debug purposes or notifications in your device.
# Connection circuit
![Config pin as input and set gpio label](/Images/buzzer_connection_circuit.svg)
# How to use?
 1. Add *buzzer.c* to **Src** and *buzzer.h* to **Inc**
![add .c and h. file](/Images/lib_add.png)
 2. Configure required pin as **GPIO_Output** (left click) and set **label** (right click): ***BUZZER***. 
![Config pin as input and set gpio label](/Images/pin_buzzer.png)
 3. Include *buzzer.h* in **main.c**:
```
 /* USER CODE BEGIN Includes */
#include "buzzer.h"
/* USER CODE END Includes */
```
 4. Open *stm32f4xx_it.c* and modify **SysTick_Handler()**:
```
/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
  HAL_SYSTICK_Callback();
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
  /* USER CODE END SysTick_IRQn 1 */
}
  ```
   6. Write callback function to execute **BUZZER_Handler()** every *1 ms*:
```
/* USER CODE BEGIN 4 */
/*** SYSTICK (T = 1ms) ***/
/**
  * @brief  SYSTICK callback.
  * @retval None
  */
void HAL_SYSTICK_Callback(void)
{
	BUZZER_Handler();
}
/* USER CODE END 4 */
```
   7.  That's all, now you can test buzzing by **Buzzer_Go**!
```
  /* USER CODE BEGIN 2 */
  Buzzer_Go(TBUZ_100, TICK_2);
  HAL_Delay(2000);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  Buzzer_Go(TBUZ_50, TICK_4);
	  HAL_Delay(2000);
    /* USER CODE END WHILE */
```
# Working demonstrating
here how it works...

# TODO
 - [ ]  Polarity choose
 - [ ] Initialize function with pin choose (based on Cube's label)