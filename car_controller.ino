#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include "index.h"

#define CMD_PICK 0
#define CMD_RELEASE 1
#define CMD_UP 2
#define CMD_DOWN 3

#define CMD_FORWARD 4
#define CMD_BACKWARD 5
#define CMD_LEFT 6
#define CMD_RIGHT 7

#define CMD_STOP 10

const char* ssid = "ssid";
const char* password = "pass";

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      break;
    case WStype_TEXT:
      String angle = String((char*)payload);
      int command = angle.toInt();
      Serial.print("command: ");
      Serial.println(command);

      switch (command) {
        case CMD_STOP:
          // stop wheel
          break;
        case CMD_FORWARD:
          // move forward
          break;
        case CMD_BACKWARD:
          // move backward
          break;
        case CMD_LEFT:
          // turn left
          break;
        case CMD_RIGHT:
          // turn right
          break;

        case CMD_PICK:
          // pickup
          break;
        case CMD_RELEASE:
          // release
          break;
        case CMD_UP:
          // up
          break;
        case CMD_DOWN:
          // down
          break;
        default:
          Serial.println("Unknown command");
      }

      break;
  }
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  server.on("/", HTTP_GET, []() {
    Serial.println("Web Server: received a web page request");
    String html = HTML_CONTENT;
    server.send(200, "text/html", html);
  });

  server.begin();
  Serial.print("ESP8266 Web Server's IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();

  webSocket.loop();
}