#include "MacAddress.h"

MacAddress::MacAddress(uint8_t *src) {
    memcpy((void*)addr, (void*)src, MAC_ADDR_LENGTH);
}

uint8_t* MacAddress::get() const {
    return addr;
}

bool MacAddress::operator== (const MacAddress &other) const {
    for (uint8_t i=0; i < MAC_ADDR_LENGTH; i++) {
        if (addr[i] != other.addr[i]) {
            return false;
        }
    }
    return true;
}

bool MacAddress::operator< (const MacAddress &other) const {
    for (uint8_t i=0; i < MAC_ADDR_LENGTH; i++) {
        if (addr[i] > other.addr[i]) {
            return false;
        } else if(addr[i] < other.addr[i]) {
            return true;
        }
    }
    return false;
}

String MacAddress::toString() {
    String strFormat;
    for(uint8_t i = 0; i < MAC_ADDR_LENGTH; i++) {
        strFormat += String(addr[i],HEX);
        strFormat += " ";
    }

    return strFormat;
}
