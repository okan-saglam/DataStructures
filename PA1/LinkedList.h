#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    
    int i, rhs_size;
    Node<T> *rhs_head = obj.getFirstNode();
    rhs_size = obj.getSize();
    
    head = NULL;
    size = 0;
    for(i=0 ; i<rhs_size ; i++)
    {
        this->append(rhs_head->data);
        rhs_head = rhs_head->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{
    
    if(head!=NULL)
    {
        int i, sizes = size;
        for(i=0 ; i<sizes-1 ; i++)
        {
            removeNodeAtIndex(0);
        }
        delete head;
    }
    size = 0;
    
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if(this != &rhs)
    {
        while(head)
        {
            removeNode(head);   
        }
        
        Node<T> *r = rhs.head;
        do
        {
            this->append(r->data);
            r = r->next;
        }
        while(r != rhs.head);
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return head == NULL;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    if(head==NULL)
        return false;
    else
    {
        int i;
        Node<T> *current = head;
        for(i=0 ; i<size ; i++, current=current->next)
        {
            if(current == node)
                return true;
        }
        return false;
    }
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if(head == NULL)
        return NULL;
    else
        return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if(head == NULL)
        return NULL;
    else
        return head->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    if(head==NULL)
        return NULL;
    else
    {
        int i;
        Node<T> *current;
        for(i=0, current=head ; i<size ; i++, current=current->next)
        {
            if(current->data == data)
                return current;
        }
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    int i;
    Node<T> *current = head;
    for(i=0 ; i<size ; i++)
    {
        if(i==index)
            return current;
        current = current->next;
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    if(head == NULL)
    {
        head = new Node<T>(data);
        head->next = head;
		head->prev = head;
    }
    else
    {
    	if(size==1)
    	{
    		head->prev = new Node<T>(data, head, head);
    		head->next = head->prev;
		}
		else
		{
			head->prev = new Node<T>(data, head->prev, head);
			head->prev->prev->next = head->prev; 
		}
	}
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    if(head==NULL)
    {
    	head = new Node<T>(data);
		head->next = head;
		head->prev = head;	
	}
    else
    {
    	if(size==1)
    	{
    		head->prev = new Node<T>(data, head, head);
    		head->next = head->prev;
    		head = head->prev;
		}
		else
		{
			head->prev = new Node<T>(data, head->prev, head);
			head = head->prev;
			head->prev->next = head;
		}
	}
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if(!containsNode(node))
        return;
    else
    {
        if(node == head)
        {
            head->next = new Node<T>(data, head, head->next);
            head->next->next->prev = head->next;
            size++;
        }
        else if(node == head->prev)
            append(data);
        else
        {
            Node<T> *current = head;
            while(current != node)
            {
                current = current->next;
            }
            current->next = new Node<T>(data, current, current->next);
            current->next->next->prev = current->next;
            size++;
        }
    }
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    if(index==0)
        prepend(data);
    else if(index==size-1)
    {
        this->insertAfterNode(data, head->prev->prev);
    }
    else if(index>size-1 && index<0)
    	return;
    else
    {
        this->insertAfterNode(data, this->getNodeAtIndex(index)->prev);
    }
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    if(!containsNode(node))
        return -1;
    else
    {
        int index=0;
        Node<T> *current = head;
        while(current != node)
        {
            current = current->next;
            index++;
        }
        return index;
    }
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if(currentIndex==newIndex)
        return;
    else if(containsNode(getNodeAtIndex(currentIndex)))
    {
        if(currentIndex>size-1)
            return;
        else if(newIndex>=size-1)
        {
            Node<T> *indexed = getNodeAtIndex(currentIndex);
            indexed->prev->next = indexed->next; indexed->next->prev = indexed->prev;
            if(currentIndex==0)
                head=head->next;
            indexed->next = head; indexed->prev = head->prev;
            indexed->prev->next = indexed; head->prev = indexed;
        }
        else
        {
            Node<T> *given, *wanted;
            given = getNodeAtIndex(currentIndex);
            wanted = getNodeAtIndex(newIndex);
            given->prev->next = given->next; given->next->prev = given->prev;
            if(currentIndex>newIndex)
            {
                given->next = wanted; given->prev = wanted->prev;
                wanted->prev = given; given->prev->next = given;
                if(newIndex==0)
                    head = given;
            }
            else
            {
                if(currentIndex==0)
                    head=head->next;
                given->prev = wanted; given->next = wanted->next;
                wanted->next = given; given->next->prev = given;
            }
        }
    }
    return;
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if(!containsNode(node))
        return;
    else
    {
        Node<T> *old;
        if(node == head)
        {
            if(head->next!=head)
            {
                old = head;
                head->prev->next = head->next;
                head->next->prev = head->prev;
                head = head->next;
                delete old;
            }
            else
            {
                delete head;
                head = NULL;
            }
        }
        else if(node == head->prev)
        {
            old = head->prev;
            head->prev = old->prev;
            old->prev->next = head;
            delete old;
        }
        else
        {
            Node<T> *current = head;
            while(current != node)
            {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        size--;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    if(!getNode(data))
        return;
    else
    {
        int i, less=0;
        Node<T> *current = head;
        for(i=0 ; i<size ; i++)
        {
            if(current == this->getNode(data))
            {
                current = current->next;
                removeNode(current->prev);
                less++;
            }
            else
                current = current->next;
        }
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    Node<T> *node = getNodeAtIndex(index);
    if(!node && head==NULL)
        return;
    else
    {
        removeNode(node);
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    int i, sizes = size;
    for(i=0 ; i<sizes-1 ; i++)
    {
        removeNodeAtIndex(size-1);
    }
    delete head;
    head = NULL;
    size = 0;
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}


#endif //LINKEDLIST_H
