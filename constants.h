#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

// WiFi settings
// -----------------------------------------------------------------------------

// The SSID of the wifi network to connect to.
static constexpr char kWifiSSID[] = "FILL ME IN";

// The password for the Wifi network.
static constexpr char kWifiPassword[] = "FILL ME IN";

// Hue settings
// -----------------------------------------------------------------------------

// The IP Address of the Hue Bridge.
static constexpr char kHueAddress[] = "FILL ME IN";

// The port of the Hue Bridge.
static constexpr uint16_t kHuePort = 80;

// The mappings between touch sensors and Hue lamps. The index is the touch
// sensor, the value is the Hue lamp ID. Use 0 for unused sensors.
static constexpr uint16_t kTouchMappings[] = {
  7,
  6,
};

// The username to use when communicating with the hue API.
static constexpr char kHueUsername[] = "FILL ME IN";

// Webserver settings
// -----------------------------------------------------------------------------

// The port to listen on.
static constexpr uint16_t kWebserverPort= 80;

// The name to use in DNS-SD.
static constexpr char kNodeName[] = "hue-touch-controller";

// Touch Sensor settings
// -----------------------------------------------------------------------------

// The I2C address of the touch sensor.
static constexpr uint8_t kTouchAddress = 0x29;

// The pin to use to reset the sensor.
static constexpr int8_t kTouchResetPin = 2;

// The delay for touch debouncing.
static constexpr unsigned long kDebounceDelayMs = 50;

// Serial Port settings
// -----------------------------------------------------------------------------

// The serial port speed.
static constexpr int kBaudRate = 115200;

#endif // CONSTANTS_H
