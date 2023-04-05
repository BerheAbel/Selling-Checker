//
// Created by abelg on 2023-03-18.
//

#ifndef ASSIGNMENT_3_NODE_H
#define ASSIGNMENT_3_NODE_H
struct Node;
using NodePtr = Node *;

struct Node {
    std::string m_data;
    NodePtr m_left{nullptr};
    NodePtr m_right{nullptr};
    int m_height = {1};
};
#endif //ASSIGNMENT_3_NODE_H
