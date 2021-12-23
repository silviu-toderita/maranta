#include <ESP8266WiFi.h>

#include "HumanTracker.h"
#include "wifi_structs.h"

#define CHANNEL_INCREMENT_INTERVAL_MS   100

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

            Serial.println("Total Requests: " + String(++HumanTracker::probeCount));
            MacAddress newMacAddr(payload + WIFI_FRAME_SRC_ADDR_OFFSET);
            HumanTracker::newMacAddrs.push(newMacAddr);

    }

}

HumanTracker::HumanTracker() {
    wifi_station_disconnect();
    wifi_set_opmode(STATION_MODE);
    wifi_set_channel(channel);
    wifi_promiscuous_enable(false);
    wifi_set_promiscuous_rx_cb(promRxCb);
    wifi_promiscuous_enable(true);
}

void HumanTracker::loop() {
    if(!newMacAddrs.empty()) {
        MacAddress macAddr = newMacAddrs.front();
        newMacAddrs.pop();
        if(macAddrs.emplace(macAddr).second) {
            Serial.println("New MAC Found: " + macAddr.toString() + " | Unique: " + String(macAddrs.size()));
        }

        incrementChannel();
    }
}

void HumanTracker::incrementChannel() {
    if(millis() > lastChannelIncrement + CHANNEL_INCREMENT_INTERVAL_MS) {
        lastChannelIncrement = millis();

        if(channel == WIFI_CHANNEL_MAX) {
            channel = WIFI_CHANNEL_MIN;
        } else {
            channel++;
        }
        wifi_set_channel(channel);

    }

}