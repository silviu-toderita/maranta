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
    calculateBrightness();

    // Update the NeoPixel
    _pixel.clear();
    _pixel.setPixelColor(0, color.R, color.G, color.B);
    _pixel.setBrightness(_brightness);
    _pixel.show();

    printStatus(humans);
    _lastIntensity = _intensity;
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

void LightGenerator::calculateBrightness() {
    if(_intensity > _lastIntensity) {
        if(_brightness <= BRIGHTNESS_MAX - BRIGHTNESS_PULSE) {
            _brightness += BRIGHTNESS_PULSE;
        } else {
            _brightness = BRIGHTNESS_MAX;
        }
    } else {
        if(_brightness >= BRIGHTNESS_DECREASE) {
            _brightness -= BRIGHTNESS_DECREASE;
        } else {
            _brightness = 0;
        }
    }
}

void LightGenerator::printStatus(uint32_t humans) {

    // Overwrite last line
    Serial.printf("\r");
    
    // Print star if a probe was recently detected
    if(_intensity > _lastIntensity) {
        Serial.printf("*");
    } else {
        Serial.printf(" ");
    }

    // Print the actual number of humans recently detected
    Serial.printf("%4d/", humans/100);
    // Print the max number of humans
    Serial.printf("%4d |", _maxHumans/100);

    printGraphIntensity();

    Serial.printf("|");

    printGraphPalette();

}

void LightGenerator::printGraphIntensity() {
    

    uint8_t graphSection = INTENSITY_GRAPH_LENGTH / COLORS_IN_PALETTE;
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

}

void LightGenerator::printGraphPalette() {
    Serial.printf("|");

    uint8_t markerPosition = (_aggregateIntensity * PALETTE_GRAPH_LENGTH) / PALETTE_CHANGE_INTENSITY;

    for(uint8_t i = 0; i < PALETTE_GRAPH_LENGTH; i++) {
        if(i == markerPosition) {
            Serial.printf("+");
        } else {
            Serial.printf("-");
        }
    }

    Serial.printf("|%2d",_currentPalette + 1);

}