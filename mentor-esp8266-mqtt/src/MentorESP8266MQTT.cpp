#include "MentorESP8266MQTT.h"

WiFiClient espClient;
PubSubClient client(espClient);

MentorESP8266MQTT::MentorESP8266MQTT(String accessKey) {
    _accessKey = accessKey;
}

void MentorESP8266MQTT::setMqttServer() {
    if(WiFi.status() != WL_CONNECTED) {
        printDebug("[MENTOR] Unable to connect to MQTT server.\n");
    }
    else {
        printDebug("[MENTOR] Setting MQTT server \"" + String(_mqttServer) + "\" on port " + String(_mqttPort) + "\n");
        client.setServer(_mqttServer, _mqttPort);
    }

}

void MentorESP8266MQTT::checkMqttConnection() {
    // _subscriptionTopic = "mentor/" + _accessKey + "/" + serviceName + "/" + deviceName ;

    if(!client.connected()) {
        while(!client.connected()) {
            printDebug("[MENTOR] Attempting MQTT connection...\n");

            String clientId = "ESP8266-" + _accessKey;

            char clientIdChar[clientId.length() + 1];
            clientId.toCharArray(clientIdChar, clientId.length() + 1);

            if(client.connect(clientIdChar)) {
                printDebug("[MENTOR] Connected! Client ID:");
                printDebug(clientIdChar);
                printDebug("\n");
				// if(_subscriptionTopic!=""){
                // char subscriptionTopicChar[_subscriptionTopic.length() + 1];
                // _subscriptionTopic.toCharArray(subscriptionTopicChar, _subscriptionTopic.length() + 1);

                // client.publish(subscriptionTopicChar, "connect!");
				// Serial.println(subscriptionTopicChar);
                // client.subscribe(subscriptionTopicChar);
				// }
            }
            else {
                printDebug("[MENTOR] Failed, rc=" + String(client.state()) + ", Will try again in 5 secs.\n");
                delay(5000);
            }
        }
    }
    client.loop();
}

void MentorESP8266MQTT::subscribe(String serviceName, String deviceName) {
    _subscriptionTopic = "mentor/" + _accessKey + "/" + serviceName + "/" + deviceName ;

    if(!client.connected()) {
        while(!client.connected()) {
            printDebug("[MENTOR] Attempting MQTT connection...\n");

            String clientId = "ESP8266-" + _accessKey;

            char clientIdChar[clientId.length() + 1];
            clientId.toCharArray(clientIdChar, clientId.length() + 1);

            if(client.connect(clientIdChar)) {
                char subscriptionTopicChar[_subscriptionTopic.length() + 1];
                _subscriptionTopic.toCharArray(subscriptionTopicChar, _subscriptionTopic.length() + 1);

                // client.publish(subscriptionTopicChar, "connect!");
				Serial.println(subscriptionTopicChar);
                client.subscribe(subscriptionTopicChar);
            }
            else {
                printDebug("[MENTOR] Failed, rc=" + String(client.state()) + ", Will try again in 5 secs.\n");
                delay(5000);
            }
        }
    }
    client.loop();
}

bool MentorESP8266MQTT::wifiConnection(String SSID, String wifiPassword) {
    char ssidChar[sizeof(SSID)];
    char wifiPasswordChar[sizeof(wifiPassword)];

    SSID.toCharArray(ssidChar, sizeof(SSID));
    wifiPassword.toCharArray(wifiPasswordChar, sizeof(wifiPassword));

    int count = 0;
    _wifiSSID = ssidChar;
    _wifiPass = wifiPasswordChar;

    WiFi.begin(_wifiSSID, _wifiPass);
    printDebug("[MENTOR] Trying to connect to " + SSID + "...\n");

    for (count=0;count<20;count++)
    {
      delay(500);
      printDebug(".");
    }

    if(WiFi.status() != WL_CONNECTED) {
        printDebug("[MENTOR] Could not connect to " + SSID + ".\n");
        return false;
    }
    else {
        WiFi.setAutoReconnect(true);
        printDebug("\n[MENTOR] WiFi Connected!\n");
        printDebug("[MENTOR] IP Address: " + ipToString(WiFi.localIP()) + "\n");
        return true;
    }
}

void MentorESP8266MQTT::add(String key, int value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    _jsonDataString = newInsert;
}

void MentorESP8266MQTT::add(String key, float value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    _jsonDataString = newInsert;
}

void MentorESP8266MQTT::add(String key, double value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    _jsonDataString = newInsert;
}

void MentorESP8266MQTT::add(String key, String value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    _jsonDataString = newInsert;
}

void MentorESP8266MQTT::printData() {
    printDebug("[MENTOR] " + _jsonDataString + "\n");
}

void MentorESP8266MQTT::printDebug(String text) {
    if(_debug) {
        Serial.print(text);
    }
}

void MentorESP8266MQTT::publish(String serviceName, String deviceName) {
    String topic = "mentor/" + _accessKey + "/" + serviceName + "/" + deviceName;
    String finalData;

    if(_debug) {
		Serial.println();
        Serial.print("[MENTOR] Topic: ");
        Serial.println(topic);
				
        DynamicJsonBuffer jsonBuffer;
        JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
        printDebug("[MENTOR] PUBLISH DATA:\n\n");
        object.prettyPrintTo(Serial);
        Serial.println("\n");
    }

    // _jsonDataString.replace("\"", "\\\"");


    // finalData += "{";
    // finalData += "\"m2m:rqp\": {";
    // finalData += "\"fr\": \"" + _accessKey +"\",";
    // finalData += "\"to\": \"/mentor-cse/mentor-id/" + serviceName + "/" + deviceName + "\",";
    // finalData += "\"op\": 1,";
    // finalData += "\"rqi\": 123456,";
    // finalData += "\"pc\": {";
    // finalData += "\"m2m:cin\": {";
    // finalData += "\"cnf\": \"message\",";
    // finalData += "\"con\": \""+ _jsonDataString + "\"";
    // finalData += "}";
    // finalData += "},";
    // finalData += "\"ty\": 4";
    // finalData += "}";
    // finalData += "}";
	finalData += _jsonDataString;

    // DynamicJsonBuffer jsonBuffer;
    // JsonObject& object = jsonBuffer.parseObject(finalData);
    // object.prettyPrintTo(Serial);

    char finalDataChar[finalData.length() + 1];
    char topicChar[topic.length() + 1];

    finalData.toCharArray(finalDataChar, finalData.length() + 1);
    topic.toCharArray(topicChar, topic.length() + 1);

    _jsonDataString = "{}";

    client.publish(topicChar, finalDataChar);
}

int MentorESP8266MQTT::getInt(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonSubDataString);
    return object[key];
}

float MentorESP8266MQTT::getFloat(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonSubDataString);
    return object[key];
}

double MentorESP8266MQTT::getDouble(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonSubDataString);
    return object[key];
}

String MentorESP8266MQTT::getString(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonSubDataString);
    return object[key];
}

void MentorESP8266MQTT::setCallback(std::function<void(char*, uint8_t*, unsigned int)> callbackFunc) {
    client.setCallback(callbackFunc);
}

bool MentorESP8266MQTT::setDebug(bool trueFalse) {
    _debug = trueFalse;
}

String MentorESP8266MQTT::get(char* topic, byte* payload, unsigned int length) {
    _receivedTopic = String(topic);

    String payloadString;
    for(int i = 0; i < length; i++) {
        payloadString += char(payload[i]);
    }

    // DynamicJsonBuffer jsonBuffer;
    // JsonObject& object = jsonBuffer.parseObject(payloadString);
    // String parsedString = object["m2m:rqp"]["pc"]["m2m:cin"]["con"];
	String parsedString = payloadString;
    _jsonSubDataString = parsedString;

    return _jsonSubDataString;
}

String MentorESP8266MQTT::getTopic() {
    return _receivedTopic;
}

String MentorESP8266MQTT::getPayload() {
    return _jsonSubDataString;
}

String MentorESP8266MQTT::ipToString(IPAddress ip) {
    String s="";
    for (int i=0; i<4; i++)
      s += i  ? "." + String(ip[i]) : String(ip[i]);
    return s;
}


