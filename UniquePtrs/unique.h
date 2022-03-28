#pragma once
#include <cstddef>
#include <type_traits>

#include "../Deleters/default_deleter.h"
#include "../my_int.h"

template<typename T,
        typename Deleter = DefaultDeleter<T>>
class UniquePtr {
public:
    // Constructors
    UniquePtr() = default;
    UniquePtr(T* ptr, Deleter deleter);
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
    void Swap(UniquePtr& other);


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