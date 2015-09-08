#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

typedef struct TestNode_s
{
    AVLTree_Node_t node;
    int32_t number;
} TestNode_t;

int32_t predicate (const AVLTree_Node_t* a, const AVLTree_Node_t* b)
{
    TestNode_t* nodeA = AVLTree_containerOf(a, TestNode_t, node);
    TestNode_t* nodeB = AVLTree_containerOf(b, TestNode_t, node);

    //printf("a.number = %d b.number = %d\n", number1->number, number2->number);

    return nodeA->number - nodeB->number;
}

/**
 * @brief printTree Debug purposes only :)
 * @param node
 */
void printTree(TestNode_t* node)
{
    if (node == NULL)
    {
        return;
    }

    printTree(AVLTree_containerOf(node->node.subtree[0], TestNode_t, node));
    printf("%d ", node->number);
    printTree(AVLTree_containerOf(node->node.subtree[1], TestNode_t, node));
}

void populateTree(AVLTree_t* tree, TestNode_t* a, const int32_t number)
{
    int32_t i;

    for (i=0; i<number; i++)
    {
        AVLTree_insert(tree, &(a[i].node));
        printTree(AVLTree_containerOf(tree->root, TestNode_t, node));
        printf("\n");
    }

    printf("Height: %d -------\n", tree->height);
}

void depopulateTree(AVLTree_t* tree, TestNode_t* a, const int32_t number)
{
    int32_t i;

    for (i=0; i<number; i++)
    {
        AVLTree_remove(tree, AVLTree_lookup(tree, &(a[i].node)));
        printTree(AVLTree_containerOf(tree->root, TestNode_t, node));
        printf("\n");
    }

    printf("Height: %d -------\n", tree->height);
}

int main()
{
    const int32_t number = 32;
    AVLTree_t tree1;
    TestNode_t a[number];
    int32_t i;

    AVLTree_init(&tree1, predicate);

    /* initialize random seed: */
    srand (time(NULL));
    for (i=0; i<number; i++)
    {
        a[i].number = (rand() % 100);
        printf("a[%d].number = %d;\n", i, a[i].number);
    }

    populateTree(&tree1, a, number);
    depopulateTree(&tree1, a, number);


    return 0;
}

