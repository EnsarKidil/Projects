#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_adc.h"
#include "fsl_sctimer.h"
#include "fsl_clock.h"
#include "fsl_power.h"
#include "fsl_syscon.h"
#include "fsl_usart.h"
#include <stdbool.h>
#include <stdio.h>


#define ADC_CHANNEL_0 		0U  
#define CORE_CLOCK 			12000000U	
#define ADC_CLOCK_DIVIDER 	1U 	
#define USART_INSTANCE 		0U
#define Conversion_Rate 	3299U / 4095U	
#define USART_BAUDRATE 		115200U / 2U	


adc_result_info_t ADCResultStruct[1]; // ADC results structure array (and pointer as well) for 2 ADC channels 

void uart_init(void);
void ADC_Configuration(adc_result_info_t *ADCResultStruct);
void SysTick_Configuration(void);
void SysTick_Handler(void);
void clock_init(void);

uint8_t counter = 0U;
uint32_t duty;

float yt;

sctimer_config_t sctConfig;
sctimer_pwm_signal_param_t pwmParam;
uint32_t event1;
uint32_t sctClock;

int main(void) {
	

    

if (SysTick_Config(SystemCoreClock / 10U - 1U)){
        while (1) { } // This would be an error condition.
    }
    
uint32_t frequency ;

BOARD_InitPins();
BOARD_InitBootClocks();
clock_init();  
uart_init();
PRINTF("%d\r\n",SystemCoreClock);
PRINTF("ADC interrupt example.\r\n");

CLOCK_EnableClock(kCLOCK_Sct);      // Enable clock of SCT.

CLOCK_EnableClock(kCLOCK_Adc);      // Enable ADC clock
POWER_DisablePD(kPDRUNCFG_PD_ADC0); // Power on ADC0
sctClock = CORE_CLOCK;

    // Configuring default SCTimer
    SCTIMER_GetDefaultConfig(&sctConfig);
    SCTIMER_Init(SCT0, &sctConfig); // Initialize Sctimer

// Hardware calibration is required after each chip reset.
// See: Sec. 21.3.4 Hardware self-calibration

pwmParam.output = kSCTIMER_Out_1; // This is the RED LED, at start only RED LED will be ON.
pwmParam.level = kSCTIMER_HighTrue;
pwmParam.dutyCyclePercent = 1; 
SCTIMER_SetupPwm(SCT0,
                &pwmParam,
                kSCTIMER_CenterAlignedPwm,
                100000U,
                sctClock,
                &event1);
    
    // Start the 32-bit Unified timer 
SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);

frequency = CLOCK_GetFreq(kCLOCK_Irc);

if (true == ADC_DoSelfCalibration(ADC0, frequency)) PRINTF("ADC Calibration Done.\r\n");
else PRINTF("ADC Calibration Failed.\r\n");

ADC_Configuration(ADCResultStruct); // Configure ADC and operation mode.

// Enable the interrupt the for Sequence A Conversion Complete:
ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable); // Within ADC0
NVIC_EnableIRQ(ADC0_SEQA_IRQn);                           // Within NVIC


PRINTF("Configuration Done.\n");




while(1){
	
    
    
} 

} // END: main()


//ISR for ADC conversion sequence A done.
void ADC0_SEQA_IRQHandler(void) {

	if(kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0)){

		ADC_GetConvSeqAGlobalConversionResult(ADC0, ADCResultStruct);
		while (!ADC_GetChannelConversionResult(ADC0, ADC_CHANNEL_0, ADCResultStruct)){}
		
		ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
      
    	PRINTF("Ch%d = %d\t\n", ADCResultStruct[0].channelNumber, ADCResultStruct[0].result * Conversion_Rate);
    	
     	duty = (ADCResultStruct[0].result/4095) * 100;
     	
     	SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_1, duty , event1);
     	
	}
	 
}


// Usage of long functions in an ISR:
// Note that in general an ISR must be written to complete and exit
// as quickly as possible.
// PRINTF is a function that may take a long time to execute.
// So it is not advisable to use PRINTF in an ISR.
// However, PRINTF is used in an ISR here to
// emphasize that the main loop is not doing anything.


void clock_init(void) { 

POWER_DisablePD(kPDRUNCFG_PD_IRC_OUT);        // Turn ON IRC OUT
POWER_DisablePD(kPDRUNCFG_PD_IRC);            // Turn ON IRC

CLOCK_Select(kSYSPLL_From_Irc);               // Connect IRC to PLL input.

clock_sys_pll_t config;
config.src = kCLOCK_SysPllSrcIrc;             // Select PLL source as IRC. 
config.targetFreq = CORE_CLOCK;             // set pll target freq

CLOCK_InitSystemPll(&config);                 // set parameters

CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcSysPll); // Select PLL as main clock source.
CLOCK_Select(kCLKOUT_From_Irc);               // select IRC for CLKOUT
CLOCK_SetCoreSysClkDiv(0x01U);				  // Set core system clock by dividing main clock by 2
SystemCoreClockUpdate();
}


// Configure and initialize the ADC
void ADC_Configuration(adc_result_info_t * ADCResultStruct) {

  adc_config_t adcConfigStruct;
  adc_conv_seq_config_t adcConvSeqConfigStruct;
  
  adcConfigStruct.clockDividerNumber = ADC_CLOCK_DIVIDER; // Defined above.
  adcConfigStruct.enableLowPowerMode = false;
  // See Sec. 21.6.11 A/D trim register (voltage mode):
  adcConfigStruct.voltageRange = kADC_HighVoltageRange;
  
  ADC_Init(ADC0, &adcConfigStruct); // Initialize ADC0 with this structure.
  
  // Insert this channel in Sequence A, and set conversion properties:
  // See Sec: 21.6.2 A/D Conversion Sequence A Control Register
  
  adcConvSeqConfigStruct.channelMask = 0x00000003U;  // Mask the least significant bit0 and bit1 for ADC channel0 and channel1 respectively; 

  // Triggered by SCT OUT3 event. See Table 277. "ADC hardware trigger inputs":
  adcConvSeqConfigStruct.triggerMask      = 3U;
  adcConvSeqConfigStruct.triggerPolarity  = kADC_TriggerPolarityPositiveEdge;
  adcConvSeqConfigStruct.enableSingleStep = false;
  adcConvSeqConfigStruct.enableSyncBypass = false;
  adcConvSeqConfigStruct.interruptMode    = kADC_InterruptForEachSequence;
  
  // Initialize the ADC0 with the sequence defined above:
  ADC_SetConvSeqAConfig(ADC0, &adcConvSeqConfigStruct);
  ADC_EnableConvSeqA(ADC0, true); // Enable the conversion sequence A.
  
  // Make the first ADC conversion so that
  // the result register has a sensible initial value.
  ADC_DoSoftwareTriggerConvSeqA(ADC0);
  ADC_GetConvSeqAGlobalConversionResult(ADC0, ADCResultStruct);
  while (!ADC_GetChannelConversionResult(ADC0, ADC_CHANNEL_0, ADCResultStruct)){}
    
  
  ADC_GetConvSeqAGlobalConversionResult(ADC0, ADCResultStruct);
}

void uart_init(void){
    uint32_t uart_clock_freq;
	usart_config_t config;

    CLOCK_EnableClock(kCLOCK_Uart0);
    /* Ser DIV of uart0. */
    CLOCK_SetClkDivider(kCLOCK_DivUsartClk, 0x01U);
    uart_clock_freq=CLOCK_GetUart0ClkFreq();     // Read UART clock frequency.
    /* Default config by using USART_GetDefaultConfig():
     * config->baudRate_bps = 9600U;
     * config->parityMode = kUSART_ParityDisabled;
     * config->stopBitCount = kUSART_OneStopBit;
     * config->bitCountPerChar = kUSART_8BitsPerChar;
     * config->loopback = false;
     * config->enableRx = false;
     * config->enableTx = false;
     * config->syncMode = kUSART_SyncModeDisabled;
     */
    USART_GetDefaultConfig(&config);
    config.enableRx     = true;
    config.enableTx     = true;
    config.baudRate_Bps = USART_BAUDRATE;
    USART_Init(USART0, &config, uart_clock_freq);

    DbgConsole_Init(USART_INSTANCE,
                             USART_BAUDRATE,
                             kSerialPort_Uart,
                             uart_clock_freq);
     
}


void SysTick_Handler(void) {

	ADC_DoSoftwareTriggerConvSeqA(ADC0);
}


