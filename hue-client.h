#ifndef HUE_CLIENT_H
#define HUE_CLIENT_H

#include <stdint.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "macros.h"

// HueClient is a client for the hue bridge.
class HueClient {
 public:
  // HueClient creates a new HueClient.
  HueClient();

  // ButtonEvent sends a button sensor event to the hue controller.
  // @param sensor the sensor ID to send.
  // @param buttonID the id of the button event.
  void ButtonEvent(uint8_t sensor, uint8_t buttonID);

 private:
  static constexpr int kJsonBufferSize = 1024;
  static constexpr char kPutMethod[] = "PUT";
  static constexpr char kURLPart1[] = "/api/";
  static constexpr char kURLPart2[] = "/sensors/";
  static constexpr char kURLPart3[] = "/state";

  JsonObject &MakeRequest(const char *method, const char *path, JsonObject *req);
  char *AppendString(char *dst, const char *src, size_t len);

  StaticJsonBuffer<kJsonBufferSize> _jsonBuffer;
  HTTPClient _http;

  DISALLOW_COPY_AND_ASSIGN(HueClient);
};

#endif  // HUE_CLIENT_H
