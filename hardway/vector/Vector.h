#pragma once

#include <iterator>

namespace learning {

    template <class T>
    class Vector {

    public:  
      typedef size_t size_type;  
      typedef T value_type;  
      typedef T* iterator;  
      typedef const T* const_iterator;  
      
      // Construct an empty Vector
      Vector();  
        // Begin iterators, various const variants
        iterator begin() { return begin_; }
        const_iterator begin() const { return begin_; }
        const_iterator cbegin() const { return begin(); }

        // Begin iterators, various const variants
        iterator end() { return end_; }
        const_iterator end() const { return end_; }
        const_iterator cend() const { return end(); }

        // Size and capacity
        size_type size() const { return end_ - begin_; }
        size_type capacity() const { return limit_ - begin_; }

    private:
        T* begin_;
        T* end_;
        T* limit_;
    };

    template <class T>
    class Holder {
    public:
        typedef T* iterator;  

        // single value constructor
        Holder(const T& val);

        // TODO: copy constructor
        Holder(const Holder& other);

        void swap(Holder<T>& other);

        // destructor
        ~Holder();

        // iterator only to single elemend
        iterator begin() { return begin_;}
    private:
        T* begin_;
    };

};

