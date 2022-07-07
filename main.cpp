#include <iostream>
#include <memory>
#include "unique.h"
#include "my_int.h"
#include "Deleters/default_deleter.h"


struct Foo {
    Foo(int _val) : val(_val) { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
    int val;
};

int main() {
    UniquePtr<MyInt[], DefaultDeleter<MyInt[]>> u(new MyInt[100]);
    if (MyInt::AliveCount() == 100) {
        std::cout << "Ok1\n";
    }

    u.Reset();
    if (MyInt::AliveCount() == 0) {
        std::cout << "Ok2\n";
    }

    return 0;
}