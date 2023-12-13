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

void old_print_text(uint8_t line, char* text, uint8_t cell)
{
uint8_t nBytes;
if (!text) return;
nBytes = strlen(text);
if (nBytes>80) return;
if(line == FIRST_LINE)
{
LCD(0x80 + cell, 0);
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
};
LCD(0x38, 0);
DELAY_US(50);
}
void Parallel_LCD_print_text(uint8_t line, char* text) {
    uint8_t latin_start_positions[16];  // Максимальное количество подстрок
    uint8_t cyrillic_start_positions[16];
    
    size_t latin_count = 0;
    size_t cyrillic_count = 0;
    
    size_t len = strlen(text);
		if (len > 17) return;
	
    int i = 0;
	// запоминаем начала кириллических и латинских подстрок
    while (i < len) {
        if (text[i] < 128) {
            latin_start_positions[latin_count] = i;
            latin_count++;
            while (i < len && text[i] < 128) {
                i++;
            }
        } else {
            cyrillic_start_positions[cyrillic_count] = i;
            cyrillic_count++;
            while (i < len && text[i] >= 128) {
                i++;
            }
        }
    }
    
    if (line == FIRST_LINE) {
				LCD(0xC, 0); //смена на первую кодовую страницу
        for (size_t j = 0; j < latin_count; j++) {
            LCD(0x80 + latin_start_positions[j], 0);
            for (size_t k = latin_start_positions[j]; k < len && text[k] < 128; k++) {
                LCD(convert_1251_to_melt(text[k]), 1);
            }
        }
				CLEAR_LCD_MELT_8BIT();
				for (size_t j = 0; j < cyrillic_count; j++) {
						LCD(0xD, 0); // вторая страница
            LCD(0x80 + cyrillic_start_positions[j], 0);
            for (size_t k = cyrillic_start_positions[j]; k < len && text[k] >= 128; k++) {
                LCD(convert_1251_to_melt(text[k]), 1);
            }
        }
    }

    if (line == SECOND_LINE) {
				LCD(0xC, 0); //смена на первую кодовую страницу
        for (size_t j = 0; j < latin_count; j++) {
            LCD(0xC0 + latin_start_positions[j], 0);
            for (size_t k = latin_start_positions[j]; k < len && text[k] < 128; k++) {
                LCD(convert_1251_to_melt(text[k]), 1);
            }
        }
				CLEAR_LCD_MELT_8BIT();
				for (size_t j = 0; j < cyrillic_count; j++) {
						LCD(0xD, 0); // вторая страница
            LCD(0xC0 + cyrillic_start_positions[j], 0);
            for (size_t k = cyrillic_start_positions[j]; k < len && text[k] >= 128; k++) {
                LCD(convert_1251_to_melt(text[k]), 1);
            }
        }
    }
LCD(0x38, 0);
DELAY_US(50);
}


void CLEAR_LCD_MELT_8BIT(void)
{
LCD(0x01, 0);
}

void create_custom_symbol(uint8_t code, const char* symbol)
{
	uint8_t adr;
	for(uint8_t j=0; j < 8; j++){
		adr = 0x40 + j + (code << 3); 
		LCD(0x38, 0); DELAY_US(50);
		LCD(adr, 0); DELAY_US(50);
		LCD(0x3C, 0); DELAY_US(50);
		LCD(0x80, 0); DELAY_US(50);
		LCD(symbol[j], 0); DELAY_US(50);  
		LCD(0x38, 0); DELAY_US(50);
		 
	}; 
}
uint8_t convert_1251_to_melt(unsigned char symbol) {
    if (symbol < 192) {
        return symbol;
    } else {

// АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ
// ABCDEFGHIJKLMNOPQRSTUVWXYZ
        unsigned char mask[] = {65, 189, 66, 190, 191, 69, 192, 193, 194, 195, 196, 197, 77, 
        72, 79, 134, 80, 67, 84, 199, 200, 88, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210}; 
        return mask[symbol - 192];
    }
}