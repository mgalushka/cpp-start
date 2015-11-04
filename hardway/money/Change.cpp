#include <exception>
#include <stdexcept>

#include "Change.h"
#include "Money.h"

namespace change {
    Money getChange(const Money& price, const Money& paid) {
        if (paid < price) {
            throw std::runtime_error("Paid cannot be less then price to get a change");
        }
        return paid - price;
    }
}