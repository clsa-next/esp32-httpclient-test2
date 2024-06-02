#include "HTTPSClient.h"
#include <time.h>
#include <Arduino.h>

HTTPSClient::HTTPSClient(const char* ssid, const char* password, const char* serverName, const char* authToken, const char* rootCACertificate, RGBLED& rgbLed)
: ssid(ssid), password(password), serverName(serverName), authToken(authToken), rootCACertificate(rootCACertificate), rgbLed(rgbLed) {}

void HTTPSClient::begin() {
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Connected to WiFi");

  // Turn off RED and turn on GREEN when connected to WiFi
  rgbLed.setColor(0, 255, 0);
  
  // Synchronize time with NTP server
  syncTime();
  
  // Set root certificate
  client.setCACert(rootCACertificate);
}

void HTTPSClient::syncTime() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" Time synchronized!");
}

void HTTPSClient::printCurrentTime() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
  Serial.print("Current time: ");
  Serial.println(buffer);
}

int HTTPSClient::post(const String& jsonPayload) {
  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, serverName);  // Specify the URL and the secure client
    http.addHeader("Content-Type", "application/json"); // Specify content-type header
    http.addHeader("Authorization", authToken); // Add the Bearer token header

    // Turn on BLUE while posting
    rgbLed.setColor(0, 0, 255);
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(jsonPayload);

    // Turn back to GREEN after posting
    rgbLed.setColor(0, 255, 0);

    // Check the response code
    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response to the request
      Serial.println(httpResponseCode);   // Print return code
      Serial.println(response);           // Print request answer
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
      Serial.println(http.errorToString(httpResponseCode)); // Print error message
    }

    // Free resources
    http.end();
    
    return httpResponseCode;
  } else {
    Serial.println("WiFi not connected");
    return -1; // Return an error code if WiFi is not connected
  }
}