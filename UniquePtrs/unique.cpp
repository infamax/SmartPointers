#include "unique.h"

template<typename T>
class UniquePtr {
public:
    UniquePtr();
private:
    T* obj_ = nullptr;
};