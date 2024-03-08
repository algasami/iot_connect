#include "utils.hpp"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <LittleFS.h>
#include <WiFiClientSecure.h>

bool remote_server_ip_set = false;
namespace Web {
ESP8266WebServer server(80);
ESP8266WiFiMulti wifi_multi;
bool wifi_connected = false, server_created = false;
} // namespace Web

using namespace Web;

void init_wifi() {
	WiFi.mode(WIFI_STA);
	Serial.println("Begin wifi initialization");
	for (size_t i = 0; i < ROUTER_SIZE; i++) {
		wifi_multi.addAP(routers[i].ssid, routers[i].password);
	}
}

void handle_wifi(uint32_t now) {
	static uint32_t last = millis();
	if (now - last < 1000) {
		return;
	}
	last = now;
	if (wifi_multi.run() != WL_CONNECTED) {
		if (wifi_connected) {
			Serial.println("Wifi disconnected!");
			remote_server_ip_set = false;
			buzz(FREQ_WIFI_DISCONNECT, 1000);
			wifi_connected = false;
		}
		return;
	}
	if (!wifi_connected) {
		wifi_connected = true;
		Serial.println("Wifi connected!");
		remote_server_ip_set = true;
		buzz(FREQ_SERVER_CREATED, 500);
	}
}

WiFiClient client;
HTTPClient http;
void post_moisture(uint32_t moisture_value) {
	if (!remote_server_ip_set) {
		Serial.println("Remote server IP not set!");
		return;
	}
	char buffer[50];
	JsonDocument data;
	data["moisture"] = moisture_value;
	serializeJsonPretty(data, buffer);

	http.begin(client, "http://172.20.10.8:3000/api");

	http.addHeader("Content-Type", "application/json");
	Serial.println(http.POST(buffer));

	http.end();
}