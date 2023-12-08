#include "melt_8_5.h"

void LCD(uint8_t val, uint8_t cmd)
{
	BitAction data;
	PORT_WriteBit(MDR_PORTF, LCD_A0, (BitAction)cmd);
	// set RS (A0) = cmd; cmd = 0 -> Command, cmd = 1 -> Data
	data = (BitAction)(val & 0x01);
	PORT_WriteBit(MDR_PORTA, LCD_DB0, data);
	data = (BitAction)((val >> 1) & 0x01);
	PORT_WriteBit(MDR_PORTA, LCD_DB1, data);
	data = (BitAction)((val >> 2) & 0x01);
	PORT_WriteBit(MDR_PORTA, LCD_DB2, data);
	data = (BitAction)((val >> 3) & 0x01);
	PORT_WriteBit(MDR_PORTB, LCD_DB3, data);
	data = (BitAction)((val >> 4) & 0x01);
	PORT_WriteBit(MDR_PORTB, LCD_DB4, data);
	data = (BitAction)((val >> 5) & 0x01);
	PORT_WriteBit(MDR_PORTB, LCD_DB5, data);
	data = (BitAction)((val >> 6) & 0x01);
	PORT_WriteBit(MDR_PORTB, LCD_DB6, data);
	data = (BitAction)((val >> 7) & 0x01);
	PORT_WriteBit(MDR_PORTB, LCD_DB7, data);
	E_SET;
	DELAY_MS(5);
	E_RESET;
	DELAY_MS(1);
	}

void Parallel_LCD_print_text(uint8_t line, char* text, uint8_t cell)
{
	uint8_t nBytes;
	nBytes = strlen(text);
	if (nBytes>80) return;
	if(line == FIRST_LINE)
	{
	LCD(0x80 + cell, 0); // для латиницы полное соотв с ascii нахуя +80
	}
	else if (line == SECOND_LINE)
	{
	LCD(0xC0 + cell, 0);
	}
	DELAY_US(50);
	for(uint8_t j=0; j < nBytes; j++)
	{
	LCD(text[j], 1);
	DELAY_US(50);
	}
	LCD(0x38, 0);
	DELAY_US(50);
}

inline void CLEAR_LCD_MELT_8BIT(void)
{
LCD(0x01, 0);
}

void CHANGE_LCD_PAGE(void){
	static uint8_t currentPage = 0xC;

    // Переключение кодовой страницы
    if (currentPage == 0xC) {
        currentPage = 0xD;
    } else {
        currentPage = 0xC;
    }
	LCD(currentPage, 0);
}
void create_custom_symbol(char* sym){
	
}