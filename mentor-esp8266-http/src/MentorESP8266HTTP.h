#ifndef MentorESP8266PHTTP_H
#define MentorESP8266HTTP_H
#include <Arduino.h>
#include <time.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// CA certificates 0x30
static const char fingerPrint[] PROGMEM = "F1:09:86:A3:5D:BA:A0:83:C7:58:5F:CD:FD:67:CE:41:B9:57:F5:D9";
// static const unsigned int caCertLen = 889;
  
class MentorESP8266HTTP
{
    public:
      MentorESP8266HTTP(String accessKey);
      String createDevice(String serviceName, String deviceName);
      // String retrieveAllDevice(String serviceName,int limit=0);
      String storeData(String serviceName, String deviceName, String nameData[], String valueData[], int sizeParameter);
      void begin(); // Initiate JSON buffer
      /*
        Overloaded functions start
        Mentor::push()

        These functions are meant to push data into the
        initiated JSON buffer (created in
        the begin() function)
      */
      void add(String key, String value);
      void add(String key, int value);
      void add(String key, float value);
      void add(String key, double value);

      // 2-level nested json
      void add(String key, String key2, String value);
      void add(String key, String key2, int value);
      void add(String key, String key2, float value);
      void add(String key, String key2, double value);

      /* Overloaded functions end */
      void send(String serviceName, String deviceName); // Store data in buffer to database
      void sendRaw(String text, String serviceName, String deviceName);
      void sendRawNonSecure(String text, String serviceName, String deviceName);
      void sendNonSecure(String serviceName, String deviceName);
      void printData(); // Print waiting list data to serial monitor
      void end();  // Clear JSON buffer
      String retrieveAllData(String serviceName, String deviceName,int limit=0);
      String retrieveLatestData(String serviceName, String deviceName);
      void get(String serviceName, String deviceName);
      String getRaw(String serviceName, String deviceName);
      String getRawNonSecure(String serviceName, String deviceName);
      void getNonSecure(String serviceName, String deviceName);
      void getTest(String serviceName, String deviceName);
      void getLatestTest(String serviceName, String deviceName);
      /*
        Mentor::get() functions

        These functions are meant to fetch data from the
        JSON buffer.
      */
      String getString(String key);
      int getInt(String key);
      float getFloat(String key);
      double getDouble(String key);

      // 2-level nested json

      String getString(String key, String key2);
      int getInt(String key, String key2);
      float getFloat(String key, String key2);
      double getDouble(String key, String key2);

      /* Overloaded functions end */
      bool getSuccess();
      bool wifiConnection(String SSID, String wifiPassword);
      bool wifiConnectionNonSecure(String SSID, String wifiPassword);
      bool checkWifiConnection();
      void setDebug(bool trueFalse);
      void setServer(String domain,String port);

      void measureSize();
      void measureGetSize();

    private:
      void printDebug(String text);
      String ipToString(IPAddress ip);
      String _accessKey;
      String _server = "http://mentorconsole.poliupg.ac.id";
      const char* _serverNoHttp = "mentorconsole.poliupg.ac.id";
      String _port = "8080";
      String _portSecure = "8443";
      uint16_t _portNum = 8080;
      uint16_t _portSecureNum = 8443;
      char* _wifiSSID;
      char* _wifiPass;
      bool _debug=false;
      bool _getSuccess=false;
      char* tempDebug;
      String jsonString = "{}";
      String jsonGetString;
      String _currentKey;
};

#endif
