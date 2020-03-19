//
// Created by Xiuge Chen on 3/19/20.
//

#include <spdlog/spdlog.h>

#include "tester_app.h"

namespace Xiuge { namespace TreapTester {

TesterApp::TesterApp(const uint32_t keyRange, IDataStruct* dataStruct)
    : mDataGen(new DataGenerator(keyRange))
    , mDataStruct(dataStruct)
{}

void TesterApp::percent_fixed_test(const std::vector<uint32_t> dataLens, const std::array<double, 3> percentage) const {
    spdlog::info("Start percentage fixed testing with percentage: insert={}, delete={}, search={}",
                 percentage[0], percentage[1], percentage[2]);

    for (auto len: dataLens) {
        spdlog::info("Start with length={}", len);

        for (uint32_t i = 0; i < len; i++) {
            // TODO: time count

            Operation operation = mDataGen->gen_with_prob(percentage);

            switch (operation.type) {
                case OperationType::INSERT :
                    mDataStruct->insert(operation);
                    break;
                case OperationType::DELETE :
                    mDataStruct->delete_key(operation);
                    break;
                case OperationType::SEARCH :
                    mDataStruct->search_key(operation);
                    break;
                default:
                    throw std::runtime_error("[TesterApp] Unkown operation type");
            }
        }
    }
}

void TesterApp::len_fixed_test(const uint32_t dataLen, const std::vector<std::array<double, 3>> percentages) const {
    spdlog::info("Start with length fixed testing with length={}", dataLen);

    for (auto percentage: percentages) {
        spdlog::info("Start with percentage: insert={}, delete={}, search={}",
                     percentage[0], percentage[1], percentage[2]);

        for (uint32_t i = 0; i < dataLen; i++) {
            // TODO: time count

            Operation operation = mDataGen->gen_with_prob(percentage);

            switch (operation.type) {
                case OperationType::INSERT :
                    mDataStruct->insert(operation);
                    break;
                case OperationType::DELETE :
                    mDataStruct->delete_key(operation);
                    break;
                case OperationType::SEARCH :
                    mDataStruct->search_key(operation);
                    break;
                default:
                    throw std::runtime_error("[TesterApp] Unkown operation type");
            }
        }
    }
}

}} // namespace ::Xiuge::TreapTester