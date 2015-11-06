#ifndef CHANGE_MONEY_H_
#define CHANGE_MONEY_H_

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

namespace change {
    class Money {
    private:
        int64_t whole;
        int8_t fraction;

    public:
        Money(const Money& other) noexcept = default;
        Money(Money&& other) noexcept = default;
        Money(int64_t _whole = 0, int8_t _fraction = 0) noexcept :
            whole(_whole),
            fraction(_fraction) {}

        ~Money() noexcept = default;

        void swap(Money& other) {
            using std::swap;
            swap(whole, other.whole);
            swap(fraction, other.fraction);
        }

        // copy assignment
        Money& operator=(const Money& other) {
            if (&other != this) {
                Money copy(other);
                copy.swap(*this);
            }
            return *this;
        }

        // move assignment
        Money& operator=(Money&& other) noexcept {
            Money copy(std::move(other));
            copy.swap(*this);
            return *this;
        }

        bool operator==(const Money& other) const {
            return whole == other.whole && fraction == other.fraction;
        }

        bool operator!=(const Money& other) const {
            return !(*this == other);
        }

        bool operator<(const Money& other) const {
            return std::make_tuple(whole, fraction) <
                   std::make_tuple(other.whole, other.fraction);
        }

        bool operator<=(const Money& other) const {
            return !(other < *this);
        }

        bool operator>(const Money& other) const {
            return other < *this;
        }

        bool operator>=(const Money& other) const {
            return !(*this < other);
        }

        Money operator+=(const Money &other) {
            // TODO: overflow check
            whole += other.whole;
            fraction += other.fraction;

            whole += fraction / 100;
            fraction = fraction % 100;
            return *this;
        }

        Money operator+(const Money& other) const {
            Money result(*this);
            return result += other;
        }

        Money operator-=(const Money &other) {
            // TODO: overflow check
            whole -= other.whole;
            fraction -= other.fraction;

            whole += fraction < 0 ? -1 : 0;
            fraction = fraction < 0 ? 100 + fraction : fraction;
            return *this;
        }

        Money operator-(const Money& other) const {
            Money result(*this);
            return result -= other;
        }

        template <class T>
        Money operator*(T number) const {
            // TODO: overflow check
            int64_t fracMult = fraction * number;
            int8_t newFrac =  static_cast<int8_t>(fracMult % 100);
            // TODO: overflow check
            int64_t newWhole = whole * number + (fracMult / 100);
            Money tmp(newWhole, newFrac);
            return tmp;
        }

        template <class T>
        Money operator/(T number) const {
            if (number == 0) {
                throw std::invalid_argument("Division by zero");
            }
            // TODO: overflow check
            int64_t total = (100 * whole) + fraction;
            int64_t result = total / number;

            int8_t newFrac = static_cast<int8_t>(result % 100);
            int64_t newWhole = result / 100;
            Money tmp(newWhole, newFrac);
            return tmp;
        }

        friend std::ostream& operator<<(std::ostream& os, const Money& money);
    };
}

#endif //CHANGE_MONEY_H_