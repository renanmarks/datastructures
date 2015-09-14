#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stddef.h>

typedef struct LinkedList_Node_s
{
    struct LinkedList_Node_s* next;

} LinkedList_Node_t;

typedef int32_t (*LinkedList_Predicate) (LinkedList_Node_t* a, LinkedList_Node_t* b);

typedef struct LinkedList_s
{
    struct LinkedList_Node_s* first;
    struct LinkedList_Node_s* last;
    LinkedList_Predicate comparisonPredicate;
    int32_t length;
} LinkedList_t;

int32_t LinkedList_init(LinkedList_t *_this, LinkedList_Predicate _comparisonPredicate);
int32_t LinkedList_destroy(LinkedList_t *_this);

LinkedList_Node_t* LinkedList_getFirst(LinkedList_t* _this);
LinkedList_Node_t* LinkedList_getNext(LinkedList_Node_t* node);
LinkedList_Node_t* LinkedList_getLast(LinkedList_t* _this);

int32_t LinkedList_length(LinkedList_t *_this);
int32_t LinkedList_insert(LinkedList_t *_this, LinkedList_Node_t *item);
int32_t LinkedList_remove(LinkedList_t *_this, LinkedList_Node_t *value);
LinkedList_Node_t *LinkedList_find(LinkedList_t *_this, LinkedList_Node_t *value);

/***********************************************************************/

typedef struct DoubleLinkedList_Node_s
{
    struct DoubleLinkedList_Node_s* next;
    struct DoubleLinkedList_Node_s* previous;

} DoubleLinkedList_Node_t;

typedef int32_t (*DoubleLinkedList_Predicate) (DoubleLinkedList_Node_t* a, DoubleLinkedList_Node_t* b);

typedef struct DoubleLinkedList_s
{
    struct DoubleLinkedList_Node_s* first;
    struct DoubleLinkedList_Node_s* last;
    DoubleLinkedList_Predicate comparisonPredicate;
    int32_t length;
} DoubleLinkedList_t;

int32_t DoubleLinkedList_init(DoubleLinkedList_t *_this, DoubleLinkedList_Predicate predicate);
int32_t DoubleLinkedList_destroy(DoubleLinkedList_t *_this);

DoubleLinkedList_Node_t* DoubleLinkedList_getFirst(DoubleLinkedList_t* _this);
DoubleLinkedList_Node_t* DoubleLinkedList_getNext(DoubleLinkedList_Node_t* node);
DoubleLinkedList_Node_t* DoubleLinkedList_getPrevious(DoubleLinkedList_Node_t* node);
DoubleLinkedList_Node_t* DoubleLinkedList_getLast(DoubleLinkedList_t* _this);

int32_t DoubleLinkedList_length(DoubleLinkedList_t *_this);
int32_t DoubleLinkedList_insert(DoubleLinkedList_t *_this, DoubleLinkedList_Node_t *item);
int32_t DoubleLinkedList_remove(DoubleLinkedList_t *_this, DoubleLinkedList_Node_t *value);
DoubleLinkedList_Node_t *DoubleLinkedList_find(DoubleLinkedList_t *_this, DoubleLinkedList_Node_t *value);

/*
 * The definition has been based on the one used in the Linux kernel.
 */
#ifdef __GNUC__
#  define LinkedListNode_containerOf(node, type, member) ({		\
    const LinkedList_Node_t *__mptr = (node);                  \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define LinkedListNode_containerOf(node, type, member)			\
    ((type *)((char *)(node) - offsetof(type, member)))
#endif	/* __GNUC__ */

/*
 * The definition has been based on the one used in the Linux kernel.
 */
#ifdef __GNUC__
#  define DoubleLinkedListNode_containerOf(node, type, member) ({		\
    const DoubleLinkedList_Node_t *__mptr = (node);                  \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define DoubleLinkedListNode_containerOf(node, type, member)			\
    ((type *)((char *)(node) - offsetof(type, member)))
#endif	/* __GNUC__ */

#endif
