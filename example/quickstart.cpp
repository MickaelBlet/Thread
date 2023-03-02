#include <iostream>

#include "mblet/threadator.h"

void threadExampleWithRefArg(double& d) {
    d += 1.0;
    std::cout << "Inside threadExampleWithRefArg(" << d << ")" << std::endl;
}

void threadExampleWithArg(double d) {
    std::cout << "Inside threadExampleWithArg(" << d << ")" << std::endl;
}

void threadExample(void) {
    std::cout << "Inside threadExample" << std::endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    std::cout << "=== Start ===" << std::endl;
    mblet::Threadator thrd;
    thrd.start(&threadExample);
    thrd.join();
    thrd.start(&threadExampleWithArg, 42.42);
    thrd.join();
    double d = 42.42;
    // return value (void), type of first argument (double&)
    thrd.start<double&>(&threadExampleWithRefArg, d);
    thrd.join();
    std::cout << "New value of d: " << d << std::endl;
    std::cout << "===  End  ===" << std::endl;
    return 0;
}