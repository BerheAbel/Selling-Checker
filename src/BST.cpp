//
// Created by abelg on 2023-03-18.
//

#include <ostream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <regex>
#include "BST.h"
#include "Node.h"


void BST::insert(std::string word) {
    m_root = insert(word, m_root);
}

NodePtr BST::insert(std::string word, NodePtr &node) {
    if (node == nullptr) {
        // node = new Node();
        // node->m_data = word;
        return new Node{word, nullptr, nullptr, 1};
    } else {
        //add node to existing tree
        if (word < node->m_data) {
            //go left
            node->m_left = insert(word, node->m_left);
        } else if (word > node->m_data) {
            //go right
            node->m_right = insert(word, node->m_right);
        } else
            return node;
        // std::cout << "duplicate value" << std::endl;
    }


    node->m_height = std::max(height(node->m_left), height(node->m_right)) + 1;
    //calculate the balance factor of node
    int bf = balance_factor(node);

    //check if right rotation is possible
    if (bf > 1 && word < node->m_left->m_data)
        return rotate_right(node);

    //check if left rotation is possible
    if (bf < -1 && word > node->m_right->m_data)
        return rotate_left(node);

    //check if double rotation is possible LR
    if (bf > 1 && word > node->m_left->m_data) {
        node->m_left = rotate_left(node->m_left);
        return rotate_right(node);
    }

    //check if double rotation is possible RL
    if (bf < -1 && word < node->m_right->m_data) {
        node->m_right = rotate_right(node->m_right);
        return rotate_left(node);
    }
    return node;
}


void BST::print(std::ostream &output, NodePtr &node, int indent = 0) {
    if (node == nullptr) {
        return;
    }
    if (node != nullptr) {
        print(output, node->m_right, indent + 8);
        output << std::setw(indent) << node->m_data << std::endl;
        print(output, node->m_left, indent + 8);
    }
}

std::ostream &operator<<(std::ostream &output, BST &bst) {
    bst.print(output, bst.m_root, 0);
    return output;
}

void BST::remove(std::string word) {
    NodePtr node = m_root;
    NodePtr parent = nullptr;

    //search for the node to delete
    while (node != nullptr) {
        if (word < node->m_data) {
            //go left
            parent = node;
            node = node->m_left;
        } else if (word > node->m_data) {
            // go right
            parent = node;
            node = node->m_right;
        } else {
            //found the node
            break;
        }
    }

    //didn't find the node
    if (node == nullptr) {
        return;
    }
    //if a node has two children
    //use the right most node in the left tree as successor
    if (node->m_right != nullptr && node->m_left != nullptr) {
        //start on the left subtree
        NodePtr successor = node->m_left;
        parent = node;
        //go as far right as possible
        while (successor->m_right != nullptr) {
            parent = successor;
            successor = successor->m_right;
        }

        //swap values with successor
        node->m_data = successor->m_data;
        //the successor become the node to delete
        node = successor;

    }

    //assume there is a subtree on the left
    NodePtr subTree = node->m_left;

    if (subTree == nullptr) {
        subTree = node->m_right;
    }

    //delete nod with no children
    if (parent == nullptr) {
        //deleting the root node
    } else if (node == parent->m_left) {
        //detach from parte's left side
        parent->m_left = subTree;
    } else if (node == parent->m_right) {
        //detach from parent's right side
        parent->m_right = subTree;
    }

    //deleting node
    delete node;
}

void BST::search_tree(std::string word) {
    std::string pure_word;
    //remove any non string characters
    for (char c: word) {
        if (isalpha(c)) {
            pure_word += c;
        }
    }
    //check if the word is a valid string
    if (std::regex_match(pure_word, std::regex("[A-z]+"))) {
        NodePtr result = search_tree(m_root, pure_word);
        //check if the searched word is available in the tree
        if (result == nullptr) {
            std::cout << "Incorrect spelled word  - " << pure_word << std::endl;
        }
    }
}

NodePtr BST::search_tree(NodePtr &nodePtr, std::string word) {
    //convert word to lower case for comparison
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (nodePtr == nullptr || nodePtr->m_data == word) {
        return nodePtr;
    }

    // If the value is less than the root's data
    if (word < nodePtr->m_data) {
        // Search in the left subtree
        return search_tree(nodePtr->m_left, word);
    } else {
        // Search in the right subtree
        return search_tree(nodePtr->m_right, word);
    }
}


int BST::height(NodePtr &nodePtr) {

    if (nodePtr == nullptr) return 0;
    return nodePtr->m_height;
}

int BST::balance_factor(NodePtr &nodePtr) {

    int result = height(nodePtr->m_left) - height(nodePtr->m_right);
    return result;
}

NodePtr BST::rotate_left(NodePtr &nodePtr) {

    NodePtr rightChild = nodePtr->m_right;
    NodePtr rightLeftChild = rightChild->m_left;

    // Perform the rotation
    rightChild->m_left = nodePtr;
    nodePtr->m_right = rightLeftChild;

    // Update heights
    nodePtr->m_height = std::max(height(nodePtr->m_left), height(nodePtr->m_right)) + 1;
    rightChild->m_height = std::max(height(rightChild->m_left), height(rightChild->m_right)) + 1;

    return rightChild;
}

NodePtr BST::rotate_right(NodePtr &nodePtr) {
    NodePtr leftChild = nodePtr->m_left;
    NodePtr leftRightChild = leftChild->m_right;

    // Perform the rotation
    leftChild->m_right = nodePtr;
    nodePtr->m_left = leftRightChild;

    // Update heights
    nodePtr->m_height = std::max(height(nodePtr->m_left), height(nodePtr->m_right)) + 1;
    leftChild->m_height = std::max(height(leftChild->m_left), height(leftChild->m_right)) + 1;
    return leftChild;
}

void BST::save_tree_to_file(std::string file) {
    std::string dirName = "output";
    std::ofstream outPut("../" + dirName + "/" + file);
    save_tree_to_file(m_root, outPut, 0);
}

void BST::save_tree_to_file(NodePtr &nodePtr, std::ofstream &outData, int indent = 0) {
    if (nodePtr == nullptr) {
        return;
    }
    //go right
    save_tree_to_file(nodePtr->m_right, outData, indent + 24);
    //write words to file
    outData << std::setw(indent) << nodePtr->m_data << std::endl;
    //go left
    save_tree_to_file(nodePtr->m_left, outData, indent + 24);
}




































