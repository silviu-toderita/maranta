#include <ESP8266WiFi.h>

#include "HumanTracker.h"

#define CHANNEL_INCREMENT_INTERVAL_MS   200
#define MAC_ADDR_LENGTH                 6
#define WIFI_CTRL_MSG_LENGTH            12
#define WIFI_FRAME_SRC_ADDR_OFFSET      10
#define FRAME_TYPE_PROBE_REQ            0x40

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

    // Calculate the average number of probe requests
    if(millis() > _lastUpdate + ACC_UPDATE_INTERVAL) {
        _lastUpdate = millis();
        _calculateProbeAverage();
    } 
    
}

uint32_t HumanTracker::get() {
    return _accumulator;
}

void HumanTracker::_calculateProbeAverage() {

    uint32_t period = ACC_PERIOD;

    // The period should be the lower of the period parameter, the alpha parameter, 
    // and the number of cycles elapsed
    if(++_count < period) {
        period = _count;
    }
    if(period < ACC_ALPHA) {
        period = ACC_ALPHA;
    }

    // Calculate a running average of probe requests
    _accumulator =  (probeCount * ACC_MULTIPLIER) + ((_accumulator * (period - ACC_ALPHA)) / period);

    probeCount = 0;
}