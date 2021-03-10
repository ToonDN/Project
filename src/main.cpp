#include <avr/io.h>
#include <util/delay.h>
#include "dwenguino/dwenguino_board.hpp"
#include "dwenguino/dwenguino_lcd.hpp"

DwenguinoLCD lcd;

int main(void)
{
initBoard();
lcd = DwenguinoLCD();
lcd.initLCD();

backlightOn();

  while(1){
    lcd.printStringToLCD("Labo 2", 0, 5);
    _delay_ms(1000);
    lcd.clearLCD();
    _delay_ms(1000);
  }
  return 0;
}