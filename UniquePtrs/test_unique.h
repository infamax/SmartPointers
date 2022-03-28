#pragma once

#include <cassert>
#include "../test_runner.h"
#include "../my_int.h"
#include "unique.h"


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

void TestLifeTime();
void TestNoCopy();
// void TestBasic();
void TestMoveSemantics();
void TestSwap();