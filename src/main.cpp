#include <vector>
#include <algorithm>

#include "HumanTracker.h"
#include "LightGenerator.h"
#include "palettes.h"

uint64_t lastUpdate = 0;

HumanTracker humanTracker(VERBOSE_IMPORTANT);
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

	Serial.println("\n\n++ PLANT ONLINE ++\n");

}

void loop() {
    humanTracker.loop();
	lightGenerator.loop(humanTracker.get());

}
