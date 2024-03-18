//By Ensar Kidil and Uras Pehlivan
#include <stdint.h>

void delay(uint32_t counts);
int ButtonRead();

void delay(uint32_t counts)
{
  uint32_t wait;
  for (wait=counts; wait>0; --wait){}
}

int ButtonRead(){
		int ButtonValue;
		if(*(volatile unsigned char *)(0xA0000011) == 1){
			
			while(*(volatile unsigned char *)(0xA0000011) == 1){}	
			ButtonValue = 1;
		}
		else if(*(volatile unsigned char *)(0xA0000012) == 1){
			while(*(volatile unsigned char *)(0xA0000012) == 1){}	
			ButtonValue = 2;
		}
		
		return ButtonValue;
	}

int main()
{
	*((volatile unsigned int *)(0x40048080)) |= 0x00000040;		// Enable GPIO clocks.
	*((volatile unsigned int *)(0xA0002000)) |= 0x0000E000;		// Make pins #13,#14 and #15 which are blue and green LEDs respectively on Alakart outputs.
	*((volatile unsigned int *)(0xA0002000)) &= ~(0x00030000);	// Make pin #17 and #18 inputs.
	volatile unsigned char state;
	state = 0;
	*((volatile unsigned char *)(0xA000000D)) = 1;				// Set pin #13 high. (Red LED is ON.)
	*((volatile unsigned char *)(0xA000000E)) = 0;				// Set pin #14 low. (Yellow LED is OFF.)
	*((volatile unsigned char *)(0xA000000F)) = 0;				// Set pin #15 low. (Green LED is OFF.)
	int ButtonCheck;
	
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
					*((volatile unsigned char *)(0xA000000D)) = 1;
					*((volatile unsigned char *)(0xA000000E)) = 0;			
					*((volatile unsigned char *)(0xA000000F)) = 0;				
					break;
				case 1:
					*((volatile unsigned char *)(0xA000000D)) = 0;
					*((volatile unsigned char *)(0xA000000E)) = 1;			
					*((volatile unsigned char *)(0xA000000F)) = 0;
					break;
				case 2:
					*((volatile unsigned char *)(0xA000000D)) = 0;
					*((volatile unsigned char *)(0xA000000E)) = 0;			
					*((volatile unsigned char *)(0xA000000F)) = 1;
					break;
				case 3:
					*((volatile unsigned char *)(0xA000000D)) = 0;
					*((volatile unsigned char *)(0xA000000E)) = 0;			
					*((volatile unsigned char *)(0xA000000F)) = 0;
					break;
				case 4:
					*((volatile unsigned char *)(0xA000000D)) = 1;
					*((volatile unsigned char *)(0xA000000E)) = 1;			
					*((volatile unsigned char *)(0xA000000F)) = 1;
					break;		
		}
	}
}

