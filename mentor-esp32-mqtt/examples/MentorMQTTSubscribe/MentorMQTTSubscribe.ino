/*
    This is an example sketch to subscribe to MQTT data on ESP8266
    via the Mentor IoT Platform.

    MQTT server & port:
    platform.mentor.id, port 1338

    MQTT topic:
    /oneM2M/req/your-access-key/mentor-cse/json

    The main function in this sketch is the callback function,
    which will be fired every time a new message is published
    to the topic.

    For more information, please visit https://mentor.id/id/docs.html
*/

#include <MentorESP8266MQTT.h>

#define ACCESSKEY "your-acces-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define serviceName "your-serviceName"
#define deviceName "your-deviceName"

MentorESP8266MQTT mentor(ACCESSKEY);

void callback(char topic[], byte payload[], unsigned int length) {
  /*
    Get the whole received data, including the topic,
    and parse the data according to the Mentor data format.
  */
  mentor.get(topic, payload, length);

  Serial.println("New Message!");
  // Print topic and payload
  Serial.println("Topic: " + mentor.getTopic());
  Serial.println("Payload: " + mentor.getPayload());
  // Print individual data
  Serial.println("Temperature: " + String(mentor.getInt("temperature")));
}

void setup() {
  Serial.begin(115200);
  mentor.setDebug(true);
  mentor.wifiConnection(WIFISSID, PASSWORD);
  mentor.setMqttServer();
  mentor.setCallback(callback);
}
void loop() {
  /*
    Check if we're still connected to the MQTT broker/server.
    If disconnected, the device will try to reconnect.
  */
  
  mentor.subscribe(serviceName,deviceName);
  
}
