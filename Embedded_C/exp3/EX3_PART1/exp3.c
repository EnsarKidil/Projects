//By Ensar Kidil and Uras Pehlivan


#include "LPC824.h"
#include "fsl_power.h"
#include "fsl_mrt.h"
#include "fsl_gpio.h"
#include <stdint.h> // Declarations of uint32_t etc.
#include "fsl_device_registers.h" // Declarations of LPC824 register names.	
#include <stdint.h> // Declarations of uint32_t etc.

#define CORE_CLOCK   30000000U
#define INT_FREQ 100U 

void clock_init(void);

//ISR IMPLEMENTATION
void MRT0_IRQHandler(void){
	
static volatile uint8_t i = 0;
static volatile uint8_t counter = 0U;

counter++;
if (counter == 50)
{
	
	if(i==0){
                          
 		GPIO_PinWrite (GPIO, 0, 15, 0);
		GPIO_PinWrite (GPIO, 0, 13, 1);                               
        i++;                    
            

                          
    }
    else if(i==1){
         
 		GPIO_PinWrite (GPIO, 0, 13, 0);
		GPIO_PinWrite (GPIO, 0, 14, 1);    
        i++;
                              
                           
              
    }
    else if(i==2){                    
    
  		GPIO_PinWrite (GPIO, 0, 14, 0);
		GPIO_PinWrite (GPIO, 0, 15, 1); 
		i = 0;  
         
          
    
	}	
counter = 0;			
}	
MRT_ClearStatusFlags(MRT0, kMRT_Channel_0, kMRT_TimerInterruptFlag);
}





int main(void) {
	
clock_init();
//CLOCK CONFIG

CLOCK_EnableClock(kCLOCK_Gpio0);
CLOCK_EnableClock(kCLOCK_Mrt);


//GPIO CONFIG	
gpio_pin_config_t output_config = {    
	kGPIO_DigitalOutput,
    0,
};

GPIO_PortInit(GPIO,0);

GPIO_PinInit(GPIO, 0, 15, &output_config);//yellow
GPIO_PinInit(GPIO, 0, 14, &output_config);//green
GPIO_PinInit(GPIO, 0, 13, &output_config);//red

GPIO_PinWrite(GPIO, 0, 13, 1);//initial condition

 
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
  SystemCoreClockUpdate ();

}


