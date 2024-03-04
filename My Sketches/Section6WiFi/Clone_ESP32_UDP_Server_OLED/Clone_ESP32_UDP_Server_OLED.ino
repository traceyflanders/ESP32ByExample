#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

WiFiUDP Udp; // Creation of wifi Udp instance

char packetBuffer[255];

unsigned int localPort = 8889;

const char *ssid = "EEK-UDP-OLED";  
const char *password = "EEK-TEST";

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setup() {
  WiFi.softAP(ssid, password);  // ESP-32 as access point
  Serial.begin(115200);
  while (!Serial){
    delay(10);
    if (millis() > 5000) break; // don't wait forever
  }
  if (Serial) Serial.println("\nSerial Connected");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.display();
  delay(2000);  // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.clearDisplay();
  display.setCursor(0, 0);


  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Soft-AP IP address:");
  display.println(WiFi.softAPIP());
  display.println("Waiting...");
  display.display();
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
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("IP: ");
    display.println(Udp.remoteIP());
    display.print("Size: ");
    display.println(packetSize);
    display.println("Packet:");
    display.println(packetBuffer);
    display.display();

    Udp.beginPacket(Udp.remoteIP(),Udp.remotePort());
    Udp.printf("received: ");
    Udp.printf(packetBuffer);
    Udp.endPacket();
    }
}