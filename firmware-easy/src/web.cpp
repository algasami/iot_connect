#include "utils.hpp"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <LittleFS.h>
#include <WiFiClientSecure.h>

char remote_server_ip[50];
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

void create_server() {
	if (server_created) {
		return;
	}
	server_created = true;
	Serial.printf("Creating server on %s\n", WiFi.localIP().toString().c_str());
	server.on("/", HTTP_GET, []() {
		// this should send a webpage with a form to give me the remote server
		// IP
		server.send(200, "text/html",
					"<form action=\"/submit\" method=\"post\">"
					"<label for=\"ip\">IP:</label>"
					"<input type=\"text\" id=\"ip\" name=\"ip\"><br><br>"
					"<input type=\"submit\" value=\"Submit\">"
					"</form>");
	});
	server.on("/submit", HTTP_POST, []() {
		Serial.println("Submitted!");
		strcpy(remote_server_ip, server.arg("ip").c_str());
		Serial.println(remote_server_ip);
		remote_server_ip_set = true;
		server.send(200, "text/html", "Submitted!");
	});
	server.begin();
}
void close_server() {
	if (!server_created) {
		return;
	}
	server_created = false;
	remote_server_ip_set = false;
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
			close_server();
			buzz(FREQ_WIFI_DISCONNECT, 1000);
			wifi_connected = false;
		}
		return;
	}
	if (!wifi_connected) {
		wifi_connected = true;
		Serial.println("Wifi connected!");
		create_server();
		buzz(FREQ_SERVER_CREATED, 500);
	}
}

WiFiClientSecure sec_client;
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

	sec_client.setInsecure();

	char site_buffer[100];
	sprintf(site_buffer, "http://%s/submit", remote_server_ip);
	http.begin(sec_client, site_buffer);

	http.addHeader("Content-Type", "application/json");
	http.POST(buffer);

	http.end();
}