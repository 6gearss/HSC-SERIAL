#ifndef CONFIG_H
#define CONFIG_H

// --- General Configuration ---
static const char FW_VERSION[] = "0.3.0"; // Base Template

// --- Board Type ---
// Override these in your project's src/config.h
static const char BOARD_TYPE_DESC[] =
    "HSC Base Device";                         // Full description for web UI
static const char BOARD_TYPE_SHORT[] = "BASE"; // Short name for MQTT topics

// --- WiFi Configuration ---
static const char *WIFI_SSID = "LocoNet";
static const char *WIFI_PASSWORD = "MyTrainRoom";

// --- MQTT Configuration ---
static const char *MQTT_SERVER = "mqtt.internal";
static const int MQTT_PORT = 1883;
static const char *MQTT_USER = "";     // Leave empty if not needed
static const char *MQTT_PASSWORD = ""; // Leave empty if not needed

// --- Device Configuration ---
// CHANGE THIS ID FOR EACH BOARD
static const int BOARD_ID = 0;

// --- Pin Definitions ---
// AP Mode Button
static const int PIN_AP_BUTTON = 4;

// --- OTA Update ---
// static const char *UPDATE_URL =
// "http://your-server/firmware_%BOARD_TYPE%.bin";

#endif
