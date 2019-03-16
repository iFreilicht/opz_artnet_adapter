/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <ArtnetWifi.h>

// Wifi settings
const char* ssid     = "my_wifi_ssid";
const char* password = "my_wifi_password";

// Artnet settings
ArtnetWifi artnet;
const int universe = 1;
const char* host = "0.0.0.0";

void setup()
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  artnet.begin(host);
  artnet.setLength(3);
  artnet.setUniverse(universe);
}

int value = 0;

void loop()
{
  uint8_t i;
  uint8_t j;

  // set the first 3 byte to all the same value. A RGB lamp will show a ramp-up white.
  for (j = 0; j < 255; j++) {
    for (i = 0; i < 3; i++) {
      artnet.setByte(i, j);
    }
    // send out the Art-Net DMX data
    artnet.write();
    Serial.println(j);
    delay(100);
  }
}

