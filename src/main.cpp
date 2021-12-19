#include <vector>
#include <algorithm>

#include "esppl_functions.h"

uint32_t devicesTotal = 0;

struct mac {
    uint8_t addr[ESPPL_MAC_LEN];

    mac(uint8_t *src) {
        for (int i=0; i < ESPPL_MAC_LEN; i++) {
            addr[i] = src[i];
        }
    }

    bool operator == (const mac &other) {
        for (uint8_t i=0; i < ESPPL_MAC_LEN; i++) {
            if (addr[i] != other.addr[i]) {
                return false;
            }
        }
        return true;
    }

} ;

std::vector<mac> devices;

String macStrFormat(mac &thisMac) {
    String strFormat;
    for(uint8_t i = 0; i < ESPPL_MAC_LEN; i++) {
        strFormat += String(thisMac.addr[i],HEX);
        strFormat += " ";
    }

    return strFormat;
}

void findAndAddMac(mac &thisMac) {
    auto search = std::find(devices.begin(), devices.end(), thisMac);
    if(search == devices.end()) {
        Serial.println("New MAC Found: " + macStrFormat(thisMac) + " | Total: " + String(devices.size()) + " Total (incl Duplicates): " + String(devicesTotal));
        devices.push_back(thisMac);
    }
}

void cb(esppl_frame_info *info) {
    mac mac1(info->sourceaddr);
    mac mac2(info->receiveraddr);

    devicesTotal++;

    findAndAddMac(mac1);
    findAndAddMac(mac2);
}

void setup() {
  delay(500);
  Serial.begin(115200);
  esppl_init(cb);
}

void loop() {
    esppl_sniffing_start();
    while (true) {
        for (int i = ESPPL_CHANNEL_MIN; i <= ESPPL_CHANNEL_MAX; i++ ) {
            esppl_set_channel(i);
            while (esppl_process_frames()) {
                //
            }
        }
    }  
}
