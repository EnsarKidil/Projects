//By Ensar Kidil and Uras Pehlivan
#include <stdio.h>
#include "pin_mux.h"
#include "fsl_mrt.h"
#include "fsl_power.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "fsl_syscon.h"
#include "fsl_swm.h"
#include "fsl_swm_connections.h"
#include "fsl_sctimer.h"
#include "fsl_reset.h"
#include "fsl_pint.h"
#include "fsl_common.h"
#include "fsl_common_arm.h"
#include <stdint.h> // Declarations of uint32_t etc.

#define GPI0_PORT 0
#define GPIO_INPUT1_PIN 18
#define GPIO_INPUT2_PIN 19
#define GPIO_INPUT3_PIN 20

#define CORE_CLOCK   30000000U
#define INT_FREQ 100U 

static inline uint32_t SysTickConfig(uint32_t ticks);
void SysTick_Handler(void);  
void delay_ms(uint32_t); 
volatile uint32_t delaytime;
void clock_init(void);
uint32_t event1,event2,event3;
volatile uint8_t PWM = 5;
//ISR IMPLEMENTATION
void MRT0_IRQHandler(void){
	
	static volatile uint8_t i = 0;
	static volatile uint8_t counter = 0U;
	
	
	counter++;
	if (counter == 50)
	{
		switch(i)
		{
			case 0:
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, PWM, event2);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, 0, event1);
				i++;
				break;
				
				
			case 1:
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_3, PWM, event3);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, 0, event2);
				i++;
				break;
				
				
			case 2:
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, PWM, event1);
				SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_3, 0, event3);
				i=0;
				break;
				
					
		}
		
	counter = 0;			
	}
	MRT_ClearStatusFlags(MRT0, kMRT_Channel_0, kMRT_TimerInterruptFlag);
}



void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status){
	static volatile uint8_t j = 0U;
	
	for(volatile uint8_t counter = 0U; counter < 100U; counter++);	// Wait 100ms to handle button debouncing
	
	
	switch(j)
	{
		case 0:
			PWM = 10;
			j++;		
			break;
		
		case 1:
			PWM = 25;
			j++;		
			break;

		case 2:
			PWM = 99;
			j++;		
			break;
			
		case 3:
			PWM = 0;
			j = 0;		
			break;	
	}
	
}





int main(void) {
	
clock_init();
//CLOCK CONFIG
CLOCK_EnableClock(kCLOCK_Iocon);
CLOCK_EnableClock(kCLOCK_Mrt);


//NO GPIO CONFIG REQUIRED

//PWM CONFIG
InitPins(); //initilize led pins

sctimer_config_t sctimerConfig;

sctimer_pwm_signal_param_t pwmParam1, pwmParam2, pwmParam3;
  
uint32_t sctimerClock;
    
CLOCK_EnableClock(kCLOCK_Sct); 
  
  
  
sctimerClock = CORE_CLOCK;
  
SCTIMER_GetDefaultConfig(&sctimerConfig);
  
SCTIMER_Init(SCT0, &sctimerConfig);  
  
 
pwmParam1.output           = kSCTIMER_Out_1; 
pwmParam1.level            = kSCTIMER_HighTrue;
pwmParam1.dutyCyclePercent = 0;

  
SCTIMER_SetupPwm(SCT0,                     
		&pwmParam1,                 
		kSCTIMER_CenterAlignedPwm, 
		10000U,                    
		sctimerClock,              
		&event1);
  
  	
pwmParam2.output           = kSCTIMER_Out_2; 
pwmParam2.level            = kSCTIMER_HighTrue;
pwmParam2.dutyCyclePercent = 0;

  
SCTIMER_SetupPwm(SCT0,                     
		&pwmParam2,                 
		kSCTIMER_CenterAlignedPwm, 
		10000U,                    
		sctimerClock,              
		&event2);
	
		   
	
pwmParam3.output           = kSCTIMER_Out_3; 
pwmParam3.level            = kSCTIMER_HighTrue;
pwmParam3.dutyCyclePercent = 0;

  
SCTIMER_SetupPwm(SCT0,                      
		&pwmParam3,                 
		kSCTIMER_CenterAlignedPwm, 
		10000U,                    
		sctimerClock,              
		&event3);

  
  
SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);



SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_3, 0, event3);
SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, 0, event2);
SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, PWM, event1); 

//PIN INTERRUPT CONFIG
SYSCON_AttachSignal(SYSCON, kPINT_PinInt0, kSYSCON_GpioPort0Pin18ToPintsel);

PINT_Init(PINT);

PINT_PinInterruptConfig(PINT,	// Pin INT base register address
	kPINT_PinInt0,       			// Use pin interrupt channel 0
	kPINT_PinIntEnableRiseEdge ,	// Use falling edges
	pint_intr_callback); 			// Name of the callback function
	

	
PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0);

	
//MRT CONFIG

mrt_config_t mrt_config;

MRT_GetDefaultConfig(&mrt_config);

MRT_Init(MRT0,&mrt_config);

MRT_SetupChannelMode(MRT0, kMRT_Channel_0, kMRT_RepeatMode);
	
MRT_EnableInterrupts(MRT0, kMRT_Channel_0, kMRT_TimerInterruptEnable);	
	
EnableIRQ(MRT0_IRQn);

uint32_t mrt_clock = USEC_TO_COUNT(10000U, CORE_CLOCK*2);

MRT_StartTimer(MRT0, kMRT_Channel_0, mrt_clock);


	
    
while (1);	
  
}








void clock_init(void) {    // Set up the clock source

  // Set up IRC
  POWER_DisablePD(kPDRUNCFG_PD_IRC_OUT);        // Turn ON IRC OUT
  POWER_DisablePD(kPDRUNCFG_PD_IRC);            // Turn ON IRC
  //POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       // In Alakart SYSOSC is not used.
  CLOCK_Select(kSYSPLL_From_Irc);               // Connect IRC to PLL input.
  clock_sys_pll_t config;
  config.src = kCLOCK_SysPllSrcIrc;             // Select PLL source as IRC. 
  config.targetFreq = CORE_CLOCK*2;             // set pll target freq
  CLOCK_InitSystemPll(&config);                 // set parameters
  //CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcIrc);  // Select IRC as main clock source.
  CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcSysPll); // Select PLL as main clock source.
  CLOCK_Select(kCLKOUT_From_Irc);               // select IRC for CLKOUT
  CLOCK_SetCoreSysClkDiv(1U);
  //CLOCK_UpdateClkOUTsrc();
  // Set SystemCoreClock variable.
  //    SystemCoreClock = CORE_CLOCK;

  // Check processor registers and calculate the
  // Actual clock speed. This is stored in the
  // global variable SystemCoreClock
  SystemCoreClockUpdate ();

}



// Delay timing is provided by a busy wait:

void delay_ms(uint32_t ms) {//delay (ms)

  delaytime=ms;        // Set the delay time to the number of millisecs of wait
  while(delaytime!=0){}// Wait here until the delay time expires.

}

void SysTick_Handler(void) { 
  if (delaytime!=0){ // If delaytime has been set somewhere in the program,
    --delaytime;     //  decrement it every time SysTick event occurs (1ms).
  }
}
     
static inline uint32_t SysTickConfig(uint32_t ticks) {
  if (ticks > 0xFFFFFFUL) // Timer is only 24 bits wide.
    return (1); //Reload value impossible
  
  *((volatile unsigned int *)(0xe000e000 + 0x14)) = ((ticks & 0xFFFFFFUL) - 1);  //Set reload register 

  *((volatile unsigned int *)(0xe000e000 + 0x18)) = 0;   //Load the initial count value. 

 *((volatile unsigned int *)(0xe000e000 + 0x10)) = 0x07;  // Counter ENABLE, INT ENABLE, CLK source=system clock.

  return (0);
}     

