#ifndef CONFIG_H
#define CONFIG_H

// Override the board type from the library defaults
// This identifies what type of device this is
#undef BOARD_TYPE_DESC
#undef BOARD_TYPE_SHORT

static const char BOARD_TYPE_DESC[] =
    "HSC Serial Device"; // Full description for web UI
static const char BOARD_TYPE_SHORT[] =
    "SERIAL"; // Short name for MQTT (e.g., "BASE-1", "YARD-2", "SIGNAL-3")

// --- OTA Update ---
static const char *UPDATE_URL =
    "http://www-srvr.internal/firmware/firmware_%BOARD_TYPE%.bin";

// You can also override other defaults from lib/HSC_Base/src/config.h here
// For example:
#undef FW_VERSION
static const char FW_VERSION[] = "0.3.0";

#endif
