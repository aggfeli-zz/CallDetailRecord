/* 
 * File:   Hashtable.h
 * Author: angelique
 *
 * Created on February 28, 2017, 10:06 PM
 */

#ifndef HASHTABLE_H
#define	HASHTABLE_H
#include "LinkedList.h"

class Hashtable {
public:
    Hashtable(int TableSize, int BucketSize);
    Hashtable(const Hashtable& orig);
    virtual ~Hashtable();
    
    // Adds an item to the Hash Table.
    void insertPoint( Point * newPoint );
       
    // Display the contents of the Hash Table to console window.
    void printTable();
  
    // Returns the number of locations in the Hash Table.
    int getLength();
    
    // Returns the number of Points in the Hash Table.
    int getNumberOfPoints();
    int HashFunction(char *token); 
    void InsertIntoHashtable(char *temp, int flag);
    void DeleteCDR(char *caller, char *cdrid);
    void FindCaller(char *arr[], int counter, int flag);
    void Indist(char *contacts[], int &counter, int finalresults[]);//char *caller1, char *caller2);
    void StoreContacts(char *caller, char *contacts[], int &counter, int flag);
    void TopDest(char *contacts[], int counter);
private:
    // Array is a reference to an array of Linked Lists.
    LinkedList * array;
    
    // Length is the size of the Hash Table array.
    int length, bucketsize;
    
};

#endif	/* HASHTABLE_H */

