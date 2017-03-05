/* 
 * File:   Hashtable.cpp
 * Author: angelique
 * 
 * Created on February 28, 2017, 10:06 PM
 */

#include "Hashtable.h"
#include <math.h>


Hashtable::Hashtable(int TableSize, int BucketSize) //Hashtable Constructor
{   
    length = TableSize;   //Length is the size of the HashTable array. 
    array = new LinkedList[ length ];
}

Hashtable::Hashtable(const Hashtable& orig) {
}

Hashtable::~Hashtable() 
{
    cout << "\n~Hashtable\n";
    delete [] array;
}

int Hashtable::HashFunction(char *token)  
{
    int hash = 0;
    for(int i = strlen(token) -1; i >= 0; i--)
    {
        hash = (token[i] + 128 * hash) % length;
    }
    //cout << "!!!!!!!!! = "<< hash << endl;
    return hash;
}



void Hashtable::InsertIntoHashtable(char *temp, int flag)
{    
    char *token, *number;
    
    int size = strlen(temp) + 1 - 14;
    char rest_info[size];
    int j = 0;
    //cout << "wholeeee " << temp <<  endl;
    if (flag == 1) //Flag for caller
    {
        token = strtok(temp, ";");
        strcpy(rest_info, token);
        token = strtok(NULL, ";");
        number = new char[strlen(token)];
        strcpy(number, token);
        //cout << "caller = "<< cdr_id << endl; 
        strcat(rest_info, ";");
        token = strtok(NULL, "");
        strcat(rest_info, token);
        //cout << "rest_info = "<< rest_info << endl; 
    }
    else          //Flag == 2 for callee
    {
        token = strtok(temp, ";");
        strcpy(rest_info, token);
        strcat(rest_info, ";");
        token = strtok(NULL, ";");
        
        strcat(rest_info, token);
        token = strtok(NULL, ";");
        number = new char[strlen(token)];
        strcpy(number, token);
        //cout << "callee = "<< token << endl;
        strcat(rest_info, ";");
        token = strtok(NULL, "");
        //cout << "rest = "<< token << endl; 
        strcat(rest_info, token);
        
        //cout << "rest_info = "<< rest_info << endl; 
    }

    int index = HashFunction(token);
    
    //cout << "info = " << index << endl;
    int found = array[index].SearchBucket(number);
    array[index].insertPoint(number, rest_info, found);
    delete []number;
}


void Hashtable::printTable()
{
    //cout << length;
    cout << "\nHash Table:\n";   
    for (int i = 0; i < length; i++)
    {
        cout << "\nBucket " << i << ": ";
        array[i].printList();
    }
}

int Hashtable::getLength()
{
    return length;
}

