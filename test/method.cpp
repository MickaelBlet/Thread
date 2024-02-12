#include <gtest/gtest.h>

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

GTEST_TEST(thread, staticMethodVoid) {
    MyTest::resultStaticMethodVoid = false;
    blet::Thread thrd(&MyTest::staticMethodVoid);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_TRUE(MyTest::resultStaticMethodVoid);
    MyTest::resultStaticMethodVoid = false;
    thrd.start(&MyTest::staticMethodVoid);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_TRUE(MyTest::resultStaticMethodVoid);
}

GTEST_TEST(thread, staticMethodArg1) {
    int v = 42;
    blet::Thread thrd;
    thrd.start<int&>(&MyTest::staticMethodArg1, v);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_EQ(v, 43);
    EXPECT_EQ(MyTest::resultStaticMethodArgs[0], 43);
    thrd.start<int&>(&MyTest::staticMethodArg1, v);
    thrd.join();
    EXPECT_EQ(v, 44);
    EXPECT_EQ(MyTest::resultStaticMethodArgs[0], 44);
}

GTEST_TEST(thread, staticMethodArg2) {
    blet::Thread thrd(&MyTest::staticMethodArg2, 1, 2);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_EQ(MyTest::resultStaticMethodArgs[0], 1);
    EXPECT_EQ(MyTest::resultStaticMethodArgs[1], 2);
}

GTEST_TEST(thread, methodVoid) {
    MyTest t;
    t.resultMethodVoid = false;
    blet::Thread thrd(&MyTest::methodVoid, &t);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_TRUE(t.resultMethodVoid);
}

GTEST_TEST(thread, methodArg1) {
    int i = 42;
    MyTest t;
    blet::Thread thrd;
    thrd.start<MyTest, int&>(&MyTest::methodArg1, &t, i);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_EQ(i, 43);
    EXPECT_EQ(t.resultMethodArgs[0], 43);
}

GTEST_TEST(thread, methodArg2) {
    MyTest t;
    blet::Thread thrd(&MyTest::methodArg2, &t, 1, 2);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_EQ(t.resultMethodArgs[0], 1);
    EXPECT_EQ(t.resultMethodArgs[1], 2);
}

GTEST_TEST(thread, methodVoidConst) {
    MyTest t;
    t.resultMethodVoidConst = false;
    blet::Thread thrd(&MyTest::methodVoidConst, &t);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_TRUE(t.resultMethodVoidConst);
}

GTEST_TEST(thread, methodArg1Const) {
    MyTest t;
    blet::Thread thrd(&MyTest::methodArg1Const, &t, 1);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_EQ(t.resultMethodArgsConst[0], 1);
}

GTEST_TEST(thread, methodArg2Const) {
    MyTest t;
    blet::Thread thrd(&MyTest::methodArg2Const, &t, 1, 2);
    EXPECT_TRUE(thrd.joinable());
    thrd.join();
    EXPECT_EQ(t.resultMethodArgsConst[0], 1);
    EXPECT_EQ(t.resultMethodArgsConst[1], 2);
}
