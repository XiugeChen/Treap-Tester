//
// Created by Xiuge Chen on 3/18/20.
//

#include "data_generator.h"

namespace Xiuge { namespace TreapTester {

DataGenerator::DataGenerator(uint32_t range) {
    mGenerator = std::mt19937(mRd());
    mKeyDist = std::uniform_int_distribution<uint32_t>(0, range);
    mPercentDist = std::uniform_real_distribution<double>(0.0, 1.0);
}

Operation DataGenerator::gen_with_prob(std::array<double, 3> percentage) {
    if (percentage[0] + percentage[1] + percentage[2] != 1)
        throw std::runtime_error("[DataGenerator] probability sums not equal to one");

    double probIndex = mPercentDist(mGenerator);

    if (probIndex < percentage[0]) {
        return gen_insertion();
    }
    else if (probIndex < percentage[0] + percentage[1]) {
        return gen_deletion();
    }
    else {
        return gen_search();
    }
}

Operation DataGenerator::gen_insertion() {
    Element insertion = Element(mId++, mKeyDist(mGenerator));
    mInsertedElems[insertion.id] = insertion.key;

    return Operation(OperationType::INSERT, insertion);
}

Operation DataGenerator::gen_deletion() {
    if (mId <= 1) {
        return Operation(OperationType::DELETE, Element(0, mKeyDist(mGenerator)));
    }

    mIdDist = std::uniform_int_distribution<uint32_t>(1, mId - 1);
    uint32_t id = mIdDist(mGenerator);

    if (mDeletedElems.count(id) == 0) {
        mDeletedElems[id] = mInsertedElems[id];
        return Operation(OperationType::DELETE, Element(0, mInsertedElems[id]));
    }
    else {
        return Operation(OperationType::DELETE, Element(0, mKeyDist(mGenerator)));
    }
}

Operation DataGenerator::gen_search() {
    return Operation(OperationType::SEARCH, Element(0, mKeyDist(mGenerator)));
}

}} // namespace ::Xiuge::TreapTester

