#pragma once

#include "Arduino.h"

#include "constants.h"
#include "Color.h"

/**
 * Serial output UI
**/
class SerialUi {

    public: 

        /**
         * CONSTRUCTOR
        **/
        SerialUi();

        /**
         * Run at boot, initializes serial UI
        **/
        void begin();
        
        /**
         * Run in loop, outputs serial UI
         * 
         * @param color current color
         * @param brightness current brightness
         * @param colorProgress current color progress
         * 
        **/
        void loop(Color color, uint8_t brightness, uint8_t colorProgress);

    private:
        /**
         * Output brightness graph
         * 
         * @param brightness current brightness
         * 
        **/
        void _brightnessGraph(uint8_t brightness);

        /**
         * Output color graph
         * 
         * @param color current color
         * @param colorProgress current color progress
         * 
        **/
        void _colorGraph(Color color, uint8_t colorProgress);

};
