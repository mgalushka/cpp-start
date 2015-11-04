#ifndef CHANGE_CHANGE_H_
#define CHANGE_CHANGE_H_

#include <algorithm>
#include <memory>

#include "Money.h"

namespace change {
    Money getChange(const Money& price);
}

#endif // CHANGE_CHANGE_H_