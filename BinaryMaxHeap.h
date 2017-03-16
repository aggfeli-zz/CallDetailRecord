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

