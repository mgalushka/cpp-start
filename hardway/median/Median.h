#include <algorithm>
#include <cmath>
#include <exception>
#include <vector>

namespace median {

    template <class T>
    T median (std::vector<T>& v) {
        typename std::vector<T>::size_type size = v.size();
        if (!size) {
            throw std::runtime_error("Input vector is empty");
        }
        if (size <= 2) {
            return v[0];
        }
        std::sort(v.begin(), v.end());
        auto mid = size / 2;
        return size % 2 == 1 ? v[mid] : (v[mid - 1] + v[mid]) / 2;
    }
};
