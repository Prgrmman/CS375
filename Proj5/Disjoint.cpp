#include "Disjoint.hpp"
#include <iostream>

using namespace std;

/*
 * Disjoint implementation
 */

// Constructor
Disjoint::Disjoint(list<string> nodes)
{
    // create node map
    int i = 0;
    for(string s: nodes){
        nodeMap.insert(make_pair(s,i));
        revMap.push_back(s);
        bwForest.push_back(i++);
        heights.push_back(0); // all heights are 0
    }
}
/*
 * returns the set representative the name belongs to
 * only use if you know the item is in the data set
 */
int Disjoint::find(string name)
{
    int rep = nodeMap.at(name);
    return findRoot(rep);
}
int Disjoint::findRoot(int rep)
{
    while(rep != bwForest[rep])
        rep = bwForest[rep];
    return rep;
}
/*
 * Makes union of the two sets
 * preserve min height
 * > set the smaller tree to the larger one
 */
void Disjoint::makeUnion(int rep1, int rep2)
{
    if(heights[rep1] == heights[rep2]){
        heights[rep1]++;
        bwForest[rep2] = rep1;
    }
    if(heights[rep1] > heights[rep2]){
        bwForest[rep2] = rep1;
    }
    else{
        bwForest[rep1] = rep2;
    }
}
/*
 * If the two nodes are in different sets, merge them
 */
void Disjoint::merge(string node1, string node2)
{
    int rep1 = find(node1);
    int rep2 = find(node2);
    if (rep1 != rep2){
        makeUnion(rep1, rep2);
    }
}
/*
 * reduce height of the tree
 */
vector<int> Disjoint::compress()
{
    vector<int> forest = bwForest; // copy our forest vector
    for(int i = 0; i < forest.size(); i++)
       forest[i] = findRoot(i);
    return forest;
}
/*
 * returns groups
 */
vector<list<string>> Disjoint::getGroups()
{
    vector<list<string>> result;
    vector<int> forest = compress();
    set<int> reps;
    for(int i : forest)
        reps.insert(i);

    for(int rep : reps){
        list<string> group;
        for(int i = 0; i < forest.size(); i++){
            if(forest[i] == rep){
               group.push_back(revMap[i]); 
            }
        }
        result.push_back(group);

    }
    return result;
    


}

/*
 * toString for debug only
 */
string Disjoint::toString()
{
    string result = "";
    for(int i : bwForest){
        result += to_string(i) + " ";
    }
    return result;
}


