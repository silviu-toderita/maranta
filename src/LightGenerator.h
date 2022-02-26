#pragma once

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "palettes.h"

#define DEFAULT_MAX_HUMANS  10
#define NUMBER_OF_LEDS      1
#define PIN_LED             10
#define LED_TYPE            NEO_RGB

class LightGenerator {

    public: 

        LightGenerator() : _pixel(NUMBER_OF_LEDS, PIN_LED, LED_TYPE) {
            _pixel.begin();
            _pixel.setBrightness(255); 
        }

        void loop(double humans) {
            uint32_t humansInt = static_cast<uint32_t>(humans);

            if(humansInt > _maxHumans) {
                _maxHumans = humansInt;
            }

            uint8_t intensity = 0;
            if(humansInt) {
                intensity = ((humansInt * COLORS_IN_PALETTE) - 1) / _maxHumans;
            }

            Color color = PALETTES[1][intensity];
            
            _pixel.clear();

            _pixel.setPixelColor(0, color.R, color.G, color.B);

            _pixel.show();
        }


    private:
        Adafruit_NeoPixel _pixel;
        uint32_t _maxHumans = DEFAULT_MAX_HUMANS;

};
