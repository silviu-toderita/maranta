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

class LightGenerator {

    public: 

        LightGenerator() : _pixel(NUMBER_OF_LEDS, PIN_LED, LED_TYPE) {
            _pixel.begin();
            _pixel.setBrightness(255); 
        }

        void loop(uint32_t humans) {
            _humans = humans;

            if(humans >= _maxHumans) {
                _maxHumans = humans;
            } else if(_maxHumans > DEFAULT_MAX_HUMANS && millis() - _lastDecrementMax >= DECREMENT_MAX_INTERVAL) {
                _maxHumans--;
                _lastDecrementMax = millis();
            }

            _intensity = (humans * INTENSITY_FACTOR) / _maxHumans;

            uint8_t colorId = 0;

            if(_intensity) {
                colorId = ((_intensity * COLORS_IN_PALETTE) - 1) / INTENSITY_FACTOR;
            }

            Color color = PALETTES[1][colorId];
            
            _pixel.clear();

            _pixel.setPixelColor(0, color.R, color.G, color.B);

            _pixel.show();

            printStatus(humans);
        }

    private:
        Adafruit_NeoPixel _pixel;
        uint32_t _humans;
        uint32_t _maxHumans = DEFAULT_MAX_HUMANS;
        uint32_t _intensity = 0;

        uint64_t _lastPrint = 0;
        uint64_t _lastDecrementMax = 0;

        void printStatus(uint32_t humans) {
                
                Serial.printf("%5d[", humans);

                uint8_t graphSection = CONSOLE_GRAPH_CHAR_LENGTH / COLORS_IN_PALETTE;
                uint8_t markerPosition = 0;
                if(_intensity) {
                    markerPosition = (((_intensity * COLORS_IN_PALETTE) -1) * graphSection) / INTENSITY_FACTOR;
                }
                uint8_t currentMarker = 0;

                for(int sections = 0; sections < COLORS_IN_PALETTE; sections++) {
                    for(int dashes = 0; dashes < graphSection; dashes++) {
                        if(currentMarker++ == markerPosition) {
                            Serial.print("X");
                        } else {
                            Serial.print("-");
                        }
                    }
                    if(sections < COLORS_IN_PALETTE - 1) {
                        Serial.print("/");
                    }
                }

                Serial.printf("]%5d\r", _maxHumans);
        }


};
