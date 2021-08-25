// code by techtutorialsx - source:
// https://techtutorialsx.com/2017/06/29/esp32-arduino-getting-started-with-wifi/

#include <WiFi.h>

// SSID and password of Wifi connection:
const char* ssid = "TYPE_YOUR_SSID_HERE";
const char* password = "TYPE_YOUR_PASSWORD_HERE";

// simple function to decipher the encryption type of a network
String translateEncryptionType(wifi_auth_mode_t encryptionType) { 
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}

// Function to scan and print all networks that can be detected by the ESP32 
void scanNetworks() {
  int numberOfNetworks = WiFi.scanNetworks();
 
  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
 
    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));
 
    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------"); 
  }
}

// function to connect to a Wifi network -> note that there is no time-out function on this
void connectToNetwork() {
  WiFi.begin(ssid, password);
  Serial.println("Establishing connection to WiFi.");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to network");
}
 
void setup() {
  Serial.begin(115200);                 // initiate local communication to PC
 
  scanNetworks();                       // scan for all WiFi networks
  connectToNetwork();                   // try to connect to SSID defined by user
 
  Serial.println(WiFi.macAddress());    // print MAC address of WiFi interface
  Serial.println(WiFi.localIP());       // print IP address of WiFi interface
}
 
void loop() {}
// not used in this example
