//
// Created by Xiuge Chen on 3/19/20.
//

#ifndef TREAPTESTER_TESTER_AOO_H
#define TREAPTESTER_TESTER_AOO_H

#include <memory>
#include <array>

#include "treap.h"
#include "dummy.h"
#include "data_generator.h"

namespace Xiuge::TreapTester {

class TesterApp {
public:
    TesterApp(const uint32_t keyRange, Treap* treap, Dummy* dummy);

    void percent_fixed_test(const std::vector<uint32_t> dataLens, const std::array<double, 3> percentage);

    void len_fixed_test(const uint32_t dataLen, const std::vector<std::array<double, 3>> percentages);

private:
    long long int runTreap();
    long long int runDummy();

    std::unique_ptr<DataGenerator> mDataGen;
    std::vector<Operation> mData;
    Treap* mTreap;
    Dummy* mDummy;
};

} // namespace ::Xiuge::TreapTester

#endif //TREAPTESTER_TESTER_AOO_H
