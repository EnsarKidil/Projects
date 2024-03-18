// This is an example program where the timer is used to directly initiate an
// ADC conversion sequence.
// At the end of the sequence, the ADC triggers the
// "ADC0 Sequence A conversion complete interrupt" and the corresponding ISR
// prints out the conversion result to the terminal.

// Modified from AO 2023

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


#define ADC_CHANNEL_0 		0U  // Channel 1 will be used in this example.
#define ADC_CHANNEL_1 		1U  // Channel 2 will be used in this example.
#define CORE_CLOCK 			24000000U	// Set core clock to 24 MHz
#define ADC_CLOCK_DIVIDER 	1U 	// See Fig 52. ADC clocking in Ref Manual.
#define USART_INSTANCE 		0U
#define Conversion_Rate 	3299U / 4095U	// This may be used to convert results to different units
#define USART_BAUDRATE 		115200U / 3U	// Set BAUD rate as 9600 bit/s


// The pointer and flag are global so that ISR can manipulate them:
adc_result_info_t ADCResultStruct[2]; // ADC results structure array (and pointer as well) for 2 ADC channels 
void uart_init(void);
void ADC_Configuration(adc_result_info_t *ADCResultStruct);
void SCT_Configuration(void);
void clock_init(void);

int counter = 0;
int main(void) {
uint32_t frequency ;

BOARD_InitPins();
BOARD_InitBootClocks();
clock_init();  
uart_init();

PRINTF("ADC interrupt example.\r\n");

CLOCK_EnableClock(kCLOCK_Sct);      // Enable clock of SCT.
SCT_Configuration();				// Configure SCT
CLOCK_EnableClock(kCLOCK_Adc);      // Enable ADC clock
POWER_DisablePD(kPDRUNCFG_PD_ADC0); // Power on ADC0

// Hardware calibration is required after each chip reset.
// See: Sec. 21.3.4 Hardware self-calibration
frequency = CLOCK_GetFreq(kCLOCK_Irc);

if (true == ADC_DoSelfCalibration(ADC0, frequency)) PRINTF("ADC Calibration Done.\r\n");
else PRINTF("ADC Calibration Failed.\r\n");

ADC_Configuration(ADCResultStruct); // Configure ADC and operation mode.

// Enable the interrupt the for Sequence A Conversion Complete:
ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable); // Within ADC0
NVIC_EnableIRQ(ADC0_SEQA_IRQn);                           // Within NVIC
PRINTF("Configuration Done.\n");
//ADC0_SEQA_IRQHandler();


/*
* The main loop is completely empty.
* All ADC conversion is handled by the hardware.
*
* ADC0 conversion is triggered by the hardware: SCT OUTPUT 3 event
* When SCT OUTPUT3 changes, the conversion of Sequence A starts.
*
* When the conversion is complete,
*   SEQA_INT (Sequence A conversion complete INT) is triggered.
* This calls ADC0_SEQA_IRQHandler function which finally prints out
*  the conversion result to the serial port (and to the terminal screen.)
*
* This has two advantages:
* 1. The main loop is free to do other tasks.
* 2. The sampling time of the analog channels is precise.
*
*/

while(1){} 

} // END: main()


//ISR for ADC conversion sequence A done.
void ADC0_SEQA_IRQHandler(void) {
  PRINTF("Press A Key To Start Conversion");
	GETCHAR(); // Read char
	if(kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0)){

		ADC_GetConvSeqAGlobalConversionResult(ADC0, ADCResultStruct);
		while (!ADC_GetChannelConversionResult(ADC0, ADC_CHANNEL_0, ADCResultStruct)){}
		PRINTF("Ch%d = %d\t", ADCResultStruct[0].channelNumber, ADCResultStruct[0].result * Conversion_Rate);
		
		ADC_GetConvSeqAGlobalConversionResult(ADC0, ADCResultStruct);
		while (!ADC_GetChannelConversionResult(ADC0, ADC_CHANNEL_1, ADCResultStruct + 1)){}
		PRINTF("Ch%d = %d\n", ADCResultStruct[1].channelNumber, ADCResultStruct[1].result * Conversion_Rate);
		
		ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
      
      // ADCConvCompleteFlag is not used in this program.
      // However if any task in the main loop must be informed of the
      // ADC conversion, that task can check this flag;
      // when the flag is true,  the task can use the conversion result:
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
config.targetFreq = CORE_CLOCK*2;             // set pll target freq

CLOCK_InitSystemPll(&config);                 // set parameters

CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcSysPll); // Select PLL as main clock source.
CLOCK_Select(kCLKOUT_From_Irc);               // select IRC for CLKOUT
CLOCK_SetCoreSysClkDiv(0x02U);				  // Set core system clock by dividing main clock by 2
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
  
  adcConvSeqConfigStruct.channelMask = 3U;  // Mask the least significant bit0 and bit1 for ADC channel0 and channel1 respectively; 

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
  while (!ADC_GetChannelConversionResult(ADC0, ADC_CHANNEL_1, ADCResultStruct+1)){}
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


void SCT_Configuration(void){
  sctimer_config_t sctimerConfig;
  uint32_t eventCounterL;
  uint16_t matchValueL;
  
  SCTIMER_GetDefaultConfig(&sctimerConfig);
  
  // Set the configuration struct for the timer:
  // For more information, see:  Xpresso_SDK/devices/LPC824/drivers/fsl_sctimer.h
  sctimerConfig.enableCounterUnify = false; // Use as two 16 bit timers.
  
  sctimerConfig.clockMode = kSCTIMER_System_ClockMode; // Use system clock as SCT input

  matchValueL = 50000U; // This is in: 16.6.20 SCT match registers 0 to 7
  sctimerConfig.enableBidirection_l= false; // Use as single directional register.
  // Prescaler is 8 bit, in: CTRL. See: 16.6.3 SCT control register
  sctimerConfig.prescale_l = 239U; // For this value +1 is used.
  SCTIMER_Init(SCT0, &sctimerConfig);    // Initialize SCTimer module
  
  // Configure the low side counter.
  // Schedule a match event for the 16-bit low counter:
  SCTIMER_CreateAndScheduleEvent(SCT0,
				 kSCTIMER_MatchEventOnly,
				 matchValueL,
				 0,    // Not used for "Match Only"
				 kSCTIMER_Counter_L,
				 &eventCounterL);

  // TODO: Rather than toggle, it should set the output:
  // Toggle output_3 when the 16-bit low counter event occurs:
  SCTIMER_SetupOutputToggleAction(SCT0, kSCTIMER_Out_3, eventCounterL);
  // Reset Counter L when the 16-bit low counter event occurs
  SCTIMER_SetupCounterLimitAction(SCT0, kSCTIMER_Counter_L, eventCounterL);
  
  // Setup the 16-bit low counter event active direction
  //  See fsl_sctimer.h
  SCTIMER_SetupEventActiveDirection(SCT0,
				    kSCTIMER_ActiveIndependent,
				    eventCounterL);
  
  // Start the 16-bit low counter
  SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);
}
