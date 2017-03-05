/* 
 * File:   LinkedList.cpp
 * Author: angelique
 * 
 * Created on February 28, 2017, 10:08 PM
 */

#include "LinkedList.h"

LinkedList::LinkedList()            //Linked List Constructor
{
    head = new Point();
    head -> next = NULL;
    length = 0;
}

LinkedList::LinkedList(const LinkedList& orig) {
}
 

LinkedList::~LinkedList()       //Linked List Destructor
{
    cout << "\n~LinkedList\n";
    Point * p = head;
    Point * q = head;
    while (q != NULL)
    {
        p = q;
        q = p -> next;
        if (q != NULL)
        {
            delete p->InfoList;
            delete p;
        }
            
    }
}

int LinkedList::SearchBucket(char *tmp)
{
    Point *temp = head->next;
    //int found = 0;
    while(temp != NULL)
    {
        if (strcmp(temp->number, tmp) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }        
    return 0;
}


// Inserts an item at the head of the list.
void LinkedList::insertPoint(char *id, char *info, int found)
{
    //cout << "insert point 1" << endl;
    if(found != 1)  //If number doesn't exist
    {    
        Point *temp = new Point(id, info);
        if (!head -> next)              //If list is empty insert here
        {
            head -> next = temp;
            length++;
            return;
        }
        temp->next = head->next;
        head->next = temp;
        length++;
    }
    else    //Number exists so just add to second list the new info
    {
        Point *temp = head->next;
        while (temp != NULL)
        {
            if (strcmp(temp->number, id) == 0)
            {
                temp->InfoList->addValue(info);
                return;
            }
            temp = temp->next;
        }
    }
}

void LinkedList::printList()      //Print whole bucket
{

    if (length == 0)
    {
        cout << "\n{ }\n";
        return;
    }
    Point * p = head->next;
    cout << "\n{ ";
    while (p)
    {       
           cout << p->number << "\t";
           p->InfoList->printList();
        if (p -> next) cout << ", ";
        else break;
        p = p->next;
    }
    cout << "}\n";
}

// Returns the length of the list.
int LinkedList::getLength()
{
    return length;
}

