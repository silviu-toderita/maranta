#include <vector>
#include <algorithm>

#include "HumanTracker.h"

HumanTracker humanTracker;

void setup() {
  Serial.begin(115200);

}

void loop() {
    humanTracker.loop();
}
