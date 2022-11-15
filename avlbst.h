#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void rotateRight(AVLNode<Key,Value>* n);
    void rotateLeft(AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n, int diff);
    AVLNode<Key,Value>* predecessor(AVLNode<Key, Value>* current);

protected:   
    AVLNode<Key,Value>* root_ = nullptr;

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key,Value>* temp = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
    temp -> setBalance(0);
    //if tree empty
    if(root_ == nullptr){
        root_ = temp;
    }
    else
    {
        //find leaf node
        AVLNode<Key,Value>* current = root_;
        AVLNode<Key,Value>* p = current;
        while(current != nullptr)
        {
            p = current;
            if(current -> getKey() == new_item.first)
            {
                current -> setValue(new_item.second);
                break;
            }
            //go right
            else if(new_item.first > current -> getKey())
            {
                current = current -> getRight();
            }
            //go left
            else
            {
                current = current -> getLeft();
            }
        }

        if(current != nullptr) return;

        //set right
        if(new_item.first > current -> getKey())
        {
            temp -> setParent(p);
            p -> setRight(temp);
        }
        //set left
        else if(new_item.first < current -> getKey())
        {
            temp -> setParent(p);
            p -> setLeft(temp);
        }

        if(p -> getBalance() == -1) p -> setBalance(0);
        else if(p -> getBalance() == 1) p -> setBalance(0);
        if(p -> getBalance() == 0)
        {
            insertFix(current, temp);
        }
    }
    BinarySearchTree<Key,Value>::root_ = root_;
}

template<class Key, class Value>
void AVLTree<Key,Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    if(p == nullptr) return;
    else if(p -> getParent() == nullptr)
    {
        //root_ = p;
        return;
    }
    AVLNode<Key,Value>* g = p -> getParent();

    //if p is the left child
    if(p -> getKey() < g -> getKey())
    {
        int gBalance = g -> getBalance();
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
                p = g -> getLeft();
                rotateRight(g);
                if(n -> getBalance() == -1)
                {
                    p -> setBalance(0);
                    g -> setBalance(1);
                    n -> setBalance(0);
                }
                else if(n -> getBalance() == 0)
                {
                    p -> setBalance(0);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }
                else
                {
                    p -> setBalance(-1);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }
            }
            else
            {
                p = g -> getLeft();
                rotateRight(g);
                p -> setBalance(0);
                g -> setBalance(0);
            }
            
        }
    }
    //must be right child since know the child exists
    else
    {
        int gBalance = g -> getBalance();
        //balance = 0
        if(gBalance == 0) return;
        //balance = 1
        else if(gBalance == 1) insertFix(g,p);
        //balance = 2
        else
        {
            //zig zag cases
            if(n -> getKey() < p -> getKey())
            {
                rotateRight(p);
                p = g -> getRight();
                rotateLeft(g);
                if(n -> getBalance() == 1)
                {
                    p -> setBalance(0);
                    g -> setBalance(-1);
                    n -> setBalance(0);
                }
                else if(n -> getBalance() == 0)
                {
                    p -> setBalance(0);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }
                else
                {
                    p -> setBalance(1);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }
            }
            else
            {
                p = g -> getRight();
                rotateLeft(g);
                p -> setBalance(0);
                g -> setBalance(0);
            }
            
        }
    }
    
    if(p -> getParent() == nullptr) root_ = p;
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* tempLeft = n -> getLeft();
    //make left parent the current parent
    tempLeft -> setParent(n -> getParent());
    if(n -> getParent() != nullptr)
    {
        
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

    n -> updateBalance(2);
    tempLeft -> updateBalance(1);
    tempLeft -> getLeft() -> updateBalance(1);
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* tempRight = n -> getRight();
    //make right parent the current parent
    tempRight -> setParent(n -> getParent());
    if(n -> getParent() != nullptr)
    {
        
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

    n -> updateBalance(-2);
    tempRight -> updateBalance(-1);
    tempRight -> getRight() -> updateBalance(-1);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    AVLNode<Key,Value>* current = root_;
    while(current != nullptr)
    {
        if(current -> getKey() == key)
        {
            break;
        }

        if(key > current -> getKey()) current = current -> getRight();
        else current = current -> getLeft();
    }

    //2 children
    if(current -> getLeft() != nullptr && current -> getRight() != nullptr)
    {
        nodeSwap(current, predecessor(current));
    }

    AVLNode<Key,Value>* p = current -> getParent();

    int diff;
    //setting diff value for fix
    if(p != nullptr)
    {
        if(current == p -> getLeft()) diff = 1;
        else diff = -1;
    }
    
    //up to this point current can have at most one child 
    
    //current has a child means current must be a right child of its parent
    if(current -> getLeft() != nullptr)
    {
        AVLNode<Key,Value>* c = current -> getLeft();
        c -> setParent(p);
        p -> setRight(c);
    }
    //has no child 
    else
    {
        //if it has a parent
        if(p != nullptr)
        {
            //if right child
            if(p -> getRight() == current)
            {
                p -> setRight(nullptr);
            }
            //if left child
            else
            {
                p -> setLeft(nullptr);
            }
        }
        // no parent means it is root node
        {
            root_ = nullptr;
        }
    }
    delete current;

    removeFix(p,diff);
    BinarySearchTree<Key,Value>::root_ = root_;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int diff)
{
    if(n == nullptr) return;

    AVLNode<Key,Value>* p = n -> getParent();
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
        if(n -> getBalance() == 0)
        {
            n -> setBalance(-1);
            return;
        }
        else if(n -> getBalance() == 1)
        {
            n -> setBalance(0);
            removeFix(p, ndiff);
        }
        //-1
        else
        {
            AVLNode<Key,Value>* c;
            //left will be taller since we removed from the right
            c = n -> getLeft();
            int balanceC = c -> getBalance();
            //zig-zig
            if(balanceC == -1)
            {
                rotateRight(n);
                n -> setBalance(0);
                c -> setBalance(0);
                removeFix(p,ndiff);
            }
            //zig-zig
            else if(balanceC == 0)
            {
                rotateRight(n);
                n -> setBalance(-1);
                c -> setBalance(1);
                return;
            }
            //zig-zag
            else
            {
                AVLNode<Key,Value>* g = c -> getRight();
                rotateLeft(c);
                rotateRight(n);
                if(g -> getBalance() == 1)
                {
                    n -> setBalance(0);
                    c -> setBalance(-1);
                    g -> setBalance(0);
                }
                else if(g -> getBalance() == 0)
                {
                    n -> setBalance(0);
                    c -> setBalance(0);
                    g -> setBalance(0);
                }
                else
                {
                    n -> setBalance(1);
                    c -> setBalance(0);
                    g -> setBalance(0);
                }
                removeFix(p,ndiff);
            }
        }
    }
    //diff = 1 since removed from the left
    else
    {
        if(n -> getBalance() == 0)
        {
            n -> setBalance(1);
            return;
        }
        else if(n -> getBalance() == -1)
        {
            n -> setBalance(0);
            removeFix(p, ndiff);
        }
        //1
        else
        {
            AVLNode<Key,Value>* c;
            //left will be taller since we removed from the left
            c = n -> getRight();
            int balanceC = c -> getBalance();
            //zig-zig
            if(balanceC == 1)
            {
                rotateLeft(n);
                n -> setBalance(0);
                c -> setBalance(0);
                removeFix(p,ndiff);
            }
            //zig-zig
            else if(balanceC == 0)
            {
                rotateLeft(n);
                n -> setBalance(1);
                c -> setBalance(-1);
                return;
            }
            //zig-zag
            else
            {
                AVLNode<Key,Value>* g = c -> getLeft();
                rotateRight(c);
                rotateLeft(n);
                if(g -> getBalance() == -1)
                {
                    n -> setBalance(0);
                    c -> setBalance(1);
                    g -> setBalance(0);
                }
                else if(g -> getBalance() == 0)
                {
                    n -> setBalance(0);
                    c -> setBalance(0);
                    g -> setBalance(0);
                }
                else
                {
                    n -> setBalance(-1);
                    c -> setBalance(0);
                    g -> setBalance(0);
                }
                removeFix(p,ndiff);
            }
        }
    }

}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* current)
{
    // TODO
    // has a left child then go to 
    if(current -> getLeft() != nullptr)
    {
        //go to the left child
        AVLNode<Key,Value>* temp = current -> getLeft();
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
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
