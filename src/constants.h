#pragma once

#define WIFI_CHANNEL_MIN                1
#define WIFI_CHANNEL_MAX                11
#define CHANNEL_INCREMENT_INTERVAL_MS   200
#define MAC_ADDR_LENGTH                 6
#define WIFI_CTRL_MSG_LENGTH            12
#define WIFI_FRAME_SRC_ADDR_OFFSET      10
#define FRAME_TYPE_PROBE_REQ            0x40

#define NUMBER_OF_LEDS                  1
#define PIN_LED                         10
#define LED_TYPE                        NEO_RGB

#define COLOR_PROGRESS_MAX              50
#define COLOR_PROGRESS_MAX_OUTPUT       255
#define COLOR_MIN                       100
#define COLOR_MAX                       255

#define BRIGHTNESS_MAX                  255
#define BRIGHTNESS_PULSE                64
#define BRIGHTNESS_DECREASE             1
#define BRIGHTNESS_DECREASE_INTERVAL    1

#define SERIAL_BAUD                     115200

#define GRAPH_LENGTH_BRIGHTNESS         32
#define GRAPH_LENGTH_COLOR              32