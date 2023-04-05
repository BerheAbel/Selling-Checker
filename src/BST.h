//
// Created by abelg on 2023-03-18.
//

#ifndef ASSIGNMENT_3_BST_H
#define ASSIGNMENT_3_BST_H

#include <string>
#include "Node.h"

class BST {
private:
    Node *m_root{nullptr};

    NodePtr insert(std::string word, NodePtr &node);

    void print(std::ostream &output, NodePtr &node, int indent);

public:
    void insert(std::string word);

    void remove(std::string word);

    void search_tree(std::string word);

    NodePtr search_tree(NodePtr &nodePtr, std::string word);

    int height(NodePtr &nodePtr);

    int balance_factor(NodePtr &nodePtr);

    NodePtr rotate_left(NodePtr &nodePtr);

    NodePtr rotate_right(NodePtr &nodePtr);

    void save_tree_to_file(std::string file);

    void save_tree_to_file(NodePtr &nodePtr, std::ofstream &outData, int indent);

    friend std::ostream &operator<<(std::ostream &output, BST &bst);
};

#endif //ASSIGNMENT_3_BST_H
