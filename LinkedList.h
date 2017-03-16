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

struct CDR{
    char array[10][SIZE];
    int size;
    int full;
    CDR *next;
    CDR(int flag)
    {
        full = 0;
        size = SIZE;
        next = NULL;
        if (flag == 1)
            for(int i = 0; i < 10; i++) strcpy(array[i] , "-"); 
    };
    
};
    
class SimpleList{
public:
    SimpleList()
    {
        head = NULL; // set head to NULL   
        length = 10;
    }

    ~SimpleList()
    {
        //cout << "\n~SimpleList\n";
        CDR * p = head;
        CDR * q = head;
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
        if(head != NULL)
        {
        CDR *p = head->next;
        while (p != NULL) //If list is empty insert here
        {
            if(p->full == 0)
            {
                for(int i = 0; i < p->size; i++)
                {
                   if (strcmp(p->array[i], "-") == 0 ) //Bucket isn't full yet, add cdr in this node
                   {
                       strcpy(p->array[i] , val);
                       if(i == p->size - 1) p->full = 1;
                       return;
                   }           
                }   
            }
            if(p->next != NULL) p = p->next;
            else break;
        }
        }
        else
        {
            head =  new CDR(0);
        }
        /*We need to add a new node to store cdrs*/
        length += 20;
        CDR *n2 = new CDR(1); 
        strcpy(n2->array[0] , val); 
        if(head != NULL)
            n2->next = head->next; 
        head->next = n2;     
    }

    // returns the first element in the list and deletes the Node.
    int popValue(char *cdrid){
        char *token;
        CDR *n = head->next;
        while (n != NULL)
        {
            for (int i = 0; i < 10; i++)
            {
                token = strtok(n->array[i], ";");
                if (strcmp(token, cdrid) == 0)
                {
                    strcpy(n->array[i] , "-");
                    n->full = 0;
                    return 1;
                }
            }            
        }
        return 0;
    }
    
    void findInfo(int counter, char *arr[])
    {
        char *token, *temp;      
        CDR *n = head->next;
        while (n != NULL)
        {
            for (int i = 0; i < 10; i++)
            {       
                if (counter  == 0){ printList(); return;}
                else if (counter == 2)
                {
                    temp = new char[strlen(n->array[i])+1];
                    strcpy(temp, n->array[i]);
                    token = strtok(temp, ";");                    
                    token = strtok(NULL, ";");
                    token = strtok(NULL, ";"); //date
                    delete temp;
                    //cout << "date = " << token << endl;
                    if(strlen(arr[1]) != strlen(token)){token = strtok(NULL, ";");} //hour
                    //cout << "hour = " << token << endl;
                    if (strcmp(token,arr[1]) > 0 && strcmp(token,arr[2]) < 0)
                        cout << n->array[i] << endl;
                    
                }
                else
                {
                    temp = new char[strlen(n->array[i])+1];
                    strcpy(temp, n->array[i]);
                    char *token2;
                    token = strtok(temp, ";");
                    token = strtok(NULL, ";");
                    token = strtok(NULL, ";");
                    token2 = strtok(NULL, ";");
                    delete temp;
                    if (strcmp(token2,arr[1]) > 0 && strcmp(token2,arr[3]) < 0 && strcmp(token,arr[2]) > 0 && strcmp(token,arr[4]) < 0 )
                        cout << n->array[i] << endl;
                    
                }  
                if(strcmp(n->array[i + 1], "-") == 0) return;
            }
            if (n->next != NULL )n = n->next;
            else return;
        }
        return;
    }
    
    void storeCallee(int &counter, char *arr[], int flag)
    {
        char *token, *temp;      
        CDR *n = head->next;
        while (n != NULL)
        {
            for (int i = 0; i < 10; i++)
            {       
                if (flag == 2 )
                {
                    counter++;
                    arr[counter] = new char[strlen(n->array[i]) + 1];
                    strcpy((arr[counter]), n->array[i]);
                }
                else
                {
                    temp = new char[strlen(n->array[i]) + 1];
                    strcpy(temp, n->array[i]);
                    token = strtok(temp, ";"); 
                    token = strtok(NULL, ";"); // This is callee
                    counter++;
                    arr[counter] = new char[strlen(token) + 1];
                    strcpy((arr[counter]), token);
                    delete temp;
                }

                if(strcmp(n->array[i + 1], "-") == 0) return;

            }
            if (n->next != NULL )n = n->next;
            else return;

        }

        return;
    }
    
    int checkCallee(int &counter, char *arr[])
    {
        char *token, *temp;      
        CDR *n = head->next;
        while (n != NULL)
        {            
            for (int i = 0; i < 10; i++)
            {       
                temp = new char[strlen(n->array[i])+1];
                strcpy(temp, n->array[i]);
                token = strtok(temp, ";"); 
                token = strtok(NULL, ";"); // This is callee
                delete temp;
                //counter++;
                for(int j = 0; j < counter; j++)
                {
                    //cout << token << "      " << arr[j] << endl;
                    if(strcmp(token, arr[j])== 0){ return 1;}
                }
                if(strcmp(n->array[i + 1], "-") == 0) return 0;
            }
            if (n->next != NULL )n = n->next;
            else return 0;
        }
        return 0;
    }

    void printList()      //Print whole cdr info
    {
        if (length == 0)
        {
            cout << "\n[ ]\n";
            return;
        }
        CDR * p = head->next;
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
    CDR * head; // this is the private member variable. It is just a pointer to the first Node
    int length;
};

struct Bucket
{
    char *number;
    SimpleList *InfoList;
    Bucket * next;
    Bucket()
    {
        number = NULL;
        next = NULL; 
        InfoList = NULL;    
    };
    Bucket(char *id, char *info)
    {       
        number = new char[strlen(id)];
        strcpy(number, id);
        next = NULL;  
        InfoList = new SimpleList();
        InfoList->addValue(info);
    };    
};

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList& orig);
    virtual ~LinkedList();
    // Inserts an item at the end of the list.
    void insertPoint(char *id, char *info, int found);
    int SearchBucket(char *tmp, char *cdrid, int flag, char *arr[], int &counter);
    int Search(char *tmp, char *info, int flag, char ***arr, int &counter);
    void printList();    
    // Returns the length of the list.
    int getLength();
private:
    Bucket * head;
    // Length is the number of data nodes.
    int length;
};

#endif	/* LINKEDLIST_H */

