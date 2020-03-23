
#include <spdlog/spdlog.h>

#include "tester_app.h"
#include "dummy.h"
#include "treap.h"

using namespace ::Xiuge::TreapTester;

const uint32_t KEY_RANGE = static_cast<const uint32_t>(pow(10, 7));
const uint32_t DATA_LEN_BASE = static_cast<const uint32_t>(pow(10, 5));

int main() {
    spdlog::set_level(spdlog::level::info);

    spdlog::info("Start treap tester");

    Dummy dummy;
    Treap treap;
    TesterApp testerApp(KEY_RANGE, &treap, &dummy);

    // Experiement 1: test with various element length on insertion only
    std::vector<uint32_t> dataLens{1 * DATA_LEN_BASE, 2 * DATA_LEN_BASE, 5 * DATA_LEN_BASE, 8 * DATA_LEN_BASE, 10 * DATA_LEN_BASE};
    std::array<double, 3> percentage{1.0, 0.0, 0.0};
    testerApp.percent_fixed_test(dataLens, percentage);

    /*/ Experiement 2: test with various deletion percentage
    std::vector<std::array<double, 3>> percentages;
    percentages.push_back({0.999,0.001,0});
    percentages.push_back({0.995,0.005,0});
    percentages.push_back({0.99,0.01,0});
    percentages.push_back({0.95,0.05,0});
    percentages.push_back({0.9,0.1,0});
    testerApp.len_fixed_test(10 * DATA_LEN_BASE, percentages);

    // Experiement 3: test with
    std::vector<std::array<double, 3>> percentages;
    percentages.push_back({0.999, 0, 0.001});
    percentages.push_back({0.995, 0, 0.005});
    percentages.push_back({0.99, 0, 0.01});
    percentages.push_back({0.95, 0, 0.05});
    percentages.push_back({0.9, 0, 0.1});
    testerApp.len_fixed_test(10 * DATA_LEN_BASE, percentages);

    // Experiement 4: test with various element length and fixed percentage of
    std::vector<uint32_t> dataLens{1 * DATA_LEN_BASE, 2 * DATA_LEN_BASE, 5 * DATA_LEN_BASE, 8 * DATA_LEN_BASE, 10 * DATA_LEN_BASE};
    std::array<double, 3> percentage{0.9, 0.05, 0.05};
    testerApp.percent_fixed_test(dataLens, percentage);
    */
    return 0;
}