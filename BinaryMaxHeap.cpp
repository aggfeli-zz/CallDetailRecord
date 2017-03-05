/* 
 * File:   BinaryMaxHeap.cpp
 * Author: angelique
 * 
 * Created on March 1, 2017, 1:48 PM
 */

#include "BinaryMaxHeap.h"
#define INT_MAX 1000

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


BinaryMaxHeap::BinaryMaxHeap() 
{
    heap_size = 0;
    root = NULL;
    last = NULL;
}

BinaryMaxHeap::BinaryMaxHeap(const BinaryMaxHeap& orig) {
}

BinaryMaxHeap::~BinaryMaxHeap() 
{
    cout << "\n~BinaryMaxHeap\n";
    
}

void BinaryMaxHeap::MoveOneUp (Node *n)
{   
    Node *p = n->parent;
    
    if (p->parent) {
        p->parent->children[p == p->parent->children[1]] = n;
    } else {
        root = n;
    }
    n->parent = p->parent;
    
    int nside = (n == p->children[1]);
    Node *c = p->children[!nside];
    
    p->children[0] = n->children[0];
    if (p->children[0]) {
        p->children[0]->parent = p;
    }
    
    p->children[1] = n->children[1];
    if (p->children[1]) {
        p->children[1]->parent = p;
    }
    
    n->children[nside] = p;
    p->parent = n;
    
    n->children[!nside] = c;
    if (c) {
        c->parent = n;
    }
    
    if (n == last) {
        last = p;
    }
}


void BinaryMaxHeap::Insert(char* temp, int money)
{
    Node *node = new Node(temp, money);
    // If the heap is empty, insert root node.
    if (root == NULL) {
        root = node;
        last = node;
        node->parent = NULL;
        node->children[0] = NULL;
        node->children[1] = NULL;
        return;
    }

    // We will be finding the node to insert below.

    // Start with the current last node and move up as long as the
    // parent exists and the current node is its right child.
    Node *cur = last;
    while (cur->parent != NULL && cur == cur->parent->children[1]) 
    {
        cur = cur->parent;
    }

    if (cur->parent != NULL) 
    {
        if (cur->parent->children[1] != NULL) 
        {
            // The parent has a right child. Attach the new node to
            // the leftmost node of the parent's right subtree.
            cur = cur->parent->children[1];
            while (cur->children[0] != NULL) 
            {
                cur = cur->children[0];
            }
        } 
        else 
        {
            // The parent has no right child. This can only happen when
            // the last node is a right child. The new node can become
            // the right child.
            cur = cur->parent;
        }
    } 
    else 
    {
        // We have reached the root. The new node will be at a new level,
        // the left child of the current leftmost node.
        while (cur->children[0] != NULL) 
        {
            cur = cur->children[0];
        }
    }

    // This is the node below which we will insert. It has either no
    // children or only a left child.
    //assert(cur->link[1] == NULL);

    // Insert the new node, which becomes the new last node.
    last = node;
    cur->children[cur->children[0] != NULL] = node;
    node->parent = cur;
    node->children[0] = NULL;
    node->children[1] = NULL;

    // Restore the heap property.
    while (node->parent != NULL && node->parent->cost > node->cost) 
    {
        MoveOneUp(node);
    }
}

void BinaryMaxHeap::ReplaceNode (Node *d, Node *s)
{
    if (d->parent) {
        d->parent->children[d == d->parent->children[1]] = s;
    } else {
        root = s;
    }
    s->parent = d->parent;
    
    s->children[0] = d->children[0];
    if (s->children[0]) {
        s->children[0]->parent = s;
    }
    
    s->children[1] = d->children[1];
    if (s->children[1]) {
        s->children[1]->parent = s;
    }
}


void BinaryMaxHeap::Remove (Node *node)
{
    // If this is the only node left, remove it.
    if (node->parent == NULL && node->children[0] == NULL && node->children[1] == NULL) {
        root = NULL;
        last = NULL;
        return;
    }

    // Locate the node before the last node.
    Node *cur = last;
    while (cur->parent != NULL && cur == cur->parent->children[0]) {
        cur = cur->parent;
    }
    if (cur->parent != NULL) {
        //assert(cur->parent->link[0] != NULL);
        cur = cur->parent->children[0];
    }
    while (cur->children[1] != NULL) {
        cur = cur->children[1];
    }

    // Disconnect the last node.
    //assert(h->last->parent != NULL);
    last->parent->children[last == last->parent->children[1]] = NULL;

    if (node == last) {
        // Deleting last, set new last.
        last = cur;
    } else {
        // Not deleting last, move last to node's place.
        Node *srcnode = last;
        ReplaceNode( node, srcnode);
        // Set new last unless node=cur; in this case it stays the same.
        if (node != cur) {
            last = cur;
        }

        // Restore the heap property.
        if (srcnode->parent != NULL && srcnode->cost < srcnode->parent->cost) {
            do {
                MoveOneUp(srcnode);
            } while (srcnode->parent != NULL && srcnode->cost < srcnode->parent->cost);
        } else {
            while (srcnode->children[0] != NULL || srcnode->children[1] != NULL) {
                bool side = srcnode->children[1] != NULL && srcnode->children[0]->cost >= srcnode->children[1]->cost;
                if (srcnode->cost > srcnode->children[side]->cost) {
                    MoveOneUp(srcnode->children[side]);
                } else {
                    break;
                }
            }
        }
    }
}


/*void BinaryMaxHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] < harr[i])
    {
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}

int BinaryMaxHeap:: extractMax()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
 
    // Store the maximum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MaxHeapify(0);
 
    return root;
}

	
void BinaryMaxHeap:: deleteKey(int i)
{
    decreaseKey(i, INT_MAX);
    extractMax();
}
	
void BinaryMaxHeap:: MaxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MaxHeapify(smallest);
    }
}
	
/*void BinaryMaxHeap::postorder(tree_node* p, int indent = 0)
{
    if(p != NULL) {
        if(p->left) postorder(p->left, indent+4);
        if(p->right) postorder(p->right, indent+4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        cout<< p->data << "\n ";
    }
}*/
		


