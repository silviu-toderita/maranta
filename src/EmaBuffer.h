#ifndef _EMA_BUFFER_H_
#define _EMA_BUFFER_H_

#include "Arduino.h"

#define COUNT_ADJUSTMENT_PERIOD 3000
#define ALPHA_MAX_FACTOR        4.0

class EmaBuffer {
    public:

        EmaBuffer(double alpha);

        void add(uint32_t newValue);

        double get();

    private:

        double _alpha;
        double _accumulator = 0;
        uint32_t _count = 0;

};

#endif