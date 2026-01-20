#include "config.h"
#include <HSC_Base.h>
#include <SPIFFS.h>

HSC_Base hscBase;
AsyncWebSocket ws("/ws");

#define RXD2 16
#define TXD2 17

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
             AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(),
                  client->remoteIP().toString().c_str());
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
  }
}

void setup() {
  // Initialize SPIFFS for device.html
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Initialize Serial2 for Lionel LCS SER2
  Serial.println("Initializing Serial2...");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Initialize the HSC_Base library
  hscBase.setBoardInfo(BOARD_TYPE_DESC, BOARD_TYPE_SHORT, FW_VERSION);
  hscBase.setUpdateUrl(UPDATE_URL);

  // Register WebSocket handler BEFORE hscBase.begin() starts the server?
  // Getting the server instance from hscBase after begin() is safer usually,
  // but let's check order. HSC_Base::begin() calls server.begin().
  // So we should attach handlers before that if possible, OR after is receiving
  // requests. Actually, we can attach handlers anytime.

  hscBase.begin();

  // Attach WebSocket
  ws.onEvent(onEvent);
  hscBase.getServer().addHandler(&ws);

  // Register device-specific page (monitor)
  hscBase.registerPage("/monitor", [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/monitor.html", "text/html");
  });

  // Register device-specific page (optional)
  hscBase.registerPage("/device", [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/device.html", String(), false,
                  [](const String &var) {
                    // Use the library's processor for all standard variables
                    return hscBase.processTemplate(var);
                  });
  });
}

void loop() {
  // Run the HSC_Base loop
  hscBase.loop();

  // Cleanup WebSocket clients
  ws.cleanupClients();

  // Check for incoming serial data
  if (Serial2.available()) {
    String data = "";
    while (Serial2.available()) {
      char c = Serial2.read();
      data += c;
    }
    // Broadcast to all connected WebSocket clients
    if (data.length() > 0) {
      ws.textAll(data);
    }
  }
}
