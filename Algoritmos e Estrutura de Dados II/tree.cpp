/*
    abstractDataTypesLib
    By Vinícius R. Miguel
    Federal University of São Paulo, 2019
    This is required at least C++
*/

#define NULL 0 // I like it oldschool

#include <iostream>

    /* Giving our desired variable an 'alias', so that it's easy to change the variable type if needed. */
typedef int data_t;

    /* Definition of a binary search tree's node */
class Node
{
    friend class Tree; // Set Tree as a friend class in order to be able to access private members of Tree.
    private:
        Node * left, * right; 
        data_t data;  
    public:    
        void print();
};

    /* Definition of a binary search tree */
class Tree
{
    private:
        Node * tree;
        Node * search(Node * n, data_t key);
    public:
        Tree() // Default constructor of the tree
        {
            tree = NULL; // Initialize tree with nullptr.
        }

        ~Tree() // Default destructor of the tree
       {
           delete tree;
       } 
        Node * search(data_t key); 
        void insert(data_t x);
        void print();
 //       void delete(data_t x); 
};

Node * Tree::search(data_t key)
{
    return search(tree, key);
}

    /* Recursive search of the binary search tree - average case: O(log n) */
Node * Tree::search(Node * n, data_t key)
{
    if(n == NULL) // If we've reached a leaf, return NULL (the tree has been completely searched)
        return NULL; 
    else if (key == n->data) 
            // If the key is equal to the node's value, we've found what we're looking for and return the node's pointer.
        return n;
    else if (key < n->data) 
        /* If the key is smaller than the current node's value, we'll keep looking for the key on all values smaller than the current node's value. */
        return search(n->left, key);
    else 
        /* If the key is bigger than the current node's value, we'll keep looking for the key on all values bigger than the current node's value. */
        return search(n->right, key);
}

void Tree::insert(data_t key)
{
    Node *q , *p = tree;
    bool found = false;

        // We'll traverse the tree to see if we can find key in it.
    while ((p) && (!found))
    {
        q = p; // The pointer q is the parent to p.
        if (key == (p->data))
            found = true; // Key is already inside the tree, so nothing'll be inserted.
        else if (key < (p->data))
            p = (p->left);
        else
            p = (p->right);
    }   

    if(!found)
    {        
        p = new Node;
        p->left = NULL;
        p->right = NULL;
        p->data = key;
        if (tree)
        {
            if(key < (q->data))
                q->left = p;
            else
                q->right = p;
        }
        else tree = p;
    }
}
