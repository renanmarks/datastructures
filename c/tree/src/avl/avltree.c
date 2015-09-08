#include "avltree.h"
#include "assert.h"

/**************************************************************************/
/* Based on libtree code by https://github.com/fbuihuu/libtree            */
/**************************************************************************/

/**************************************************************************/
/* Private stuff */

enum SubtreeType
{
    SUBTREE_LEFT  = 0,
    SUBTREE_RIGHT = 1
};

static inline uint32_t isRoot(AVLTree_Node_t* _this)
{
    return (_this->parent == NULL);
}

static inline void initNode(AVLTree_Node_t* _this)
{
    _this->subtree[SUBTREE_LEFT]  = NULL;
    _this->subtree[SUBTREE_RIGHT] = NULL;
    _this->parent  = NULL;
    _this->balance = 0;
}

static inline int32_t getBalance(AVLTree_Node_t* _this)
{
    return _this->balance;
}

static inline void setBalance(AVLTree_Node_t* _this, int32_t value)
{
    _this->balance = value;
}

static inline int32_t incBalance(AVLTree_Node_t* _this)
{
    return ++(_this->balance);
}

static inline int32_t decBalance(AVLTree_Node_t* _this)
{
    return --(_this->balance);
}

static inline AVLTree_Node_t* getParent(AVLTree_Node_t* _this)
{
    return _this->parent;
}

static inline void setParent(AVLTree_Node_t* _this, AVLTree_Node_t* parent)
{
    _this->parent = parent;
}

static inline void setChild( AVLTree_Node_t* node, enum SubtreeType type, AVLTree_Node_t* child)
{
    node->subtree[type] = child;
}

/**
 * @brief rotateTree Rotate the subtree root node informed to the left or right.
 * @param _this
 * @param tree
 * @param subtree_type
 */
static void rotateTree(AVLTree_Node_t* _this, AVLTree_t* tree, enum SubtreeType subtree_type)
{
    enum SubtreeType subtree_complement = (subtree_type + 1) % 2;
    AVLTree_Node_t* x        = _this;
    AVLTree_Node_t* xParent  = getParent(x);

    AVLTree_Node_t* y        = x->subtree[subtree_complement]; /* cant be null */

    x->subtree[subtree_complement] = y->subtree[subtree_type];

    if (y->subtree[subtree_type] != NULL)
    {
        setParent(y->subtree[subtree_type], x);
    }

    setParent(y, xParent);

    if (xParent == NULL)
    {
        tree->root = y;
    }
    else
    {
        if (xParent->subtree[SUBTREE_LEFT] == x)
        {
            xParent->subtree[SUBTREE_LEFT] = y;
        }
        else
        {
            xParent->subtree[SUBTREE_RIGHT] = y;
        }
    }

    y->subtree[subtree_type] = x;
    setParent(x, y);
}


static inline void rotateRight(AVLTree_Node_t* _this, AVLTree_t* tree)
{
    rotateTree(_this, tree, SUBTREE_RIGHT);
}

static inline void rotateLeft(AVLTree_Node_t* _this, AVLTree_t* tree)
{
    rotateTree(_this, tree, SUBTREE_LEFT);
}

/**
 * @brief getLowestNodeOnSubtree Get the lowest node on the asked subtree. Usefull for the
 * getfirst() and getlast() functions.
 * @param _this
 * @param type
 * @return
 */
static AVLTree_Node_t* getLowestNodeOnSubtree(AVLTree_Node_t* _this, enum SubtreeType type)
{
    AVLTree_Node_t* aux = _this;

    while (aux->subtree[type] != NULL)
    {
        aux = aux->subtree[type];
    }

    return aux;
}

static AVLTree_Node_t* getNeightbour(AVLTree_Node_t* node, enum SubtreeType type)
{
    AVLTree_Node_t* temp = node;
    AVLTree_Node_t* parent;
    enum SubtreeType subtree_complement = (type + 1) % 2;

    if (temp->subtree[type] != NULL)
    {
        return getLowestNodeOnSubtree(temp->subtree[type], subtree_complement);
    }

    parent = getParent(temp);

    while ((parent != NULL) && (parent->subtree[type] == temp))
    {
        temp = parent;
        parent = getParent(temp);
    }

    return parent;
}

static AVLTree_Node_t* doLookup(const AVLTree_t* tree,
                                const AVLTree_Node_t* key,
                                AVLTree_Node_t** pparent,
                                AVLTree_Node_t** unbalanced,
                                enum SubtreeType* type)
{
    AVLTree_Node_t* node  = tree->root;
    int32_t compareResult = 0;

    *pparent    = NULL;
    *unbalanced = node;
    *type       = SUBTREE_RIGHT;

    while (node != NULL)
    {
        if (getBalance(node) != 0)
        {
            *unbalanced = node;
        }

        compareResult = tree->comparisonPredicate(node, key);

        if (compareResult == 0)
        {
            return node;
        }

        *pparent = node;
        *type    = (compareResult > 0) ? SUBTREE_LEFT : SUBTREE_RIGHT;
        node     = node->subtree[*type];
    }

    return NULL;
}

/**************************************************************************/
/* Iterators */

AVLTree_Node_t* AVLTree_getFirst(AVLTree_t* _this)
{
    return _this->first;
}

AVLTree_Node_t* AVLTree_getLast(AVLTree_t* _this)
{
    return _this->last;
}

AVLTree_Node_t* AVLTree_getNext(AVLTree_t* _this, AVLTree_Node_t* node)
{
    //TODO: maybe check if node is part of _this tree?
    return getNeightbour(node, SUBTREE_RIGHT);
}

AVLTree_Node_t* AVLTree_getPrevious(AVLTree_t* _this, AVLTree_Node_t* node)
{
    //TODO: maybe check if node is part of _this tree?
    return getNeightbour(node, SUBTREE_LEFT);
}

/**************************************************************************/
/* Operations */

int32_t AVLTree_init(AVLTree_t* _this, AVLTree_ComparisonPredicate comparisonPredicate)
{
    if (_this == NULL)
        return -1;

    _this->comparisonPredicate = comparisonPredicate;
    _this->root     = NULL;
    _this->first    = NULL;
    _this->last     = NULL;
    _this->height   = -1;

    return 0;
}

AVLTree_Node_t* AVLTree_lookup(const AVLTree_t* _this, const AVLTree_Node_t* node)
{
    AVLTree_Node_t* parent;
    AVLTree_Node_t* unbalanced;
    enum SubtreeType type;

    return doLookup(_this, node, &parent, &unbalanced, &type);
}

AVLTree_Node_t* AVLTree_insert(AVLTree_t* _this, AVLTree_Node_t* node)
{
    AVLTree_Node_t* key;
    AVLTree_Node_t* parent;
    AVLTree_Node_t* unbalanced;
    enum SubtreeType type;

    key = doLookup(_this, node, &parent, &unbalanced, &type);

    if (key != NULL)
    {
        return key;
    }

    initNode(node);

    if (parent == NULL)
    {
        _this->root = node;
        _this->first = node;
        _this->last = node;
        _this->height++;
        return NULL;
    }

    if (type == SUBTREE_LEFT)
    {
        if (parent == _this->first)
        {
            _this->first = node;
        }
    }
    else
    {
        if (parent == _this->last)
        {
            _this->last = node;
        }
    }

    setParent(node, parent);
    setChild(parent, type, node);

    while (1)
    {
        if (parent->subtree[SUBTREE_LEFT] == node)
        {
            decBalance(parent);
        }
        else
        {
            incBalance(parent);
        }

        if (parent == unbalanced)
        {
            break;
        }

        node   = parent;
        parent = getParent(parent);
    }

    switch(getBalance(unbalanced))
    {
    case 1:
    case -1:
        ++(_this->height);
        /* fall through */
    case 0:
        break;
    case 2:
    {
        AVLTree_Node_t* right = unbalanced->subtree[SUBTREE_RIGHT];

        if (getBalance(right) == 1)
        {
            setBalance(unbalanced, 0);
            setBalance(right, 0);
        }
        else
        {
            switch (getBalance(right->subtree[SUBTREE_LEFT]))
            {
            case 1:
                setBalance(unbalanced, -1);
                setBalance(right, 0);
                break;
            case 0:
                setBalance(unbalanced, 0);
                setBalance(right, 0);
                break;
            case -1:
                setBalance(unbalanced, 0);
                setBalance(right, 1);
                break;
            }
            setBalance(right->subtree[SUBTREE_LEFT], 0);
            rotateRight(right, _this);
        }
        rotateLeft(unbalanced, _this);
        break;
    }
    case -2:
    {
        AVLTree_Node_t* left = unbalanced->subtree[SUBTREE_LEFT];

        if (getBalance(left) == -1)
        {
            setBalance(unbalanced, 0);
            setBalance(left, 0);
        }
        else
        {
            switch (getBalance(left->subtree[SUBTREE_RIGHT]))
            {
            case 1:
                setBalance(unbalanced, 0);
                setBalance(left, -1);
                break;
            case 0:
                setBalance(unbalanced, 0);
                setBalance(left, 0);
                break;
            case -1:
                setBalance(unbalanced, 1);
                setBalance(left, 0);
                break;
            }
            setBalance(left->subtree[SUBTREE_RIGHT], 0);
            rotateLeft(left, _this);
        }
        rotateRight(unbalanced, _this);
        break;
    }
    }
    return NULL;
}

void AVLTree_remove(AVLTree_t* _this, AVLTree_Node_t* node)
{
    AVLTree_Node_t*  parent;
    AVLTree_Node_t*  left;
    AVLTree_Node_t*  right;
    AVLTree_Node_t*  next;
    enum SubtreeType type;

    if (node == NULL)
    {
        return;
    }

    parent = getParent(node);
    left   = node->subtree[SUBTREE_LEFT];
    right  = node->subtree[SUBTREE_RIGHT];

    if (node == _this->first)
    {
        _this->first = AVLTree_getNext(_this, node);
    }

    if (node == _this->last)
    {
        _this->last = AVLTree_getPrevious(_this, node);
    }

    if (left == NULL)
    {
        next = right;
    }
    else if (right == NULL)
    {
        next = left;
    }
    else
    {
        next = getLowestNodeOnSubtree(right, SUBTREE_LEFT); // get first of this sub tree
    }

    if (parent != NULL)
    {
        type = (parent->subtree[SUBTREE_LEFT] == node) ? SUBTREE_LEFT : SUBTREE_RIGHT;
        setChild(parent, type, next);
    }
    else
    {
        _this->root = next;
    }

    if ((left != NULL) && (right != NULL))
    {
        setBalance(next, getBalance(node));
        next->subtree[SUBTREE_LEFT] = left;
        setParent(left, next);

        if (next != right)
        {
            parent = getParent(next);
            setParent(next, getParent(node));

            node = next->subtree[SUBTREE_RIGHT];
            parent->subtree[SUBTREE_LEFT] = node;
            type = SUBTREE_LEFT;

            next->subtree[SUBTREE_RIGHT] = right;
            setParent(right, next);
        }
        else
        {
            setParent(next, parent);
            parent = next;
            node   = parent->subtree[SUBTREE_RIGHT];
            type   = SUBTREE_RIGHT;
        }
        assert(parent != NULL);
    }
    else
    {
        node = next;
    }

    if (node != NULL)
    {
        setParent(node, parent);
    }

    /*
     * At this point, 'parent' can only be null, if 'node' is the
     * tree's root and has at most one child.
     *
     * case 1: the subtree is now balanced but its height has
     * decreased.
     *
     * case 2: the subtree is mostly balanced and its height is
     * unchanged.
     *
     * case 3: the subtree is unbalanced and its height may have
     * been changed during the rebalancing process, see below.
     *
     * case 3.1: after a left rotation, the subtree becomes mostly
     * balanced and its height is unchanged.
     *
     * case 3.2: after a left rotation, the subtree becomes
     * balanced but its height has decreased.
     *
     * case 3.3: after a left and a right rotation, the subtree
     * becomes balanced or mostly balanced but its height has
     * decreased for all cases.
     */
    while (parent != NULL)
    {
        int32_t balance;
        node    = parent;
        parent  = getParent(parent);

        if (type == SUBTREE_LEFT)
        {
            type    = ((parent != NULL) && (parent->subtree[SUBTREE_LEFT] == node)) ? SUBTREE_LEFT : SUBTREE_RIGHT;
            balance = incBalance(node);

            if (balance == 0)                       /* case 1 */
            {
                continue;
            }

            if (balance == 1)                       /* case 2 */
            {
                return;
            }

            right = node->subtree[SUBTREE_RIGHT];   /* case 3 */

            switch (getBalance(right))
            {
            case 0:                                 /* case 3.1 */
                setBalance(node, 1);
                setBalance(right, -1);
                rotateLeft(node, _this);
                return;

            case 1:                                 /* case 3.2 */
                setBalance(node, 0);
                setBalance(right, 0);
                break;

            case -1:                                /* case 3.3 */
                switch (getBalance(right->subtree[SUBTREE_LEFT]))
                {
                case 1:
                    setBalance(node, -1);
                    setBalance(right, 0);
                    break;

                case 0:
                    setBalance(node, 0);
                    setBalance(right, 0);
                    break;

                case -1:
                    setBalance(node, 0);
                    setBalance(right, 1);
                    break;
                }
                setBalance(right->subtree[SUBTREE_LEFT], 0);
                rotateRight(right, _this);
                break;
            }
            rotateLeft(node, _this);
        }
        else
        {
            type    = ((parent != NULL) && (parent->subtree[SUBTREE_LEFT] == node)) ? SUBTREE_LEFT : SUBTREE_RIGHT;
            balance = decBalance(node);

            if (balance == 0)                       /* case 1 */
            {
                continue;
            }

            if (balance == -1)                       /* case 2 */
            {
                return;
            }

            left = node->subtree[SUBTREE_LEFT];     /* case 3 */

            switch (getBalance(left))
            {
            case 0:                                 /* case 3.1 */
                setBalance(node, -1);
                setBalance(left, 1);
                rotateRight(node, _this);
                return;

            case -1:                                /* case 3.2 */
                setBalance(node, 0);
                setBalance(left, 0);
                break;

            case 1:                                 /* case 3.3 */
                switch (getBalance(left->subtree[SUBTREE_RIGHT]))
                {
                case 1:
                    setBalance(node, 0);
                    setBalance(left, -1);
                    break;

                case 0:
                    setBalance(node, 0);
                    setBalance(left, 0);
                    break;

                case -1:
                    setBalance(node, 1);
                    setBalance(left, 0);
                    break;
                }
                setBalance(left->subtree[SUBTREE_RIGHT], 0);
                rotateLeft(left, _this);
                break;
            }
            rotateRight(node, _this);
        }
    }
    _this->height--;
}

void AVLTree_replace(AVLTree_t* _this, AVLTree_Node_t* oldNode, AVLTree_Node_t* newNode)
{
    AVLTree_Node_t* parent = getParent(oldNode);

    if (parent != NULL)
    {
        enum SubtreeType type = (parent->subtree[SUBTREE_LEFT] == oldNode) ? SUBTREE_LEFT : SUBTREE_RIGHT;

        setChild(parent, type, newNode);
    }
    else
    {
        _this->root = newNode;
    }

    if (oldNode->subtree[SUBTREE_LEFT] != NULL)
    {
        setParent(oldNode->subtree[SUBTREE_LEFT], newNode);
    }

    if (oldNode->subtree[SUBTREE_RIGHT] != NULL)
    {
        setParent(oldNode->subtree[SUBTREE_RIGHT], newNode);
    }

    if (_this->first == oldNode)
    {
        _this->first = newNode;
    }

    if (_this->last == oldNode)
    {
        _this->last = newNode;
    }

    *newNode = *oldNode;
}
