/*
  This code will fetches all data from your Mentor project device.
  For more information visit hhttps://mentor.poliupg.ac.id/documentation.html
*/

#include "MentorESP8266HTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define serviceName "your-project-name"
#define deviceName "your-device-name"

MentorESP8266HTTP mentor(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  mentor.setDebug(true);
  mentor.wifiConnection(WIFISSID,PASSWORD);
  /* Use wifiConnectionNonSecure instead if you don't want to use HTTPS
   * and avoid SNTP matching */
  //mentor.wifiConnectionNonSecure(WIFISSID,PASSWORD);

}

void loop() {
  Serial.println(mentor.retrieveAllData(serviceName, deviceName));
  delay(10000);
}
