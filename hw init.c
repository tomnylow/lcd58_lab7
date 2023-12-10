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
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
	
	PORT_InitTypeDef PORT_InitStruct;

	PORT_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_InitStruct.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStruct.PORT_OE = PORT_OE_OUT;
	PORT_InitStruct.PORT_Pin = LCD_DB0 + LCD_DB1 + LCD_DB2;  // Добавьте другие пины, если необходимо
	PORT_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORT_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;

	PORT_Init(MDR_PORTA, &PORT_InitStruct);
	
	PORT_InitStruct.PORT_Pin = LCD_DB3 + LCD_DB4 + LCD_DB5 + LCD_DB6 + LCD_DB7;
	PORT_Init(MDR_PORTB, &PORT_InitStruct);
	
	PORT_InitStruct.PORT_Pin = PORT_Pin_1 + PORT_Pin_3 + LCD_A0;
	PORT_Init(MDR_PORTF, &PORT_InitStruct);
	
	PORT_InitStruct.PORT_Pin = PORT_Pin_1 + PORT_Pin_0;
	PORT_Init(MDR_PORTC, &PORT_InitStruct);
	
}