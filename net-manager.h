#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <ESP8266WiFi.h>

#include <functional>

#include "macros.h"

// NetManager takes care of the WiFi connection and runs the callback when the
// network state changes.
class NetManager {
 public:
  typedef enum {
    NET_CONFIGURED,
    NET_DISCONNECT,
  } Event;

  typedef std::function<void(Event)> Callback;

  // Create a new NetManager and connect to the given network.
  // @param ssid the SSID to connect to.
  // @param password the WiFi password to use.
  // @param callback the callback to run on events.
  NetManager(const char *ssid, const char *password, Callback callback);

  // Initialize the network manager.
  void Init();

 private:
  void OnConnect(const WiFiEventStationModeConnected &state);
  void OnConfigure(const WiFiEventStationModeGotIP &state);
  void OnDisconnect(const WiFiEventStationModeDisconnected &state);

  const WiFiEventHandler _connectHandler;
  const WiFiEventHandler _configureHandler;
  const WiFiEventHandler _disconnectHandler;

  const char *_ssid;
  const char *_password;
  const Callback _callback;

  DISALLOW_COPY_AND_ASSIGN(NetManager);
};

#endif  // NETMANAGER_H
