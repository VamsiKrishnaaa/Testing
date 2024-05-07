#include "rbt.h"

RedBlackTree::RedBlackTree() : root(nullptr) {}

RedBlackTree::~RedBlackTree() {
    destroyTree(root);
}

void RedBlackTree::inOrder() {
    inOrderHelper(root);
    std::cout << std::endl;
}

void RedBlackTree::preOrder() {
    preOrderHelper(root);
    std::cout << std::endl;
}

void RedBlackTree::postOrder() {
    postOrderHelper(root);
    std::cout << std::endl;
}

int RedBlackTree::getHeight() {
    return getHeightHelper(root);
}

bool RedBlackTree::isBalanced() {
    return isBalancedHelper(root);
}

void RedBlackTree::insert(int val) {
    Node *newNode = new Node(val);
    Node *parent = nullptr;
    Node *current = root;

    while (current != nullptr) {
        parent = current;
        if (val < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;
    if (parent == nullptr)
        root = newNode;
    else if (val < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsertion(newNode);
}

void RedBlackTree::remove(int val) {
    // TODO: Implement removal
}

bool RedBlackTree::search(int val) {
    Node *current = root;
    while (current != nullptr) {
        if (val == current->data)
            return true;
        else if (val < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

void RedBlackTree::display() {
    displayHelper(root, "", true);
}

void RedBlackTree::rotateLeft(Node *&node) {
    Node *rightChild = node->right;
    node->right = rightChild->left;
    if (node->right != nullptr)
        node->right->parent = node;
    rightChild->parent = node->parent;
    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;
    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(Node *&node) {
    Node *leftChild = node->left;
    node->left = leftChild->right;
    if (node->left != nullptr)
        node->left->parent = node;
    leftChild->parent = node->parent;
    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;
    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::fixInsertion(Node *&node) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (node != root && node->color != BLACK && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::fixDeletion(Node *&node) {
    // TODO: Implement fix-up for deletion
}

void RedBlackTree::transplant(Node *&target, Node *&with) {
    if (target->parent == nullptr)
        root = with;
    else if (target == target->parent->left)
        target->parent->left = with;
    else
        target->parent->right = with;
    if (with != nullptr)
        with->parent = target->parent;
}

Node *RedBlackTree::minimumNode(Node *&node) {
    Node *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

void RedBlackTree::displayHelper(Node *node, std::string indent, bool last) {
    if (node != nullptr) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }

        std::string sColor = (node->color == RED) ? "RED" : "BLACK";
        std::cout << node->data << "(" << sColor << ")" << std::endl;

        displayHelper(node->left, indent, false);
        displayHelper(node->right, indent, true);
    }
}

void RedBlackTree::destroyTree(Node *&node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
        node = nullptr;
    }
}

void RedBlackTree::inOrderHelper(Node *node) {
    if (node != nullptr) {
        inOrderHelper(node->left);
        std::cout << node->data << " ";
        inOrderHelper(node->right);
    }
}

void RedBlackTree::preOrderHelper(Node *node) {
    if (node != nullptr) {
        std::cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

void RedBlackTree::postOrderHelper(Node *node) {
    if (node != nullptr) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout << node->data << " ";
    }
}

int RedBlackTree::getHeightHelper(Node *node) {
    if (node == nullptr)
        return -1;
    else
        return 1 + max(getHeightHelper(node->left), getHeightHelper(node->right));
}

int RedBlackTree::max(int a, int b) {
    return (a > b) ? a : b;
}

int RedBlackTree::getHeight(Node *node) {
    if (node == nullptr)
        return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

bool RedBlackTree::isBalancedHelper(Node *node) {
    if (node == nullptr)
        return true;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return std::abs(leftHeight - rightHeight) <= 1 && isBalancedHelper(node->left) && isBalancedHelper(node->right);
}