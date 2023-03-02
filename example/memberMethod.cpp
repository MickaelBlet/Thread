#include <iostream>

#include "mblet/threadator.h"

class Example {
  public:
    Example() :
        _privateVar(0) {}

    void threadExampleWithRefArg(double& d) {
        d += 1.0;
        ++_privateVar;
        std::cout << "Inside threadExampleWithRefArg(" << d << ")" << std::endl;
    }

    void threadExampleWithArg(double d) {
        ++_privateVar;
        std::cout << "Inside threadExampleWithArg(" << d << ")" << std::endl;
    }

    void threadExample(void) {
        ++_privateVar;
        std::cout << "Inside threadExample" << std::endl;
    }

    const int& getPrivateVar() const {
        return _privateVar;
    }

  private:
    int _privateVar;
};

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    std::cout << "=== Start ===" << std::endl;
    Example example;
    std::cout << "Example private var: " << example.getPrivateVar() << std::endl;
    mblet::Threadator thrd;
    thrd.start(&Example::threadExample, &example);
    thrd.join();
    std::cout << "Example private var: " << example.getPrivateVar() << std::endl;
    thrd.start(&Example::threadExampleWithArg, &example, 42.42);
    thrd.join();
    std::cout << "Example private var: " << example.getPrivateVar() << std::endl;
    double d = 42.42;
    // type of object, type of first argument (double&)
    thrd.start<Example, double&>(&Example::threadExampleWithRefArg, &example, d);
    thrd.join();
    std::cout << "New value of d: " << d << std::endl;
    std::cout << "Example private var: " << example.getPrivateVar() << std::endl;
    std::cout << "===  End  ===" << std::endl;
    return 0;
}