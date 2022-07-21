#include "ESP8266TrueRandom.h"

#include "LightGenerator.h"
#include "constants.h"

LightGenerator::LightGenerator() : _pixel(NUMBER_OF_LEDS, PIN_LED, LED_TYPE) {
    _pixel.begin();
    _pixel.setBrightness(255);

}

void LightGenerator::begin() {
    _colorBase = _generateColor();
    _colorNext = _generateColor(); 
}

void LightGenerator::loop() {

    // Calculate new color
    _calculateColor();

    // Update the NeoPixel
    _pixel.clear();
    _pixel.setPixelColor(0, _colorCurrent.R, _colorCurrent.G, _colorCurrent.B);
    _pixel.setBrightness(_brightness);
    _pixel.show();

    // Decrease brightness
    if(millis() >= _lastBrightnessDecrease + BRIGHTNESS_DECREASE_INTERVAL) {
        _lastBrightnessDecrease = millis();

        if(_brightness >= BRIGHTNESS_DECREASE) {
            _brightness -= BRIGHTNESS_DECREASE;
        } else {
            _brightness = 0;
        }

    }


}

void LightGenerator::probeReceived(int numProbes) {
    _totalProbes += numProbes;

    if ((numProbes * BRIGHTNESS_PULSE) + _brightness > BRIGHTNESS_MAX) {
        _brightness = BRIGHTNESS_MAX;
    } else {
        _brightness += BRIGHTNESS_PULSE;
    }
}

Color LightGenerator::getColor() {
    return _colorCurrent;
}

uint8_t LightGenerator::getBrightness() {
    return _brightness;
}

uint8_t LightGenerator::getColorProgress() {
    return (_totalProbes * COLOR_PROGRESS_MAX_OUTPUT) / COLOR_PROGRESS_MAX;
}

void LightGenerator::_calculateColor() {

    if(_totalProbes >= COLOR_PROGRESS_MAX) {
        _totalProbes = 0;
        _colorBase = _colorNext;
        _colorNext = _generateColor();
    }

    int16_t deltaRed = _colorNext.R - _colorBase.R;
    int16_t deltaGreen = _colorNext.G - _colorBase.G;
    int16_t deltaBlue = _colorNext.B - _colorBase.B;

    _colorCurrent = _colorBase;
    _colorCurrent.R += (deltaRed * _totalProbes) / COLOR_PROGRESS_MAX;
    _colorCurrent.G += (deltaGreen * _totalProbes) / COLOR_PROGRESS_MAX;
    _colorCurrent.B += (deltaBlue * _totalProbes) / COLOR_PROGRESS_MAX; 

}

Color LightGenerator::_generateColor() {
    Color color;
    
    color.R = ESP8266TrueRandom.random(COLOR_MIN, COLOR_MAX);
    color.G = ESP8266TrueRandom.random(COLOR_MIN, COLOR_MAX);
    color.B = ESP8266TrueRandom.random(COLOR_MIN, COLOR_MAX);

    return color;

}
