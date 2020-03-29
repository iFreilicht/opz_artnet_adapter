/*
 *  Settings to adjust to your local setup.
 */

// WiFi credentials for the WiFi you want to connect to.
char ssid[]     = "my_wifi_ssid";
const char* password = "my_wifi_password";

// Artnet settings.
// Do NOT use universe 0, that will fail silently in most cases
const int universe = 1;
// Set this to the IP or hostname you want to send to,
// or the broadcast adress of your network.
// See https://en.wikipedia.org/wiki/Broadcast_address#IP_networking
const char* host = "192.168.1.255";
