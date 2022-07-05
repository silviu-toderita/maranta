#pragma once

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "palettes.h"

#define DEFAULT_MAX_HUMANS          500
#define INTENSITY_FACTOR            10000

#define PRINT_INTERVAL              1000
#define DECREMENT_MAX_INTERVAL      250

#define NUMBER_OF_LEDS              1
#define PIN_LED                     10
#define LED_TYPE                    NEO_RGB

#define CONSOLE_GRAPH_CHAR_LENGTH   100

/**
 * Generates light patterns on a single NeoPixel LED
**/
class LightGenerator {

    public: 

        /**
         * CONSTRUCTOR
        **/
        LightGenerator();

        /**
         * Run as frequently as possible to update the light
         * 
         * @param humans x100 as a basis for light patterns
        **/
        void loop(uint32_t humans);

    private:
        Adafruit_NeoPixel _pixel;
        uint32_t _humans;
        uint32_t _maxHumans = DEFAULT_MAX_HUMANS;
        uint32_t _intensity = 0;

        uint64_t _lastPrint = 0;
        uint64_t _lastDecrementMax = 0;

        /**
         * Print a graph of the current light status
         * 
         * @param humans x100
        **/
        void printGraph(uint32_t humans);

};
