#ifndef _HUMAN_TRACKER_H_
#define _HUMAN_TRACKER_H_

#include <queue>
#include <map>

#include "Arduino.h"

#define WIFI_CHANNEL_MIN    1
#define WIFI_CHANNEL_MAX    11

#define ACC_UPDATE_INTERVAL 100
#define ACC_MULTIPLIER      100
#define ACC_PERIOD          300 
#define ACC_ALPHA           2

/**
 * Tracks the number of humans nearby using WiFi probe requests
**/
class HumanTracker {
    public:

        static uint32_t probeCount;

        /**
         * CONSTRUCTOR
        **/
        HumanTracker();
       
        /**
         * Run as frequently as possible to keep track of probe requests
        **/       
        void loop();

        /**
         * Get the number of humans detected nearby
         * 
         * @return the number of humans nearby x100
        **/
        uint32_t get();

    private:

        uint8_t _channel = WIFI_CHANNEL_MIN;
        uint64_t _lastChannelIncrement = 0;

        uint32_t _accumulator = 0;
        uint32_t _count = 0;
        uint64_t _lastUpdate = 0;

        /**
         * Calculate the average number of probes based on new probe requests
        **/
        void _calculateProbeAverage();

};

#endif