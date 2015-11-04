#ifndef CHANGE_CHANGE_H_
#define CHANGE_CHANGE_H_

#include "Money.h"

namespace change {
    Money getChange(const Money& price, const Money& paid);
}

#endif // CHANGE_CHANGE_H_