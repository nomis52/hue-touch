# An ESP8266 touch sensor to control Phillips Hue lights.

I created this so that I could use our touch lamps with the Phillips Hue
lighting.

Features:
 - 8 touch sensors can be configured to trigger [Generic IP Sensors](https://www.developers.meethue.com/documentation/how-use-ip-sensors)
 - HTTP interface to check the status, discoverable via DNS-SD.
 - Upgradable over Wifi

## Hardware

- [ESP8266](https://www.adafruit.com/product/2821)
- [CAP1188](https://www.adafruit.com/product/1602)

## Installation & Setup

- Install the Arduino IDE
- Open the sketch in the IDE.
- In `constants.h` configure the SSID, password, address of the hue bridge the
  mappings of touch sensor to Hue sensor ID.
- Select the USB port from Tools -> Port, then Sketch -> Upload.                                                                                                                                                                                     

To update the firmware later using OTA:

- Select the OTA port from Tools -> Port
- Compile & upload as normal.

# LED Status

| State      | Meaning                           |
|------------|-----------------------------------|
| Off        | Not connected to Wifi             |
| Blinking   | Missing CAP1188 Sensor            |
| On         | Connected and waiting for events  |

# Opening the Web UI

The web UI is discoverable via [DNS-SD](http://www.dns-sd.org/). For Mac I
recommend [Bonjour Browser](http://www.tildesoft.com/).

You can restart the ESP2866 from the web by loading `/restart`.
