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

    Color palette[5];
    getColorPalette(palette);
    Color color = getColorHue(palette);
    
    // Update the NeoPixel
    _pixel.clear();
    _pixel.setPixelColor(0, color.R, color.G, color.B);
    _pixel.show();

    printGraph(humans);
}

void LightGenerator::getColorPalette(Color *palette) {
    _aggregateIntensity += _intensity;

    if(_aggregateIntensity >= PALETTE_CHANGE_INTENSITY) {
        _aggregateIntensity = 0;
        _currentPalette = _nextPalette;
        if(_nextPalette == NUMBER_OF_PALETTES - 1) {
            _nextPalette = 0;
        } else {
            _nextPalette++;
        }
    }
    
    for(uint8_t i = 0; i < COLORS_IN_PALETTE; i++) {

        int64_t deltaRed = PALETTES[_nextPalette][i].R - PALETTES[_currentPalette][i].R;
        int32_t deltaGreen = PALETTES[_nextPalette][i].G - PALETTES[_currentPalette][i].G;
        int32_t deltaBlue = PALETTES[_nextPalette][i].B - PALETTES[_currentPalette][i].B;

        palette[i] = PALETTES[_currentPalette][i];
        palette[i].R += (deltaRed * _aggregateIntensity) / PALETTE_CHANGE_INTENSITY;
        palette[i].G += (deltaGreen * _aggregateIntensity) / PALETTE_CHANGE_INTENSITY;
        palette[i].B += (deltaBlue * _aggregateIntensity) / PALETTE_CHANGE_INTENSITY; 

    }

}

Color LightGenerator::getColorHue(Color *palette) {
    uint8_t baseColorId = 0;
    uint16_t colorMod = 0;
    uint16_t colorModMax = INTENSITY_FACTOR / (COLORS_IN_PALETTE - 1);

    // If any humans are detected, calculate the color ID
    if(_intensity) {
        baseColorId = _intensity / colorModMax;
        colorMod = _intensity % colorModMax;
    }

    int8_t deltaRed = palette[baseColorId+1].R - palette[baseColorId].R;
    int8_t deltaGreen = palette[baseColorId+1].G - palette[baseColorId].G;
    int8_t deltaBlue = palette[baseColorId+1].B - palette[baseColorId].B;

    Color output = palette[baseColorId];
    output.R += (deltaRed * colorMod) / colorModMax;
    output.G += (deltaGreen * colorMod) / colorModMax;
    output.B += (deltaBlue * colorMod) / colorModMax;    
    
    return output;
}

void LightGenerator::printGraph(uint32_t humans) {

    // Overwrite last line
    Serial.printf("\r");
    
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
    Serial.printf("|%5d", _maxHumans/100);

    Serial.printf(" Palette: %2d", _currentPalette);

}