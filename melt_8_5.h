#ifndef MELT_H
#define MELT_H

#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_config.h"           // Keil::Device:Startup
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "hw init.h"
#include <string.h>

void LCD(uint8_t val, uint8_t cmd);
void Parallel_LCD_print_text(uint8_t line, char* text, uint8_t cell);
inline void CLEAR_LCD_MELT_8BIT(void);
void CHANGE_LCD_PAGE(void);
void create_custom_symbol(char* sym);
#endif
