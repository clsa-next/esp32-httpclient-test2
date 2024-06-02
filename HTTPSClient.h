#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "RGBLED.h"

class HTTPSClient {
public:
  HTTPSClient(const char* ssid, const char* password, const char* serverName, const char* authToken, const char* rootCACertificate, RGBLED& rgbLed);
  void begin();
  int post(const String& jsonPayload);
  void printCurrentTime();

private:
  void syncTime();

  const char* ssid;
  const char* password;
  const char* serverName;
  const char* authToken;
  const char* rootCACertificate;
  WiFiClientSecure client;
  HTTPClient http;
  RGBLED& rgbLed;
};

#endif