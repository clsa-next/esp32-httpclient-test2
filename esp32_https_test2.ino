#include <Arduino.h>
#include "HTTPSClient.h"
#include "RGBLED.h"
#include "secrets.h"

// Define RGB LED pins
#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 7

// Create RGBLED instance
RGBLED rgbLed(RED_PIN, GREEN_PIN, BLUE_PIN);

// Create HTTPSClient instance
HTTPSClient httpsClient(ssid, password, serverName, authToken, rootCACertificate, rgbLed);

void setup() {
  // Initialize serial communication at a baud rate of 115200
  Serial.begin(115200);
  
  // Begin RGB LED
  rgbLed.begin();
  rgbLed.setColor(255, 0, 0); // Turn on RED when the device is turned on

  // Begin HTTPS client
  httpsClient.begin();
}

void loop() {
  // JSON payload to send
  String jsonPayload = "{\"field1\":\"value1\",\"field2\":\"value2\"}";

  // Send HTTP POST request
  httpsClient.post(jsonPayload);

  // Print current time
  httpsClient.printCurrentTime();

  // Wait for 10 seconds
  delay(10000);
}