//
// Copy this file to main/secrets.h and replace default values with the ones specific to your device and home environment.
//


#include <string>


//
// WIFI SSID and passwords for over-the-air updates
//
struct {
    const char* ssid;
    const char* passwd;
} wifiCredentials = {"ssid", "passwd"};


//
// OTA https server IP address and SSL certificate
//
struct {
    const char* addr;
    uint16_t    port;
    const char* cert;
} httpsCredentials = {"192.168.0.1",
                      8037,   // If you change this, you need to change it in webserver.py too
                      //
                      // Certificate from server_certs/ca_cert.pem
                      // Note: the escaped newlines are important
                      //
                      "-----BEGIN CERTIFICATE-----\n"
                      "MIIDVDCCAjwCCQCT92eT62y+zjANBgkqhkiG9w0BAQsFADBsMQswCQYDVQQGEwJV\n"
                      ...
                      "OOk+Z5w+ebPCNIHFt0oG6PxYdy3W8nDSeSnbTjPHP9qgDQ6OPKk2oQ==\n"
                      "-----END CERTIFICATE-----\n"};
