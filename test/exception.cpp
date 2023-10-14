#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "blet/thread.h"

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

GTEST_TEST(thread, staticMethodVoid_AlreadyStarted) {
    MyTest::resultStaticMethodVoid = false;

    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                thrd.start(&MyTest::staticMethodVoid);
                thrd.start(&MyTest::staticMethodVoid);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, staticMethodArg1_AlreadyStarted) {
    MyTest::resultStaticMethodVoid = false;

    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                int v = 42;
                thrd.start<int&>(&MyTest::staticMethodArg1, v);
                thrd.start<int&>(&MyTest::staticMethodArg1, v);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, staticMethodArg2_AlreadyStarted) {
    MyTest::resultStaticMethodVoid = false;

    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                thrd.start(&MyTest::staticMethodArg2, 1, 2);
                thrd.start(&MyTest::staticMethodArg2, 1, 2);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodVoid_AlreadyStarted) {
    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                MyTest t;
                thrd.start(&MyTest::methodVoid, &t);
                thrd.start(&MyTest::methodVoid, &t);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

static void launchThread_AlreadyStarted(blet::Thread& thrd) {
    MyTest t;
    int v = 42;
    thrd.start<MyTest, int&>(&MyTest::methodArg1, &t, v);
    sleep(1);
    thrd.start<MyTest, int&>(&MyTest::methodArg1, &t, v);
}

GTEST_TEST(thread, methodArg1_AlreadyStarted) {
    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                launchThread_AlreadyStarted(thrd);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodArg2_AlreadyStarted) {
    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                MyTest t;
                thrd.start(&MyTest::methodArg2, &t, 1, 2);
                thrd.start(&MyTest::methodArg2, &t, 1, 2);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodVoidConst_AlreadyStarted) {
    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                MyTest t;
                thrd.start(&MyTest::methodVoidConst, &t);
                thrd.start(&MyTest::methodVoidConst, &t);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodArg1Const_AlreadyStarted) {
    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                MyTest t;
                thrd.start(&MyTest::methodArg1Const, &t, 1);
                thrd.start(&MyTest::methodArg1Const, &t, 1);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodArg2Const_AlreadyStarted) {
    EXPECT_THROW(
        {
            blet::Thread thrd;
            try {
                MyTest t;
                thrd.start(&MyTest::methodArg2Const, &t, 1, 2);
                thrd.start(&MyTest::methodArg2Const, &t, 1, 2);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread already started");
                thrd.join();
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodArg2Const_NotJoinable) {
    EXPECT_THROW(
        {
            try {
                blet::Thread thrd;
                thrd.join();
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Thread is not joinable");
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodArg2Const_NotJoining) {
    MyTest t;
    blet::Thread thrd;
    thrd.start(&MyTest::methodArg2Const, &t, 1, 2);
}