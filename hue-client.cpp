#include <Stream.h>
#include <ArduinoJson.h>
#include <stdlib.h>

#include <sstream>
#include <string>

#include "macros.h"
#include "constants.h"
#include "hue-client.h"

constexpr char HueClient::kPutMethod[];
constexpr char HueClient::kURLPart1[];
constexpr char HueClient::kURLPart2[];
constexpr char HueClient::kURLPart3[];

HueClient::HueClient()
  : _http() {
  _http.setReuse(true);
}

void HueClient::ButtonEvent(uint8_t sensor, uint8_t buttonID) {
  Serial.printf("sensor: %d, button: %d\n", sensor, buttonID);
  constexpr size_t pathSize = arraysize(kURLPart1) + arraysize(kHueUsername) +
                              arraysize(kURLPart2) + 3 /* uint8_t */ +
                              arraysize(kURLPart3) + 1;
  char path[pathSize];
  char *p = path;
  p = AppendString(p, kURLPart1, arraysize(kURLPart1));
  p = AppendString(p, kHueUsername, arraysize(kHueUsername));
  p = AppendString(p, kURLPart2, arraysize(kURLPart2));
  itoa(sensor, p, 10 /* base 10 */);
  p += strlen(p);
  p = AppendString(p, kURLPart3, arraysize(kURLPart3));
  *p = 0;

  _jsonBuffer.clear();
  JsonObject &request = _jsonBuffer.createObject();
  request.set("buttonevent", buttonID);
  MakeRequest(kPutMethod, path, &request);
}

JsonObject &HueClient::MakeRequest(const char *method, const char *path, JsonObject *request) {
  String data;
  if (request != nullptr) {
    data.reserve(request->measureLength() + 1);
    request->printTo(data);
  }

  _http.begin(kHueAddress, kHuePort, path);
  int httpCode = _http.sendRequest(method, data);

  Serial.printf("%s %s:%d%s -> [%d]\n", method, kHueAddress, kHuePort, path, httpCode);
  if (data.length() > 0) {
    Serial.println(data);
  }

  if (httpCode != 200) {
    return JsonObject::invalid();
  }

  JsonObject& root = _jsonBuffer.parseObject(_http.getStream());
  _http.end();
  return root;
}

char *HueClient::AppendString(char *dst, const char *src, size_t len) {
  strncpy(dst, src, len);
  return dst + len - 1;
}
