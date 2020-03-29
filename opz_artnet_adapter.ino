/*
 *  Adapter of OP-Z to Artnet via WiFi.
 *
 *  This has to be run on an ESP8266 (I recommend the ESP-01 module)
 *  with an FTDI232 as the USB-to-serial converter.
 */

#include <ArtnetWifi.h>
#include <DMXUSB.h>
#include <ESP8266WiFi.h>

// Modify the settings headers to fit your setup
#include "artnet_settings.h"
#include "dmx/16_led_strip/settings.h"

ArtnetWifi artnet;

// Callback on incoming DMX packet
void dmxCallback(int universe, char buffer[512]) {
  // Get value for each channel
  for (int i = 0; i < num_channels; i++) {
    int channel = i;
    int value = buffer[i];
    artnet.setByte(channel, value);
  }
  // send out the Art-Net DMX data
  artnet.write();
}

// Initialise DMX
DMXUSB dmxUsb(Serial, baud_rate, 0, dmxCallback);

void setup() {
  Serial.begin(baud_rate);
  delay(10);

  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Connect to Artnet host
  artnet.begin(host);
  artnet.setLength(num_channels);
  artnet.setUniverse(universe);
}

void loop() {
  dmxUsb.listen();
  // Sleep to reduce power consumption
  // This is necessary, otherwise the OP-Z will refuse to provide power
  delay(40);
}
