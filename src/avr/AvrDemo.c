#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <I2C.h>


/*
+--------+
|  A168  |
|        |
|    PB0 +---> LED ---> GND 
|        |
+--------+
*/

int main(void) {
  clock_prescale_set(clock_div_1);

  HAL_Pin led = {&PORTB, 0};
  HAL_setPinDirection(&led, OUTPUT);

  HAL_Pin sclPin = { &PORTB, 5, PULLUP_ENABLE };

  I2C_Config i2c_config = {
    .addr = 51,
    .loggingLevel = 4,
    .sclOutPin = &sclPin
  };

  I2C_init(&i2c_config);
  while (1) {
    HAL_pinWrite(&led, HIGH); 
    _delay_ms(500);
    HAL_pinWrite(&led, LOW); 
    _delay_ms(500);
  }

}