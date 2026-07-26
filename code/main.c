#include "main.h"

uint32_t Start_Time = 0;
uint32_t End_Time = 0;
uint32_t Execution_Time = 0;
uint32_t Deadline = 1000;

int main(void)
{
	//Enable the GPIOA Clock
	RCC->AHB1ENR |= (1 << 0);

	//SETTING THE LED AS OUTPUT
	GPIOA->MODER &= ~(3 << (6 * 2));
	GPIOA->MODER |=  (1 << (6 * 2));

	//Enable the SysTick Timer

	//Load Reload Value
	SysTick->LOAD = 0x00FFFFFF;

	//Reset Counter
	SysTick->VAL = 0;

	//Configure Control Register
	//Processor Clock
	//No Interrupt
	//Enable Counter
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	while(1)
	{
		//Reset the Timer
		SysTick->VAL = 0;

		//Record the Start Time
		Start_Time = SysTick->VAL;

		//==============================
		//Task Starts Here
		//==============================

		GPIOA->ODR ^= (1 << 6);

		for(volatile uint32_t i = 0; i < 50000; i++);

		//==============================
		//Task Ends Here
		//==============================

		//Record the End Time
		End_Time = SysTick->VAL;

		//Calculate the Execution Time
		Execution_Time = Start_Time - End_Time;

		//Compare with Deadline
		if(Execution_Time <= Deadline)
		{
			//Task completed within Deadline
			GPIOA->ODR |= (1 << 6);
		}
		else
		{
			//Task exceeded Deadline
			GPIOA->ODR &= ~(1 << 6);
		}
	}

	return 0;
}
