#include "hw init.h"
#include "melt_8_5.h"

void main(void) {
	Ports_Init();
	LCD_Init();
	char str[] = "Привет, мир!";
	Parallel_LCD_print_text(FIRST_LINE, str, 0);
	
}