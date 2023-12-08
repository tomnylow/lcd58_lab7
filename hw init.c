#include "hw init.h"

void LCD_Init(void)
{
	RW_RESET;
	PSB_SET;
	XRES_SET;
	LCD(0x38, 0); 
	LCD(0x38, 0); 
	LCD(0x38, 0); // init
	LCD(0x38, 0); // 2 lines 5*7 matrix
	LCD(0x0C, 0); // Display on, cursor off, 0 page
	LCD(0x01, 0); // Clear display
	LCD(0x06, 0); // Increment cursor (shift right)

}

void Ports_Init(void)
{
	
	
}