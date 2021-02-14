#include "MentorESP32MQTT.h"

WiFiClient espClient;
PubSubClient client(espClient);

MentorESP32MQTT::MentorESP32MQTT(String accessKey) {
    _accessKey = accessKey;
}

void MentorESP32MQTT::setMqttServer() {
    if(WiFi.status() != WL_CONNECTED) {
        printDebug("[MENTOR] Unable to connect to MQTT server.\n");
    }
    else {
        printDebug("[MENTOR] Setting MQTT server \"" + String(_mqttServer) + "\" on port " + String(_mqttPort) + "\n");
        client.setServer(_mqttServer, _mqttPort);
    }

}

void MentorESP32MQTT::checkMqttConnection() {
    // _subscriptionTopic = "mentor/" + _accessKey + "/" + serviceName + "/" + deviceName ;

    if(!client.connected()) {
        while(!client.connected()) {
            printDebug("[MENTOR] Attempting MQTT connection...\n");

            String clientId = "ESP32-" + _accessKey;

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

void MentorESP32MQTT::subscribe(String serviceName, String deviceName) {
    _subscriptionTopic = "mentor/" + _accessKey + "/" + serviceName + "/" + deviceName ;

    if(!client.connected()) {
        while(!client.connected()) {
            printDebug("[MENTOR] Attempting MQTT connection...\n");

            String clientId = "ESP32-" + _accessKey;

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

bool MentorESP32MQTT::wifiConnection(String SSID, String wifiPassword) {
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

void MentorESP32MQTT::add(String key, int value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    _jsonDataString = newInsert;
}

void MentorESP32MQTT::add(String key, float value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    _jsonDataString = newInsert;
}

void MentorESP32MQTT::add(String key, double value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    _jsonDataString = newInsert;
}

void MentorESP32MQTT::add(String key, String value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonDataString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    _jsonDataString = newInsert;
}

void MentorESP32MQTT::printData() {
    printDebug("[MENTOR] " + _jsonDataString + "\n");
}

void MentorESP32MQTT::printDebug(String text) {
    if(_debug) {
        Serial.print(text);
    }
}

void MentorESP32MQTT::publish(String serviceName, String deviceName) {
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

int MentorESP32MQTT::getInt(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonSubDataString);
    return object[key];
}

float MentorESP32MQTT::getFloat(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonSubDataString);
    return object[key];
}

double MentorESP32MQTT::getDouble(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonSubDataString);
    return object[key];
}

String MentorESP32MQTT::getString(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(_jsonSubDataString);
    return object[key];
}

void MentorESP32MQTT::setCallback(std::function<void(char*, uint8_t*, unsigned int)> callbackFunc) {
    client.setCallback(callbackFunc);
}

bool MentorESP32MQTT::setDebug(bool trueFalse) {
    _debug = trueFalse;
}

String MentorESP32MQTT::get(char* topic, byte* payload, unsigned int length) {
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

String MentorESP32MQTT::getTopic() {
    return _receivedTopic;
}

String MentorESP32MQTT::getPayload() {
    return _jsonSubDataString;
}

String MentorESP32MQTT::ipToString(IPAddress ip) {
    String s="";
    for (int i=0; i<4; i++)
      s += i  ? "." + String(ip[i]) : String(ip[i]);
    return s;
}


