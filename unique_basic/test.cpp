#include "../unique.h"
#include "../my_int.h"

#include "../catch.hpp"
#include <vector>


////////////////////////////////////////////////////////////////////////////////////////////////////

struct Person {
    virtual int GetFavoriteNumber() const = 0;
    virtual ~Person() = default;
};

struct Alice : Person {
    int GetFavoriteNumber() const override {
        return 37;
    }
};

struct Bob : Person {
    int GetFavoriteNumber() const override {
        return 43;
    }
};

TEST_CASE("Basic") {
    SECTION("Lifetime") {
        {
            UniquePtr<MyInt> s(new MyInt);

            REQUIRE(MyInt::AliveCount() == 1);
        }

        REQUIRE(MyInt::AliveCount() == 0);
    }



    SECTION("Default value") {
        UniquePtr<int> s;

        REQUIRE(s.Get() == nullptr);
    }

    SECTION("Move") {
        UniquePtr<int> s1(new int);
        UniquePtr<int> s2(new int);

        int* p = s1.Get();
        s2 = std::move(s1);

        REQUIRE(s2.Get() == p);
        REQUIRE(s1.Get() == nullptr);
    }

    SECTION("Self move") {
        UniquePtr<MyInt> s(new MyInt(42));
        MyInt* p = s.Get();
        s = std::move(s);

        REQUIRE(MyInt::AliveCount() == 1);
        REQUIRE(s.Get() == p);
        REQUIRE(*p == 42);
    }

    SECTION("NULL") {
        UniquePtr<MyInt> s(new MyInt);

        REQUIRE(MyInt::AliveCount() == 1);

        s = NULL;  // NOLINT

        REQUIRE(MyInt::AliveCount() == 0);
        REQUIRE(s.Get() == nullptr);
    }

    SECTION("Nullptr") {
        UniquePtr<MyInt> s(new MyInt);

        REQUIRE(MyInt::AliveCount() == 1);

        s = nullptr;

        REQUIRE(MyInt::AliveCount() == 0);
        REQUIRE(s.Get() == nullptr);
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////



