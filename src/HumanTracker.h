#pragma once

#include <queue>
#include <map>

#include "Arduino.h"

#include "constants.h"


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
         * Set a callback function to call when new probe requests are detected
         * 
         * @param callback
        **/ 
        void setProbeCallback(void (*callback)(int));

    private:

        uint8_t _channel = WIFI_CHANNEL_MIN;
        uint64_t _lastChannelIncrement = 0;
        void (*_callback)(int) = NULL;

};