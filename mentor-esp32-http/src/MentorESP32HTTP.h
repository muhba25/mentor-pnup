#ifndef MentorESP32HTTP_H
#define MentorESP32HTTP_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

// Certificate ROOT CA
static const char* test_root_ca = \
      "-----BEGIN CERTIFICATE-----\n"
      "MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n"
      "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"
      "DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n"
      "PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n"
      "Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"
      "AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n"
      "rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n"
      "OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n"
      "xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n"
      "7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n"
      "aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n"
      "HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n"
      "SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n"
      "ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n"
      "AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n"
      "R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n"
      "JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n"
      "Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n"
      "-----END CERTIFICATE-----\n";


class MentorESP32HTTP {

public:
    MentorESP32HTTP(String accessKey);
      void begin();
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
