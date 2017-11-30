#include <ESP8266WiFi.h>

#include "constants.h"
#include "net-manager.h"

using namespace std::placeholders;

NetManager::NetManager(const char *ssid, const char *password, Callback callback)
  : _connectHandler(WiFi.onStationModeConnected(std::bind(&NetManager::OnConnect, this, _1))),
    _configureHandler(WiFi.onStationModeGotIP(std::bind(&NetManager::OnConfigure, this, _1))),
    _disconnectHandler(WiFi.onStationModeDisconnected(std::bind(&NetManager::OnDisconnect, this, _1))),
    _ssid(ssid),
    _password(password),
    _callback(callback) {
}

void NetManager::Init() {
  Serial.print("Connecting to ");
  Serial.println(_ssid);

  WiFi.begin(_ssid, _password);
}

void NetManager::OnConnect(const WiFiEventStationModeConnected &state) {
  Serial.print("WiFi connected: ");
  Serial.println(state.ssid);
}

void NetManager::OnConfigure(const WiFiEventStationModeGotIP &state) {
  Serial.print("WiFi Configured, IP: ");
  Serial.println(state.ip);

  if (_callback != nullptr) {
    _callback(NET_CONFIGURED);
  }
}

void NetManager::OnDisconnect(const WiFiEventStationModeDisconnected &state) {
  Serial.println("WiFi lost connection");

  if (_callback != nullptr) {
    _callback(NET_DISCONNECT);
  }
}
