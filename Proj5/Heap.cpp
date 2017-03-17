#include <iostream>
#include <string>
#include "Heap.hpp"

using namespace std;


/*
 * Heap implementation
 */

/*
 * --Constructor--
 *  takes a vector of nodes and creates a heap
 */
Heap::Heap(vector<Node> nodes)
{
    this->nodes  = nodes; // copy
    makeHeap();

}
void Heap::makeHeap()
{
    if(size() < 2) // It's already a heap
        return;
    for (int i = (size()-2)/2; i >= 0; i--){
        siftDown(i);
    }
}
// sift down

void Heap::siftDown(int i)
{
    while(!isLeaf(i)){
        int min = getLeft(i);
        if(min + 1 < size() && nodes[min].distance > nodes[min+1].distance)
            min = min +1;
        if(nodes[i].distance <= nodes[min].distance)
            return;
        swap(nodes[i], nodes[min]);
        i = min;
    }

}
Node Heap::extractMin()
{
    Node min = nodes[0];
    swap(nodes[0], nodes[size()-1]);
    nodes.pop_back();
    siftDown(0);
    return min;
}

Node Heap::peek()
{
    return nodes[0];
}
// find the key, reset its value and perclate
void Heap::decKey(int id, int key)
{
    int loc = -1;
    for(int i = 0; i < size(); i++){
        if(nodes[i].name == id){
            loc = i;
            break;
        }
    }
    if (loc == -1)
        return;
    nodes[loc].distance = key;
    percolate(loc); 

}

void Heap::percolate(int i)
{
    int parent = getParent(i);
    while(i > 0 && nodes[i].distance < nodes[parent].distance){
        swap(nodes[i], nodes[parent]);
        i = parent;
        parent = getParent(i);

    }
}
// returns size of heap
int Heap::size()
{
    return nodes.size();
}


// returns left child of index
int Heap::getLeft(int i)
{
    return 2 * i; 
}
// returns right child of index
int Heap::getRight(int i){
    return getLeft(i)+1;
}

// returns the parent of index
int Heap::getParent(int i)
{
    return i / 2;
}

// returns true if index is a leaf
bool Heap::isLeaf(int i)
{
    return 2*i + 1 > size() -1;
}


string Heap::toString()
{
    string result = "";
    for (Node n : nodes)
        result += (to_string(n.name) + " ") + (to_string(n.distance) + " ");
    return result;
}



