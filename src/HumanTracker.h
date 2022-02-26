#ifndef _HUMAN_TRACKER_H_
#define _HUMAN_TRACKER_H_

#include <queue>
#include <map>

#include "Arduino.h"
#include "constants.h"
#include "EmaBuffer.h"

#define WIFI_CHANNEL_MIN 1
#define WIFI_CHANNEL_MAX 11


class HumanTracker {
    public:

        static uint32_t probeCount;
        static VERBOSITY_LEVEL _verbose;

        HumanTracker(VERBOSITY_LEVEL verbose = VERBOSE_OFF);

        void loop();

        double get();

    private:

        uint8_t _channel = WIFI_CHANNEL_MIN;
        uint64_t _lastChannelIncrement = 0;

        EmaBuffer _emaProbes;
        uint64_t _lastUpdate = 0;

        void _calculateProbeAverage();

};

#endif