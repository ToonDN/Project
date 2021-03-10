#include <avr/io.h>
#include <util/delay.h>
#include "dwenguino/dwenguino_board.h"
#include "dwenguino/dwenguino_lcd.h"

main() {
   DDRA = 0xFF; // All LEDs as output
   PORTA = 0;   // All LEDs off

   unsigned char a =  0x11;
   unsigned char b = 17;
   

   if ( a == b ) {
      PORTA |= 0b00000001;
   }
	
	
}