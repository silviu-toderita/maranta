#ifndef _HUMAN_TRACKER_H_
#define _HUMAN_TRACKER_H_

#include <queue>
#include <unordered_set>

#include "Arduino.h"
#include "MacAddress.h"

#define WIFI_CHANNEL_MIN 1
#define WIFI_CHANNEL_MAX 11



class HumanTracker {
    public:

        static std::queue<MacAddress> newMacAddrs;
        static uint32_t probeCount;

        HumanTracker();

        void loop();

    private:

        std::unordered_set<MacAddress, MacAddressHash> macAddrs;
        uint8_t channel = WIFI_CHANNEL_MIN;
        uint64_t lastChannelIncrement = 0;

        uint32_t lastProbeCount     = 0;
        uint64_t lastProbeCountTime = 0;
        double probeCountAverage    = 0.0;
        uint32_t totalSeconds       = 0;


        void incrementChannel();

        void calculateProbeAverages();

};

#endif