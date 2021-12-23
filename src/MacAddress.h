#ifndef _MAC_ADDRESS_H_
#define _MAC_ADDRESS_H_

#include <string>

#include "Arduino.h"

#define MAC_ADDR_LENGTH 6

class MacAddress {
    public:
        
        MacAddress(uint8_t *src);

        uint8_t* get() const;

        bool operator== (const MacAddress &other) const;

        String toString();

    private:
        mutable uint8_t addr[MAC_ADDR_LENGTH];

};

class MacAddressHash{

    public:

        size_t operator()(const MacAddress &m) const;

};

#endif