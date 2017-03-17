#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include "Node.hpp"

class Heap
{
    private:
        std::vector<Node> nodes; // internal heap array
        void makeHeap();
        void siftDown(int);
        void percolate(int);
        int getParent(int);
        int getLeft(int);
        int getRight(int);
        bool isLeaf(int);
    public:
        Heap(std::vector<Node>);
        Node extractMin();
        Node peek();
        void decKey(int, int); // decrease priority
        int size();
        std::string toString();

};


#endif
