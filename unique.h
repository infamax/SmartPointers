#pragma once
#include <cstddef>
#include <type_traits>

#include "Deleters/default_deleter.h"

template<typename T,
        typename Deleter = DefaultDeleter<T>>
class UniquePtr {
public:
    // Constructors
    UniquePtr() = default;
    explicit UniquePtr(T* ptr) {
        ptr_ = ptr;
        ptr = nullptr;
    }

    UniquePtr(T* ptr, Deleter deleter) {
        ptr_ = ptr;
        ptr = nullptr;
        deleter_ = deleter;
    }

    UniquePtr(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept {
        ptr_ = other.ptr_;
        deleter_ = other.deleter_;
        other.ptr_ = nullptr;
    }

    // operators =
    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete ptr_;
        ptr_ = other.ptr_;
        deleter_ = other.deleter_;
        other.ptr_ = nullptr;
        return *this;
    }

    UniquePtr& operator=(std::nullptr_t) {
        if (ptr_) {
            deleter_(ptr_);
        }
        ptr_ = nullptr;
        return *this;
    }

    // modifies
    T* Get() const noexcept {
        return ptr_;
    }

    T* Release() noexcept {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void Reset(T* ptr = nullptr) noexcept {
        T* old_ptr = ptr_;
        ptr_ = ptr;
        if (old_ptr) {
            deleter_(old_ptr);
        }
    }

    void Swap(UniquePtr& other) {
        T* tmp = other.ptr_;
        other.ptr_ = ptr_;
        ptr_ = tmp;
    }


    // operator * / ->
    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const noexcept {
        return ptr_;
    }

    explicit operator bool() const noexcept {
        if (ptr_) {
            return true;
        }
        return false;
    }

    // destructor
    ~UniquePtr() {
        deleter_(ptr_);
    }
private:
    T* ptr_ = nullptr;
    Deleter deleter_;
};

/*
// Function make_unique specialisation for not array
template <typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&& args);




// Specialisation for arrays
template<typename T,
        typename Deleter>
class UniquePtr <T[], Deleter> {
public:
    T& operator[] (size_t index) const;

    // operators =
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    UniquePtr& operator=(std::nullptr_t);

    // modifies
    T* Get() const noexcept;
    T* Release() noexcept;
    void Reset(T* ptr) noexcept;
    void Swap(UniquePtr& other);

    // Destructor
    ~UniquePtr();
private:
    T* ptr_ = nullptr;
    Deleter deleter_;
};
 */
