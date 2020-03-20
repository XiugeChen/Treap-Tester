//
// Created by Xiuge Chen on 3/19/20.
//

#ifndef TREAPTESTER_TREAP_H
#define TREAPTESTER_TREAP_H

#include <random>

#include "types.h"

namespace Xiuge { namespace TreapTester {

class Treap : public IDataStruct {
public:
    Treap();

    void insert(const Operation operation) override;
    bool delete_key(const Operation operation) override;
    Element search_key(const Operation operation) override;

    void print(TreapNode* node, int level);

private:
    // Perform binary search tree insert, return the inserted node
    TreapNode* bst_insert(TreapNode* startNode, Element insertElem);
    // perform binary search tree search
    TreapNode* bst_search(TreapNode* startNode, Element searchElem);
    //
    void maintain_priority(TreapNode* startNode);

    // Will be used to obtain a seed for the random number engine
    std::random_device mRd;
    // Standard mersenne_twister_engine seeded with mRd()
    std::mt19937 mGenerator;
    // Uniform real distribution of priority
    std::uniform_real_distribution<double> mPriorityDist;

    std::unique_ptr<TreapNode> mRoot{ nullptr };
};

}} // namespace ::Xiuge::TreapTester

#endif //TREAPTESTER_TREAP_H
