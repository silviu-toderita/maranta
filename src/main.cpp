#include <vector>
#include <algorithm>

#include "HumanTracker.h"
#include "LightGenerator.h"
#include "palettes.h"

#define UPDATE_INTERVAL 1000

uint64_t lastUpdate = 0;

HumanTracker humanTracker(VERBOSE_OFF);
LightGenerator lightGenerator;

void setup() {
	Serial.begin(115200);

	Serial.println("\n");
	Serial.println("*****************************************************************************");
	Serial.println("                                                                             ");
	Serial.println("        ███    ███  █████  ██████   █████  ███    ██ ████████  █████         ");
	Serial.println("        ████  ████ ██   ██ ██   ██ ██   ██ ████   ██    ██    ██   ██        ");
	Serial.println("        ██ ████ ██ ███████ ██████  ███████ ██ ██  ██    ██    ███████        ");
	Serial.println("        ██  ██  ██ ██   ██ ██   ██ ██   ██ ██  ██ ██    ██    ██   ██        ");
	Serial.println("        ██      ██ ██   ██ ██   ██ ██   ██ ██   ████    ██    ██   ██        ");
	Serial.println("                                                                             ");
	Serial.println("*****************************************************************************");
	Serial.println();
	Serial.println("         +++++++++++++++++++++  PLANT ONLINE  ++++++++++++++++++++++\n");

}

void loop() {
    humanTracker.loop();
	lightGenerator.loop(humanTracker.get());

	if(millis() > lastUpdate + UPDATE_INTERVAL) {
		lastUpdate = millis();
		// Serial.println("HumanTracker: " + String(humanTracker.get()));
	}
}
