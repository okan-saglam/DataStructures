#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    
    
    int height(Node<T> *r) const;
    int size(Node<T> *r) const;
    
    T& contains(Node<T> *r, T val) const;
    bool bool_contains(Node<T> *r, T val) const;
    
    T& ceiling(Node<T> *r, T element) const;
    T& floor(Node<T> *r, T element) const;
    
    T& min(Node<T> *r) const;
    T& max(Node<T> *r) const;
    
    T& next(Node<T> *r, T element) const;
    
    void treeToArray(Node<T> *r, T sorted[], int& i);
    void arrayToTree(T *&array, int start, int end, Node<T>*& r);
    void balance_2(Node<T> *&r) ;
    
    void removePostOrder(Node<T>* &r);
    
    
    Node<T>* insert_2(Node<T> *&r,const T &element);
    bool checkHeight();
    
    Node<T>* parent_2(Node<T>* r, T value);
    Node<T>* parent(T value);
    
    Node<T>* remove_2(Node<T>* r, T value);
    
    Node<T>* min_2(Node<T> *r) const;
    Node<T>* max_2(Node<T> *r) const;
    
    Node<T>* copy(Node<T>*& lhs, Node<T>*& rhs);
    
    void remove_helper(Node<T>* &r, T value, Node<T>* &parent_node);

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H


template <class T>
Node<T>* ScapegoatTree<T>::copy(Node<T>*& lhs, Node<T>*& rhs)
{
    if(rhs == NULL)
        return NULL;
    else
    {
        insert_2(lhs, rhs->element);
        copy(lhs->left, rhs->left);
        copy(lhs->right, rhs->right);
    }
    return lhs;
}

template <class T>
Node<T>* ScapegoatTree<T>::parent_2(Node<T>* r, T value)
{
    if(root == NULL)
        return NULL;
    else if(value == root->element)
        return NULL;
    else if(r->left == NULL && r->right == NULL)
        return NULL;
    else if((r->left && r->left->element == value) || (r->right && r->right->element == value))
        return r;
    else if(r->element < value)
        return parent_2(r->right, value);
    else if(r->element > value)
        return parent_2(r->left, value);
}

template <class T>
Node<T>* ScapegoatTree<T>::parent(T value)
{
    return parent_2(root, value);
}

template <class T>
void ScapegoatTree<T>::removePostOrder(Node<T>* &r)
{
    if(r != NULL)
    {
        removePostOrder(r->left);
        removePostOrder(r->right);
        delete r;
        r = NULL;
    }
}

template <class T>
int ScapegoatTree<T>::height(Node<T> *r) const
{
    if(r == NULL)
        return -1;
    else
        return std::max(height(r->left), height(r->right))+1;
}

template<class T>
int ScapegoatTree<T>::size(Node<T> *r) const
{
    if(r == NULL)
        return 0;
    else
        return size(r->left) + 1 + size(r->right);
}

template <class T>
T& ScapegoatTree<T>::contains(Node<T> *r, T val) const
{
    if(r == NULL)
        throw NoSuchItemException();
    else if(r->element == val)
        return r->element;
    else if(r->element < val)
        return contains(r->right, val);
    else if(r->element > val)
        return contains(r->left, val);
}

template <class T>
bool ScapegoatTree<T>::bool_contains(Node<T> *r, T val) const
{
    if(r == NULL)
        return false;
    else if(r->element == val)
        return true;
    else if(r->element < val)
        return bool_contains(r->right, val);
    else if(val < r->element)
        return bool_contains(r->left, val);
}

template <class T>
T& ScapegoatTree<T>::ceiling(Node<T> *r, T element) const
{
    if(bool_contains(r, element))
        return contains(r, element);
    else
    {
        if(element < r->element)
        {
            if(max_2(r->left)->element < element)
                return r->element;
            else 
                return ceiling(r->left, element);
        }
        else if(r->element < element)
        {
            if(element < min_2(r->right)->element)
                return min_2(r->right)->element;
            else 
                return ceiling(r->right, element);
        }
    }
}

template <class T>
T& ScapegoatTree<T>::floor(Node<T> *r, T element) const
{
    if(bool_contains(r, element))
        return contains(r, element);
    else
    {
        if(element < r->element)
        {
            if(max_2(r->left)->element < element)
                return max_2(r->left)->element;
            else
                return floor(r->left, element);
        }
        else if(r->element < element)
        {
            if(element < min_2(r->right)->element)
                return r->element;
            else
                return floor(r->right, element);
        }
    }
}

template <class T>
T& ScapegoatTree<T>::min(Node<T> *r) const
{
    if(r == NULL)
        throw NoSuchItemException();
    while(r->left)
        r = r->left;
    return r->element;
}

template <class T>
Node<T>* ScapegoatTree<T>::min_2(Node<T> *r) const
{
    Node<T> *current = r;
    while(current && current->left)
        current = current->left;
    return current;
}

template <class T>
T& ScapegoatTree<T>::max(Node<T> *r) const
{
    if(r == NULL)
        throw NoSuchItemException();
    while(r->right)
        r = r->right;
    return r->element;
}

template <class T>
Node<T>* ScapegoatTree<T>::max_2(Node<T> *r) const
{
    Node<T> *current = r;
    while(current && current->right)
        current = current->right;
    return current;
}

template <class T>
T& ScapegoatTree<T>::next(Node<T> *r, T element) const
{
    if(element < r->element)
    {
        if(max_2(r->left) == NULL || max_2(r->left)->element <= element)
            return r->element;
        else
            return next(r->left, element);
    }
    else if(r->element <= element)
    {
        if(element < min_2(r->right)->element)
            return min_2(r->right)->element;
        else
            return next(r->right, element);
    }
}

template <class T>
void ScapegoatTree<T>::treeToArray(Node<T> *r, T sorted[], int& i)
{
    if(r != NULL)
    {
        treeToArray(r->left, sorted, i);
        sorted[i++] = r->element;
        treeToArray(r->right, sorted, i);
    }
}

template <class T>
void ScapegoatTree<T>::arrayToTree(T *&array, int start, int end, Node<T>*& r)
{
    int mid = (start + end) / 2;
    if(start > end)
        return;
    else
    {
        r = new Node<T>();
        r->element = array[mid];
        arrayToTree(array, start, mid-1, r->left);
        arrayToTree(array, mid+1, end, r->right);
    }
}

template <class T>
void ScapegoatTree<T>::balance_2(Node<T>*& r)
{
    int number_of_element = size(r), i=0; 
    T *arr = new T[number_of_element];
    treeToArray(r, arr, i);
    removePostOrder(r);
    arrayToTree(arr, 0, number_of_element-1, r);
    delete [] arr;
}

template<class T>
Node<T>* ScapegoatTree<T>::insert_2(Node<T> *&r, const T &element)
{
    if(r == NULL){
        r = new Node<T>(element, NULL, NULL);
        return r;
    }
    else if(element < r->element)
        insert_2(r->left, element);
    else if(element > r->element)
        insert_2(r->right, element);
}

template <class T>
bool ScapegoatTree<T>::checkHeight()
{
    int height = getHeight();
    if(height <= (log(upperBound)/log(1.5)))
        return true;
    return false;
}

template <class T>
void ScapegoatTree<T>::remove_helper(Node<T>* &r, T value, Node<T>* &parent_node)
{
    if(r==NULL)
        return;
    else if(r->element < value){
        if(r->right->element == value)
            parent_node = r;
        remove_helper(r->right, value, parent_node);
    }
    else if(value < r->element){
        if(r->left->element == value)
            parent_node = r;
        remove_helper(r->left, value, parent_node);
    }
    else // we find the node
    {
        Node<T> *temp;
        if(r->left == NULL && r->right == NULL) // it is a leaf
        {
            delete r;
            r = NULL;
        }
        else if(r->right == NULL) // it has a left child, but not right
        {
            if(parent_node)
            {
                if(parent_node->element < value) {temp = parent_node->right; parent_node->right = r->left;}
                else {temp = parent_node->left; parent_node->left = r->left;}
                delete temp;
                temp = NULL;
            }
            else // it is root
            {
                temp = r;
                r = r->left;
                delete temp;
                temp = NULL;
            }
        }
        else if(r->left == NULL) // it has a right child, but not left
        {
            if(parent_node)
            {
                if(parent_node->element < value) {temp = parent_node->right; parent_node->right = r->right;}
                else {temp = parent_node->left; parent_node->left = r->right;}
                delete temp;
                temp = NULL;
            }
            else // it is root
            {
                temp = r;
                r = r->right;
                delete temp;
                temp = NULL;
            }
        }
        else if(r->right != NULL && r->left != NULL) // both children exist
        {
            Node<T>* maxofleft = max_2(r->left);
            T max = maxofleft->element;
            parent_node = r;
            remove_helper(r->left, maxofleft->element, parent_node);
            r->element = max;
        }
    }
}

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    Node<T>* rhs_root = obj.root;
    root = NULL;
    upperBound = obj.upperBound;
    copy(root, rhs_root);
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    removeAllNodes();
    delete root;
    upperBound = 0;
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    return root == NULL;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    return height(root);
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    return size(root);
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    Node<T> *inserted;
    if(bool_contains(root, element))
        return false;
    inserted = insert_2(root, element);
    upperBound++;
    if(checkHeight())
    {
        return true;
    }
    else
    {
        Node<T> *parent_ptr = parent(element);
        while(size(inserted) * 3 <= size(parent_ptr) * 2)
        {
            inserted = parent_ptr;
            parent_ptr = parent(parent_ptr->element);
        }
        if(parent_ptr)
        {
            inserted = parent(parent_ptr->element);
            balance_2(parent_ptr); 
            if(inserted->element < parent_ptr->element)
                inserted->right = parent_ptr;
            else
                inserted->left = parent_ptr;
        }
        else
            balance_2(inserted);
        return true;
    }
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element)
{
    if(!bool_contains(root, element))
        return false;
    else
    {
        int size;
        Node<T> *parent_node = NULL;
        remove_helper(root, element, parent_node);
        size = getSize();
        if((upperBound/2.0) <= size && size <= upperBound)
            return true;
        else
        {
            balance();
            upperBound = getSize();
            return true;
        }
    }
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    removePostOrder(root);
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    return contains(root, element);
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        // Ben
        if(isEmpty())
        {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        // Ben
    } else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        /* TODO */
        // Ben
        if(isEmpty())
        {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        // Ben
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        // Ben
        if(node == NULL)
            return;
        std::cout << "\t" << node->element;
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        // Ben
    } else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
          return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == postorder) {
        /* TODO */
        // Ben
        if(node == NULL)
            return;
            
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        
        std::cout << "\t" << node->element;
        // Ben
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    if(this != &rhs)
    {
        Node<T>* rhs_root = rhs.root;
        removeAllNodes();
        root = NULL;
        upperBound = rhs.upperBound;
        copy(root, rhs_root);
    }
    return *this;
}

template<class T>
void ScapegoatTree<T>::balance() {
    balance_2(root);
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    if(element < getMin())
        return getMin();
    else if(getMax() < element)
        throw NoSuchItemException();
    else
        return ceiling(root, element);
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    if(element < getMin())
        throw NoSuchItemException();
    else if(getMax() < element)
        return getMax();
    else
        return floor(root, element);
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    return min(root);
}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    return max(root);
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    T maxofall = max_2(root)->element;
    if(maxofall <= element)
        throw NoSuchItemException();
    else
        return next(root, element);
}
