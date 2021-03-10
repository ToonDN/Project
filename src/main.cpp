#include <avr/io.h>
#include <util/delay.h>
#include "dwenguino/dwenguino_board.hpp"
#include "dwenguino/dwenguino_lcd.hpp"
#include <avr/interrupt.h>

DwenguinoLCD lcd;

int main(void)
{
  SREG |= (1 << SREG_I);
  DDRC |= (1 << PC0);

  TIMSK1 |= (1 << OCIE1A);

  TCCR1A &= ~(1 << WGM11);
  TCCR1A &= ~(1 << WGM10);
  TCCR1B |= ~(1 << WGM12);
  TCCR1B &= ~(1 << WGM13);

  initBoard();
  lcd = DwenguinoLCD();
  lcd.initLCD();

  backlightOn();

  while (1)
  {
    lcd.printStringToLCD("Labo 2", 0, 5);
    _delay_ms(1000);
    lcd.clearLCD();
    _delay_ms(1000);
  }
  return 0;
}