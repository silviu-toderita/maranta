#include <vector>
#include <algorithm>

#include "HumanTracker.h"
#include "LightGenerator.h"
#include "SerialUi.h"

HumanTracker humanTracker;
LightGenerator lightGenerator;
SerialUi serialUi;

void probeCallback(int probes) {
	lightGenerator.probeReceived(probes);
}

void setup() {

	humanTracker.setProbeCallback(probeCallback);

	lightGenerator.begin();

	serialUi.begin();

}

void loop() {
    humanTracker.loop();
	lightGenerator.loop();
	serialUi.loop(lightGenerator.getColor(), lightGenerator.getBrightness(), lightGenerator.getColorProgress());
}
