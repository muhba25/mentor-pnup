/*
    This is an example sketch to publish MQTT data to your
    Mentor IoT Platform project device via ESP8266.

    MQTT server & port:
    platform.mentor.id, port 1338

    MQTT topic:
    /oneM2M/req/your-access-key/mentor-cse/json

    This sketch will deploy data to your Mentor device
    and publish to the MQTT topic simultaneously.

    For more information, please visit https://mentor.id/id/docs.html
*/

#include <MentorESP8266MQTT.h>

#define ACCESSKEY "your-acces-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define serviceName "your-serviceName"
#define deviceName "your-deviceName"

MentorESP8266MQTT mentor(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  mentor.setDebug(true);
  mentor.wifiConnection(WIFISSID, PASSWORD);
  mentor.setMqttServer();
}

void loop() {
  /*
    Check if we're still connected to the MQTT broker/server.
    If disconnected, the device will try to reconnect.
   */
  mentor.checkMqttConnection();

  // Variable init
  int temp = random(25,30) ;
  int hum = random(75,90);
  float windsp = float(random(20, 30))/3.33;
  float rainlv = float(random(0, 20))/6.99;
  String lat = "-6.8718189";
  String lon = "107.5872477";

  // Add variable to data storage buffer
  antares.add("temperature", temp);
  antares.add("humidity", hum);
  antares.add("wind_speed", windsp);
  antares.add("rain_level", rainlv);
  antares.add("latitude", lat);
  antares.add("longitude", lon);

  // Publish and print data
  mentor.publish(serviceName, deviceName);
  delay(5000);
}
