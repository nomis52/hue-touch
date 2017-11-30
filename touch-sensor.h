#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include <functional>

#include "cap1188.h"
#include "macros.h"

// TouchSensor is responsible for interpreting the touch events from the
// CAP1188 device.
class TouchSensor {
 public:
  typedef enum {
   SINGLE_TAP,
   // DOUBLE_TAP,
   // LONG_TAP,
  } Event;

  typedef std::function<void(uint8_t, Event)> Callback;

  // TouchSensor creates a new TouchSensor.
  // @param onTouch the callback to run when a touch event occurs.
  // @param resetPin The GPIO pin number to use to reset the touch sensor.
  // @param i2caddress The I2C address of the touch sensor.
  TouchSensor(Callback onTouch, uint8_t resetPin, uint8_t i2caddress);

  // Init initializes the sensor.
  bool Init();

  // CheckForEvents should be called within the main loop() function.
  void CheckForEvents();

 private:
  typedef struct {
    unsigned long lastDebounceTime;
    bool buttonState;
    bool lastButtonState;
  } sensorState;

  static constexpr int kSensorCount = 8;

  CAP1188 _cap;
  const Callback _callback;

  sensorState _states[kSensorCount];

  DISALLOW_COPY_AND_ASSIGN(TouchSensor);
};

#endif // TOUCH_SENSOR_H
