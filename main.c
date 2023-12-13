#include "hw init.h"
#include "melt_8_5.h"

int main(void) {
	Ports_Init();
	LCD_Init();
	char str[] = "DRPQ 12 БГД !Ш?";
	char symb[] = = {
  0x00,
  0x04,
  0x15,
  0x1F,
  0x1F,
  0x1F,
  0x11,
  0x00
};
	create_custom_symbol(0, symb);
	char custom_str[] = {0, 32, 0, 32, 0}
	while(1){
	Parallel_LCD_print_text(FIRST_LINE, str);
	}
	
	
	return 0;
}