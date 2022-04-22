#include <ESP8266WiFi.h>

#include "HumanTracker.h"

#define CHANNEL_INCREMENT_INTERVAL_MS   200
#define MAC_ADDR_LENGTH                 6
#define WIFI_CTRL_MSG_LENGTH            12
#define WIFI_FRAME_SRC_ADDR_OFFSET      10
#define FRAME_TYPE_PROBE_REQ            0x40

uint32_t HumanTracker::probeCount = 0;
VERBOSITY_LEVEL HumanTracker::_verbose = VERBOSE_OFF;

String macAddrToString(uint8_t* macAddrPtr) {
    String strFormat;
    for(uint8_t i = 0; i < MAC_ADDR_LENGTH; i++) {
        strFormat += String(macAddrPtr[i],HEX);
        strFormat += ":";
    }

    return strFormat.substring(0, strFormat.length() - 1);

}


void promRxCb(uint8_t *buf, uint16_t len) {
    
    // If this is just a control message, it won't contain a MAC address
    if(len == WIFI_CTRL_MSG_LENGTH) {
        return;
    }

    // Calculate payload address
    uint8_t* payload = buf + WIFI_CTRL_MSG_LENGTH;

    // Check if this is a Probe Request frame
    if(payload[0] == FRAME_TYPE_PROBE_REQ) {

            HumanTracker::probeCount++;

            if(HumanTracker::_verbose == VERBOSE_HIGH) {
                Serial.println("Probe Req From: " + macAddrToString(payload + WIFI_FRAME_SRC_ADDR_OFFSET));
            }

    }

}

HumanTracker::HumanTracker(VERBOSITY_LEVEL verbose) {
    _verbose = verbose;

    wifi_station_disconnect();
    wifi_set_opmode(STATION_MODE);
    wifi_set_channel(_channel);
    wifi_promiscuous_enable(false);
    wifi_set_promiscuous_rx_cb(promRxCb);
    wifi_promiscuous_enable(true);
}

void HumanTracker::loop() {

    if(millis() > _lastChannelIncrement + CHANNEL_INCREMENT_INTERVAL_MS) {
        _lastChannelIncrement = millis();

        if(_channel == WIFI_CHANNEL_MAX) {
            _channel = WIFI_CHANNEL_MIN;
        } else {
            _channel++;
        }
        wifi_set_channel(_channel);

    }

    if(millis() > _lastUpdate + ACC_UPDATE_INTERVAL) {
        _lastUpdate = millis();
        _calculateProbeAverage();
        if(_verbose >= VERBOSE_LOW) {
            Serial.println("HumanTracker: " + String(_accumulator));
        }
    } 
    
}

uint32_t HumanTracker::get() {
    return _accumulator;
}

void HumanTracker::_calculateProbeAverage() {

    uint32_t period = ACC_PERIOD;

    if(++_count < period) {
        period = _count;
    }

    if(period < ACC_ALPHA) {
        period = ACC_ALPHA;
    }

    _accumulator =  (probeCount * ACC_MULTIPLIER) 
                    + ((_accumulator * (period - ACC_ALPHA)) / period);

    probeCount = 0;
}