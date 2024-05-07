#include <deepstate/DeepState.hpp>
#include "rbt.h"
#include <set>

using namespace deepstate;

TEST(RedBlackTree, InsertionAndSearch) {
    unsigned int seed = DeepState_UInt();
    srand(seed);

    RedBlackTree tree;
    std::set<int> values;

    for (int i = 0; i < 100; ++i) {
        int val = DeepState_IntInRange(0, 1000);
        tree.insert(val);
        values.insert(val);
    }

    for (int val : values) {
        ASSERT_TRUE(tree.search(val));
    }
}

TEST(RedBlackTree, DeletionAndSearch) {
    unsigned int seed = DeepState_UInt();
    srand(seed);

    RedBlackTree tree;
    std::set<int> values;

    for (int i = 0; i < 100; ++i) {
        int val = DeepState_IntInRange(0, 1000);
        tree.insert(val);
        values.insert(val);
    }

    for (int i = 0; i < 50; ++i) {
        int val = *values.begin();
        tree.remove(val);
        values.erase(val);
    }

    for (int val : values) {
        ASSERT_TRUE(tree.search(val));
    }

    for (int i = 0; i < 50; ++i) {
        int val = DeepState_IntInRange(0, 1000);
        ASSERT_EQ(tree.search(val), values.find(val) != values.end());
    }
}

TEST(RedBlackTree, HeightAndBalanced) {
    unsigned int seed = DeepState_UInt();
    srand(seed);

    RedBlackTree tree;
    std::set<int> values;

    for (int i = 0; i < 100; ++i) {
        int val = DeepState_IntInRange(0, 1000);
        tree.insert(val);
        values.insert(val);
    }

    ASSERT_EQ(tree.getHeight(), values.size() - 1);
    ASSERT_TRUE(tree.isBalanced());
}

