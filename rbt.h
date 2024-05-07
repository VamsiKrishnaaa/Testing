#ifndef RBT_H
#define RBT_H

#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *parent, *left, *right;

    Node(int val) : data(val), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(int val);
    void remove(int val);
    bool search(int val);
    void display();
    void inOrder();
    void preOrder();
    void postOrder();
    int getHeight();
    bool isBalanced();

private:
    Node *root;

    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertion(Node *&);
    void fixDeletion(Node *&);
    void transplant(Node *&, Node *&);
    Node *minimumNode(Node *&);
    void displayHelper(Node *, std::string, bool);
    void destroyTree(Node *&);
    void inOrderHelper(Node *);
    void preOrderHelper(Node *);
    void postOrderHelper(Node *);
    int getHeightHelper(Node *);
    int max(int, int);
    int getHeight(Node *);
    bool isBalancedHelper(Node *);
};

#endif
