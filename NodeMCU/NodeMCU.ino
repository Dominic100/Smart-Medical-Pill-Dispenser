#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

ESP8266WebServer server(80); // 80 is the port number

const char* ssid = "Aneesh's Galaxy S21 FE 5G";
const char* password = "okvs2599";

SoftwareSerial mySerial(D1, D2); // (Rx, Tx)

String disp, dont;

void handleDispense() {
  if (server.hasArg("message")) {
    String message = server.arg("message");
    mySerial.println(message);
    disp = "Dispensing: " + message;
  } else {
    disp = "Invalid request. Message parameter missing.";
  }
  server.send(200, "text/html", disp);
}

void handleNo() {
  mySerial.println("");
  dont = "No action taken.";
  server.send(200, "text/html", dont);
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print(WiFi.localIP());

  server.on("/dispense", HTTP_GET, handleDispense);
  server.on("/no", HTTP_GET, handleNo);

  server.begin();
}

void loop() {
  server.handleClient();
  delay(1);
}
