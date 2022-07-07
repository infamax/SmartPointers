#include <iostream>
#include <memory>
#include "unique.h"
#include "my_int.h"


struct Foo {
    Foo(int _val) : val(_val) { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
    int val;
};

int main() {
    UniquePtr<MyInt> s(new MyInt);

    if (MyInt::AliveCount() == 1) {
        std::cout << "Ok1\n";
    }

    s = nullptr;

    if (MyInt::AliveCount() == 0) {
        std::cout << "Ok2\n";
    }

    if (s.Get() == nullptr) {
        std::cout << "Ok3\n";
    }

    return 0;
}