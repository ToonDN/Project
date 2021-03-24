#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "dwenguino/dwenguino_board.hpp"
#include "dwenguino/dwenguino_lcd.hpp"
#include "servos.h"
#include "drawer.h"

// DwenguinoLCD lcd;

int main(void)
{
  initBoard();
  LEDS = 0;

  // Create servo variables
  //* Servo 1 heeft het rechte stuk, Servo 2 heeft het ronde stuk
  Servo servo1 = Servo();
  servo1.high = 4750;
  servo1.low = 1330;
  servo1.value = 1330;
  servo1.pin = PINC0;

  Servo servo2 = Servo();
  servo2.high = 5050;
  servo2.low = 1330;
  servo2.value = 1090;
  servo2.pin = PINC1;

  Drawer drawer = Drawer();

  // Set servos as output
  DDRC = 0xFF;

  TCCR1A |= 1 << WGM11;
  TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS11;
  TIMSK1 |= 1 << OCIE1A;

  ICR1 = 39999; //20 ms
  sei();

  servo1.rotateTo(40);
  servo2.rotateTo(0);

  Queue queue = Queue();

  // drawer.goTo(servo1, servo2, 50, 50);
  drawer.straightLineTo(90, 90);
  // drawer.straightLineTo(servo1, servo2, 0, 0);

  // servo2.value = 1000;

  while (1)
  {
    if (TCNT1 > 1000 && TCNT1 < 5100)
    {
      if (TCNT1 >= servo1.value && bit_is_set(PORTC, servo1.pin))
        PORTC &= ~(1 << servo1.pin);

      if (TCNT1 >= servo2.value && bit_is_set(PORTC, servo2.pin))
        PORTC &= ~(1 << servo2.pin);
    }
    else
    {
      if (TCNT1 < 20000)
      {
        drawer.hasChanged = false;
      }
      else if (not drawer.hasChanged)
      {
        drawer.rotateTimeLeft -= 1;
        drawer.hasChanged = true;
      }

      

      drawer.drawNext(servo1, servo2);

      //* Buttons control
      if (!(PINE & 1 << PINE7)) //* Top
      {
        servo1.value += 0.001;
      }
      if (!(PINE & 1 << PINE6)) //* Right
      {
        if (servo1.value < servo1.high)
        {
          servo1.value += 0.1;
        }
      }
      if (!(PINE & 1 << PINE5)) //* Bottom
      {
      }
      if (!(PINE & 1 << PINE4)) //* Left
      {
        if (servo1.value > servo1.low)
        {
          servo1.value -= 0.1;
        }
      }
      if (!(PINC & 1 << PINC7)) //* Center
      {
      }
    }
  }

  return 0;
}

ISR(TIMER1_COMPA_vect)
{
  PORTC = 0xFF;
}
