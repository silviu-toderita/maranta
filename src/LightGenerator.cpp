#include "LightGenerator.h"
#include "HumanTracker.h"

LightGenerator::LightGenerator() : _pixel(NUMBER_OF_LEDS, PIN_LED, LED_TYPE) {
    _pixel.begin();
    _pixel.setBrightness(255); 
}

void LightGenerator::loop(uint32_t humans) {
    _humans = humans;

    // Calculate the max human number
    if(humans >= _maxHumans) {
        _maxHumans = humans;
    } else if(_maxHumans > DEFAULT_MAX_HUMANS && millis() - _lastDecrementMax >= DECREMENT_MAX_INTERVAL) {
        _maxHumans--;
        _lastDecrementMax = millis();
    }

    // Calculate the intensity factor
    _intensity = (humans * INTENSITY_FACTOR) / _maxHumans;

    uint8_t colorId = 0;

    // If any humans are detected, calculate the color ID
    if(_intensity) {
        colorId = ((_intensity * COLORS_IN_PALETTE) - 1) / INTENSITY_FACTOR;
    }
    Color color = PALETTES[1][colorId];
    
    // Update the NeoPixel
    _pixel.clear();
    _pixel.setPixelColor(0, color.R, color.G, color.B);
    _pixel.show();

    printGraph(humans);
}

void LightGenerator::printGraph(uint32_t humans) {

    // Print star if a probe was recently detected
    if(HumanTracker::probeCount) {
        Serial.printf("*");
    } else {
        Serial.printf(" ");
    }

    // Print the actual number of humans recently detected
    Serial.printf("%5d|", humans/100);

    // Calculate and render graph
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

    // Print the max number of humans
    Serial.printf("|%5d\r", _maxHumans/100);
}