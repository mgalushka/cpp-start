#include "Money.h"

#include <iomanip>

namespace change {
    Money::Money(const Money& other) {
        whole = other.whole;
        fraction = other.fraction;
    }

    Money::Money(const Money&& other) {
        *this = std::move(other);
    }

    Money::Money(int32_t _whole, int8_t _fraction) {
        whole = _whole;
        fraction = _fraction;
    }

    Money::~Money() {
        // nothing for now
    }

    void Money::swap(Money other) {
        std::swap(whole, other.whole);
        std::swap(fraction, other.fraction);
    }

    // this is just for test purposes - print in dollars always
    std::ostream& operator<<(std::ostream& os, const Money& money)  {
        return os << '$' << std::to_string(money.whole) << '.' << std::setw(2) << std::setfill('0') << static_cast<int16_t>(money.fraction);
    }

}