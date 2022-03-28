#include "test_unique.h"


void TestLifeTime() {
    {
        UniquePtr<MyInt> s(new MyInt);
        ASSERT_EQUAL(MyInt::AliveCount(), 1);
    }
    ASSERT_EQUAL(MyInt::AliveCount(), 0);
}

void TestNoCopy() {
    static_assert(!std::is_copy_constructible_v<UniquePtr<int>> &&
                  !std::is_copy_assignable_v<UniquePtr<int>>);
}

/*
void TestBasic() {
    UniquePtr<int> s;
    AssertEqual(s.Get(), nullptr);
}
 */

void TestMoveSemantics() {
    UniquePtr<int> s1(new int);
    UniquePtr<int> s2(new int);

    int* p = s1.Get();
    s2 = std::move(s1);

    if (s2.Get() == p && s1.Get() == nullptr) {
        std::cerr << "TestMoveSemantics Ok" << std::endl;
    }

}

void TestSwap() {
    MyInt* p1 = new MyInt(1);
    UniquePtr<MyInt> s1(p1);
    MyInt* p2 = new MyInt(2);
    UniquePtr<MyInt> s2(p2);

    if (s1.Get() == p1 && s2.Get() == p2 && *s1 == 1 && *s2 == 2) {
        std::cerr << "First part TestSwap is Ok" << std::endl;
    }

    s1.Swap(s2);

    if (s1.Get() == p2 && *s1 == 2 && s2.Get() == p1 && *s2 == 1 && MyInt::AliveCount() == 2) {
        std::cerr << "Second part TestSwap is Ok" << std::endl;
    }

    std::swap(s1, s2);

    if (s1.Get() == p1 && s2.Get() == p2 && *s1 == 1 && *s2 == 2) {
        std::cerr << "Third part TestSwap is Ok" << std::endl;
    }

}

