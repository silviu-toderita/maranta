#ifndef _HUMAN_TRACKER_H_
#define _HUMAN_TRACKER_H_

#include <queue>
#include <map>

#include "Arduino.h"
#include "constants.h"

#define WIFI_CHANNEL_MIN    1
#define WIFI_CHANNEL_MAX    11

#define ACC_UPDATE_INTERVAL 100
#define ACC_MULTIPLIER      100
#define ACC_PERIOD          600 
#define ACC_ALPHA           2


class HumanTracker {
    public:

        static uint32_t probeCount;
        static VERBOSITY_LEVEL _verbose;

        HumanTracker(VERBOSITY_LEVEL verbose = VERBOSE_OFF);

        void loop();

        uint32_t get();

    private:

        uint8_t _channel = WIFI_CHANNEL_MIN;
        uint64_t _lastChannelIncrement = 0;

        uint32_t _accumulator = 0;
        uint32_t _count = 0;
        uint64_t _lastUpdate = 0;

        void _calculateProbeAverage();

};

#endif