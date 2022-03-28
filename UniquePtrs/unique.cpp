#include "unique.h"


template<typename T, typename Deleter>
UniquePtr<T, Deleter>::UniquePtr(T *ptr) : ptr_(ptr) {
    ptr = nullptr;
}



template<typename T, typename Deleter>
UniquePtr<T, Deleter>::UniquePtr(UniquePtr<T, Deleter> &&other)  noexcept {
    ptr_ = other.ptr_;
    deleter_ = other.deleter_;
    other.ptr_ = nullptr;
}

template<typename T, typename Deleter>
UniquePtr<T, Deleter>& UniquePtr<T, Deleter>::operator=(UniquePtr<T, Deleter> &&other)  noexcept {
    ptr_ = other.ptr_;
    deleter_ = other.deleter_;
    other.ptr_ = nullptr;
    return *this;
}

template<typename T, typename Deleter>
UniquePtr<T, Deleter>& UniquePtr<T, Deleter>::operator=(std::nullptr_t) {
    ptr_ = nullptr;
}

template<typename T, typename Deleter>
T* UniquePtr<T, Deleter>::Get() const noexcept {
    return ptr_;
}

template<typename T, typename Deleter>
T* UniquePtr<T, Deleter>::Release() noexcept {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template<typename T, typename Deleter>
void UniquePtr<T, Deleter>::Reset(T *ptr) noexcept {
    T* old_ptr = ptr_;
    ptr_ = ptr;
    if (old_ptr) {
        deleter_(old_ptr);
    }
}

template<typename T, typename Deleter>
T& UniquePtr<T, Deleter>::operator*() const {
    return *ptr_;
}

template<typename T, typename Deleter>
T* UniquePtr<T, Deleter>::operator->() const noexcept {
    return ptr_;
}

template<typename T, typename Deleter>
UniquePtr<T, Deleter>::operator bool() const noexcept {
    return ptr_ != nullptr;
}

template<typename T, typename Deleter>
UniquePtr<T,Deleter>::~UniquePtr<T, Deleter>() {
    deleter_(ptr_);
}


template class UniquePtr<int>;
template class UniquePtr<MyInt>;







