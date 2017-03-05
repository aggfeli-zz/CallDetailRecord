/* 
 * File:   LinkedList.h
 * Author: angelique
 *
 * Created on February 28, 2017, 10:08 PM
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#define SIZE 52

using namespace std;

struct Bucket{
    char array[10][SIZE];
    int size;
    int full;
    Bucket *next;
    Bucket(int flag)
    {
        //cout << "bucket constructor" << endl;
        full = 0;
        size = SIZE;
        next = NULL;
        if (flag == 1)
            for(int i = 0; i < 10; i++) strcpy(array[i] , "-"); 
        //cout << "after init" << endl;
    };
    
};
    
class SimpleList{
public:
    SimpleList()
    {
        //head = new Bucket(0);
        head = NULL; // set head to NULL   
        length = 10;
    }

    ~SimpleList()
    {
        cout << "\n~SimpleList\n";
        Bucket * p = head;
        Bucket * q = head;
        while (q != NULL)
        {
            p = q;
            q = p -> next;
            if (q != NULL) delete p;
        }
    }
    
    // Add new value at the beginning of the list
    void addValue(char *val)
    {
        //cout <<  "1" << endl;
        if(head != NULL)
        {
            //cout <<  "2" << endl;
        Bucket *p = head->next;
        //cout <<  "2" << endl;
        while (p != NULL) //If list is empty insert here
        {
            //cout <<  "3" << endl;
            if(p->full == 0)
            {
                for(int i = 0; i < p->size; i++)
                {
                    //cout <<  "4" << endl;
                   if (strcmp(p->array[i], "-") == 0 ) //Bucket isn't full yet, add cdr in this node
                   {
                       strcpy(p->array[i] , val);
                       if(i == p->size - 1) p->full = 1;
                       return;
                   }           
                }   
            }
            //cout <<  "5" << endl;
            if(p->next != NULL) p = p->next;
            else break;
        }
        }
        else
        {
            head =  new Bucket(0);
        }
        /*We need to add a new node to store cdrs*/
        //cout <<  "6" << endl;
        Bucket *n2 = new Bucket(1); 
        //cout <<  "7" << endl;
        strcpy(n2->array[0] , val); 
        //cout <<  "8" << endl;
        if(head != NULL)
            n2->next = head->next; 
        //cout <<  "9" << endl;
        head->next = n2;     
        //cout <<  "10" << endl;
    }

    // returns the first element in the list and deletes the Node.
    int popValue(){
        Bucket *n = head;
        //int ret = n->array;

        head = head->next;
        delete n;
        //return ret;
    }
    
    void printList()      //Print whole bucket
    {
        if (length == 0)
        {
            cout << "\n[ ]\n";
            return;
        }
        Bucket * p = head->next;
        cout << "[ ";
        while (p)
        {       
            for(int i = 0; i < 10; i++)
               cout << p->array[i] << "\t";               
            if (p -> next) cout << ", ";
            else break;
            p = p->next;
        }
        cout << "]\n";
    };
    
    int getLength(){return length;};
private:
    Bucket * head; // this is the private member variable. It is just a pointer to the first Node
    int length;
};

struct Point
{
    char *number;
    //int flag;
    SimpleList *InfoList;
    Point * next;
    Point()
    {
        //cout << "point constructor" << endl;
        number = NULL;
        next = NULL; 
        InfoList = NULL;    
        
        //cout << "point constructor enddddd" << endl;
    };
    Point(char *id, char *info)
    {       
        //cout << "point 1" << endl;
        number = new char[strlen(id)];
        strcpy(number, id);
        //cout << "point 2    " <<  number << endl;
        next = NULL;  
        //cout << "point 3" << endl;
        InfoList = new SimpleList();
        //cout << InfoList->getLength() << endl;
        InfoList->addValue(info);
        //flag = -1;
    };    
};

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList& orig);
    virtual ~LinkedList();
    // Inserts an item at the end of the list.
    void insertPoint(char *id, char *info, int found);
    int SearchBucket(char *tmp);
    void printList();    
    // Returns the length of the list.
    int getLength();
private:
    Point * head;
    // Length is the number of data nodes.
    int length;
};

#endif	/* LINKEDLIST_H */

