/*
 *  Settings to adjust to your local setup.
 */

// WiFi credentials for the WiFi you want to connect to.
char ssid[]     = "my_wifi_ssid";
const char* password = "my_wifi_password";

// Artnet settings.
// Do NOT use universe 0, that will fail silently in most cases
const int universe = 1;
const char* host = "0.0.0.0";
