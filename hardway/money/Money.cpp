#include <algorithm>
#include <memory>
#include "Money.h"

namespace change {
    Money::Money(int32_t _whole, int8_t _fraction) {
        whole = _whole;
        fraction = _fraction;
    }

    Money::~Money() {
        // nothing for now
    }
}