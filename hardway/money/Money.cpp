#include "Money.h"

#include <iomanip>

namespace change {

    // this is just for test purposes - print in dollars always
    std::ostream& operator<<(std::ostream& os, const Money& money)  {
        return os << '$' << std::to_string(money.whole) << '.'
                  << std::setw(2) << std::setfill('0')
                  << static_cast<int16_t>(money.fraction);
    }

}