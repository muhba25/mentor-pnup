/*
  This code will fetch the latest data from your mentor project device.
  Your Mentor project device must have a structure like this:
  (Note that nesting the JSON object can only be done up to 2 levels using this library)
  {
    "temperature": some-integer,
    "humidity": some-integer,
    "wind_speed": some-float,
    "rain_level": some-float,
    "location" : {
      "latitude": "static-string",
      "longitude": "static-string"
    }
  }
  For more information please visit https://mentor.poliupg.ac.id/documentation.html
*/

#include "MentorESP8266HTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-ssid-wifi"
#define PASSWORD "your-password-wifi"

#define serviceName "your-serviceName"
#define deviceName "your-deviceNamw"

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
  mentor.get(serviceName, deviceName); // Store latest value in buffer
  /*
    Uncomment the line below to use HTTP instead of HTTPS.
    Will be faster, but less secure
  */
  // mentor.getNonSecure(projectName, deviceName);

 //  Check if we're actually getting data
 if(mentor.getSuccess()) {
   // Get each values
   int temp = mentor.getInt("temperature");
   int hum = mentor.getInt("humidity");
   float windsp = mentor.getFloat("wind_speed");
   float rainlv = mentor.getFloat("rain_level");
   String lat = mentor.getString("location", "latitude");
   String lon = mentor.getString("location", "longitude");

   // Print each values
   Serial.println("Temperature: " + String(temp));
   Serial.println("Humidity: " + String(hum));
   Serial.println("Wind speed: " + String(windsp));
   Serial.println("Rain level: " + String(rainlv));
   Serial.println("Latitude: " + lat);
   Serial.println("Longitude: " + lon);
 }
 delay(100);
}
