#include <ESP8266WiFi.h>

#include "HumanTracker.h"

#define CHANNEL_INCREMENT_INTERVAL_MS   200

#define DEVICE_STALE_INTERVAL_MS        30000

#define WIFI_CTRL_MSG_LENGTH            12
#define WIFI_FRAME_SRC_ADDR_OFFSET      10

#define FRAME_TYPE_PROBE_REQ            0x40

std::queue<MacAddress> HumanTracker::newMacAddrs;
uint32_t HumanTracker::probeCount = 0;

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
            MacAddress newMacAddr(payload + WIFI_FRAME_SRC_ADDR_OFFSET);
            HumanTracker::newMacAddrs.push(newMacAddr);

    }

}

HumanTracker::HumanTracker() : _emaProbes(0.05) {
    wifi_station_disconnect();
    wifi_set_opmode(STATION_MODE);
    wifi_set_channel(_channel);
    wifi_promiscuous_enable(false);
    wifi_set_promiscuous_rx_cb(promRxCb);
    wifi_promiscuous_enable(true);
}

void HumanTracker::loop() {
    if(!newMacAddrs.empty()) {
        MacAddress macAddr = newMacAddrs.front();
        newMacAddrs.pop();
        _macAddrs[macAddr] = millis();
 
    }

    _incrementChannel();
}

void HumanTracker::_incrementChannel() {
    if(millis() > _lastChannelIncrement + CHANNEL_INCREMENT_INTERVAL_MS) {
        _lastChannelIncrement = millis();

        if(_channel == WIFI_CHANNEL_MAX) {
            _calculateProbeAverage();
            _channel = WIFI_CHANNEL_MIN;
        } else {
            _channel++;
        }
        wifi_set_channel(_channel);

    }

}

void HumanTracker::_calculateProbeAverage() {
    _emaProbes.add(probeCount);
    probeCount = 0;

    double probeRate = _emaProbes.get();
    uint32_t uniqueDevices = _macAddrs.size();

    Serial.println("Probe Rate: " + String(probeRate) + " - Unique Devices: " + String(uniqueDevices) + " - People Density: " + String(probeRate * uniqueDevices));
    
    for(auto const& i : _macAddrs) {
        if(millis() > i.second + DEVICE_STALE_INTERVAL_MS) {
            _macAddrs.erase(i.first);
        }
    }
}