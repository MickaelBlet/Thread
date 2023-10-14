#include <unistd.h>

#include <iostream>

#include "blet/thread.h"

void functionExampleWithRefArg(double& d) {
    d += 1.0;
    std::cout << "Inside functionExampleWithRefArg(" << d << ")" << std::endl;
}

void functionExampleWithArg(double d) {
    std::cout << "Inside functionExampleWithArg(" << d << ")" << std::endl;
}

void functionExample(void) {
    std::cout << "Inside functionExample" << std::endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    std::cout << "=== Start ===" << std::endl;
    blet::Thread thrd;
    thrd.start(&functionExample);
    thrd.join();
    thrd.start(&functionExampleWithArg, 42.42);
    thrd.join();
    double d = 42.42;
    // type of first argument (double&)
    thrd.start<double&>(&functionExampleWithRefArg, d);
    thrd.join();
    std::cout << "New value of d: " << d << std::endl;
    std::cout << "===  End  ===" << std::endl;
    return 0;
}