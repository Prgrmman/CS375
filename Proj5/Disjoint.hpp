#ifndef DISJOINT_H
#define DISJOINT_H
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>

/****************************************************
 * ---class Disjoint---
 *
 * Description:
 *     This is an implementation of a disjoint data
 *     structure implemented as a backwards forest using
 *     improved height
 * Fields:
 *     bwForest <-- vector
 *     nodeMap  <-- map
 *     heights  <-- vector
 *     nodes    <-- vector
 *
 * Methods:
 * -> makeUnion:
 *      performs a union on two sets
 * -> merge:
 *      merges the sets of the items
 * -> find:
 *      finds the representative of an item's set
 * -> compress:
 *      return a copy of compressed backward forest
 * -> findroot:
 *      helper function for find
 * -> getGroups
 *      returns the names of the nodes in each set
 *
 ****************************************************/

class Disjoint
{
    private:
        std::vector<int> bwForest; // backwards forest of nodes
        std::map<std::string, int> nodeMap; // map of nodes to index
        std::vector<std::string> revMap; // used as reverse map
        std::vector<int> heights; // list of heights of each node
        int findRoot(int);
    public:
        Disjoint(std::list<std::string>); // Constructor
        void merge(std::string, std::string);
        void makeUnion(int, int);
        int find(std::string);
        std::string toString();
        std::vector<int> compress(); // return a copy of compressed backward forest
        std::vector<std::list<std::string>> getGroups();
};
#endif
