#include "SerialUi.h"

SerialUi::SerialUi() {
    Serial.begin(SERIAL_BAUD);
}

void SerialUi::begin() {
    // Print startup message
    Serial.println("\n\n");
    Serial.println("          *********************************************************************          ");
    Serial.println("                                                                                         ");
    Serial.println("              ███    ███  █████  ██████   █████  ███    ██ ████████  █████               ");
    Serial.println("              ████  ████ ██   ██ ██   ██ ██   ██ ████   ██    ██    ██   ██              ");
    Serial.println("              ██ ████ ██ ███████ ██████  ███████ ██ ██  ██    ██    ███████              ");
    Serial.println("              ██  ██  ██ ██   ██ ██   ██ ██   ██ ██  ██ ██    ██    ██   ██              ");
    Serial.println("              ██      ██ ██   ██ ██   ██ ██   ██ ██   ████    ██    ██   ██              ");
    Serial.println("                                                                                         ");
    Serial.println("          *********************************************************************          ");
    Serial.println();
    Serial.println();
    Serial.println();
}

void SerialUi::loop(Color color, uint8_t brightness, uint8_t colorProgress) {
    Serial.print("\r");
    
    _brightnessGraph(brightness);
    _colorGraph(color, colorProgress);
}

void SerialUi::_brightnessGraph(uint8_t brightness) {
    uint8_t markerPosition = 0;

    if(brightness) {
        markerPosition = ((brightness - 1) * GRAPH_LENGTH_BRIGHTNESS) / BRIGHTNESS_MAX;
    }

    Serial.print("Activity|");            
    
    for(uint8_t i = 0; i < GRAPH_LENGTH_BRIGHTNESS; i++) {
        if (i == markerPosition) {
            Serial.print("█");
        } else {
            Serial.print("-");
        }
    }
    Serial.print("||");
}

void SerialUi::_colorGraph(Color color, uint8_t colorProgress) {
    uint8_t markerPosition = 0;

    if(colorProgress) {
        markerPosition = ((colorProgress - 1) * GRAPH_LENGTH_COLOR) / COLOR_PROGRESS_MAX_OUTPUT;
    }

    Serial.printf(" \x1b[38;2;%d;%d;%dm", color.R, color.G, color.B);
    Serial.print(" Color|");

    for(uint8_t i = 0; i < GRAPH_LENGTH_COLOR; i++) {
        if (i == markerPosition) {
            Serial.printf("█");
        } else {
            Serial.print("-");
        }
    }

    Serial.printf("|#%02X%02X%02X", color.R, color.G, color.B);
    Serial.printf("\x1b[0m");

}