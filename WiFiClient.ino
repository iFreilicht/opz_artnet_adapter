/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <ArtnetWifi.h>
#include <DMXUSB.h>

// Wifi settings
const char* ssid     = "my_wifi_ssid";
const char* password = "my_wifi_password";

// Artnet settings
ArtnetWifi artnet;
const int universe = 1;
const char* host = "0.0.0.0";

// DMX settings
const int num_channels_per_fixture = 3;
const int num_fixtures = 16;
const int num_channels = num_fixtures * num_channels_per_fixture;
const int baud_rate = 115200;

// I2C settings
const int slave_address = 1;

// Callback on incoming DMX packet
void dmxCallback(int universe, char buffer[512]){
  // Get value for each channel
  for (int i = 0 ; i < num_channels; i++) {
    // channels start at 1
    int channel = i;
    int value = buffer[i];
    artnet.setByte(channel, value);
  }
  // send out the Art-Net DMX data
  artnet.write();
}

// Initialise DMX
DMXUSB dmxUsb(Serial2, baud_rate, 1, dmxCallback);

void setup()
{
  Serial2.begin(baud_rate);
  Serial.begin(baud_rate);
  delay(10);

  // Connect to WiFi network
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
  }

  Serial.write("WiFi connected.\n");

  // Connect to Artnet host
  artnet.begin(host);
  artnet.setLength(num_channels);
  artnet.setUniverse(universe);
  Serial.write("ArtNet initialized.\n");
}

void loop()
{
  dmxUsb.listen();
  delay(40);
}

