#include <vector>
#include <algorithm>

#include "HumanTracker.h"
#include "LightGenerator.h"
#include "palettes.h"

#define UPDATE_INTERVAL 1000

HumanTracker humanTracker;
LightGenerator lightGenerator;

void setup() {
	Serial.begin(115200);

	// Print startup message
	Serial.println("\n\n");
	Serial.println("                        *********************************************************************");
	Serial.println("                                                                                             ");
	Serial.println("                            ███    ███  █████  ██████   █████  ███    ██ ████████  █████     ");
	Serial.println("                            ████  ████ ██   ██ ██   ██ ██   ██ ████   ██    ██    ██   ██    ");
	Serial.println("                            ██ ████ ██ ███████ ██████  ███████ ██ ██  ██    ██    ███████    ");
	Serial.println("                            ██  ██  ██ ██   ██ ██   ██ ██   ██ ██  ██ ██    ██    ██   ██    ");
	Serial.println("                            ██      ██ ██   ██ ██   ██ ██   ██ ██   ████    ██    ██   ██    ");
	Serial.println("                                                                                             ");
	Serial.println("                        *********************************************************************");
	Serial.println();
	Serial.println();
	Serial.println();

	// Print graph titles
	Serial.println("  Humans   |Intensity                                                                                               ||Aggregate Intensity |Palette");
}

void loop() {
    humanTracker.loop();
	lightGenerator.loop(humanTracker.get());
}
