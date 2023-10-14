#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "blet/mockc.h"
#include "blet/thread.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

struct MyTest {
    static void staticMethodVoid() {
        resultStaticMethodVoid = true;
    }
    static void staticMethodArg1(int& a1) {
        ++a1;
        resultStaticMethodArgs.clear();
        resultStaticMethodArgs.push_back(a1);
    }
    static void staticMethodArg2(int a1, int a2) {
        resultStaticMethodArgs.clear();
        resultStaticMethodArgs.push_back(a1);
        resultStaticMethodArgs.push_back(a2);
    }

    void methodVoid() {
        resultMethodVoid = true;
    }
    void methodArg1(int& a1) {
        ++a1;
        resultMethodArgs.clear();
        resultMethodArgs.push_back(a1);
    }
    void methodArg2(int a1, int a2) {
        resultMethodArgs.clear();
        resultMethodArgs.push_back(a1);
        resultMethodArgs.push_back(a2);
    }

    void methodVoidConst() const {
        resultMethodVoidConst = true;
    }
    void methodArg1Const(int a1) const {
        resultMethodArgsConst.clear();
        resultMethodArgsConst.push_back(a1);
    }
    void methodArg2Const(int a1, int a2) const {
        resultMethodArgsConst.clear();
        resultMethodArgsConst.push_back(a1);
        resultMethodArgsConst.push_back(a2);
    }

    static bool resultStaticMethodVoid;
    bool resultMethodVoid;
    static bool resultMethodVoidConst;
    static std::vector<int> resultStaticMethodArgs;
    std::vector<int> resultMethodArgs;
    static std::vector<int> resultMethodArgsConst;
};

bool MyTest::resultStaticMethodVoid = false;
bool MyTest::resultMethodVoidConst = false;
std::vector<int> MyTest::resultStaticMethodArgs = std::vector<int>();
std::vector<int> MyTest::resultMethodArgsConst = std::vector<int>();

// create new function and singleton instance for mock
MOCKC_METHOD1(pthread_detach,
              int(pthread_t __newthread))

GTEST_TEST(thread, staticMethodVoid) {
    MyTest::resultStaticMethodVoid = false;

    EXPECT_CALL(MOCKC_INSTANCE(pthread_detach), pthread_detach(_))
        .WillOnce(Return(-1))
        .WillOnce(Return(0));

    EXPECT_THROW(
        {
            try {
                blet::Thread thrd;
                thrd.detach();
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread is not detachable");
                throw;
            }
        },
        blet::Thread::Exception);

    EXPECT_THROW(
        {
            try {
                blet::Thread thrd;
                thrd.start(&MyTest::staticMethodVoid);
                thrd.detach();
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to detach thread");
                throw;
            }
        },
        blet::Thread::Exception);

    {
        blet::Thread thrd;
        thrd.start(&MyTest::staticMethodVoid);
        thrd.detach();
    }
}