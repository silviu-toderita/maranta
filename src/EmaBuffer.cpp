#include "EmaBuffer.h"

EmaBuffer::EmaBuffer(double alpha) : _alpha(alpha) {}

void EmaBuffer::add(uint32_t newValue) {
    double alpha = _alpha;
    double alphaMax = _alpha * ALPHA_MAX_FACTOR;

    if(++_count < COUNT_ADJUSTMENT_PERIOD) {
        alpha = alphaMax - ((alphaMax - alpha) * ((double)_count / (double)COUNT_ADJUSTMENT_PERIOD));
    }

    _accumulator = (alpha * (double)newValue) + ((1.0 - alpha) * _accumulator);
}

double EmaBuffer::get() {
    return _accumulator;
}