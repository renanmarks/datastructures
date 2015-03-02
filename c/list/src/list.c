#include "list.h"
#include <stdlib.h>

int32_t LinkedList_create(LinkedList_t* _this)
{
    if (_this == NULL)
    {
        return -1;
    }

    _this->next = NULL;

    return 0;
}

int32_t LinkedList_destroy(LinkedList_t* _this)
{
    // INFO: free the memory of the list?

    return 0;
}

int32_t LinkedList_length(LinkedList_t* _this)
{
    LinkedList_t* it = _this;
    uint32_t count = 0;

    while (it != NULL)
    {
        count++;
        it = it->next;
    }

    return count;
}

int32_t LinkedList_insert(LinkedList_t** _this, LinkedList_t* item, LinkedList_InsertionPredicate predicate)
{
    LinkedList_t* aux = *_this;

    if (item == NULL)
    {
        return -2;
    }

    if (*_this == NULL)
    {
        item->next     = NULL;
        *_this = item;
        return 0;
    }

    if ( predicate(*_this, item) != 0 )
    {
        item->next        = *_this;
        *_this = item;
        return 0;
    }

    // Get the last item in list
    // Order by predicate
    while ((aux->next != NULL) && predicate(item, aux->next) != 0)
    {
        aux = aux->next;
    }

    item->next     = aux->next;
    aux->next      = item;

    return 0;
}

int32_t LinkedList_remove(LinkedList_t** _this, void* value, LinkedList_ComparisonPredicate predicate)
{
    LinkedList_t* aux;

    if (value == NULL)
    {
        return -1;
    }

    // Case 1: first element of the list
    if ( predicate(*_this, value) != 0 )
    {
        LinkedList_t* next     = (*_this)->next;
        (*_this)->next         = NULL;
        (*_this)               = next;

        return 0;
    }

    // Case 2: element in the middle of the list
    for (aux = *_this; aux != NULL; aux = aux->next)
    {
        if ( predicate(aux->next, value) != 0 )
        {
            LinkedList_t* item = aux->next;
            LinkedList_t* next = item->next;
            aux->next = next;

            break;
        }
    }

    return 0;
}

LinkedList_t* LinkedList_find(LinkedList_t* _this, void* value, LinkedList_ComparisonPredicate predicate)
{
    LinkedList_t* aux;

    if (value == NULL)
    {
        return NULL;
    }

    for (aux = _this; aux != NULL; aux = aux->next)
    {
        if ( predicate(aux, value) != 0 )
        {
            return aux;
        }
    }

    return NULL;
}

/***********************************************************************/

int32_t DoubleLinkedList_create(DoubleLinkedList_t* _this)
{
    if (_this == NULL)
    {
        return -1;
    }

    _this->next     = NULL;
    _this->previous = NULL;

    return 0;
}

int32_t DoubleLinkedList_destroy(DoubleLinkedList_t* _this)
{
    // INFO: free the memory of the list?

    return 0;
}

int32_t DoubleLinkedList_length(DoubleLinkedList_t* _this)
{
    DoubleLinkedList_t* it = _this;
    uint32_t count = 0;

    while (it != NULL)
    {
        count++;
        it = it->next;
    }

    return count;
}

int32_t DoubleLinkedList_insert(DoubleLinkedList_t **_this, DoubleLinkedList_t *item, DoubleLinkedList_InsertionPredicate predicate)
{
    DoubleLinkedList_t* aux = *_this;

    if (item == NULL)
    {
        return -2;
    }

    if (*_this == NULL)
    {
        item->next     = NULL;
        item->previous = NULL;
        *_this = item;
        return 0;
    }

    if ( predicate(*_this, item) != 0 )
    {
        item->next        = *_this;
        item->previous    = NULL;
        (*_this)->previous = item;
        *_this = item;
        return 0;
    }

    // Get the last item in list
    // Order by predicate
    while ((aux->next != NULL) && predicate(item, aux->next) != 0)
    {
        aux = aux->next;
    }

    item->next     = aux->next;
    item->previous = aux;
    aux->next      = item;

    return 0;
}

int32_t DoubleLinkedList_remove(DoubleLinkedList_t **_this, void *value, DoubleLinkedList_ComparisonPredicate predicate)
{
    DoubleLinkedList_t* aux;

    if (value == NULL)
    {
        return -1;
    }

    // Case 1: first element of the list
    if ( predicate(*_this, value) != 0 )
    {
        DoubleLinkedList_t* item = (*_this);
        DoubleLinkedList_t* next = item->next;

        (*_this) = next;

        if (next != NULL)
        {
            next->previous = NULL;
        }

        item->next      = NULL;
        item->previous  = NULL;

        return 0;
    }

    // Case 2: element in the middle of the list
    for (aux = *_this; aux != NULL; aux = aux->next)
    {
        if ( predicate(aux->next, value) != 0 )
        {
            DoubleLinkedList_t* item = aux->next;
            DoubleLinkedList_t* next = item->next;

            aux->next = next;

            if (next != NULL)
            {
                next->previous = aux;
            }

            item->next      = NULL;
            item->previous  = NULL;

            break;
        }
    }

    return 0;
}

DoubleLinkedList_t *DoubleLinkedList_find(DoubleLinkedList_t* _this, void *value, DoubleLinkedList_ComparisonPredicate predicate)
{
    DoubleLinkedList_t* aux;

    if (value == NULL)
    {
        return NULL;
    }

    for (aux = _this; aux != NULL; aux = aux->next)
    {
        if ( predicate(aux, value) )
        {
            return aux;
        }
    }

    return NULL;
}
