#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

const PROGMEM uint8_t deg_sign[] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

const PROGMEM uint8_t arrow_up[] = {
  0b00000,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00100,
  0b00000,
};

const PROGMEM uint8_t arrow_down[] = {
  0b00000,
  0b00100,
  0b00100,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00000,
};

void createChars(hd44780_I2Cexp lcd){
  lcd.createChar (0x00, deg_sign);
  lcd.createChar (0x01, arrow_up);
  lcd.createChar (0x02, arrow_down);
}