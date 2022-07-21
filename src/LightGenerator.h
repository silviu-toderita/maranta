#pragma once

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

#include "Color.h"

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
         * Begin light generator, run as close as possible to boot
        **/
        void begin();

        /**
         * Update light, run as frequently as possible
        **/
        void loop();

        /**
         * 1 or more probes received
         * 
         * @param numProbes
        **/
        void probeReceived(int numProbes);

        /**
         * @return current color
        **/
        Color getColor();

        /**
         * @return current brightness 
        **/       
        uint8_t getBrightness();

        /**
         * @return current color progress
        **/
        uint8_t getColorProgress();

    private:

        Adafruit_NeoPixel _pixel;

        uint16_t _totalProbes = 0;

        Color _colorBase;
        Color _colorNext;
        Color _colorCurrent;

        uint8_t _brightness = 0;
        uint32_t _lastBrightnessDecrease = 0;

        /**
         * Calculate current color
         * 
         * @return current color
        **/
        void _calculateColor();

        /**
         * Generate random new color suitable for the LED
         * 
         * @return new color
        **/
        Color _generateColor();

};
