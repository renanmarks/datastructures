#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stddef.h>

typedef struct LinkedList_s
{
    struct LinkedList_s* next;

} LinkedList_t;

typedef uint32_t (*LinkedList_InsertionPredicate) (LinkedList_t* a, LinkedList_t* b);
typedef uint32_t (*LinkedList_ComparisonPredicate)(LinkedList_t* a, void* b);

int32_t LinkedList_create(LinkedList_t* _this);
int32_t LinkedList_destroy(LinkedList_t* _this);

int32_t LinkedList_length(LinkedList_t* _this);
int32_t LinkedList_insert(LinkedList_t **_this, LinkedList_t *item, LinkedList_InsertionPredicate predicate);
int32_t LinkedList_remove(LinkedList_t **_this, void* value, LinkedList_ComparisonPredicate predicate);
LinkedList_t *LinkedList_find(LinkedList_t* _this, void *value, LinkedList_ComparisonPredicate predicate);

/***********************************************************************/

typedef struct DoubleLinkedList_s
{
    struct DoubleLinkedList_s* next;
    struct DoubleLinkedList_s* previous;

} DoubleLinkedList_t;

typedef uint32_t (*DoubleLinkedList_InsertionPredicate) (DoubleLinkedList_t* a, DoubleLinkedList_t* b);
typedef uint32_t (*DoubleLinkedList_ComparisonPredicate)(DoubleLinkedList_t* a, void* b);

int32_t DoubleLinkedList_create(DoubleLinkedList_t* _this);
int32_t DoubleLinkedList_destroy(DoubleLinkedList_t* _this);

int32_t DoubleLinkedList_length(DoubleLinkedList_t* _this);
int32_t DoubleLinkedList_insert(DoubleLinkedList_t **_this, DoubleLinkedList_t *item, DoubleLinkedList_InsertionPredicate predicate);
int32_t DoubleLinkedList_remove(DoubleLinkedList_t **_this, void* value, DoubleLinkedList_ComparisonPredicate predicate);
DoubleLinkedList_t *DoubleLinkedList_find(DoubleLinkedList_t* _this, void *value, DoubleLinkedList_ComparisonPredicate predicate);

#endif
