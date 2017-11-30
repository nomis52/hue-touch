#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <functional>

#include <ESP8266WebServer.h>

#include "constants.h"
#include "net-manager.h"
#include "touch-sensor.h"
#include "hue-client.h"

class Controller {
 public:
  Controller();

  bool Init();
  void Loop();

 private:
  void InitOTA();
  void BlinkLED();

  void NetworkEvent(NetManager::Event event);
  void OnTouch(uint8_t sensor, TouchSensor::Event event);

  // HTTP Handlers
  void HandleRoot();
  void HandleRestart();

  NetManager _net;
  ESP8266WebServer _httpServer;
  TouchSensor _sensor;
  HueClient _hueClient;

  bool _wifiConnected;
  bool _touchInitialized;
  bool _ledOn;
  unsigned long _ledLastChanged;

  DISALLOW_COPY_AND_ASSIGN(Controller);
};

#endif // CONTROLLER_H
