#include <iostream>

#include "data_generator.h"

using namespace ::Xiuge::TreapTester;

uint32_t KEY_RANGE = pow(10, 7);
uint32_t DATA_LEN = pow(10, 3);

int main() {
    DataGenerator dataGen(KEY_RANGE);

    for (int i = 0; i < DATA_LEN; i++) {
        Operation operation = dataGen.gen_insertion();
        std::cout << "Insert: " << operation.element.id << ", " << operation.element.key << std::endl;
    }

    return 0;
}