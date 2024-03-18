//By Ensar Kidil and Uras Pehlivan

#include "pin_mux.h"
#include "LPC824.h"
#include "fsl_power.h"
#include "fsl_swm.h"
#include "fsl_mrt.h"
#include "fsl_swm_connections.h"
#include "fsl_sctimer.h"
#include "fsl_gpio.h"
#include <stdint.h> // Declarations of uint32_t etc.
#include "fsl_device_registers.h" // Declarations of LPC824 register names.	
#include <stdint.h> // Declarations of uint32_t etc.

#define GPI0_PORT 0
#define GPIO_INPUT1_PIN 6
#define GPIO_INPUT2_PIN 7
#define GPIO_INPUT3_PIN 8

#define CORE_CLOCK   30000000U
#define INT_FREQ 100U 


void clock_init(void);
uint32_t event1,event2,event3;
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
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, 80, event2);
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, 5, event1);
			i++;
			break;
			
			
		case 1:
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_3, 80, event3);
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2, 5, event2);
			i++;
			break;
			
			
		case 2:
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, 80, event1);
			SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_3, 5, event3);
			i=0;
			break;
			
				
	}
	
counter = 0;			
}
MRT_ClearStatusFlags(MRT0, kMRT_Channel_0, kMRT_TimerInterruptFlag);
}





int main(void) {
	
clock_init();
//CLOCK CONFIG

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
SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, 80, event1); 
//MRT CONFIG

mrt_config_t mrt_config;

MRT_GetDefaultConfig(&mrt_config);

MRT_Init(MRT0,&mrt_config);

MRT_SetupChannelMode(MRT0, kMRT_Channel_0, kMRT_RepeatMode);
	
MRT_EnableInterrupts(MRT0, kMRT_Channel_0, kMRT_TimerInterruptEnable);	
	
EnableIRQ(MRT0_IRQn);

uint32_t mrt_clock = USEC_TO_COUNT(10000U*2, CORE_CLOCK);

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




