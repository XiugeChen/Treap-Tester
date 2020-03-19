//
// Created by Xiuge Chen on 3/18/20.
//

#ifndef TREAPTESTER_TYPES_H
#define TREAPTESTER_TYPES_H

#include <cstdint>

namespace Xiuge { namespace TreapTester {

struct Element {
    Element(uint32_t newId, uint32_t newKey) {
        id = newId;
        key = newKey;
    }

    Element() {
        id = 0;
        key = 0;
    }

    uint32_t id;
    uint32_t key;
};

enum class OperationType {
    INSERT,
    DELETE,
    SEARCH
};

struct Operation {
    Operation(OperationType newType, Element newElem) {
        type = newType;
        element = newElem;
    }

    OperationType type;
    Element element;
};

/**
 * Common interface of all data structures
 */
class IDataStruct {
    virtual void insert(Operation operation) = 0;
    // Return true if delete successfully, otherwise return false
    virtual bool delete_key(Operation operation) = 0;
    // Return element if find it, otherwise return NULL
    virtual Element search_key(Operation operation) = 0;
};

}} // namespace ::Xiuge::TreapTester

#endif //TREAPTESTER_TYPES_H
