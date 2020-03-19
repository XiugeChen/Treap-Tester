//
// Created by Xiuge Chen on 3/19/20.
//

#include <spdlog/spdlog.h>

#include <memory>

#include "treap.h"

namespace Xiuge { namespace TreapTester {

Treap::Treap()
    : mGenerator( std::mt19937(mRd()) )
    , mPriorityDist( std::uniform_real_distribution<double>(0.0, 1.0) )
{}

void Treap::insert(const Operation operation) {
    if (operation.type != OperationType::INSERT)
        throw std::runtime_error("[Treap] Insert invalid operation");

    if (operation.element.id == 0)
        throw std::runtime_error("[Treap] Insert invalid element");

    if (!mRoot) {
        mRoot = std::make_unique<TreapNode>(operation.element, mPriorityDist(mGenerator));
        return;
    }

    TreapNode* insertedNode = bst_insert(mRoot.get(), operation.element);

    maintain_priority(insertedNode);
}

bool Treap::delete_key(const Operation operation) {
    if (operation.type != OperationType::DELETE)
        throw std::runtime_error("[Treap] Delete invalid operation");

    if (operation.element.id != 0)
        throw std::runtime_error("[Treap] Delete invalid element");

    TreapNode* deleteNode = bst_search(mRoot.get(), operation.element);

    if (deleteNode) {
        deleteNode->priority = 2;
        maintain_priority(deleteNode);
    }

    spdlog::info("[Treap] delete operation, can't find element");
    return false;
}

Element Treap::search_key(const Operation operation) {
    if (operation.type != OperationType::SEARCH)
        throw std::runtime_error("[Treap] Search invalid operation");

    if (operation.element.id != 0)
        throw std::runtime_error("[Treap] Search invalid element");

    if (mRoot) {
        TreapNode* result = bst_search(mRoot.get(), operation.element);

        if (result)
            return result->element;
    }

    spdlog::info("[Treap] search operation, can't find element");
    return{0, 0};
}

TreapNode* Treap::bst_insert(TreapNode* startNode, Element insertElem) {
    if (!startNode)
        throw std::runtime_error("[Treap] insert start node is null");

    if (insertElem == startNode->element)
        throw std::runtime_error("[Treap] Inserted element already exist in treap");

    if (insertElem < startNode->element) {
        if (startNode->left)
            return bst_insert(startNode->left.get(), insertElem);
        else {
            startNode->left = std::make_unique<TreapNode>(insertElem, mPriorityDist(mGenerator));
            startNode->left->parent = startNode;
            return startNode->left.get();
        }
    }
    else{
        if (startNode->right)
            return bst_insert(startNode->right.get(), insertElem);
        else {
            startNode->right = std::make_unique<TreapNode>(insertElem, mPriorityDist(mGenerator));
            startNode->right->parent = startNode;
            return startNode->right.get();
        }
    }
}

TreapNode* Treap::bst_search(TreapNode* startNode, Element searchElem) {
    if (!startNode)
        throw std::runtime_error("[Treap] search start node is null");

    if (searchElem == startNode->element)
        return startNode;

    if (searchElem < startNode->element && startNode->left)
        return bst_search(startNode->left.get(), searchElem);

    if (searchElem > startNode->element && startNode->right)
        return bst_search(startNode->right.get(), searchElem);

    return nullptr;
}

void Treap::maintain_priority(TreapNode* startNode) {
    // TODO:

}

}} // namespace ::Xiuge::TreapTester