/* USER CODE BEGIN Includes */
#include <buzzer.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PV */

typedef struct BuzzerDebug
{
	uint16_t Tout;
	uint16_t ToutSave;
	uint8_t Tick;
	uint8_t Help;
}buzdebug_t;

buzdebug_t Buz = {0, 0, 0, 0};

/* USER CODE END PV */

/**
  * @brief Turn on buzzer by PWM signal
  * @note No need init
  * @param 0%-100%
  * @retval No
  */
void Buzz_PWM_Percent(uint8_t percent)
{
	/* Check range */
	if(percent > 100){
		percent = 100;
	}
#if(USE_PASSIVE_BUZZER)

	uint16_t tim_arr = __HAL_TIM_GET_AUTORELOAD(TIM_BUZZER_HANDLE);

	uint16_t tim_ccr_new = (percent*tim_arr*0.01) + 1;

	__HAL_TIM_SET_COMPARE(TIM_BUZZER_HANDLE, TIM_CHANNEL_1, tim_ccr_new);
#endif

}

/**
  * @brief Turn on buzzer
  * @note No need init
  * @param No
  * @retval No
  */
void BUZZER_On(void)
{

#if(USE_PASSIVE_BUZZER)

	Buzz_PWM_Percent(50);

#else

#if(USE_ACTIVE_HIGH)
	/* For buzzer with generator */
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
#else
	/* For buzzer with generator */
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
#endif
#endif

}

/**
  * @brief Turn off buzzer
  * @note No need init
  * @param No
  * @retval No
  */
void BUZZER_Off(void)
{
#if(USE_PASSIVE_BUZZER)

	Buzz_PWM_Percent(0);

#else

#if(USE_ACTIVE_HIGH)
	/* For buzzer with generator */
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
#else
	/* For buzzer with generator */
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
#endif
#endif
}

/**
  * @brief Toggle buzzer state
  * @note No need init
  * @param No
  * @retval No
  */
void BuzzerToggle(void)
{

#if(USE_PASSIVE_BUZZER)

	static uint8_t toggle = 0;

	if(toggle)
	{
		Buzz_PWM_Percent(50);
	}else
	{
		Buzz_PWM_Percent(0);
	}

	toggle = ~toggle;
#else

	/* For buzzer with generator */
	HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin);

	#endif





}


/**
  * @brief Disable buzzer
  * @note No need init
  * @param time between ticks in ms, ticks quantity
  * @retval No
  */
void BUZZER_Go(buztime_t period, buztick_t ticks)
{
	BUZZER_On();
	Buz.Help = 0;
	Buz.ToutSave = period;
	Buz.Tout = period;
	Buz.Tick = ticks;
}


/**
  * @brief Disable buzzer
  * @note Insert func.in the 1kHz interrupt handler (e.g. SysTick)
  * @param No
  * @retval No
  */
void BUZZER_Handler(void)
{
	if(Buz.Tick)
	{
		if(--Buz.Tout <= 0)
		{
			Buz.Tick--;

			if(Buz.Help)
			{
				BUZZER_On();
			}
			else
			{
				BUZZER_Off();
			}

			Buz.Tout = Buz.ToutSave;

			/* Toggle */
			Buz.Help = ~Buz.Help;
		}
	}
}
