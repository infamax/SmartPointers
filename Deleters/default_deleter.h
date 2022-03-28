#pragma once


// This is functor delete managed object
template<typename T>
struct DefaultDeleter {
    void operator()(T* ptr) noexcept {
        delete ptr;
    }
};

// Specialization for arrays
template<typename T>
struct DefaultDeleter <T[]> {
    void operator()(T* ptr) noexcept {
        delete ptr;
    }
};

