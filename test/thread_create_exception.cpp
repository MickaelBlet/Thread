#include <gtest/gtest.h>

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
MOCKC_METHOD4(int, pthread_create,
              (pthread_t* __newthread, const pthread_attr_t* __attr,
                  void* (*__start_routine)(void*), void* __arg));

GTEST_TEST(thread, staticMethodVoid) {
    MOCKC_NEW_INSTANCE(pthread_create);
    MyTest::resultStaticMethodVoid = false;

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                blet::Thread thrd;
                thrd.start(&MyTest::staticMethodVoid);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, staticMethodArg1) {
    MOCKC_NEW_INSTANCE(pthread_create);
    MyTest::resultStaticMethodVoid = false;

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                int v = 42;
                blet::Thread thrd;
                thrd.start<int&>(&MyTest::staticMethodArg1, v);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, staticMethodArg2) {
    MOCKC_NEW_INSTANCE(pthread_create);
    MyTest::resultStaticMethodVoid = false;

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                blet::Thread thrd;
                thrd.start(&MyTest::staticMethodArg2, 1, 2);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodVoid) {
    MOCKC_NEW_INSTANCE(pthread_create);

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                MyTest t;
                blet::Thread thrd;
                thrd.start(&MyTest::methodVoid, &t);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}

static void launchThread() {
    MyTest t;
    blet::Thread thrd;
    int v = 42;
    thrd.start<MyTest, int&>(&MyTest::methodArg1, &t, v);
}

GTEST_TEST(thread, methodArg1) {
    MOCKC_NEW_INSTANCE(pthread_create);

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                launchThread();
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodArg2) {
    MOCKC_NEW_INSTANCE(pthread_create);

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                MyTest t;
                blet::Thread thrd;
                thrd.start(&MyTest::methodArg2, &t, 1, 2);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodVoidConst) {
    MOCKC_NEW_INSTANCE(pthread_create);

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                MyTest t;
                blet::Thread thrd;
                thrd.start(&MyTest::methodVoidConst, &t);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodArg1Const) {
    MOCKC_NEW_INSTANCE(pthread_create);

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                MyTest t;
                blet::Thread thrd;
                thrd.start(&MyTest::methodArg1Const, &t, 1);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}

GTEST_TEST(thread, methodArg2Const) {
    MOCKC_NEW_INSTANCE(pthread_create);

    EXPECT_CALL(MOCKC_INSTANCE(pthread_create), pthread_create(_, _, _, _))
        .WillOnce(Return(-1));

    EXPECT_THROW(
        {
            MOCKC_GUARD(pthread_create);
            try {
                MyTest t;
                blet::Thread thrd;
                thrd.start(&MyTest::methodArg2Const, &t, 1, 2);
            }
            catch (const blet::Thread::Exception& e) {
                EXPECT_STREQ(e.what(), "Failed to create thread");
                throw;
            }
        },
        blet::Thread::Exception);
}
