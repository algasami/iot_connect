#include <Arduino.h>

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

constexpr char AP_ssid[] = "Big_Phone_888";
constexpr char password[] =
    "87654321"; // hi stranger. you can connect to my wifi now!
char HOSTNAME[50];

ESP8266WebServer server(80);

void handleRoot();
void handleChipsay();
void handleNotFound();
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  Serial.println("Begin Wifi Initialization...");
  WiFi.begin(AP_ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection...");
  }
  Serial.println("Successfully connected!");
  strcpy(HOSTNAME, WiFi.hostname().c_str());
  Serial.printf("Current hostname: %s\n", WiFi.hostname().c_str());
  server.begin();
  server.on("/", HTTP_GET, handleRoot);
  server.on("/chipsay", HTTP_GET, handleChipsay);
  server.onNotFound(handleNotFound);
  Serial.println("HTTP server Initialized!");
}

void loop() { server.handleClient(); }

char buffer[500]; // ! This is volatile because if handleroot and handlenotfound
                  // ! are both called at the same time, it could result in race
                  // ! condition

void blink() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);
}

void handleRoot() {
  blink();
  JsonDocument res;
  res["HOSTNAME"] = HOSTNAME;
  res["Info"] = "This is the page root of an ESP8266 web server! Please say hi "
                "if you see a tiny chip blinking in your peripheral vision.";
  serializeJsonPretty(res, buffer);
  server.send(200, "application/json", buffer);
}

void handleNotFound() {
  blink();
  JsonDocument res;
  res["code"] = 404;
  serializeJsonPretty(res, buffer);
  server.send(404, "application/json", buffer);
}

void handleChipsay() {
  blink();
  if (server.args() == 0) {
    server.send(200, "text/plain", "You forgot to include a param!");
    return;
  }
  for (size_t i = 0; i < static_cast<size_t>(server.args()); i++) {
    if (server.argName(i) == "msg") {
      sprintf(buffer, "%s chip says \"%s\"", HOSTNAME, server.arg(i).c_str());
      break;
    }
  }
  server.send(200, "text/plain", buffer);
}