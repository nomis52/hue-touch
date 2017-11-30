/***************************************************
  This is a library for the CAP1188 I2C/SPI 8-chan Capacitive Sensor

  Designed specifically to work with the CAP1188 sensor from Adafruit
  ----> https://www.adafruit.com/products/1602

  These sensors use I2C/SPI to communicate,  pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "cap1188.h"
#include <Wire.h>

static constexpr uint8_t CAP1188_REG_MAIN = 0x00;
static constexpr uint8_t CAP1188_REG_SENSOR_INPUT_STATUS = 0x03;
static constexpr uint8_t CAP1188_REG_MTBLK = 0x2A;
static constexpr uint8_t CAP1188_REG_STANDBYCFG = 0x41;
static constexpr uint8_t CAP1188_REG_LEDLINK = 0x72;
static constexpr uint8_t CAP1188_REG_PRODUCT_ID = 0xFD;
static constexpr uint8_t CAP1188_REG_MANUFACTURER_ID = 0xFE;
static constexpr uint8_t CAP1188_REG_REVISION = 0xFF;

static constexpr uint8_t CAP1188_INT_FLAG = 0x01;

CAP1188::CAP1188(int8_t resetPin, uint8_t i2caddr)
  : _resetPin(resetPin),
    _i2caddr(i2caddr) {
}

bool CAP1188::Init() {
  Wire.begin();

  if (_resetPin != -1) {
    pinMode(_resetPin, OUTPUT);
    digitalWrite(_resetPin, LOW);
    delay(100);
    digitalWrite(_resetPin, HIGH);
    delay(100);
    digitalWrite(_resetPin, LOW);
    delay(100);
  }

  readRegister(CAP1188_REG_PRODUCT_ID);

  if ( (readRegister(CAP1188_REG_PRODUCT_ID) != 0x50) ||
       (readRegister(CAP1188_REG_MANUFACTURER_ID) != 0x5D) ||
       (readRegister(CAP1188_REG_REVISION) != 0x83)) {
    return false;
  }

  /*
  Serial.print("Product ID: 0x");
  Serial.println(readRegister(CAP1188_REG_PRODUCT_ID), HEX);
  Serial.print("Manuf. ID: 0x");
  Serial.println(readRegister(CAP1188_REG_MANUFACTURER_ID), HEX);
  Serial.print("Revision: 0x");
  Serial.println(readRegister(CAP1188_REG_REVISION), HEX);
  */

  // allow multiple touches
  writeRegister(CAP1188_REG_MTBLK, 0);
  // Have LEDs follow touches
  writeRegister(CAP1188_REG_LEDLINK, 0xFF);
  // speed up a bit
  writeRegister(CAP1188_REG_STANDBYCFG, 0x30);
  return true;
}

uint8_t  CAP1188::Sample() {
  uint8_t t = readRegister(CAP1188_REG_SENSOR_INPUT_STATUS);
  if (t) {
    writeRegister(CAP1188_REG_MAIN, readRegister(CAP1188_REG_MAIN) & ~CAP1188_INT_FLAG);
  }
  return t;
}

uint8_t CAP1188::readRegister(uint8_t reg) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(_i2caddr, 1);
  return Wire.read();
}

void CAP1188::writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}
