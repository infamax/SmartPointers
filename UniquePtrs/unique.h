#pragma once
#include <cstddef>
#include <type_traits>

#include "../Deleters/default_deleter.h"
#include "../my_int.h"

template<typename T,
        typename Deleter = DefaultDeleter<T>>
class UniquePtr {
public:
    // Ctr
    UniquePtr() = default;
    explicit UniquePtr(T* ptr);
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other) noexcept;

    // operators =
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    UniquePtr& operator=(std::nullptr_t);

    // modifies
    T* Get() const noexcept;
    T* Release() noexcept;
    void Reset(T* ptr) noexcept;

    // operator * / ->
    T& operator*() const;
    T* operator->() const noexcept;
    explicit operator bool() const noexcept;

    // destructor
    ~UniquePtr();
private:
    T* ptr_ = nullptr;
    Deleter deleter_;
};