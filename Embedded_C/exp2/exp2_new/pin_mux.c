#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_swm.h"
#include "fsl_gpio.h"
#include "pin_mux.h"


void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}


void BOARD_InitPins(void) {
  // This struct keeps the GPIO pin configuration
  uint32_t IOCON_PIO_config; 	// See: User Manual Section 8.4.1 Pin Configuration & Fig.10
  // Struct for input pins
  gpio_pin_config_t input_config = {
				  kGPIO_DigitalInput,
				  0,
  };
  
  CLOCK_EnableClock(kCLOCK_Iocon); 	// Enable clock for IOCON block.
  CLOCK_EnableClock(kCLOCK_Swm);  	// Enables clock for switch matrix.
  GPIO_PortInit(GPIO, 0);			// Initialize GPIO port.
  
  // Configure PIO_19
  // This is the external pull-up Button 1
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config = (IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		      IOCON_PIO_HYS_EN |       // Enable hysteresis
		      IOCON_PIO_INV_DI |       // Do not invert input
		      IOCON_PIO_OD_DI |        // Disable open-drain function
		      IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		      IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_19, IOCON_PIO_config);
  
  // Then initialize PIO_19 as input
  GPIO_PinInit(GPIO, 0, 19, &input_config);
 
  // Configure PIO_20
  // This is the external pull-up Button 2
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config = (IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		      IOCON_PIO_HYS_EN |       // Enable hysteresis
		      IOCON_PIO_INV_DI |       // Do not invert input
		      IOCON_PIO_OD_DI |        // Disable open-drain function
		      IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		      IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_20, IOCON_PIO_config);
  
  // Then initialize PIO_20 as input
  GPIO_PinInit(GPIO, 0, 20, &input_config);
  
  // Configure PIO_21
  // This is the external pull-up Button 3
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config = (IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		      IOCON_PIO_HYS_EN |       // Enable hysteresis
		      IOCON_PIO_INV_DI |       // Do not invert input
		      IOCON_PIO_OD_DI |        // Disable open-drain function
		      IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		      IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_18, IOCON_PIO_config);
  
  // Then initialize PIO_21 as input
  GPIO_PinInit(GPIO, 0, 18, &input_config);


  // In this processor, outputs of some peripheral devices
  // can be connected to any GPIO pin by configuring a "Pin multiplexer".
  // This is only possible for peripherals with "moveable pins"
  // This code does the configuration.
    
  /////////////// SCT OUT0 Configuration /////////////////////////////////

  // Configure PIO_13, (Alakart label: P13)  as : SCT OUT0
  // This is the Red LED
  // IC package physical pin is: 2,
  // GPIO pin name: PIO12_0
  // Peripheral: SCT, signal: OUT0,
  
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config = (IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		      IOCON_PIO_HYS_EN |       // Enable hysteresis
		      IOCON_PIO_INV_DI |       // Do not invert input
		      IOCON_PIO_OD_DI |        // Disable open-drain function
		      IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		      IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_13, IOCON_PIO_config);
  
  // Second, connect SCT_OUT0 to P0_13 using the multiplexer:
  // SCT_OUT1 is a moveable pin.
  // Connect it to Port 0, Pin 13: PIO0_13
  // PIO0_13 is pin #2  on the 32 pin IC package
  SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT0, kSWM_PortPin_P0_13);
  
  
  /////////////////////////////////// SCT OUT1 Configuration /////////////////////////////////

  // Configure PIO_27, (Alakart label: P27) as : SCT OUT1
  // This is the Green LED
  // IC package physical pin is: 11,
  // GPIO pin name: PIO27_0
  // Peripheral: SCT, signal: OUT1
  
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config =(IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		     IOCON_PIO_HYS_EN |       // Enable hysteresis
		     IOCON_PIO_INV_DI |       // Do not invert input
		     IOCON_PIO_OD_DI |        // Disable open-drain function
		     IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		     IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_14, IOCON_PIO_config);

  // Second, connect SCT_OUT1 to P0_27 using the multiplexer:
  // SCT_OUT1 is a moveable pin.
  // Connect it to Port 0, Pin 27: PIO0_27
  // PIO0_27 is pin #11  on the 32 pin IC package
  SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT1, kSWM_PortPin_P0_14);
  
  
  /////////////// SCT OUT2 Configuration /////////////////////////////////

  // Configure PIO_16, (Alakart label: P16)  as : SCT OUT2
  // This is the Yellow LED
  // IC package physical pin is: 10,
  // GPIO pin name: PIO16_0
  // Peripheral: SCT, signal: OUT2,
  
  
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config = (IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		      IOCON_PIO_HYS_EN |       // Enable hysteresis
		      IOCON_PIO_INV_DI |       // Do not invert input
		      IOCON_PIO_OD_DI |        // Disable open-drain function
		      IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		      IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_15, IOCON_PIO_config);
  
  // Second, connect SCT_OUT2 to P0_16 using the multiplexer:
  // SCT_OUT2 is a moveable pin.
  // Connect it to Port 0, Pin 16: PIO0_16
  // PIO0_16 is pin #10  on the 32 pin IC package
  SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT2, kSWM_PortPin_P0_15);
  
  
  CLOCK_DisableClock(kCLOCK_Swm); // Disable clock for switch matrix.
}

