#ifndef CHANGE_MONEY_H_
#define CHANGE_MONEY_H_

#include <exception>
#include <iostream>
#include <string>

namespace change {
    class Money {
    private:
        int32_t whole;
        int8_t fraction;

        void swap(Money other);

    public:
        Money(const Money& other);
        Money(const Money&& other);
        Money(int32_t _whole, int8_t _fraction);
        ~Money();

        int32_t getWhole() const { return whole; }
        int8_t getFraction() const { return fraction; }

        Money& operator=(const Money& other) {
            if (&other != this) {
                whole = other.whole;
                fraction = other.fraction;
            }
            return *this;
        }

        bool operator==(const Money& other) const {
            return whole == other.whole && fraction == other.fraction;
        }

        bool operator!=(const Money& other) const {
            return !(*this == other);
        }

        bool operator>(const Money& other) const {
            if (whole > other.whole) {
                return true;
            } else if (whole == other.whole) {
                return fraction > other.fraction;
            } else{
                return false;
            }
        }

        bool operator>=(const Money& other) const {
            return (*this == other || *this > other);
        }

        bool operator<(const Money& other) const {
            return !(*this == other || *this > other);
        }

        bool operator<=(const Money& other) const {
            return (*this == other || *this < other);
        }

        Money operator+(Money& other) const {
            Money result(0, 0);
            int16_t sum = fraction + other.fraction;
            int16_t newFrac = static_cast<int16_t>(sum) % 100;
            int64_t carry = sum > 100 ? 1 : 0;
            // TODO: overflow check
            result.whole =  whole + other.whole + carry;
            result.fraction = static_cast<int8_t>(newFrac);
            return result;
        }

        Money operator+=(Money other) {
            *this = *this + other;
            return *this;
        }

        Money operator-(const Money& other) const {
            Money result(0, 0);
            int8_t newFrac = (fraction - other.fraction) % 100;
            int32_t carry = newFrac < 0 ? -1 : 0;
            newFrac = newFrac < 0 ? 100 + newFrac : newFrac;
            // TODO: overflow
            result.whole = whole - other.whole + carry;
            result.fraction = newFrac;
            return result;
        }

        Money operator-=(Money other) {
            *this = *this - other;
            return *this;
        }

        template <class T>
        Money operator*(T number) const {
            // TODO: overflow check
            int64_t fracMult = static_cast<int64_t>(fraction) * number;
            int8_t newFrac =  static_cast<int8_t>(fracMult % 100);
            // TODO: overflow check
            int32_t newWhole = whole * number + (fracMult / 100);
            Money tmp(newWhole, newFrac);
            return tmp;
        }

        template <class T>
        Money operator/(T number) const {
            if (number == 0) {
                throw std::invalid_argument("Division by zero");
            }
            // TODO: overflow check
            int64_t total = (100 * static_cast<int64_t>(whole)) + fraction;
            int64_t result = total / number;

            int8_t newFrac = static_cast<int8_t>(result % 100);
            int32_t newWhole = static_cast<int32_t>(result / 100);
            Money tmp(newWhole, newFrac);
            return tmp;
        }

        friend std::ostream& operator<<(std::ostream& os, const Money& money);
    };
}

#endif //CHANGE_MONEY_H_