#pragma once

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "palettes.h"

#define NUMBER_OF_LEDS                  1
#define PIN_LED                         10
#define LED_TYPE                        NEO_RGB

#define DEFAULT_MAX_HUMANS              500
#define INTENSITY_FACTOR                10000
#define DECREMENT_MAX_INTERVAL          250
#define PALETTE_CHANGE_INTENSITY        10000000

#define BRIGHTNESS_MAX                  255
#define BRIGHTNESS_PULSE                64
#define BRIGHTNESS_DECREASE             2

#define PRINT_INTERVAL                  1000
#define INTENSITY_GRAPH_LENGTH          100
#define PALETTE_GRAPH_LENGTH            20

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
        uint32_t _lastIntensity = 0;
        int64_t _aggregateIntensity = 0;
        uint8_t _currentPalette = 0;
        uint8_t _nextPalette = 1;

        uint8_t _brightness = 255;

        uint64_t _lastPrint = 0;
        uint64_t _lastDecrementMax = 0;

        /**
         * Get a color palette based on aggregate intensity
         * 
         * @param color pointer to palette to fill with color
        **/
        void getColorPalette(Color *palette);

        /**
         * Get the averaged color from a palette based on the intensity factor
         * 
         * @param palette of possible colors
         * 
         * @return averaged color
        **/
        Color getColorHue(Color *palette);

        /**
         * Calculate the brightness of the light based on intensity spikes
        **/
        void calculateBrightness();

        /**
         * Print current light status
         * 
         * @param humans x100
        **/
        void printStatus(uint32_t humans);

        void printGraphIntensity();

        void printGraphPalette();

};
