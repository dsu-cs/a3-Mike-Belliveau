#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;

    Node<T> *insertHelp(int val, Node<T> *root);

    Node<T> *removeHelp(Node<T> *node, int val);

    std::vector<T> *inorderHelp(std::vector<T> *x, Node<T> *node);

    std::vector<T> *postorderHelp(std::vector<T> *x, Node<T> *node);

    std::vector<T> *preorderHelp(std::vector<T> *x, Node<T> *node);

    Node<T> *searchHelp(Node<T> *node, int val);

};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;
    inorderHelp(vec, root);
    return vec;
}


template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    preorderHelp(vec, root);
    return vec;
}


template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    postorderHelp(vec, root);
    return vec;
}

template<class T>
void BST<T>::insert(T new_data)
{
    root = insertHelp(new_data, root);
}


template<class T>
Node<T> *BST<T>::search(T val)
{
    return searchHelp(root, val);
}



template<class T>
void BST<T>::remove(T val)
{
   root = removeHelp(root, val);
}



template<class T>
int BST<T>::get_size()
{
    return node_count;
}

template<class T>
std::vector<T> *BST<T>::inorderHelp(std::vector<T> *x, Node<T> *node)
{
    if(node == NULL)
    {
        return NULL;
    }
    inorderHelp(x, node->get_left());
    x->push_back(node->get_data());
    inorderHelp(x, node->get_right());
    return x;
}

template<class T>
std::vector<T> *BST<T>::preorderHelp(std::vector<T> *x, Node<T> *node)
{
    if(node == NULL)
    {
        return NULL;
    }
    x->push_back(node->get_data());
    preorderHelp(x, node->get_left());
    preorderHelp(x, node->get_right());
    return x;
}

template<class T>
std::vector<T> *BST<T>::postorderHelp(std::vector<T> *x, Node<T> *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    postorderHelp(x, node->get_left());
    postorderHelp(x, node->get_right());
    x->push_back(node->get_data());
    return x;
}

template<class T>
Node<T> *BST<T>::insertHelp(int val, Node<T> * node)
{
    if(node == NULL)
    {
        Node<T> *tmp = new Node<T>;
        tmp->set_data(val);
        tmp->set_left(NULL);
        tmp->set_right(NULL);
        node_count++;
        return tmp;
    }
    else if (val < node->get_data())
    {
        node->set_left(insertHelp(val, node->get_left()));
    }
    else if (val > node->get_data())
    {
        node->set_right(insertHelp(val, node->get_right()));
    }
    return node;
}

template <class T>
Node<T> *BST<T>::searchHelp(Node<T> *node, int val)
{
    if (node == NULL)
    {
        return NULL;
    }
    Node<T> *foundNode = new Node<T>;

    if (node->get_data() == val)
    {
        return node;
    }
    else if (val < node->get_data())
    {
        searchHelp(node->get_left(), val);
    }
    else if (val > node->get_data())
    {
        searchHelp(node->get_right(), val);
    }

}

template <class T>
Node<T> *BST<T>::removeHelp(Node<T> *node, int val)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (val < node->get_data())
    {
        node->set_left(removeHelp(node->get_left(), val));
    }
    else if (val > node->get_data())
    {
        node->set_right(removeHelp(node->get_right(), val));
    }
    else if (val == node->get_data())
    {
        if (node->get_left() == NULL)
        {
            Node<T> *tmp = node->get_right();
            delete(node);
            return tmp;
        }
        else if (node->get_right() == NULL)
        {
            Node<T> *tmp = node->get_left();
            delete(node);
            return tmp;
        }
        
        Node<T> *tmp = new Node<T>;
        tmp = node->get_right();

        while(tmp && tmp->get_left() != NULL)
        {
            tmp = tmp->get_left();
        }
        T data = tmp->get_data();
        node->set_data(data);
        node->set_right(removeHelp(node->get_right(), tmp->get_data()));
    }
    
    return node;
    
    
}