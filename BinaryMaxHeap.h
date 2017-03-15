/* 
 * File:   BinaryMaxHeap.h
 * Author: angelique
 *
 * Created on March 1, 2017, 1:48 PM
 */

#ifndef BINARYMAXHEAP_H
#define	BINARYMAXHEAP_H
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

struct Node {
    Node *parent;
    //Node *left;
    //Node *right;
    Node *children[2];
    char* cdr;
    double cost;
    Node(char* temp, double money)
    {
        cdr = new char[strlen(temp)];
        strcpy(cdr, temp); cost = money;
    };
};

class BinaryMaxHeap {
public:
    BinaryMaxHeap();
    BinaryMaxHeap(const BinaryMaxHeap& orig);
    virtual ~BinaryMaxHeap();
    
    void levelOrder() ;
    //void MaxHeapify(int i );
 
    //int parent(int i) { return (i-1)/2; }
 
    // to get index of left child of node at index i
    //int left(int i) { return (2*i + 1); }
 
    // to get index of right child of node at index i
    //int right(int i) { return (2*i + 2); }
 
    // to extract the root which is the minimum element
    //int extractMax();
 
    // Decreases key value of key at index i to new_val
    //void decreaseKey(int i, int new_val);
 
    // Returns the maximum key (key at root) from max heap
    //int getMax() { return harr[0]; }
 
    // Deletes a key stored at index i
    //void deleteKey(int i);
 
    // Inserts a new key 'k'
    //void insertKey(int k);
    void MoveOneUp (Node *n);
    void Insert(char* temp, char tarrifarray[][3][4]);
    void Remove (Node *node);
    void ReplaceNode (Node *d, Node *s);
private:
    Node *root;
    Node *last;
    int heap_size; // Current number of elements in min heap
};

#endif	/* BINARYMAXHEAP_H */

