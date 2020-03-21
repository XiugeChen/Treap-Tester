//
// Created by Xiuge Chen on 3/19/20.
//

#include <spdlog/spdlog.h>

#include  "dummy.h"

namespace Xiuge { namespace TreapTester {

void Dummy::insert(const Operation operation) {
    if (operation.type != OperationType::INSERT)
        throw std::runtime_error("[Dummy] Insert invalid operation");

    if (operation.element.id == 0)
        throw std::runtime_error("[Dummy] Insert invalid element");

    spdlog::debug("[Dummy] insert operation, id={}, key={}", operation.element.id, operation.element.key);

    mDynamicArray.push_back(operation.element);
}

bool Dummy::delete_key(const Operation operation) {
    if (operation.type != OperationType::DELETE)
        throw std::runtime_error("[Dummy] Delete invalid operation");

    if (operation.element.id != 0)
        throw std::runtime_error("[Dummy] Delete invalid element");

    spdlog::debug("[Dummy] delete operation, id={}, key={}", operation.element.id, operation.element.key);

    std::vector<uint32_t>::size_type i = 0;
    for(; i < mDynamicArray.size(); i++) {
        if (mDynamicArray[i].key == operation.element.key)
            break;
    }

    if (i < mDynamicArray.size()) {
        mDynamicArray[i] = mDynamicArray[mDynamicArray.size() - 1];
        mDynamicArray.pop_back();

        // resize the array if has filled less than 1/4 elements
        if (mDynamicArray.size() < mDynamicArray.capacity() / 4) {
            uint32_t newCap = static_cast<uint32_t>(mDynamicArray.capacity() / 2);

            mDynamicArray.shrink_to_fit();
            mDynamicArray.reserve(newCap);

            spdlog::debug("[Dummy] resize dynamic array, newSize={}, newCapacity={}", mDynamicArray.size(),
                    mDynamicArray.capacity());
        }

        return true;
    }

    spdlog::debug("[Dummy] delete operation, can't find element");
    return false;
}

Element Dummy::search_key(const Operation operation) {
    if (operation.type != OperationType::SEARCH)
        throw std::runtime_error("[Dummy] Search invalid operation");

    if (operation.element.id != 0)
        throw std::runtime_error("[Dummy] Search invalid element");

    spdlog::debug("[Dummy] search operation, id={}, key={}", operation.element.id, operation.element.key);

    for (auto& element : mDynamicArray) {
        if (element.key == operation.element.key)
            return element;
    }

    spdlog::debug("[Dummy] search operation, can't find element");
    return{0, 0};
}

}} // namespace ::Xiuge::TreapTester
