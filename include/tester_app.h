//
// Created by Xiuge Chen on 3/19/20.
//

#ifndef TREAPTESTER_TESTER_AOO_H
#define TREAPTESTER_TESTER_AOO_H

#include <memory>
#include <array>

#include "types.h"
#include "data_generator.h"

namespace Xiuge { namespace TreapTester {

class TesterApp {
public:
    TesterApp(const uint32_t keyRange, IDataStruct* dataStruct);

    void percent_fixed_test(const std::vector<uint32_t> dataLens, const std::array<double, 3> percentage) const;

    void len_fixed_test(const uint32_t dataLen, const std::vector<std::array<double, 3>> percentages) const;

private:
    std::unique_ptr<DataGenerator> mDataGen;
    IDataStruct* mDataStruct;
};

}} // namespace ::Xiuge::TreapTester

#endif //TREAPTESTER_TESTER_AOO_H
