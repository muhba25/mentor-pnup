#include "MentorESP32HTTP.h"

MentorESP32HTTP::MentorESP32HTTP(String accessKey) {
    _accessKey = accessKey;
}


// Overloadded function: String
void MentorESP32HTTP::add(String key, String value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

// Overloadded function: int
void MentorESP32HTTP::add(String key, int value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

// Overloadded function: float
void MentorESP32HTTP::add(String key, float value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

// Overloadded function: double
void MentorESP32HTTP::add(String key, double value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

// 2-level nested json start

// Overloadded function: String
void MentorESP32HTTP::add(String key, String key2, String value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

// Overloadded function: int
void MentorESP32HTTP::add(String key, String key2, int value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

// Overloadded function: float
void MentorESP32HTTP::add(String key, String key2, float value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

// Overloadded function: double
void MentorESP32HTTP::add(String key, String key2, double value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

void MentorESP32HTTP::printData() {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& sendObject = jsonBuffer.parseObject(jsonString);
    JsonObject& getObject = jsonBuffer.parseObject(jsonGetString);
    printDebug("\n\n[MENTOR] Data to send: \n\n");
    sendObject.prettyPrintTo(Serial);
    printDebug("\n\n[MENTOR] Data available to get: \n\n");
    getObject.prettyPrintTo(Serial);
}

void MentorESP32HTTP::get(String serviceName, String deviceName) {
    WiFiClientSecure client;
    _getSuccess = false;
    jsonGetString = "";
    // Load root certificate in DER format into WiFiClientSecure object
    
    client.setCACert(test_root_ca);


    // Connect to remote server
    printDebug("[MENTOR] connecting to " + String(_serverNoHttp) + "\n");
    const int httpPort = 8443;
    if (!client.connect(_serverNoHttp, httpPort)) {
        printDebug("[MENTOR] connection failed\n");
        return;
    }


    String url = "/sensors/"+ serviceName +"/" + deviceName + "/last";
    printDebug("[MENTOR] requesting URL: " + url + "\n");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "token: " + _accessKey + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("[MENTOR] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[MENTOR] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    while (client.connected()) {
        String line = "";
        while(client.read() != '{');
        line += "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        // JsonObject& payloadJson = jsonBuffer.parseObject(line);
        // String dataString = payloadJson["m2m:cin"]["con"];
        JsonObject& jsonGetPool = jsonBuffer.parseObject(line);
        jsonGetPool.printTo(jsonGetString);

        if(_debug) {
            jsonGetPool.prettyPrintTo(Serial);
            printDebug("\n");
        }
    }
    _getSuccess = true;
}

String MentorESP32HTTP::getRaw(String serviceName, String deviceName) {
    WiFiClientSecure client;
    _getSuccess = false;
    jsonGetString = "";
    // Load root certificate in DER format into WiFiClientSecure object
    
    client.setCACert(test_root_ca);


    // Connect to remote server
    printDebug("[MENTOR] connecting to " + String(_serverNoHttp) + "\n");
    const int httpPort = 8443;
    if (!client.connect(_serverNoHttp, httpPort)) {
        printDebug("[MENTOR] connection failed\n");
        return "Conn failed";
    }


    String url = "/sensors/"+ serviceName +"/" + deviceName + "/last";
    printDebug("[MENTOR] requesting URL: " + url + "\n");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "token: " + _accessKey + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Accept: application/json\r\n" +
    //               "User-Agent: BuildFailureDetectorESP32\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("[MENTOR] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[MENTOR] Client Timeout !\n");
            client.stop();
            return "Could not GET";
        }
    }

    String returnPayload = "";
    while (client.connected()) {
        String line = "";
        while(client.read() != '{');
        line += "{";
        line += client.readStringUntil('\r');
        // DynamicJsonBuffer jsonBuffer;
        // JsonObject& payloadJson = jsonBuffer.parseObject(line);
        // String dataString = payloadJson["m2m:cin"]["con"];
		// String dataString = payloadJson;
        returnPayload = line;
    }
    _getSuccess = true;
    return returnPayload;
}

String MentorESP32HTTP::getRawNonSecure(String serviceName, String deviceName) {
    WiFiClient client;
    _getSuccess = false;
    jsonGetString = "";

    // Connect to remote server
    printDebug("[MENTOR] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect(_serverNoHttp, _portNum)) {
        printDebug("[MENTOR] connection failed\n");
        return "Conn failed";
    }

    String url = "/sensors/"+ serviceName +"/" + deviceName + "/last";
    printDebug("[MENTOR] requesting URL: " + url + "\n");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "token: " + _accessKey + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Accept: application/json\r\n" +
    //               "User-Agent: BuildFailureDetectorESP32\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("[MENTOR] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[MENTOR] Client Timeout !\n");
            client.stop();
            return "Could not GET";
        }
    }

    String returnPayload = "";
    while (client.connected()) {
        String line = "";
        while(client.read() != '{');
        line += "{";
        line += client.readStringUntil('\r');
        // DynamicJsonBuffer jsonBuffer;
        // JsonObject& payloadJson = jsonBuffer.parseObject(line);
        // String dataString = payloadJson;
        returnPayload = line;
    }
    _getSuccess = true;
    return returnPayload;
}

void MentorESP32HTTP::getNonSecure(String serviceName, String deviceName) {
    WiFiClient client;
    _getSuccess = false;
    jsonGetString = "";
    // Connect to remote server
    printDebug("[MENTOR] connecting to " + String(_serverNoHttp) + "\n");
    const int httpPort = 8080;
	if (!client.connect(_serverNoHttp, httpPort)) {
        printDebug("[MENTOR] connection failed\n");
        return;
    }

    String url = "/sensors/"+ serviceName +"/" + deviceName + "/last";
    printDebug("[MENTOR] requesting URL: " + url + "\n");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "token: " + _accessKey + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("[MENTOR] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[MENTOR] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    while (client.connected()) {
        String line = "";
        while(client.read() != '{');
        line += "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& jsonGetPool = jsonBuffer.parseObject(line);
        jsonGetPool.printTo(jsonGetString);

        if(_debug) {
            jsonGetPool.prettyPrintTo(Serial);
            printDebug("\n");
        }
    }
    _getSuccess = true;
}

void MentorESP32HTTP::send(String serviceName, String deviceName) {
    WiFiClientSecure client;
    // Load root certificate in DER format into WiFiClientSecure object
    client.setCACert(test_root_ca);


    // Connect to remote server
    printDebug("[MENTOR] connecting to " + String(_serverNoHttp) + "\n");
	const int httpPort = 8443;
    if (!client.connect(_serverNoHttp, httpPort)) {
        printDebug("[MENTOR] connection failed\n");
        return;
    }


    String url = "/sensors/"+ serviceName +"/" + deviceName;
    printDebug("[MENTOR] requesting URL: " + url + "\n");

    // jsonString.replace("\"", "\\\"");

    // Create JSON with Mentor format
    String body;
	body += jsonString;
    // body += "{";
    // body += "\"m2m:cin\":{";
    // body += "\"con\":\"" + jsonString + "\"";
    // body += "}";
    // body += "}";

    const uint16_t bodyLength = body.length();
	
	
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "token: " + _accessKey + "\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " + String(bodyLength) + "\r\n\r\n" +
               body
           );

    Serial.println("[MENTOR] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[MENTOR] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // while (client.connected()) {
        // String line = client.readStringUntil('\r');
        // printDebug(line + "\n");
		// printDebug("Send Data Success\n");
    // }
    jsonString = "{}";
    _currentKey = "";
}

void MentorESP32HTTP::sendRaw(String text, String serviceName, String deviceName) {
    WiFiClientSecure client;
    // Load root certificate in DER format into WiFiClientSecure object
   client.setCACert(test_root_ca);

    

    // Connect to remote server
    printDebug("[MENTOR] connecting to " + String(_serverNoHttp) + "\n");
    const int httpPort = 8443;
    if (!client.connect(_serverNoHttp, httpPort)) {
        printDebug("[MENTOR] connection failed\n");
        return;
    }


    String url = "/sensors/"+ serviceName +"/" + deviceName;
    printDebug("[MENTOR] requesting URL: " + url + "\n");

    // Create JSON with Mentor format
    String body;
    body += "{";
    // body += "\"m2m:cin\":{";
    body += "\"text\":\"" + text + "\"";
    // body += "}";
    body += "}";

    const uint16_t bodyLength = body.length();

    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "token: " + _accessKey + "\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " + String(bodyLength) + "\r\n\r\n" +
               body
           );

    Serial.println("[MENTOR] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[MENTOR] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // while (client.connected()) {
        // String line = client.readStringUntil('\r');
        // printDebug(line + "\n");
		// printDebug("Send Data Success\n");
    // }
}

void MentorESP32HTTP::sendRawNonSecure(String text, String serviceName, String deviceName) {
    WiFiClient client;

    // Connect to remote server
    printDebug("[MENTOR] connecting to " + String(_serverNoHttp) + "\n");
    const int httpPort = 8080;
    if (!client.connect(_serverNoHttp, httpPort)) {
        printDebug("[MENTOR] connection failed\n");
        return;
    }

    String url = "/sensors/"+ serviceName +"/" + deviceName;
    printDebug("[MENTOR] requesting URL: " + url + "\n");

    // Create JSON with Mentor format
    String body;
    body += "{";
    // body += "\"m2m:cin\":{";
    body += "\"text\":\"" + text + "\"";
    // body += "}";
    body += "}";

    const uint16_t bodyLength = body.length();

    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "token: " + _accessKey + "\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " + String(bodyLength) + "\r\n\r\n" +
               body
           );

    Serial.println("[MENTOR] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[MENTOR] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // while (client.connected()) {
        // String line = client.readStringUntil('\r');
        // printDebug(line + "\n");
		// printDebug("Send Data Success\n");
    // }
}

void MentorESP32HTTP::sendNonSecure(String serviceName, String deviceName) {
    WiFiClient client;

    // Connect to remote server
    printDebug("[MENTOR] connecting to " + String(_serverNoHttp) + "\n");
    const int httpPort = 8080;
    if (!client.connect(_serverNoHttp, httpPort)) {
        printDebug("[MENTOR] connection failed\n");
        return;
    }

    String url = "/sensors/"+ serviceName +"/" + deviceName;
    printDebug("[MENTOR] requesting URL: " + url + "\n");

    // jsonString.replace("\"", "\\\"");

    // Create JSON with Mentor format
    String body;
	body += jsonString ;
    // body += "{";
    // body += "\"m2m:cin\":{";
    // body += "\"con\":\"" + jsonString + "\"";
    // body += "}";
    // body += "}";

    const uint16_t bodyLength = body.length();

    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "token: " + _accessKey + "\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " + String(bodyLength) + "\r\n\r\n" +
               body
           );

    Serial.println("[MENTOR] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[MENTOR] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // while (client.connected()) {
        // String line = client.readStringUntil('\r');
        // printDebug(line + "\n");
		// printDebug("Send Data Success\n");
    // }
    jsonString = "{}";
}

bool MentorESP32HTTP::getSuccess() {
    return _getSuccess;
}


String MentorESP32HTTP::getString(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key];
    return value;
}

String MentorESP32HTTP::getString(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key][key2];
    return value;
}

int MentorESP32HTTP::getInt(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key];
    return value;
}

int MentorESP32HTTP::getInt(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key][key2];
    return value;
}

float MentorESP32HTTP::getFloat(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key];
    return value;
}

float MentorESP32HTTP::getFloat(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key][key2];
    return value;
}

double MentorESP32HTTP::getDouble(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key];
    return value;
}

double MentorESP32HTTP::getDouble(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key][key2];
    return value;
}

bool MentorESP32HTTP::wifiConnection(String SSID, String wifiPassword) {
    char ssidChar[sizeof(SSID)];
    char wifiPasswordChar[sizeof(SSID)];

    SSID.toCharArray(ssidChar, sizeof(SSID));
    wifiPassword.toCharArray(wifiPasswordChar, sizeof(wifiPassword));

    int count=0;
    _wifiSSID = ssidChar;
    _wifiPass = wifiPasswordChar;

    WiFi.begin(_wifiSSID, _wifiPass);
    printDebug("[MENTOR] Trying to connect to " + SSID + "...\n");

    // for (count=0;count<20;count++) {
    //     delay(500);
    //     printDebug(".");
    // }

    int counter = 0;
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        printDebug(".");
        counter++;
        if(counter >= 10) {
            counter = 0;
            printDebug("[MENTOR] Could not connect to " + SSID + "! Retrying...\n");
        }
    }

    WiFi.setAutoReconnect(true);
    printDebug("\n[MENTOR] WiFi Connected!\n");
    printDebug("[MENTOR] IP Address: " + ipToString(WiFi.localIP()) + "\n");

    delay(1000);
    printDebug("[MENTOR] Setting time using SNTP\n");
    configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    time_t now = time(nullptr);

    while (now < 8 * 3600 * 2) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    printDebug("\n");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    printDebug("Current time: ");
    printDebug(String(asctime(&timeinfo)));

    return true;
}


bool MentorESP32HTTP::checkWifiConnection() {
    if(WiFi.status() != WL_CONNECTED) {
        printDebug("[MENTOR] WIFI RECONNECT...");
        return wifiConnection(_wifiSSID, _wifiPass);
    }
}

void MentorESP32HTTP::setDebug(bool trueFalse){
    _debug = trueFalse;
}

void MentorESP32HTTP::setServer(String domain, String port){
    _server = domain;
    _port = port;
}

void MentorESP32HTTP::printDebug(String text){
    if (_debug)
        Serial.print(text);
}

String MentorESP32HTTP::ipToString(IPAddress ip){
    String s="";
    for (int i=0; i<4; i++)
        s += i  ? "." + String(ip[i]) : String(ip[i]);
    return s;
}
