#include <iostream>
#include <spdlog/spdlog.h>

#include "data_generator.h"

using namespace ::Xiuge::TreapTester;

const uint32_t KEY_RANGE = static_cast<const uint32_t>(pow(10, 7));
const uint32_t DATA_LEN = static_cast<const uint32_t>(pow(10, 0));

int main() {
    spdlog::info("Start treap tester");

    DataGenerator dataGen(KEY_RANGE);

    for (int i = 0; i < DATA_LEN; i++) {
        Operation operation = dataGen.gen_insertion();
        std::cout << "Insert: " << operation.element.id << ", " << operation.element.key << std::endl;
    }

    spdlog::info("Finish treap tester");

    return 0;
}