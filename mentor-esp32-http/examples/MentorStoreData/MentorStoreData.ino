/*
  This code will deploy data to your Mentor project device with the following structure:
  (Note that nesting the JSON object can only be done up to 2 levels using this library)
  {
    "temperature": random-int,
    "humidity": random-int,
    "wind_speed": random-float,
    "rain_level": random-float,
    "location" : {
      "latitude": "static-string",
      "longitude": "static-string"
    }
  }
  For more information please visit https://mentor.poliupg.ac.id/documentation.html
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
  // Variables
  int temp = random(25,30) ;
  int hum = random(75,90);
  float windsp = float(random(20, 30))/3.33;
  float rainlv = float(random(0, 20))/6.99;
  String lat = "-6.8718189";
  String lon = "107.5872477";

  // Add variable data to storage buffer
  mentor.add("temperature", temp);
  mentor.add("humidity", hum);
  mentor.add("wind_speed", windsp);
  mentor.add("rain_level", rainlv);
  mentor.add("location", "latitude", lat);
  mentor.add("location", "longitude", lon);

  // Send from buffer to Mentor
  mentor.send(serviceName, deviceName);
  /*
    Uncomment the line below to use HTTP instead of HTTPS.
    Will be faster, but less secure
  */
  // mentor.sendNonSecure(serviceName, deviceName); 
  delay(10000);
}
