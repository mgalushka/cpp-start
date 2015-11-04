#ifndef CHANGE_MONEY_H_
#define CHANGE_MONEY_H_

#include <algorithm>
#include <memory>

namespace change {
    class Money {
    private:
        int32_t whole;
        int8_t fraction;

    public:
        Money(int32_t _whole, int8_t _fraction);
        ~Money();

        bool operator==(const Money& other) {
            return whole == other.whole && fraction == other.fraction;
        }

        bool operator!=(const Money& other) {
            return !(*this == other);
        }
    };
}

#endif //CHANGE_MONEY_H_