//
// Created by Xiuge Chen on 3/19/20.
//

#include <chrono>
#include <spdlog/spdlog.h>

#include "tester_app.h"

namespace Xiuge::TreapTester {

TesterApp::TesterApp(const uint32_t keyRange, Treap* treap, Dummy* dummy)
    : mDataGen(new DataGenerator(keyRange))
    , mTreap(treap)
    , mDummy(dummy)
{}

void TesterApp::percent_fixed_test(const std::vector<uint32_t> dataLens, const std::array<double, 3> percentage) {
    spdlog::info("Start percentage fixed testing with percentage: insert={}, delete={}, search={}",
                 percentage[0], percentage[1], percentage[2]);

    for (auto len: dataLens) {
        spdlog::info("Start with length={}", len);

        // generate data fisrt
        mData.clear();
        mData.shrink_to_fit();

        for (uint32_t i = 0; i < len; i++) {
            mData.push_back(mDataGen->gen_with_prob(percentage));
        }

        // start experiments
        long long int runningTime = runTreap();
        spdlog::info("Finsh length fixed testing on Treap with length={}, timeInMilli={}", len, runningTime);

        runningTime = runDummy();
        spdlog::info("Finsh length fixed testing on Dummy with length={}, timeInMilli={}", len, runningTime);
    }
}

void TesterApp::len_fixed_test(const uint32_t dataLen, const std::vector<std::array<double, 3>> percentages) {
    spdlog::info("Start with length fixed testing with length={}", dataLen);

    for (auto percentage: percentages) {
        spdlog::info("Start with percentage: insert={}, delete={}, search={}",
                     percentage[0], percentage[1], percentage[2]);

        // generate data fisrt
        mData.clear();
        mData.shrink_to_fit();

        for (uint32_t i = 0; i < dataLen; i++) {
            mData.push_back(mDataGen->gen_with_prob(percentage));
        }

        // start experiments
        long long int runningTime = runTreap();
        spdlog::info("Finsh length fixed testing on Treap with insert={}, delete={}, search={}, timeInMilli={}",
                     percentage[0], percentage[1], percentage[2], runningTime);

        runningTime = runDummy();
        spdlog::info("Finsh length fixed testing on Dummy with insert={}, delete={}, search={}, timeInMilli={}",
                     percentage[0], percentage[1], percentage[2], runningTime);
    }
}

long long int TesterApp::runTreap() {
    mTreap->clear();

    long long int startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();

    for (auto operation : mData) {
        switch (operation.type) {
            case OperationType::INSERT :
                mTreap->insert(operation);
                break;
            case OperationType::DELETE :
                mTreap->delete_key(operation);
                break;
            case OperationType::SEARCH :
                mTreap->search_key(operation);
                break;
            default:
                throw std::runtime_error("[TesterApp] Unkown operation type");
        }
    }

    long long int endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();

    return endTime - startTime;
}

long long int TesterApp::runDummy() {
    mDummy->clear();

    long long int startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();

    for (auto operation : mData) {
        switch (operation.type) {
            case OperationType::INSERT :
                mDummy->insert(operation);
                break;
            case OperationType::DELETE :
                mDummy->delete_key(operation);
                break;
            case OperationType::SEARCH :
                mDummy->search_key(operation);
                break;
            default:
                throw std::runtime_error("[TesterApp] Unkown operation type");
        }
    }

    long long int endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();

    return endTime - startTime;
}

} // namespace ::Xiuge::TreapTester