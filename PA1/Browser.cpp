#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    windows.prepend(Window());
}

void Browser::closeWindow() {
    if(windows.isEmpty())
        return;
    else
    {
        windows.removeNodeAtIndex(0);  
    }
}

void Browser::switchToWindow(int index) {
    windows.moveToIndex(index, 0);
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    Tab active = from.getActiveTab();
    to.newTab(active);
    from.closeTab();
}

void Browser::mergeWindows(Window &window1, Window &window2) {
    Tab active;
    window2.changeActiveTabTo(0);
    while(!window2.isEmpty())
    {
        active = window2.getActiveTab();
        window1.newTab(active);
        window2.closeTab();
    }
}

void Browser::mergeAllWindows() {
    int i, size = windows.getSize();
    Node<Window> *current, *head = windows.getFirstNode();
    current=head;
    for(i=1 ; i<size ; i++)
    {
        this->mergeWindows(head->data, current->next->data);
        current=current->next;
    }
}

void Browser::closeAllWindows() {
    windows.removeAllNodes();
}

void Browser::closeEmptyWindows() {
    int i, size = windows.getSize();
    Node<Window> *head = windows.getFirstNode(), *current;
    current=head;
    for(i=0 ; i<size ; i++)
    {
        if((current->data).isEmpty())
        {    
            current=current->next;
            windows.removeNode(current->prev);
        }
        else 
            current=current->next;
    }
    return;
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}
