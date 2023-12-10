#include "hw init.h"
#include "melt_8_5.h"

int main(void) {
	Ports_Init();
	LCD_Init();
	char str[] = "DRPQ 12 БГД !Ш?";
	while(1){
	Parallel_LCD_print_text(FIRST_LINE, str);
	}
	return 0;
}