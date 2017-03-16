/* 
 * File:   LinkedList.cpp
 * Author: angelique
 * 
 * Created on February 28, 2017, 10:08 PM
 */

#include "LinkedList.h"

LinkedList::LinkedList()            //Linked List Constructor
{
    head = new Bucket();
    head -> next = NULL;
    length = 0;
}

LinkedList::LinkedList(const LinkedList& orig) {
}
 

LinkedList::~LinkedList()       //Linked List Destructor
{
    //cout << "\n~LinkedList\n";
    Bucket * p = head;
    Bucket * q = head;
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

int LinkedList::SearchBucket(char *tmp, char *info, int flag, char **arr, int &counter)
{
    Bucket *temp = head->next;
    while(temp != NULL)
    {
        if (strcmp(temp->number, tmp) == 0)
        {
            if (flag == 1)          //Second case: syntax:delete caller cdr-id
            {
                temp->InfoList->popValue(info);
                return 1;
            }
            else if (flag == 2)     //Third/Fourth case: syntax: find/lookup caller [time1][year1] [time2][year2]
            {
                temp->InfoList->findInfo(counter, arr);
                return 1;
            }
            else if (flag == 3)     //Store in array only callee number info that exist in second list
            {
                temp->InfoList->storeCallee(counter, arr, 1);
                return 1;
            }
            else if (flag == 4)   //Fifth case: syntax: indist caller1 caller2/check which callee hasn't any contact with the rest in array 
            {
                return temp->InfoList->checkCallee(counter, arr);               
            }
            else if(flag == 5)  //Store in array all cdr info that exist in second list
            {             
                temp->InfoList->storeCallee(counter, arr, 2);
                
            }
            else return 1;
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
        Bucket *temp = new Bucket(id, info);
        if (!head -> next)              //If list is empty insert here
        {
            head -> next = temp;
            length++;
            return;
        }
        temp->next = head->next;
        head->next = temp;
        length++;
        return;
    }
    else    //Number exists so just add to second list the new info
    {
        Bucket *temp = head->next;
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
    cout << "IError" << endl;
}

void LinkedList::printList()      //Print whole bucket
{

    if (length == 0)
    {
        cout << "\n{ }\n";
        return;
    }
    Bucket * p = head->next;
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

