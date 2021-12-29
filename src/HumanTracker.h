#ifndef _HUMAN_TRACKER_H_
#define _HUMAN_TRACKER_H_

#include <queue>
#include <map>

#include "Arduino.h"
#include "MacAddress.h"
#include "EmaBuffer.h"

#define WIFI_CHANNEL_MIN 1
#define WIFI_CHANNEL_MAX 11



class HumanTracker {
    public:

        static std::queue<MacAddress> newMacAddrs;
        static uint32_t probeCount;

        HumanTracker();

        void loop();

    private:

        std::map<MacAddress, uint64_t> _macAddrs;
        uint8_t _channel = WIFI_CHANNEL_MIN;
        uint64_t _lastChannelIncrement = 0;

        EmaBuffer _emaProbes;

        void _incrementChannel();

        void _calculateProbeAverage();

};

#endif