//
// Created by Xiuge Chen on 3/19/20.
//

#ifndef TREAPTESTER_DUMMY_H
#define TREAPTESTER_DUMMY_H

#include <vector>

#include "types.h"

namespace Xiuge::TreapTester {

/**
 * Dummy implementation of this data structure
 * Basically it is a dynamic array that puts new elements at the end of array and search elements from beginning to end
 */
class Dummy : public IDataStruct {
public:
    void insert(const Operation operation) override;
    bool delete_key(const Operation operation) override;
    Element search_key(const Operation operation) override;
    void clear() override;

private:
    std::vector<Element> mDynamicArray;
};

} // namespace ::Xiuge::TreapTester

#endif //TREAPTESTER_DUMMY_H
