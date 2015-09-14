#include "list.h"
#include <stdlib.h>

int32_t LinkedList_init(LinkedList_t* _this, LinkedList_Predicate _comparisonPredicate)
{
    if (_this == NULL)
    {
        return -1;
    }

    _this->comparisonPredicate = _comparisonPredicate;
    _this->first  = NULL;
    _this->last   = NULL;
    _this->length = 0;

    return 0;
}

int32_t LinkedList_destroy(LinkedList_t* _this)
{
    // INFO: free the memory of the list?

    return 0;
}

LinkedList_Node_t* LinkedList_getFirst(LinkedList_t* _this)
{
    if (_this == NULL)
    {
        return NULL;
    }

    return _this->first;
}

LinkedList_Node_t* LinkedList_getNext(LinkedList_Node_t* node)
{
    if (node == NULL)
    {
        return NULL;
    }

    return node->next;
}

LinkedList_Node_t* LinkedList_getLast(LinkedList_t* _this)
{
    if (_this == NULL)
    {
        return NULL;
    }

    return _this->last;
}

int32_t LinkedList_length(LinkedList_t* _this)
{
    return _this->length;
}

int32_t LinkedList_insert(LinkedList_t* _this, LinkedList_Node_t* item)
{
    LinkedList_Node_t* aux;

    if (_this == NULL)
    {
        return -1;
    }

    if (item == NULL)
    {
        return -2;
    }

    if (_this->first == NULL) // List empty
    {
        item->next     = NULL;
        _this->first   = item;
        (_this->length)++;
        return 0;
    }

    if ( _this->comparisonPredicate(_this->first, item) > 0 ) // item > first
    {
        item->next   = _this->first;
        _this->first = item;
        (_this->length)++;
        return 0;
    }

    aux = _this->first;

    // Get the last item in list
    // Order by predicate
    while (aux->next != NULL) // next > item
    {
        int32_t result = _this->comparisonPredicate(item, aux->next);

        if (result > 0)
        {
            aux = aux->next;
            continue;
        }

        if (result == 0)
        {
            return 0;
        }

        if (result < 0)
        {
            break;
        }
    }

    item->next     = aux->next;
    aux->next      = item;

    if (item->next == NULL) // Last element?
    {
        _this->last = item;
    }

    (_this->length)++;

    return 0;
}

int32_t LinkedList_remove(LinkedList_t* _this, LinkedList_Node_t* value)
{
    LinkedList_Node_t* aux;

    if (_this == NULL)
    {
        return -1;
    }

    if (value == NULL)
    {
        return -2;
    }

    // Case 1: first element of the list
    if ( _this->comparisonPredicate(_this->first, value) == 0 )
    {
        LinkedList_Node_t* next = _this->first->next;
        _this->first->next      = NULL;
        _this->first            = next;
        (_this->length)--;

        return 0;
    }

    // Case 2: element in the middle of the list
    for (aux = _this->first; aux != NULL; aux = aux->next)
    {
        if ( _this->comparisonPredicate(aux->next, value) == 0 )
        {
            LinkedList_Node_t* item = aux->next;
            LinkedList_Node_t* next = item->next;
            aux->next = next;
            (_this->length)--;

            if (_this->last == item) // Last element?
            {
                _this->last = next;
            }

            break;
        }
    }

    return 0;
}

LinkedList_Node_t* LinkedList_find(LinkedList_t* _this, LinkedList_Node_t* value)
{
    LinkedList_Node_t* aux;

    if (_this == NULL)
    {
        return NULL;
    }

    if (value == NULL)
    {
        return NULL;
    }

    for (aux = _this->first; aux != NULL; aux = aux->next)
    {
        if ( _this->comparisonPredicate(aux, value) == 0 )
        {
            return aux;
        }
    }

    return NULL;
}

/***********************************************************************/

int32_t DoubleLinkedList_init(DoubleLinkedList_t* _this, DoubleLinkedList_Predicate predicate)
{
    if (_this == NULL)
    {
        return -1;
    }

    _this->first  = NULL;
    _this->last   = NULL;
    _this->length = 0;
    _this->comparisonPredicate = predicate;

    return 0;
}

int32_t DoubleLinkedList_destroy(DoubleLinkedList_t* _this)
{
    // INFO: free the memory of the list?

    return 0;
}

DoubleLinkedList_Node_t* DoubleLinkedList_getFirst(DoubleLinkedList_t* _this)
{
    if (_this == NULL)
    {
        return NULL;
    }

    return _this->first;
}

DoubleLinkedList_Node_t* DoubleLinkedList_getNext(DoubleLinkedList_Node_t* node)
{
    if (node == NULL)
    {
        return NULL;
    }

    return node->next;
}

DoubleLinkedList_Node_t* DoubleLinkedList_getPrevious(DoubleLinkedList_Node_t* node)
{
    if (node == NULL)
    {
        return NULL;
    }

    return node->previous;
}

DoubleLinkedList_Node_t* DoubleLinkedList_getLast(DoubleLinkedList_t* _this)
{
    if (_this == NULL)
    {
        return NULL;
    }

    return _this->last;
}

int32_t DoubleLinkedList_length(DoubleLinkedList_t* _this)
{
    return _this->length;
}

int32_t DoubleLinkedList_insert(DoubleLinkedList_t* _this, DoubleLinkedList_Node_t *item)
{
    DoubleLinkedList_Node_t* aux;

    if (_this == NULL)
    {
        return -1;
    }

    if (item == NULL)
    {
        return -2;
    }

    if (_this->first == NULL && _this->last == NULL)
    {
        item->next     = NULL;
        item->previous = NULL;
        _this->first   = item;
        _this->last    = item;
        (_this->length)++;
        return 0;
    }

    if ( _this->comparisonPredicate(_this->first, item) > 0 )
    {
        if (_this->first->next == NULL)
        {
            _this->last = _this->first;
        }

        item->next             = _this->first;
        item->previous         = NULL;
        _this->first->previous = item;
        _this->first = item;
        (_this->length)++;
        return 0;
    }

    aux = _this->first;

    // Get the last item in list
    // Order by predicate
    while (aux->next != NULL) // next > item
    {
        int32_t result = _this->comparisonPredicate(item, aux->next);

        if (result > 0)
        {
            aux = aux->next;
            continue;
        }

        if (result == 0)
        {
            return 0;
        }

        if (result < 0)
        {
            break;
        }
    }

    item->next     = aux->next;
    item->previous = aux;
    aux->next      = item;

    if (item->next == NULL) // Last element?
    {
        _this->last = item;
    }
    else
    {
        item->next->previous = item;
    }

    (_this->length)++;

    return 0;
}

int32_t DoubleLinkedList_remove(DoubleLinkedList_t* _this, DoubleLinkedList_Node_t* value)
{
    DoubleLinkedList_Node_t* aux;

    if (_this == NULL)
    {
        return -1;
    }

    if (value == NULL)
    {
        return -2;
    }

    // Case 1: first element of the list
    if ( _this->comparisonPredicate(_this->first, value) == 0 )
    {
        DoubleLinkedList_Node_t* item = _this->first;
        DoubleLinkedList_Node_t* next = item->next;

        _this->first = next;

        if (_this->first == NULL)
        {
            _this->last = NULL;
        }

        if (next != NULL)
        {
            next->previous = NULL;
        }

        item->next      = NULL;
        item->previous  = NULL;

        (_this->length)--;

        return 0;
    }

    // Case 2: element in the middle of the list
    for (aux = _this->first; aux != NULL; aux = aux->next)
    {
        if ( _this->comparisonPredicate(aux->next, value) == 0 )
        {
            DoubleLinkedList_Node_t* item = aux->next;
            DoubleLinkedList_Node_t* next = item->next;
            aux->next = next;
            (_this->length)--;

            if (_this->last == item) // Last element?
            {
                _this->last = item->previous;
            }

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

DoubleLinkedList_Node_t *DoubleLinkedList_find(DoubleLinkedList_t* _this, DoubleLinkedList_Node_t* value)
{
    DoubleLinkedList_Node_t* aux;

    if (_this == NULL)
    {
        return NULL;
    }

    if (value == NULL)
    {
        return NULL;
    }

    for (aux = _this->first; aux != NULL; aux = aux->next)
    {
        if ( _this->comparisonPredicate(aux, value) == 0 )
        {
            return aux;
        }
    }

    return NULL;
}
