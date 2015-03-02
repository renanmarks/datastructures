#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct MyClassS_s
{
    LinkedList_t base;
    int32_t info;

} MyClassS_t;

uint32_t MyClassS_InsertionPredicate (LinkedList_t* a, LinkedList_t* b)
{
    MyClassS_t* item1 = (MyClassS_t*)a;
    MyClassS_t* item2 = (MyClassS_t*)b;

    if (a == NULL || b == NULL)
    {
        return 0;
    }

    return item1->info > item2->info;
}

uint32_t MyClassS_ComparisonPredicate(LinkedList_t* a, void* b)
{
    MyClassS_t* item1 = (MyClassS_t*)a;
    uint32_t item2 = *(uint32_t*)b;

    if (a == NULL || b == NULL)
    {
        return 0;
    }

    return item1->info == item2;
}

/*************/

typedef struct MyClassD_s
{
    DoubleLinkedList_t base;
    int32_t info;

} MyClassD_t;

uint32_t MyClassD_InsertionPredicate (DoubleLinkedList_t* a, DoubleLinkedList_t* b)
{
    MyClassD_t* item1 = (MyClassD_t*)a;
    MyClassD_t* item2 = (MyClassD_t*)b;

    if (a == NULL || b == NULL)
    {
        return 0;
    }

    return item1->info > item2->info;
}

uint32_t MyClassD_ComparisonPredicate(DoubleLinkedList_t* a, void* b)
{
    MyClassD_t* item1 = (MyClassD_t*)a;
    uint32_t item2 = *(uint32_t*)b;

    if (a == NULL || b == NULL)
    {
        return 0;
    }

    return item1->info == item2;
}

/*************/

int LinkedList_test()
{
    uint32_t i;
    MyClassS_t* head = NULL;
    MyClassS_t* iterator = NULL;

    for(i=0; i<10; i++)
    {
        MyClassS_t* item = (MyClassS_t*)malloc(sizeof(MyClassS_t));
        LinkedList_create((LinkedList_t*)item);
        item->info = i * 2;

        LinkedList_insert((LinkedList_t**)&head, (LinkedList_t*)item, MyClassS_InsertionPredicate);
    }

    for (iterator = head; iterator != NULL; iterator = (MyClassS_t*)iterator->base.next)
    {
        printf("%d -> ", iterator->info);
    }

    printf("\n");

    uint32_t value = 8;
    LinkedList_remove((LinkedList_t**)&head, (void*)&value, MyClassS_ComparisonPredicate);

    for (iterator = head; iterator != NULL; iterator = (MyClassS_t*)iterator->base.next)
    {
        printf("%d -> ", iterator->info);
    }

    printf("\n");

    value = 0;
    LinkedList_remove((LinkedList_t**)&head, (void*)&value, MyClassS_ComparisonPredicate);

    for (iterator = head; iterator != NULL; iterator = (MyClassS_t*)iterator->base.next)
    {
        printf("%d -> ", iterator->info);
    }

    printf("\n");

    value = 18;
    LinkedList_remove((LinkedList_t**)&head, (void*)&value, MyClassS_ComparisonPredicate);

    for (iterator = head; iterator != NULL; iterator = (MyClassS_t*)iterator->base.next)
    {
        printf("%d -> ", iterator->info);
    }

    printf("\n");

    value = 14;
    iterator = (MyClassS_t*) LinkedList_find((LinkedList_t*)head, (void*)&value, MyClassS_ComparisonPredicate);

    if (iterator != NULL)
    {
        printf("found = %d\n", iterator->info);
    }
}

int DoubleLinkedList_test()
{
    uint32_t i;
    MyClassD_t* head = NULL;
    MyClassD_t* iterator = NULL;

    for(i=0; i<10; i++)
    {
        MyClassD_t* item = (MyClassD_t*)malloc(sizeof(MyClassD_t));
        DoubleLinkedList_create((DoubleLinkedList_t*)item);
        item->info = i * 2;

        DoubleLinkedList_insert((DoubleLinkedList_t**)&head, (DoubleLinkedList_t*)item, MyClassD_InsertionPredicate);
    }

    for (iterator = head; iterator != NULL; iterator = (MyClassD_t*)iterator->base.next)
    {
        printf("%d <-> ", iterator->info);
    }

    printf("\n");

    uint32_t value = 8;
    DoubleLinkedList_remove((DoubleLinkedList_t**)&head, (void*)&value, MyClassD_ComparisonPredicate);

    for (iterator = head; iterator != NULL; iterator = (MyClassD_t*)iterator->base.next)
    {
        printf("%d <-> ", iterator->info);
    }

    printf("\n");

    value = 0;
    DoubleLinkedList_remove((DoubleLinkedList_t**)&head, (void*)&value, MyClassD_ComparisonPredicate);

    for (iterator = head; iterator != NULL; iterator = (MyClassD_t*)iterator->base.next)
    {
        printf("%d <-> ", iterator->info);
    }

    printf("\n");

    value = 18;
    DoubleLinkedList_remove((DoubleLinkedList_t**)&head, (void*)&value, MyClassD_ComparisonPredicate);

    for (iterator = head; iterator != NULL; iterator = (MyClassD_t*)iterator->base.next)
    {
        printf("%d <-> ", iterator->info);
    }

    printf("\n");

    value = 14;
    iterator = (MyClassD_t*) DoubleLinkedList_find((DoubleLinkedList_t*)head, (void*)&value, MyClassD_ComparisonPredicate);

    if (iterator != NULL)
    {
        printf("found = %d\n", iterator->info);
    }

    for (iterator = head; iterator->base.next != NULL; iterator = (MyClassD_t*)iterator->base.next)
    {
    }

    for (; iterator != NULL; iterator = (MyClassD_t*)iterator->base.previous)
    {
        printf("%d <-> ", iterator->info);
    }

    printf("\n");
}

int main(void)
{
    printf("Hello World!\n");

    LinkedList_test();
    DoubleLinkedList_test();

    return 0;
}

