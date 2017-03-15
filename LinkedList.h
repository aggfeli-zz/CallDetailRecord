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
        //cout << "\n~SimpleList\n";
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
        length += 20;
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
    int popValue(char *cdrid){
        char *token;
        Bucket *n = head->next;
        //int ret = n->array;
        while (n != NULL)
        {
            for (int i = 0; i < 10; i++)
            {
                //cout << "n->array[i] = " << n->array[i] << endl;
                token = strtok(n->array[i], ";");
                //cout << "token = " << token << endl;
                if (strcmp(token, cdrid) == 0)
                {
                    strcpy(n->array[i] , "-");
                    n->full = 0;
                    return 1;
                }
            }
            
        }
        //head = head->next;
        //delete n;
        return 0;
    }
    
    void findInfo(int counter, char *arr[])
    {
        char *token, *temp;      
        Bucket *n = head->next;
        while (n != NULL)
        {
            //cout << "1" << endl;
            for (int i = 0; i < 10; i++)
            {       
                //cout << "2" << endl;
                if (counter  == 0){ printList(); return;}
                else if (counter == 2)
                {
                    //cout << "3" << endl;
                    temp = new char[strlen(n->array[i])+1];
                    strcpy(temp, n->array[i]);
                    token = strtok(temp, ";");                    
                    token = strtok(NULL, ";");
                    //cout << "callee = " << token << endl;
                    token = strtok(NULL, ";");
                    delete temp;
                    //cout << "date = " << token << endl;
                    if(strlen(arr[1]) != strlen(token)){token = strtok(NULL, ";");}
                    //cout << "hour = " << token << endl;
                    if (strcmp(token,arr[1]) > 0 && strcmp(token,arr[2]) < 0)
                        cout << n->array[i] << endl;
                    
                }
                else
                {
                    //cout << "4" << endl;
                    temp = new char[strlen(n->array[i])+1];
                    //cout << "5" << endl;
                    strcpy(temp, n->array[i]);
                    //cout << "6" << endl;
                    char *token2;
                    token = strtok(temp, ";");
                    token = strtok(NULL, ";");
                    token = strtok(NULL, ";");
                    token2 = strtok(NULL, ";");
                    //cout << "7" << endl;
                    delete temp;
                    //cout << "8" << endl;
                    if (strcmp(token2,arr[1]) > 0 && strcmp(token2,arr[3]) < 0 && strcmp(token,arr[2]) > 0 && strcmp(token,arr[4]) < 0 )
                        cout << n->array[i] << endl;
                    
                }  
                //cout << "5" << endl;
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
        Bucket *n = head->next;
        while (n != NULL)
        {
            //cout << "11111111111111" << endl;
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
                    //cout << "1" << endl;
                    temp = new char[strlen(n->array[i]) + 1];
                    //cout << "2" << endl;
                    strcpy(temp, n->array[i]);
                    //cout << "3" << temp << endl;
                    token = strtok(temp, ";"); 
                    //cout << "4" << endl;
                    token = strtok(NULL, ";"); // This is callee
                    counter++;
                    arr[counter] = new char[strlen(token) + 1];
                
                    //cout << "6" << endl;
                    strcpy((arr[counter]), token);
                    //cout << "4" << endl;

                    delete temp;
                    //arr = (char**)realloc(*arr, (counter+1)*sizeof(char*));
                    //cout << "counter =   " <<  counter << endl;
                }
                
                
                //cout << "7  " <<  *(arr[counter]) << endl;
                if(strcmp(n->array[i + 1], "-") == 0) return;
                //cout << "8" << endl;
                
               // cout << "9" << endl;
            }
            if (n->next != NULL )n = n->next;
            else return;
            //cout << "10" << endl;
        }
        //cout << "11" << endl;
        return;
    }
    
    int checkCallee(int &counter, char *arr[])
    {
        char *token, *temp;      
        Bucket *n = head->next;
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
    
    void TopDest(char *caller, char *contacts[])
    {
        char *token, *temp;    
        
        /*Bucket *n = head->next;
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
        }*/
        return ;
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
    int SearchBucket(char *tmp, char *cdrid, int flag, char *arr[], int &counter);
    int Search(char *tmp, char *info, int flag, char ***arr, int &counter);
    void printList();    
    // Returns the length of the list.
    int getLength();
private:
    Point * head;
    // Length is the number of data nodes.
    int length;
};

#endif	/* LINKEDLIST_H */

