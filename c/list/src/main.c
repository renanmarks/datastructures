#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct MyClassS_s
{
    LinkedList_Node_t node;
    int32_t number;

} MyClassS_t;

int32_t MyClassS_Predicate (LinkedList_Node_t* a, LinkedList_Node_t* b)
{
    if (a != NULL && b != NULL)
    {
        MyClassS_t* item1 = LinkedListNode_containerOf(a, MyClassS_t, node);
        MyClassS_t* item2 = LinkedListNode_containerOf(b, MyClassS_t, node);

        return item1->number - item2->number;
    }

    return 1;
}

int LinkedList_test()
{
    const int32_t number = 16;
    LinkedList_t list;
    MyClassS_t a[number];

    LinkedList_init(&list, MyClassS_Predicate);

    srand (time(NULL));

    {
        int32_t i;

        for (i=0; i<number; i++)
        {
            a[i].number = (rand() % 100);
            printf("a[%d].number = %d;\n", i, a[i].number);
        }
    }

    {
        int32_t i;

        for (i=0; i<number; i++)
        {
            LinkedList_insert(&list, &a[i].node);
        }
    }

    {
        LinkedList_Node_t* aux = LinkedList_getFirst(&list);

        while (aux != NULL)
        {
            MyClassS_t* a = LinkedListNode_containerOf(aux, MyClassS_t, node);
            printf("%d ", a->number);
            aux = LinkedList_getNext(aux);
        }

        printf("Length: %d\n", LinkedList_length(&list));
    }

    {
        int32_t i;

        for (i=0; i<number; i++)
        {
            LinkedList_remove(&list, &a[i].node);
        }

        printf("Length: %d\n", LinkedList_length(&list));
    }

    return 0;
}

/*************/

typedef struct MyClassD_s
{
    DoubleLinkedList_Node_t node;
    int32_t number;

} MyClassD_t;

int32_t MyClassD_Predicate (DoubleLinkedList_Node_t* a, DoubleLinkedList_Node_t* b)
{
    if (a != NULL && b != NULL)
    {
        MyClassD_t* item1 = DoubleLinkedListNode_containerOf(a, MyClassD_t, node);
        MyClassD_t* item2 = DoubleLinkedListNode_containerOf(b, MyClassD_t, node);

        return item1->number - item2->number;
    }

    return 1;
}

void printdlist(DoubleLinkedList_t list)
{
    {
        DoubleLinkedList_Node_t* aux = DoubleLinkedList_getFirst(&list);

        while (aux != NULL)
        {
            MyClassD_t* a = DoubleLinkedListNode_containerOf(aux, MyClassD_t, node);
            printf("%d ", a->number);
            aux = DoubleLinkedList_getNext(aux);
        }

        printf(". Length: %d\n", DoubleLinkedList_length(&list));
    }
}

void printdlist_inv(DoubleLinkedList_t list)
{
    {
        DoubleLinkedList_Node_t* aux = DoubleLinkedList_getLast(&list);

        while (aux != NULL)
        {
            MyClassD_t* a = DoubleLinkedListNode_containerOf(aux, MyClassD_t, node);
            printf("%d ", a->number);
            aux = DoubleLinkedList_getPrevious(aux);
        }

        printf(". Length: %d\n", DoubleLinkedList_length(&list));
    }
}

int DoubleLinkedList_test()
{
    const int32_t number = 16;
    DoubleLinkedList_t list;
    MyClassD_t a[number];

    DoubleLinkedList_init(&list, MyClassD_Predicate);

    srand (time(NULL));

    {
        int32_t i;

        for (i=0; i<number; i++)
        {
            a[i].number = (rand() % 100);
            printf("a[%d].number = %d;\n", i, a[i].number);
        }
    }

    {
        int32_t i;

        for (i=0; i<number; i++)
        {
            DoubleLinkedList_insert(&list, &a[i].node);
            printdlist(list);
            printdlist_inv(list);
        }
    }

    printf("---\n");

    {
        int32_t i;

        for (i=0; i<number; i++)
        {
            DoubleLinkedList_remove(&list, &a[i].node);
            printdlist(list);
            printdlist_inv(list);
        }
    }

    return 0;
}

int main(void)
{
    LinkedList_test();
    DoubleLinkedList_test();

    return 0;
}

