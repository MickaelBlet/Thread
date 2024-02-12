#include <iostream>

#include "blet/thread.h"

class Example {
  public:
    Example() :
        _privateVar(0) {}

    void methodExampleWithRefArg(double& d) {
        d += 1.0;
        ++_privateVar;
        std::cout << "Inside methodExampleWithRefArg(" << d << ")" << std::endl;
    }

    void methodExampleWithArg(double d) {
        ++_privateVar;
        std::cout << "Inside methodExampleWithArg(" << d << ")" << std::endl;
    }

    void methodExample(void) {
        ++_privateVar;
        std::cout << "Inside methodExample" << std::endl;
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
    std::cout << "Example private var: " << example.getPrivateVar()
              << std::endl;
    blet::Thread thrd;
    thrd.start(&Example::methodExample, &example);
    thrd.join();
    std::cout << "Example private var: " << example.getPrivateVar()
              << std::endl;
    thrd.start(&Example::methodExampleWithArg, &example, 42.42);
    thrd.join();
    std::cout << "Example private var: " << example.getPrivateVar()
              << std::endl;
    double d = 42.42;
    // type of object, type of first argument (double&)
    thrd.start<Example, double&>(&Example::methodExampleWithRefArg, &example,
                                 d);
    thrd.join();
    std::cout << "New value of d: " << d << std::endl;
    std::cout << "Example private var: " << example.getPrivateVar()
              << std::endl;
    std::cout << "===  End  ===" << std::endl;
    return 0;
}
