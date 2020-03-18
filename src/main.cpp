#include <iostream>

#include "data_generator.h"

using namespace ::Xiuge;

int main() {
    std::cout << "Hello, World!" << std::endl;
    TreapTester::DataGenerator test = TreapTester::DataGenerator();
    test.gen_insertion();
    return 0;
}