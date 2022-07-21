#include <ESP8266WiFi.h>

#include "HumanTracker.h"


// STATIC
uint32_t HumanTracker::probeCount = 0;

/**
 * Process a packet received over WiFi and check if it is a probe request
 * 
 * @param buf pointer to buffer containing payload
 * @param len length of payload in bytes
 * 
**/
void processWifiPacket(uint8_t *buf, uint16_t len) {
    
    // If this is just a control message, it won't contain a MAC address
    if(len == WIFI_CTRL_MSG_LENGTH) {
        return;
    }

    // Calculate payload address
    uint8_t* payload = buf + WIFI_CTRL_MSG_LENGTH;

    // Check if this is a Probe Request frame
    if(payload[0] == FRAME_TYPE_PROBE_REQ) {

            HumanTracker::probeCount++;

    }

}

HumanTracker::HumanTracker() {

    wifi_station_disconnect();
    wifi_set_opmode(STATION_MODE);
    wifi_set_channel(_channel);
    wifi_promiscuous_enable(false);
    // Set callback function for WiFi packets received in promiscuous mode
    wifi_set_promiscuous_rx_cb(processWifiPacket);
    // Enable WiFi Promiscuous mode
    wifi_promiscuous_enable(true);
}

void HumanTracker::loop() {

    // Cycle through all WiFi channels to ensure we capture devices on any channel
    if(millis() > _lastChannelIncrement + CHANNEL_INCREMENT_INTERVAL_MS) {
        _lastChannelIncrement = millis();

        if(_channel == WIFI_CHANNEL_MAX) {
            _channel = WIFI_CHANNEL_MIN;
        } else {
            _channel++;
        }
        wifi_set_channel(_channel);

    }

    // If any probe requests have been detected since the last loop, call the callback function
    if(probeCount) {
        if(_callback) {
            _callback(probeCount);
        }
        probeCount = 0;
    }
    
}

void HumanTracker::setProbeCallback(void (*callback)(int)) {
    _callback = callback;
}