//
// Created by Xiuge Chen on 3/18/20.
//

#ifndef TREAPTESTER_DATA_GENERATOR_H
#define TREAPTESTER_DATA_GENERATOR_H

#include <iostream>
#include <random>
#include <unordered_map>

#include "types.h"

namespace Xiuge { namespace TreapTester {

/**
 * Data generator of this experiment, will produce one of insertion, deletion or search operation
 */
class DataGenerator {
public:
    DataGenerator(uint32_t range);

    Operation gen_insertion();
    Operation gen_deletion();
    Operation gen_search();

private:
    // Will be used to obtain a seed for the random number engine
    std::random_device mRd;
    // Standard mersenne_twister_engine seeded with mRd()
    std::mt19937 mGenerator;
    // Uniform distribution of key (is fixed at construction stage)
    std::uniform_int_distribution<uint32_t > mKeyDist;
    // Uniform distribution of id (is changed every time call deletion)
    std::uniform_int_distribution<uint32_t > mIdDist;

    // A map to store all deleted elements
    std::unordered_map<uint32_t, uint32_t> mDeletedElems;
    // A map to store all inserted elements
    std::unordered_map<uint32_t, uint32_t> mInsertedElems;
    // ID of next element
    uint32_t mId = 1;
};

}} // namespace ::Xiuge::TreapTester

#endif //TREAPTESTER_DATA_GENERATOR_H
