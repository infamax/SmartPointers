#include <iostream>
#include <memory>
#include <vector>

#include "test_runner.h"
#include "UniquePtrs/test_unique.h"


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLifeTime);
    TestNoCopy();
    //RUN_TEST(tr, TestBasic);
    //RUN_TEST(tr, TestMoveSemantics);
    TestMoveSemantics();
    TestSwap();
    return 0;
}
