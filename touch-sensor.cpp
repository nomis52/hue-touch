#include "touch-sensor.h"
#include "constants.h"

TouchSensor::TouchSensor(Callback callback, uint8_t resetPin, uint8_t address)
  : _cap(resetPin, address),
    _callback(callback) {
  for (int i = 0; i < kSensorCount; i++) {
    _states[i].lastDebounceTime = 0;
    _states[i].buttonState = false;
    _states[i].lastButtonState = false;
  }
}

bool TouchSensor::Init() {
  return _cap.Init();
}

void TouchSensor::CheckForEvents() {
  uint8_t sample = _cap.Sample();

  for (uint8_t i=0; i<8; i++) {
    bool state = sample & (1 << i);
    // TODO: Add support for double tap and long tap.
    if (state != _states[i].lastButtonState) {
      _states[i].lastDebounceTime = millis();
      _states[i].lastButtonState = state;
    }

    if ((millis() - _states[i].lastDebounceTime) > kDebounceDelayMs) {
      continue;
    }

    if (state == _states[i].buttonState) {
      continue;
    }

    _states[i].buttonState = state;
    if (_states[i].buttonState && _callback != nullptr) {
      _callback(i + 1, SINGLE_TAP);
    }
  }
}
