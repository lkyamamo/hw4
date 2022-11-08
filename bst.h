#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();
        iterator& operator--();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void insertFix(Node<Key,Value>* p, Node<Key,Value>* n);
    void removeFix(Node<Key,Value>* n, int diff);
    void recursiveDelete(Node<Key,Value>* cur);
    int calculateHeight(const Node<Key,Value>* root) const;
    void rotateRight(Node<Key,Value>* n);
    void rotateLeft(Node<Key,Value>* n);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr):
current_(ptr)
{
    // TODO
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator():
current_(nullptr)
{
    // TODO
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if(current_ == rhs.current_)
    {
        return true;
    }
    return false;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if(current_ != rhs.current_)
    {
        return true;
    }
    return false;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = successor(current_);
    return *this;
}

template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator--()
{
    current_ = predecessor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree():
root_(nullptr)
{

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    Node<Key,Value>* temp = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, nullptr);
    //if tree empty
    if(root_ == nullptr){
        root_ = temp;
        return;
    }

    //find leaf node
    BinarySearchTree<Key,Value>::iterator it = root_;
    while(it.current_ -> getLeft() != nullptr || it.current_ -> getRight() != nullptr)
    {
        if(it -> first == keyValuePair.first)
        {
            it.current_ -> setValue(keyValuePair.second);
            break;
        }
        //go right
        else if(keyValuePair.first > it -> first)
        {
            it.current_ = it.current_ -> getRight();
        }
        //go left
        else
        {
            it.current_ = it.current_ -> getLeft();
        }
    }

    //set right
    if(keyValuePair.first > it -> first)
    {
        temp -> setParent(it.current_);
        it.current_ -> setRight(temp);
    }
    //set left
    else if(keyValuePair.first < it -> first)
    {
        temp -> setParent(it.current_);
        it.current_ -> setLeft(temp);
    }

    //if not balanced
    if(!isBalanced())
    {
        insertFix(it.current_ -> getParent(), it.current_);
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    //find the node we are looking for
    BinarySearchTree::iterator it(root_);
    while(it != end())
    {
        if(it -> first == key)
        {
            break;
        }

        if(key > it -> first) it.current_ = it.current_ -> getRight();
        else it.current_ = it.current_ -> getLeft();
    }

    //if it wasn't found
    if(it == end()) return;
    
    nodeSwap(it.current_, predecessor(it.current_));
    Node<Key,Value>* p = it.current_ -> getParent();
    int diff = 0;
    if(p != nullptr)
    {
        //left child
        if(it -> first < p -> getKey()) diff = 1;
        //right child
        else diff = -1;
    }

    //right child
    if(it -> first > it.current_ -> getParent() -> getKey())
    {
        it.current_ -> getParent() -> setRight(nullptr);
        delete it.current_;
    }
    //left child
    else
    {
        it.current_ -> getParent() -> setLeft(nullptr);
        delete it.current_;
    }

    if(! isBalanced()) removeFix(p,diff);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeFix(Node<Key,Value>* n, int diff)
{
    if(n == nullptr) return;
    int balanceN = calculateHeight(n -> getRight()) - calculateHeight(n -> getLeft());

    Node<Key,Value>* p = n -> getParent();
    int ndiff = 0;
    if(p != nullptr)
    {
        //left child
        if(n -> getKey() < p -> getKey()) ndiff = 1;
        //right child
        else ndiff = -1;
    }

    //diff = -1 means removed a right child
    if(diff == -1)
    {
        if(balanceN == 0)
        {
            return;
        }
        else if(balanceN == 1)
        {
            removeFix(p, ndiff);
        }
        //-1
        else
        {
            Node<Key,Value>* c;
            //left will be taller since we removed from the right
            c = n -> getLeft();
            int balanceC = calculateHeight(c -> getRight()) - calculateHeight(c -> getLeft());
            //zig-zig
            if(balanceC == -1)
            {
                rotateRight(n);
                removeFix(p,ndiff);
            }
            //zig-zig
            else if(balanceC == 0)
            {
                rotateRight(n);
                return;
            }
            //zig-zag
            else
            {
                rotateLeft(c);
                rotateRight(n);
                removeFix(p,ndiff);
            }
        }
    }
    //diff = 1 since removed from the left
    else
    {
        if(calculateHeight(n) == 0)
        {
            return;
        }
        else if(calculateHeight(n) == -1)
        {
            removeFix(p, ndiff);
        }
        //1
        else
        {
            Node<Key,Value>* c;
            //right will be taller since we removed from the left
            c = n -> getRight();
            int balanceC = calculateHeight(c -> getRight()) - calculateHeight(c -> getLeft());
            //zig-zig
            if(balanceC == 1)
            {
                rotateLeft(n);
                removeFix(p,ndiff);
            }
            //zig-zig
            else if(balanceC == 0)
            {
                rotateLeft(n);
                return;
            }
            //zig-zag
            else
            {
                rotateRight(c);
                rotateLeft(n);
                removeFix(p,ndiff);
            }
        }
    }

}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // has a left child then go to 
    if(current -> getLeft() != nullptr)
    {
        //go to the left child
        Node<Key,Value>* temp = current -> getLeft();
        //find right most child
        while(temp -> getRight() != nullptr)
        {
            temp = temp -> getRight();
        }
        return temp;
    }
    // has a parent
    else if(current -> getParent() != nullptr)
    {
        //right child
        if(current -> getKey() <= current -> getParent() -> getKey())
        {
            return (current -> getParent());
        }
        //left child
        else
        { 
            return (current -> getParent() -> getParent());
        }
    }
    //has no parent means it is the root node with no left child
    else
    {
        //means it is "right most" node in tree
        return nullptr;
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    // has a right child then go to 
    if(current -> getRight() != nullptr)
    {
        //go to the right child
        Node<Key,Value>* temp = current -> getRight();
        while(temp -> getLeft() != nullptr)
        {
            temp = temp -> getLeft();
        }
        return temp;
    }
    // has a parent
    else if(current -> getParent() != nullptr)
    {
        //left child
        if(current -> getKey() <= current -> getParent() -> getKey())
        {
            return current -> getParent();
        }
        //right child
        else
        { 
            return (current -> getParent() -> getParent());
        }
    }
    //has no parent means it is the root node with no right child
    else
    {
        //means it is "right most" node in tree
        return nullptr;
    }
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    recursiveDelete(root_);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::recursiveDelete(Node<Key,Value>* cur)
{
    if(cur == nullptr)
    {
        return;
    }

    recursiveDelete(cur -> getLeft());
    recursiveDelete(cur -> getRight());
    delete cur;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    BinarySearchTree<Key,Value>::iterator it(root_);
    while(it != nullptr)
    {
        if(it.current_ -> getLeft() == nullptr) break;
        it.current_ = it.current_ -> getLeft();
    }
    return it.current_;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    BinarySearchTree<Key,Value>::iterator it(root_);
    while( it.current_ != nullptr )
    {
        if(it -> first == key)
        {
            return it.current_;
        }
        else if(it -> first > key)
        {
            it = it.current_ -> getLeft();
        }
        else
        {
            it = it.current_ -> getRight();
        }
    }
    return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    Node<Key,Value>* leftNode = nullptr;
    Node<Key,Value>* rightNode = nullptr;

    if(root_ -> getLeft() != nullptr)
    {
        leftNode = root_ -> getLeft();
    }
    if(root_ -> getRight() != nullptr)
    {
        rightNode = root_ -> getRight();
    }
    int left = -1 * (calculateHeight(leftNode));
    int right = calculateHeight(rightNode);
    
    if(abs(left + right) > 1) return false;
    return true;

}

template<typename Key, typename Value>
int BinarySearchTree<Key,Value>::calculateHeight(const Node<Key,Value>* n) const{
	if (n == nullptr) return 0;
	
    Node<Key,Value>* leftNode = n -> getLeft();
    Node<Key,Value>* rightNode = n -> getRight();
    int left = calculateHeight(leftNode);
    int right = calculateHeight(rightNode);
	
    return std::max(left,right) + 1;
}

template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::insertFix(Node<Key,Value>* p, Node<Key,Value>* n)
{
    if(p == nullptr) return;
    else if(p -> getParent() == nullptr)
    {
        //root_ = p;
        return;
    }
    Node<Key,Value>* g = p -> getParent();

    //if p is the left child
    if(p -> getKey() < g -> getKey())
    {
        int gBalance = calculateHeight(g);
        //balance = 0
        if(gBalance == 0) return;
        //balance = -1
        else if(gBalance == -1) insertFix(g,p);
        //balance = -2
        else
        {
            //zig zag cases
            if(n -> getKey() > p -> getKey())
            {
                rotateLeft(p);
            }
            rotateRight(g);
        }
    }
    //must be right child since know the child exists
    else
    {
        int gBalance = calculateHeight(g);
        //balance = 0
        if(gBalance == 0) return;
        //balance = -1
        else if(gBalance == -1) insertFix(g,p);
        //balance = -2
        else
        {
            //zig zag cases
            if(n -> getKey() < p -> getKey())
            {
                rotateRight(p);
            }
            rotateLeft(g);
        }
    }
    
    if(p -> getParent() == nullptr) root_ = p;
}

template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::rotateRight(Node<Key,Value>* n)
{
    Node<Key,Value>* tempLeft = n -> getLeft();

    if(n -> getParent() != nullptr)
    {
        //make left parent the current parent
        tempLeft -> setParent(n -> getParent());
        //make the child of the parent the left node
        if (n -> getKey() > n -> getParent() -> getKey())
        {
            //true if right child
            tempLeft -> getParent() -> setRight(tempLeft);
        }
        else
        {
            //true if left child
            tempLeft -> getParent() -> setLeft(tempLeft);
        }
    }
    
    //make the left of current the right of the left
    n -> setLeft(tempLeft -> getRight());
    //make the right the current
    tempLeft -> setRight(n);
    //set the parent to the left
    n -> setParent(tempLeft);
}

template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::rotateLeft(Node<Key,Value>* n)
{
    Node<Key,Value>* tempRight = n -> getRight();

    if(n -> getParent() != nullptr)
    {
        //make right parent the current parent
        tempRight -> setParent(n -> getParent());
        //make the child of the parent the right node
        if (n -> getKey() > n -> getParent() -> getKey())
        {
            //true if right child
            tempRight -> getParent() -> setRight(tempRight);
        }
        else
        {
            //true if left child
            tempRight -> getParent() -> setLeft(tempRight);
        }
    }
    
    //make the right of current the left of the right
    n -> setRight(tempRight -> getLeft());
    //make left the current
    tempRight -> setLeft(n);
    //set the parent to the left
    n -> setParent(tempRight);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
