// This program is written in C programming language.
// It lights LEDs according to a finite state machine approach.
// It uses peripheral library functions.
//By Ensar Kidil and Uras Pehlivan


#include <stdint.h>
#include "lpc824.h" //bare metal version

#define SYSTEM_CORE_CLOCK 60000000UL   //30MHz

#define CLKOUTCLK_SRC_IRC_OSC       0
#define CLKOUTCLK_SRC_SYS_OSC       1
#define CLKOUTCLK_SRC_WDT_OSC       2
#define CLKOUTCLK_SRC_MAIN_CLK      3
void delay(uint32_t counts);
int ButtonRead();
void delay(uint32_t counts) {

  uint32_t wait;
  for (wait=counts; wait>0; --wait){
  }

}

int main(void){
	// Configure GPIO and define a state conter 
	SYSCON_SYSAHBCLKCTRL |= (1<<6); 	// Enable GPIO clocks.
	GPIO_DIR0 |= (1<<13);				// Make Pin #13 an output. Red Led
	GPIO_DIR0 |= (1<<14);				// Make Pin #14 an output. Yellow Led
	GPIO_DIR0 |= (1<<15);				// Make Pin #15 an output. Green Led
	GPIO_DIR0 &= ~(1<<17);				// Make Pin #17 an input. User Button 1.
	GPIO_DIR0 &= ~(1<<18);				// Make Pin #18 an input. User Button 2.
	volatile unsigned char state;
	state = 0;
	int ButtonCheck;
	GPIO_B13 = 1;	
	GPIO_B14 = 0;	
	GPIO_B15 = 0;			
	while(1) 
	{
		delay(100000);
		ButtonCheck = 0;
		
		while (ButtonCheck == 0){
			ButtonCheck = ButtonRead();
			
		}
		
		if(ButtonCheck == 1)
		{
			
			if(state==4){
				state = 0;
			}
			else{
				state+=1;
			}	
		}
		else if(ButtonCheck == 2){
			
			if(state == 4){
				state = 1;
			}
			else if(state == 3){
				state = 0;
			}
			else{
				state+=2;
			}
		}
		
		
		
		switch(state)
			{
				case 0:
					GPIO_B13 = 1;
					GPIO_B14 = 0;
					GPIO_B15 = 0;
					break;
				case 1:
					GPIO_B13 = 0;
					GPIO_B14 = 1;
					GPIO_B15 = 0;
					break;
				case 2:
					GPIO_B13 = 0;
					GPIO_B14 = 0;
					GPIO_B15 = 1;
					break;
				case 3:
					GPIO_B13 = 0;
					GPIO_B14 = 0;
					GPIO_B15 = 0;
					break;
				case 4:
					GPIO_B13 = 1;
					GPIO_B14 = 1;
					GPIO_B15 = 1;
					break;			
			}	
	}
}
	
	
	int ButtonRead(){
		int ButtonValue;
		if(GPIO_B17 == 1){
			
			while(GPIO_B17==1){}	
			ButtonValue = 1;
		}
		else if(GPIO_B18 == 1){
			while(GPIO_B18==1){}	
			ButtonValue = 2;
		}
		
		return ButtonValue;
	}

