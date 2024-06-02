# esp32-httpclient-test2

## Requires `secrets.h`

```cpp
#ifndef SECRETS_H
#define SECRETS_H

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Server details
const char* serverName = "https://YOUR_SERVER_URL/post-endpoint";
const char* authToken = "YOUR_AUTH_TOKEN";

// Root certificate of your server
const char* rootCACertificate = \
"-----BEGIN CERTIFICATE-----\n" \
"YOUR_ROOT_CA_CERTIFICATE_HERE" \
"-----END CERTIFICATE-----\n";

#endif // SECRETS_H
```
