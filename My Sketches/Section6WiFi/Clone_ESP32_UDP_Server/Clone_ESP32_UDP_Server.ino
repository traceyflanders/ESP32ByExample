#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp; // Creation of wifi Udp instance

char packetBuffer[255];

unsigned int localPort = 8889; // Tello uses this port

const char *ssid = "EEK-Udp-Demo";  
const char *password = "EEK-Demo";

void setup() {
  WiFi.softAP(ssid, password);  // ESP-32 as access point
  Serial.begin(115200);
  while (!Serial){
    delay(10);
    if (millis() > 5000) break; // don't wait forever
  }
  if (Serial) Serial.println("\nSerial Connected");
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  Udp.begin(localPort);
  }

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
    Serial.print("Received(IP/Size/Data): ");
    Serial.print(Udp.remoteIP());Serial.print(" / ");
    Serial.print(packetSize);Serial.print(" / ");
    Serial.println(packetBuffer);

    Udp.beginPacket(Udp.remoteIP(),Udp.remotePort());
    Udp.printf("received: ");
    Udp.printf(packetBuffer);
    Udp.endPacket();
    }
}