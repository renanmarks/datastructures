#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdint.h>
#include <stddef.h>

/**************************************************************************/
/* Based on libtree code by https://github.com/fbuihuu/libtree            */
/**************************************************************************/

typedef struct AVLTree_Node_s
{
    struct AVLTree_Node_s* subtree[2];
    struct AVLTree_Node_s* parent;
    int32_t                balance;
} AVLTree_Node_t;

typedef int32_t (*AVLTree_ComparisonPredicate) (const AVLTree_Node_t* a, const AVLTree_Node_t* b);

typedef struct AVLTree_s
{
    AVLTree_Node_t* root;
    AVLTree_Node_t* first;
    AVLTree_Node_t* last;
    uint32_t height;
    AVLTree_ComparisonPredicate comparisonPredicate;
    /* WARNING: this is really necessary? uint64_t reserved[4]; */
    //uint64_t reserved[4];
} AVLTree_t;

/*
 * The definition has been "stolen" from the Linux kernel.
 */
#ifdef __GNUC__
#  define AVLTree_containerOf(node, type, member) ({		\
    const AVLTree_Node_t *__mptr = (node);                  \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define AVLTree_containerOf(node, type, member)			\
    ((type *)((char *)(node) - offsetof(type, member)))
#endif	/* __GNUC__ */

/* Iterators */
AVLTree_Node_t* AVLTree_getFirst    (AVLTree_t* _this);
AVLTree_Node_t* AVLTree_getLast     (AVLTree_t* _this);
AVLTree_Node_t* AVLTree_getNext     (AVLTree_t* _this, AVLTree_Node_t* node);
AVLTree_Node_t* AVLTree_getPrevious (AVLTree_t* _this, AVLTree_Node_t* node);

/* Operations */
int32_t         AVLTree_init    (AVLTree_t* _this, AVLTree_ComparisonPredicate comparisonPredicate);
AVLTree_Node_t* AVLTree_lookup  (const AVLTree_t* _this, const AVLTree_Node_t* node);
AVLTree_Node_t* AVLTree_insert  (AVLTree_t* _this, AVLTree_Node_t* node);
void            AVLTree_remove  (AVLTree_t* _this, AVLTree_Node_t* node);
void            AVLTree_replace (AVLTree_t* _this, AVLTree_Node_t* oldNode, AVLTree_Node_t* newNode);

#endif
