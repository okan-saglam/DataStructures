#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    if(tabs.isEmpty())
        return Tab();
    /*{
        Node<Tab> *head = tabs.getFirstNode();
        Tab *newtab = new Tab();
        tabs.prepend(*newtab);
        return head->data;
    }*/
    else
        return (tabs.getNodeAtIndex(activeTab))->data;
}

bool Window::isEmpty() const {
    if(tabs.isEmpty())
        return true;
    else
        return false;
}

void Window::newTab(const Tab &tab) {
    Node<Tab> *head = tabs.getFirstNode();
    Node<Tab> data_tab = Node<Tab>(tab);
    if(head == NULL)
    {
        addTab(data_tab);
    }
    else
    {
        Node<Tab> *active = tabs.getNodeAtIndex(activeTab);
        tabs.insertAfterNode(tab, active);
        activeTab++;
    }
}

void Window::closeTab() {
    if(tabs.isEmpty())
        return;
    Node<Tab> *active = tabs.getNodeAtIndex(activeTab);
    if(active == tabs.getLastNode() && activeTab>0)
    {
        tabs.removeNodeAtIndex(activeTab);
        activeTab--;
    }   
    else
    {   
        tabs.removeNodeAtIndex(activeTab);
        if(this->isEmpty())
            activeTab = -1;
    } 
}

void Window::moveActiveTabTo(int index) {
    int size = tabs.getSize();
    tabs.moveToIndex(activeTab, index);
    if(index>size-1)
        activeTab = size-1;
    else
        activeTab = index;
}

void Window::changeActiveTabTo(int index) {
    int size = tabs.getSize();
    if(index>=size || index<0)
        return;
    else
        activeTab = index;
}

void Window::addTab(Node<Tab> &tab) {
    static int count = 0;
    int size = tabs.getSize();
    Node<Tab> *head = tabs.getFirstNode();
    if(size==1 && !count && head!=NULL)
    {
        head->data = tab.data;
    }
    else
    {
        if(isEmpty())
            activeTab++;
        tabs.append(tab.data);
    }
    count++;
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
