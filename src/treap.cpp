//
// Created by Xiuge Chen on 3/19/20.
//

#include <memory>
#include <iostream>
#include <spdlog/spdlog.h>

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

    spdlog::info("[Treap] insert operation, id={}, key={}", operation.element.id, operation.element.key);

    if (!mRoot) {
        mRoot = std::make_unique<TreapNode>(operation.element, mPriorityDist(mGenerator));
        return;
    }

    TreapNode* insertedNode = bst_insert(mRoot.get(), operation.element);

    maintain_priority(insertedNode);

    spdlog::info("[Treap] Finial insertion result");
    print(mRoot.get(), 0);
}

bool Treap::delete_key(const Operation operation) {
    if (operation.type != OperationType::DELETE)
        throw std::runtime_error("[Treap] Delete invalid operation");

    if (operation.element.id != 0)
        throw std::runtime_error("[Treap] Delete invalid element");

    spdlog::info("[Treap] delete operation, id={}, key={}", operation.element.id, operation.element.key);

    if (mRoot) {
        TreapNode* deleteNode = bst_search(mRoot.get(), operation.element);

        if (deleteNode) {
            deleteNode->priority = 2;

            while (deleteNode->left || deleteNode->right) {
                maintain_priority(deleteNode);
            }

            spdlog::info("[Treap] Deletion final rotation results");
            print(mRoot.get(), 0);

            if (deleteNode->parent->left && deleteNode->parent->left->element == deleteNode->element)
                deleteNode->parent->left.reset(nullptr);

            if (deleteNode->parent->right && deleteNode->parent->right->element == deleteNode->element)
                deleteNode->parent->right.reset(nullptr);

            return true;
        }
    }

    spdlog::info("[Treap] delete operation, can't find element");
    return false;
}

Element Treap::search_key(const Operation operation) {
    if (operation.type != OperationType::SEARCH)
        throw std::runtime_error("[Treap] Search invalid operation");

    if (operation.element.id != 0)
        throw std::runtime_error("[Treap] Search invalid element");

    spdlog::info("[Treap] search operation, id={}, key={}", operation.element.id, operation.element.key);

    if (mRoot) {
        TreapNode* result = bst_search(mRoot.get(), operation.element);

        if (result)
            return result->element;
    }

    spdlog::info("[Treap] search operation, can't find element");
    return{0, 0};
}

void Treap::print(TreapNode* node, int level)
{
    if (node) {
        print(node->right.get(), level + 1);

        for (int i = 0; i < level; i++)
            std::cout << "        ";

        std::cout << "(Key={" << node->element.key << "}, Id={" << node->element.id << "}, Priority={" <<
            node->priority << "}, parentId={" << (node->parent ? node->parent->element.id : 0) << "})" << std::endl;

        print(node->left.get(), level + 1);
    }
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

    if (searchElem.key == startNode->element.key)
        return startNode;

    if (searchElem.key < startNode->element.key && startNode->left)
        return bst_search(startNode->left.get(), searchElem);

    if (searchElem.key > startNode->element.key && startNode->right)
        return bst_search(startNode->right.get(), searchElem);

    return nullptr;
}

void Treap::maintain_priority(TreapNode* startNode) {
    // if parent node has larger priority than child node
    if (startNode->parent && startNode->parent->priority > startNode->priority) {
        // if child node is the left child of parent, do a right rotation
        if (startNode->parent->left && startNode->parent->left->element == startNode->element) {
            spdlog::info("[Treap] perform right rotation from key={}, id={}, priority={}",
                    startNode->element.key, startNode->element.id, startNode->priority);

            std::unique_ptr<TreapNode> temp = std::move(startNode->parent->left);
            TreapNode* grandparent = temp->parent->parent;

            temp->parent->left = std::move(temp->right);
            if (temp->parent->left)
                temp->parent->left->parent = temp->parent;

            // also need to determine whether parent is root, or left/right child of grandparent node
            if (grandparent) {
                if (grandparent->left && grandparent->left->element == temp->parent->element) {
                    temp->right = std::move(grandparent->left);
                    grandparent->left = std::move(temp);

                    grandparent->left->parent->parent = grandparent->left.get();
                    grandparent->left->parent = grandparent;
                }
                else if (grandparent->right && grandparent->right->element == temp->parent->element) {
                    temp->right = std::move(grandparent->right);
                    grandparent->right = std::move(temp);

                    grandparent->right->parent->parent = grandparent->right.get();
                    grandparent->right->parent = grandparent;
                }
            }
            else {
                temp->right = std::move(mRoot);
                mRoot = std::move(temp);
                mRoot->parent->parent = mRoot.get();
                mRoot->parent = nullptr;
            }

            maintain_priority(startNode);
        }
        // if child node is the right child of parent, do a left rotation
        else if (startNode->parent->right && startNode->parent->right->element == startNode->element) {
            spdlog::info("[Treap] perform left rotation from key={}, id={}, priority={}",
                    startNode->element.key, startNode->element.id, startNode->priority);

            std::unique_ptr<TreapNode> temp = std::move(startNode->parent->right);
            TreapNode* grandparent = temp->parent->parent;

            temp->parent->right = std::move(temp->left);
            if (temp->parent->right)
                temp->parent->right->parent = temp->parent;

            // also need to determine whether parent is root, or left/right child of grandparent node
            if (grandparent) {
                if (grandparent->left && grandparent->left->element == temp->parent->element) {
                    temp->left = std::move(grandparent->left);
                    grandparent->left = std::move(temp);

                    grandparent->left->parent->parent = grandparent->left.get();
                    grandparent->left->parent = grandparent;
                }
                else if (grandparent->right && grandparent->right->element == temp->parent->element) {
                    temp->left = std::move(grandparent->right);
                    grandparent->right = std::move(temp);

                    grandparent->right->parent->parent = grandparent->right.get();
                    grandparent->right->parent = grandparent;
                }
            }
            else {
                temp->left = std::move(mRoot);
                mRoot = std::move(temp);
                mRoot->parent->parent = mRoot.get();
                mRoot->parent = nullptr;
            }

            maintain_priority(startNode);
        }
    }

    // if child nodes has smaller priority than parent node
    if (startNode->left && startNode->left->priority < startNode->priority)
        maintain_priority(startNode->left.get());

    if (startNode->right && startNode->right->priority < startNode->priority)
        maintain_priority(startNode->right.get());
}

}} // namespace ::Xiuge::TreapTester