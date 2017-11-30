/***************************************************
  This is a library for the CAP1188 8-Channel Capacitive Sensor

  Designed specifically to work with the CAP1188 breakout from Adafruit
  ----> https://www.adafruit.com/products/1602

  These sensors use I2C/SPI to communicate, 2+ pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Arduino.h"

// The interface to the CAP1188 sensor chip.
class CAP1188 {
 public:
  // Create a new CAP1188 instance.
  // @param resetPin the GPIO pin to use to reset.
  // @param i2caddr the I2C address of the cap1188 chip.
  CAP1188(int8_t resetPin, uint8_t i2caddr);

  // Init initializes the chip.
  bool Init();

  // Sample returns the latest data from the cap1188 chip.
  uint8_t Sample();

 private:
  const int8_t _i2caddr;
  const int8_t _resetPin;

  uint8_t readRegister(uint8_t reg);
  void writeRegister(uint8_t reg, uint8_t value);
};

