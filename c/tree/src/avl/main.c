#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

typedef struct TestNode_s
{
    AVLTree_Node_t nodeOrder1;
    AVLTree_Node_t nodeOrder2;
    int32_t number;
} TestNode_t;

int32_t predicateOrder1(const AVLTree_Node_t* a, const AVLTree_Node_t* b)
{
    TestNode_t* nodeA = AVLTree_containerOf(a, TestNode_t, nodeOrder1);
    TestNode_t* nodeB = AVLTree_containerOf(b, TestNode_t, nodeOrder1);

    //printf("a.number = %d b.number = %d\n", number1->number, number2->number);

    return nodeA->number - nodeB->number;
}

int32_t predicateOrder2(const AVLTree_Node_t* a, const AVLTree_Node_t* b)
{
    TestNode_t* nodeA = AVLTree_containerOf(a, TestNode_t, nodeOrder2);
    TestNode_t* nodeB = AVLTree_containerOf(b, TestNode_t, nodeOrder2);

    //printf("a.number = %d b.number = %d\n", number1->number, number2->number);

    return nodeB->number - nodeA->number;
}

int main()
{
    const int32_t number = 32;
    AVLTree_t tree1;
    AVLTree_t tree2;
    TestNode_t a[number];
    int32_t i;

    AVLTree_init(&tree1, predicateOrder1);
    AVLTree_init(&tree2, predicateOrder2);

    /* initialize random seed: */
    srand (time(NULL));
    for (i=0; i<number; i++)
    {
        a[i].number = (rand() % 100);
        printf("a[%d].number = %d;\n", i, a[i].number);
    }

    {
        int32_t i;

        for (i=0; i<number; i++)
        {
            AVLTree_insert(&tree1, &(a[i].nodeOrder1));
            AVLTree_insert(&tree2, &(a[i].nodeOrder2));
        }
    }

    {
        AVLTree_Node_t* aux = AVLTree_getFirst(&tree1);

        while (aux != NULL)
        {
            TestNode_t* a = AVLTree_containerOf(aux, TestNode_t, nodeOrder1);
            printf("%d ", a->number);
            aux = AVLTree_getNext(&tree1, aux);
        }
        printf("\n");
    }

    {
        AVLTree_Node_t* aux = AVLTree_getFirst(&tree2);

        while (aux != NULL)
        {
            TestNode_t* a = AVLTree_containerOf(aux, TestNode_t, nodeOrder2);
            printf("%d ", a->number);
            aux = AVLTree_getNext(&tree2, aux);
        }
        printf("\n");
    }

    {
        int32_t i;

        for (i=0; i<number; i++)
        {
            AVLTree_remove(&tree1, AVLTree_lookup(&tree1, &(a[i].nodeOrder1)));
            AVLTree_remove(&tree2, AVLTree_lookup(&tree2, &(a[i].nodeOrder2)));
        }
    }

    return 0;
}

