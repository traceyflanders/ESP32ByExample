#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

// const char* ssid = "........";
// const char* password = "........";

WebServer server(80);

const int led = 13;
const int blueLed = 12;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  delay(5000);
  digitalWrite(led, 0);
}

void handleBlue() {
  digitalWrite(blueLed, 1);
  server.send(200, "text/plain", "hello from esp32; Blue was lit !");
  delay(5000);
  digitalWrite(blueLed, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "Page Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  delay(5000);
  digitalWrite(led, 0);
}

void setup(void) {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

  Serial.begin(115200);

  pinMode(led, OUTPUT);
  pinMode(blueLed, OUTPUT);
  digitalWrite(led, 0);
  digitalWrite(blueLed, 0);

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;
  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("EEKConnectHS", "password");  // password protected ap


  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/blue", handleBlue);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

}

void loop(void) {
  server.handleClient();
  delay(2);  //allow the cpu to switch to other tasks
}
