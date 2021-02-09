/*
    MQTT server & port:
    118.98.121.229, port 32575
    
    MQTT topic:
    /mentor/your-access-key/serviceName/deviceName
    
    This sketch will deploy data to your Mentor device
    and publish to the MQTT topic simultaneously.
    
    For more information, please visit https://mentor.poliupg.ac.id/documentation.html
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
  Serial.println("Humidity: " + String(antares.getInt("humidity")));
  Serial.println("Wind speed: " + String(antares.getFloat("wind_speed")));
  Serial.println("Rain level: " + String(antares.getFloat("rain_level")));
  Serial.println("Latitude: " + antares.getString("latitude"));
  Serial.println("Longitude: " + antares.getString("longitude"));
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
