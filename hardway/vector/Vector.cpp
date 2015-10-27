#include <memory>
#include "Vector.h"

namespace learning {

    template <class T>
    Holder<T>::Holder(const T& val) {
        std::allocator<T> alloc;
        begin_ = alloc.allocate(1);
        std::uninitialized_fill_n(begin_, 1, val);
    }

    template <class T>
    Holder<T>::~Holder() {
        if (begin_ == nullptr) {
            return;
        }

        begin_->~T();

        std::allocator<T> alloc;
        alloc.deallocate(begin_, 1);
        begin_ = nullptr;
    }

}