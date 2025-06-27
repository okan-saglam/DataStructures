#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
    struct HeapElement sentinel;
    sentinel.uniqueId = 0; sentinel.weight = 0;
    elements.push_back(sentinel); // index 0 will be 0
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    bool flag = false;
    int i, size;
    size = elements.size();
    
    for(i = 0 ; i < size ; i++)
    {
        if(elements[i].uniqueId == uniqueId && uniqueId != 0)
            flag = true;
    }
    
    if(flag)
        return false;
    else
    {
        struct HeapElement temp, added;
        added.uniqueId = uniqueId; added.weight = weight;
        elements.push_back(added);
    
        temp = added;
        for(i = size ; i > 1 && elements[i].weight < elements[i/2].weight; i /= 2)
        {
            HeapElement swap = elements[i];
            elements[i] = elements[i/2];
            elements[i/2] = swap;
        }
        return true;
    }
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    if(elements.size() == 1)
        return false;
    else
    {
        int i, j, size;
        i = 1; j = 2*i;
        size = elements.size();
        outUniqueId = elements[1].uniqueId; outWeight = elements[1].weight;   
        elements[i] = elements[size-1];
        elements.pop_back();
        
        for(j ; j < size-1 ; j *= 2)
        {
            if(elements[j].weight > elements[j+1].weight)
                j++;
            if(elements[i].weight > elements[j].weight)
            {
                struct HeapElement temp = elements[i];
                elements[i] = elements[j];
                elements[j] = temp;
                i = j;
            }
            else
                break;
        }
        return true;
    }
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    bool flag = false;
    int i, j, size;
    size = elements.size();
    
    for(i = 1 ; i < size ; i++)
    {
        if(elements[i].uniqueId == uniqueId)
        {
            elements[i].weight = newWeight;
            flag = true;
            break;
        }
    }
    
    if(!flag)
        return false;
    else
    {
        if(2*i < size && (elements[i].weight > elements[2*i].weight || elements[i].weight > elements[2*i+1].weight))
        {
            if(elements[i].weight > elements[2*i].weight && elements[i].weight > elements[2*i+1].weight)
            {
                if(elements[2*i].weight > elements[2*i+1].weight)
                    j = 2*i+1;
                else
                    j = 2*i;
            }
            else if(elements[i].weight > elements[2*i].weight && elements[i].weight < elements[2*i+1].weight)
                j = 2*i;
            else if(elements[i].weight > elements[2*i+1].weight && elements[i].weight < elements[2*i].weight)
                j = 2*i+1;

            while(j < size && (elements[i].weight > elements[2*i].weight || elements[i].weight > elements[2*i+1].weight))
            {
                struct HeapElement temp = elements[i];
                elements[i] =  elements[j];
                elements[j] = temp;
                i = j;
                j *= 2;
            }
        }
        else if(elements[i].weight < elements[i/2].weight)
        {
            for(i ; i > 1 && elements[i].weight < elements[i/2].weight ; i /= 2)
            {
                struct HeapElement temp = elements[i];
                elements[i] =  elements[i/2];
                elements[i/2] = temp;
            }
        }
        return true;
    }
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return elements.size()-1;
}