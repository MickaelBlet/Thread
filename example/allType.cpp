#include <iostream>
#include <sstream>

#include "mblet/threadator.h"

struct Test {
    void method0() {
        std::ostringstream oss;
        oss << "method0" << std::endl;
        std::cout << oss.str();
    }
    void method1(int a1) {
        std::ostringstream oss;
        oss << "method1"
            << ": " << a1 << std::endl;
        std::cout << oss.str();
    }
    void method2(int a1, int a2) {
        std::ostringstream oss;
        oss << "method2"
            << ": " << a1 << ", " << a2 << std::endl;
        std::cout << oss.str();
    }
    void method3(int a1, int a2, int a3) {
        std::ostringstream oss;
        oss << "method3"
            << ": " << a1 << ", " << a2 << ", " << a3 << std::endl;
        std::cout << oss.str();
    }
    void method4(int a1, int a2, int a3, int a4) {
        std::ostringstream oss;
        oss << "method4"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << std::endl;
        std::cout << oss.str();
    }
    void method5(int a1, int a2, int a3, int a4, int a5) {
        std::ostringstream oss;
        oss << "method5"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << std::endl;
        std::cout << oss.str();
    }
    void method6(int a1, int a2, int a3, int a4, int a5, int a6) {
        std::ostringstream oss;
        oss << "method6"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << std::endl;
        std::cout << oss.str();
    }
    void method7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        std::ostringstream oss;
        oss << "method7"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7
            << std::endl;
        std::cout << oss.str();
    }
    void method8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
        std::ostringstream oss;
        oss << "method8"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << std::endl;
        std::cout << oss.str();
    }
    void method9(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9) {
        std::ostringstream oss;
        oss << "method9"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << ", " << a9 << std::endl;
        std::cout << oss.str();
    }
    void method10(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
        std::ostringstream oss;
        oss << "method10"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << ", " << a9 << ", " << a10 << std::endl;
        std::cout << oss.str();
    }
    void cmethod0() const {
        std::ostringstream oss;
        oss << "cmethod0" << std::endl;
        std::cout << oss.str();
    }
    void cmethod1(int a1) const {
        std::ostringstream oss;
        oss << "cmethod1"
            << ": " << a1 << std::endl;
        std::cout << oss.str();
    }
    void cmethod2(int a1, int a2) const {
        std::ostringstream oss;
        oss << "cmethod2"
            << ": " << a1 << ", " << a2 << std::endl;
        std::cout << oss.str();
    }
    void cmethod3(int a1, int a2, int a3) const {
        std::ostringstream oss;
        oss << "cmethod3"
            << ": " << a1 << ", " << a2 << ", " << a3 << std::endl;
        std::cout << oss.str();
    }
    void cmethod4(int a1, int a2, int a3, int a4) const {
        std::ostringstream oss;
        oss << "cmethod4"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << std::endl;
        std::cout << oss.str();
    }
    void cmethod5(int a1, int a2, int a3, int a4, int a5) const {
        std::ostringstream oss;
        oss << "cmethod5"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << std::endl;
        std::cout << oss.str();
    }
    void cmethod6(int a1, int a2, int a3, int a4, int a5, int a6) const {
        std::ostringstream oss;
        oss << "cmethod6"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << std::endl;
        std::cout << oss.str();
    }
    void cmethod7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        std::ostringstream oss;
        oss << "cmethod7"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7
            << std::endl;
        std::cout << oss.str();
    }
    void cmethod8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) const {
        std::ostringstream oss;
        oss << "cmethod8"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << std::endl;
        std::cout << oss.str();
    }
    void cmethod9(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9) const {
        std::ostringstream oss;
        oss << "cmethod9"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << ", " << a9 << std::endl;
        std::cout << oss.str();
    }
    void cmethod10(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) const {
        std::ostringstream oss;
        oss << "cmethod10"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << ", " << a9 << ", " << a10 << std::endl;
        std::cout << oss.str();
    }
    static void smethod0() {
        std::ostringstream oss;
        oss << "smethod0" << std::endl;
        std::cout << oss.str();
    }
    static void smethod1(int a1) {
        std::ostringstream oss;
        oss << "smethod1"
            << ": " << a1 << std::endl;
        std::cout << oss.str();
    }
    static void smethod2(int a1, int a2) {
        std::ostringstream oss;
        oss << "smethod2"
            << ": " << a1 << ", " << a2 << std::endl;
        std::cout << oss.str();
    }
    static void smethod3(int a1, int a2, int a3) {
        std::ostringstream oss;
        oss << "smethod3"
            << ": " << a1 << ", " << a2 << ", " << a3 << std::endl;
        std::cout << oss.str();
    }
    static void smethod4(int a1, int a2, int a3, int a4) {
        std::ostringstream oss;
        oss << "smethod4"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << std::endl;
        std::cout << oss.str();
    }
    static void smethod5(int a1, int a2, int a3, int a4, int a5) {
        std::ostringstream oss;
        oss << "smethod5"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << std::endl;
        std::cout << oss.str();
    }
    static void smethod6(int a1, int a2, int a3, int a4, int a5, int a6) {
        std::ostringstream oss;
        oss << "smethod6"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << std::endl;
        std::cout << oss.str();
    }
    static void smethod7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        std::ostringstream oss;
        oss << "smethod7"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7
            << std::endl;
        std::cout << oss.str();
    }
    static void smethod8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
        std::ostringstream oss;
        oss << "smethod8"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << std::endl;
        std::cout << oss.str();
    }
    static void smethod9(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9) {
        std::ostringstream oss;
        oss << "smethod9"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << ", " << a9 << std::endl;
        std::cout << oss.str();
    }
    static void smethod10(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
        std::ostringstream oss;
        oss << "smethod10"
            << ": " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", "
            << a8 << ", " << a9 << ", " << a10 << std::endl;
        std::cout << oss.str();
    }
};

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    Test test;
    mblet::Threadator thrd0(&Test::method0, &test);
    mblet::Threadator thrd1(&Test::method1, &test, 1);
    mblet::Threadator thrd2(&Test::method2, &test, 1, 2);
    mblet::Threadator thrd3(&Test::method3, &test, 1, 2, 3);
    mblet::Threadator thrd4(&Test::method4, &test, 1, 2, 3, 4);
    mblet::Threadator thrd5(&Test::method5, &test, 1, 2, 3, 4, 5);
    mblet::Threadator thrd6(&Test::method6, &test, 1, 2, 3, 4, 5, 6);
    mblet::Threadator thrd7(&Test::method7, &test, 1, 2, 3, 4, 5, 6, 7);
    mblet::Threadator thrd8(&Test::method8, &test, 1, 2, 3, 4, 5, 6, 7, 8);
    mblet::Threadator thrd9(&Test::method9, &test, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    mblet::Threadator thrd10(&Test::method10, &test, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    mblet::Threadator cthrd0(&Test::cmethod0, &test);
    mblet::Threadator cthrd1(&Test::cmethod1, &test, 1);
    mblet::Threadator cthrd2(&Test::cmethod2, &test, 1, 2);
    mblet::Threadator cthrd3(&Test::cmethod3, &test, 1, 2, 3);
    mblet::Threadator cthrd4(&Test::cmethod4, &test, 1, 2, 3, 4);
    mblet::Threadator cthrd5(&Test::cmethod5, &test, 1, 2, 3, 4, 5);
    mblet::Threadator cthrd6(&Test::cmethod6, &test, 1, 2, 3, 4, 5, 6);
    mblet::Threadator cthrd7(&Test::cmethod7, &test, 1, 2, 3, 4, 5, 6, 7);
    mblet::Threadator cthrd8(&Test::cmethod8, &test, 1, 2, 3, 4, 5, 6, 7, 8);
    mblet::Threadator cthrd9(&Test::cmethod9, &test, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    mblet::Threadator cthrd10(&Test::cmethod10, &test, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    mblet::Threadator sthrd0(&Test::smethod0);
    mblet::Threadator sthrd1(&Test::smethod1, 1);
    mblet::Threadator sthrd2(&Test::smethod2, 1, 2);
    mblet::Threadator sthrd3(&Test::smethod3, 1, 2, 3);
    mblet::Threadator sthrd4(&Test::smethod4, 1, 2, 3, 4);
    mblet::Threadator sthrd5(&Test::smethod5, 1, 2, 3, 4, 5);
    mblet::Threadator sthrd6(&Test::smethod6, 1, 2, 3, 4, 5, 6);
    mblet::Threadator sthrd7(&Test::smethod7, 1, 2, 3, 4, 5, 6, 7);
    mblet::Threadator sthrd8(&Test::smethod8, 1, 2, 3, 4, 5, 6, 7, 8);
    mblet::Threadator sthrd9(&Test::smethod9, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    mblet::Threadator sthrd10(&Test::smethod10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    thrd0.join();
    thrd1.join();
    thrd2.join();
    thrd3.join();
    thrd4.join();
    thrd5.join();
    thrd6.join();
    thrd7.join();
    thrd8.join();
    thrd9.join();
    thrd10.join();
    cthrd0.join();
    cthrd1.join();
    cthrd2.join();
    cthrd3.join();
    cthrd4.join();
    cthrd5.join();
    cthrd6.join();
    cthrd7.join();
    cthrd8.join();
    cthrd9.join();
    cthrd10.join();
    sthrd0.join();
    sthrd1.join();
    sthrd2.join();
    sthrd3.join();
    sthrd4.join();
    sthrd5.join();
    sthrd6.join();
    sthrd7.join();
    sthrd8.join();
    sthrd9.join();
    sthrd10.join();
    return 0;
}
