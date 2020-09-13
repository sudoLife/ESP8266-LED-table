#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


const char *ssid = "your_ssid";

// This shit must be at least 8 characters!!!
const char *password = "your_password";

WiFiServer server(80);

void init_wifi()
{
	WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.begin();
  Serial.println("HTTP server started");
}
