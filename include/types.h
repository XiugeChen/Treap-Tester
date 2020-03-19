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

    bool operator==(const Element& elem) {
        return id == elem.id && key == elem.key;
    }

    bool operator<(const Element& elem) {
        return (key < elem.key) || (key == elem.key && id < elem.id);
    }

    bool operator>(const Element& elem) {
        return (key > elem.key) || (key == elem.key && id > elem.id);
    }
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

struct TreapNode {
    TreapNode(Element newElem, double newPriority) {
        element = newElem;
        priority = newPriority;
    }

    Element element;
    double priority;

    std::unique_ptr<TreapNode> left{ nullptr };
    std::unique_ptr<TreapNode> right{ nullptr };
    TreapNode* parent{ nullptr };
};

/**
 * Common interface of all data structures
 */
class IDataStruct {
public:
    virtual void insert(const Operation operation) = 0;
    // Return true if delete successfully, otherwise return false
    virtual bool delete_key(const Operation operation) = 0;
    // Return element if find it, otherwise return NULL
    virtual Element search_key(const Operation operation) = 0;
};

}} // namespace ::Xiuge::TreapTester

#endif //TREAPTESTER_TYPES_H
