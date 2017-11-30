#include "controller.h"

#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <functional>

using namespace std::placeholders;

Controller::Controller()
  : _net(kWifiSSID, kWifiPassword, std::bind(&Controller::NetworkEvent, this, _1)),
    _httpServer(kWebserverPort),
    _sensor(std::bind(&Controller::OnTouch, this, _1, _2), kTouchResetPin, kTouchAddress),
    _wifiConnected(false),
    _touchInitialized(false),
    _ledOn(false) {
}

bool Controller::Init() {
  Serial.begin(kBaudRate);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  _httpServer.on("/", std::bind(&Controller::HandleRoot, this));
  _httpServer.on("/restart", std::bind(&Controller::HandleRestart, this));

  _net.Init();
  _touchInitialized = _sensor.Init();
}

void Controller::Loop() {
  _httpServer.handleClient();
  _sensor.CheckForEvents();
  ArduinoOTA.handle();

  if (!_touchInitialized) {
    _touchInitialized = _sensor.Init();
  }

  BlinkLED();
}

void Controller::BlinkLED() {
  if (!_touchInitialized) {
    unsigned long now = millis();

    if (now - _ledLastChanged < 500) {
      return;
    }
    _ledLastChanged = now;

    if (_ledOn) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
    _ledOn = !_ledOn;
  }
}

void Controller::InitOTA() {
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void Controller::NetworkEvent(NetManager::Event event) {
  switch (event) {
    case NetManager::NET_CONFIGURED:
      digitalWrite(LED_BUILTIN, LOW);

      if (!MDNS.begin(kNodeName)) {
        Serial.println("MDNS responder failed to start");
      }

      _httpServer.begin();
      _wifiConnected = true;
      MDNS.addService("http", "tcp", kWebserverPort);
      break;
    case NetManager::NET_DISCONNECT:
      digitalWrite(LED_BUILTIN, HIGH);
      _httpServer.stop();
      _wifiConnected = false;
      break;
  }
}

void Controller::OnTouch(uint8_t sensor, TouchSensor::Event event) {
  Serial.printf("ID: %d, event: %d\n", sensor, event);
  if (!_wifiConnected) {
    return;
  }

  if (sensor > arraysize(kTouchMappings)) {
    return;
  }

  int16_t lamp = kTouchMappings[sensor-1];
  if (lamp > 0) {
    _hueClient.ButtonEvent(lamp, 2);
  }
}

void Controller::HandleRoot() {
  String message = "<html><body><h3>Hue Touch Sensor</h3>";

  if (_touchInitialized) {
    message += "<p>Touch sensor connected.</p>";
  } else {
    message += "<p>Missing Touch sensor!</p>";
  }

  message += "</body></html>";
  _httpServer.send(200, "text/html", message);
}

void Controller::HandleRestart() {
  ESP.restart();
}
