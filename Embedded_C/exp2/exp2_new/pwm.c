// This program sets up SCTimer 0 to produce 3 PWM signals.
// The signals are center aligned.
// The main() function allows users to update PWM signals.
// Modified from NXP Xpresso_SDK, driver_examples simple_pwm
//By Ensar Kidil and Uras Pehlivan


#include "fsl_sctimer.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "board.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
void delay(uint64_t counts);
void delay(uint64_t counts)
{
  uint64_t wait;
  for (wait=counts; wait>0; --wait){}
}

int ButtonRead();

int main(){
	int state;
	state = 0;
	int RedPwm = 15U;
	int GreenPwm = 15U;
	int YellowPwm = 15U;
	sctimer_config_t sctimerConfig;		// sctimerConfig structure contains the configuration of SCTimer.
	sctimer_pwm_signal_param_t pwmParam0, pwmParam1, pwmParam2;	// This struct stores several parameters for PWM signals.
	
	uint32_t event0, event1, event2;	// These are events for PWM outputs.
	uint32_t sctimerClock;
	
	// Initialize board
	BOARD_InitBootPins();        // Initialize board pins.
	BOARD_InitBootClocks();      // Initialize clock signals.
	
	// Configure clocks
	CLOCK_EnableClock(kCLOCK_Sct); 				// Enable clock of SCTimer peripheral
	sctimerClock = CLOCK_GetFreq(kCLOCK_Irc);	// The SCTimer gets 12 MHz frequency
	SCTIMER_GetDefaultConfig(&sctimerConfig);	// Set it to a default value. See the library function.
	SCTIMER_Init(SCT0, &sctimerConfig); 		// Initialize SCTimer module:
	
	
	// Configure PWM signals with frequency 1kHz
	
	pwmParam0.output = kSCTIMER_Out_0;	// This is the Red LED.
	pwmParam0.level = kSCTIMER_HighTrue;	// High duty ratio will produce a lower average signal.
	pwmParam0.dutyCyclePercent = 15;	// Here 0 is dim, 100 is bright.
	// Configure the PWM for Red LED.
	SCTIMER_SetupPwm(SCT0,          	// Use SCT0 timer.
		&pwmParam0,                 	// Use the pwmParam struct.
		kSCTIMER_CenterAlignedPwm, 		// Generate center aligned PWM
		1000U,                    		// Freq is 1kHz
		sctimerClock,              		// Use the clock from sctimer
		&event0);
	
	pwmParam1.output = kSCTIMER_Out_1;	// This is the Green LED.
	pwmParam1.level = kSCTIMER_HighTrue;	// High duty ratio will produce a lower average signal.
	pwmParam1.dutyCyclePercent = 0;	// Here 0 is dim, 100 is bright.
	// Configure the PWM for Green LED.
	SCTIMER_SetupPwm(SCT0,        		// Use SCT0 timer.
		&pwmParam1,                 	// Use the pwmParam struct.
		kSCTIMER_CenterAlignedPwm, 		// Generate center aligned PWM
		1000U,                    		// Freq is 1kHz
		sctimerClock,              		// Use the clock from sctimer
		&event1);
	
	pwmParam2.output = kSCTIMER_Out_2;	// This is the Blue LED.
	pwmParam2.level = kSCTIMER_HighTrue;	// High duty ratio will produce a lower average signal.
	pwmParam2.dutyCyclePercent = 0;	// Here 0 is dim, 100 is bright.
	// Configure the PWM for Blue LED.
	SCTIMER_SetupPwm(SCT0,           	// Use SCT0 timer.
		&pwmParam2,						// Use the pwmParam struct.
		kSCTIMER_CenterAlignedPwm, 		// Generate center aligned PWM
		1000U,                    		// Freq is 1kHz
		sctimerClock,              		// Use the clock from sctimer
		&event2);
	

	SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);	// Start the 32-bit unified timer

	int ButtonCheck;
	//int flag;
	// Loop
	while(1){
		delay(10000000);
		ButtonCheck = 0;
		
		while(ButtonCheck == 0){
			ButtonCheck = ButtonRead();
		}
		
		if(ButtonCheck == 3){
			
			if(state == 0){
				state = 1;
			}
			else if(state == 1){
				state = 2;
			}
			else{
				state = 0;
			}
		}
		
		
		switch(state)
		{
			case 0:
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_0, RedPwm, event0);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, 0, event1);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, 0, event2);
				if(ButtonCheck == 1)
				{
					//while(anan == 1){}
						if(RedPwm < 60U)
						{
							RedPwm += 5U;
							SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_0, RedPwm, event0);
							//break;
						}
				}
				else if(ButtonCheck == 2)
				{
					//while(anan == 2){}
						if(RedPwm > 5U)
						{
							RedPwm -= 5U;
							SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_0, RedPwm, event0);
							//break;
						}
				}
				/*else if(GPIO_PinRead(GPIO,0,18) == 0)
				{
						while(GPIO_PinRead(GPIO,0,18) == 0){}
						state = 1;
				}*/
				break;
				case 1:
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_0, 0, event0);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, GreenPwm, event1);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, 0, event2);
				if(ButtonCheck == 1)
				{
					//while(anan == 2){}
						if(GreenPwm < 60U)
						{
							GreenPwm += 5U;
							SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, GreenPwm, event1);
							//break;
						}
				}
				else if(ButtonCheck == 2)
				{
					//while(GPIO_PinRead(GPIO,0,20)){}
						if(GreenPwm > 5U)
						{
							GreenPwm -= 5U;
							SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, GreenPwm, event1);
							//break;
						}
				}
				/*else if(GPIO_PinRead(GPIO,0,18) == 0)
				{
						while(GPIO_PinRead(GPIO,0,18) == 0){}
						state = 2;
				}*/
				break;
				case 2:
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_0, 0, event0);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, 0, event1);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, YellowPwm, event2);
				if(ButtonCheck == 1)
				{
					//while(GPIO_PinRead(GPIO,0,19)){}
						if(YellowPwm < 60U)
						{
							YellowPwm += 5U;
							SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, YellowPwm, event2);
							//break;
						}
				}
				else if(ButtonCheck == 2)
				{
					//while(GPIO_PinRead(GPIO,0,20)){}
						if(YellowPwm > 5U)
						{
							YellowPwm -= 5U;
							SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, YellowPwm, event2);
							//break;
						}
				}
				break;
				/*else if(GPIO_PinRead(GPIO,0,18) == 0)
				{
						while(GPIO_PinRead(GPIO,0,18) == 0){}
						state = 0;
				}*/
		}
		
		
		/*// If button 1 is pressed once
		if(GPIO_PinRead(GPIO, 0, 19)){
			while(GPIO_PinRead(GPIO, 0, 19)){}
			// Increase PWM duty cycle ratios by 5% up to 100%
			if(pwmParam0.dutyCyclePercent < 100U) pwmParam0.dutyCyclePercent += 5U;
			if(pwmParam1.dutyCyclePercent < 100U) pwmParam1.dutyCyclePercent += 5U;
			if(pwmParam2.dutyCyclePercent < 100U) pwmParam2.dutyCyclePercent += 5U;
			// Update PWM outputs
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_0, pwmParam0.dutyCyclePercent, event0);
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, pwmParam1.dutyCyclePercent, event1);
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, pwmParam2.dutyCyclePercent, event2);
		}
		// If button 2 is pressed once
		else if(GPIO_PinRead(GPIO, 0, 20)){
			while(GPIO_PinRead(GPIO, 0, 20)){}
			// Decrease PWM duty cycle ratios by 5% up to 0%
			if(pwmParam0.dutyCyclePercent > 0U) pwmParam0.dutyCyclePercent -= 5U;
			if(pwmParam1.dutyCyclePercent > 0U) pwmParam1.dutyCyclePercent -= 5U;
			if(pwmParam2.dutyCyclePercent > 0U) pwmParam2.dutyCyclePercent -= 5U;
			// Update PWM outputs
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_0, pwmParam0.dutyCyclePercent, event0);
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, pwmParam1.dutyCyclePercent, event1);
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, pwmParam2.dutyCyclePercent, event2);
		}
		// Else do nothing
		else{}*/
	}
}

int ButtonRead(){
		int ButtonValue = 0;
		//int flag = 0;
		if(GPIO_PinRead(GPIO,0,19)){
			/*while(GPIO_PinRead(GPIO,0,19)){}
			delay(100000);
			if(GPIO_PinRead(GPIO,0,19)){
				flag = 1;
			}*/
			while(GPIO_PinRead(GPIO,0,19)){}	
			ButtonValue = 1;
		}
		else if(GPIO_PinRead(GPIO,0,20)){
			/*while(GPIO_PinRead(GPIO,0,20)){}
			delay(100000);
			if(GPIO_PinRead(GPIO,0,20)){
				flag = 2;
			}*/
			while(GPIO_PinRead(GPIO,0,20)){}	
			ButtonValue = 2;
		}
		else if(GPIO_PinRead(GPIO,0,18)){
			/*while(GPIO_PinRead(GPIO,0,18)){}	
			delay(100000);
			if(GPIO_PinRead(GPIO,0,18)){
				flag = 3;
			}*/
			while(GPIO_PinRead(GPIO,0,18)){}	
			ButtonValue = 3;
		}
		/*if (flag == 1){
			ButtonValue = 1;
			for(int i = 0; i<100; i++){
				delay(5000);
				if((GPIO_PinRead(GPIO,0,19)) || flag == 0){
					delay(100000);
					if((GPIO_PinRead(GPIO,0,19)) || flag == 0){
						flag = 0;
						break;
					}
				}
			}
		}
		else if(flag == 2){
			ButtonValue = 2;
			for(int i = 0; i<100; i++){
				delay(5000);
				if((GPIO_PinRead(GPIO,0,20)) || flag == 0){
					delay(100000);
					if((GPIO_PinRead(GPIO,0,20)) || flag == 0){
						flag = 0;
						break;
					}
				}
			}
		}
		
		else if(flag == 3){
			ButtonValue = 3;
			for(int i = 0; i<100; i++){
				delay(5000);
				if((GPIO_PinRead(GPIO,0,18)) || flag == 0){
					delay(100000);
					if((GPIO_PinRead(GPIO,0,18)) || flag == 0){
						flag = 0;
						break;
					}
				}
			}
		}*/
		
		return ButtonValue;
	}
