#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <list>
#include <set>
#include <algorithm>
#include "Disjoint.hpp"

#define THRESHOLD 60


using namespace std;

/*************************************
 * Object Definitions
 *************************************/
// an Edge of a graph
struct Edge
{
    string to;
    string from;
    int simlevel;
};

/*************************************
 * File reading
 *************************************/
// reads in edges from file
list<Edge> readEdges(string filename)
{
    fstream file;
    list<Edge> edges;
    file.open(filename);
    if (!file.is_open()){
        cerr << "File open error\n";
        exit(1);
    }
    string line, to, from;
    int simlevel;
    stringstream ss;
    while(getline(file, line)){
        ss.clear();
        ss.str(line);
        Edge edge;
        ss >> from >> to >> simlevel;
        edge.to = to;
        edge.from = from;
        edge.simlevel = simlevel;
        edges.push_back(edge);
    }
    file.close();
    return edges;
}
// reads the nodes from file
list<string> readNodes(string filename)
{
    fstream file;
    list<string> result;
    set<string> nodes;

    file.open(filename);
    if (!file.is_open()){
        cerr << "File open error\n";
        exit(1);
    }
    string line, to, from;
    stringstream ss;
    while(getline(file, line)){
        ss.clear();
        ss.str(line);
        ss >> from >> to;
        nodes.insert(to);
        nodes.insert(from);
    }
    file.close();
    for(string s : nodes)
        result.push_back(s);
    return result;
}
/*************************************
 * helper functions
 *************************************/
// returns if an edge is within the threshold
bool belowThresh(const Edge& edge)
{
    return edge.simlevel < THRESHOLD;
}

// removes edges outside of thesh
void pruneEdges(list<Edge>& edges)
{
    edges.remove_if(belowThresh);
}
// sorts edges from greatest to least
void sortEdges(list<Edge>& edges)
{
    edges.sort([](const Edge& a, const Edge& b){
            return a.simlevel > b.simlevel;
            });
}

/*************************************
 * core functions
 *************************************/
// Kruskal's implementation
void maxSpanningTree(Disjoint& nodes, list<Edge>& edges)
{
    pruneEdges(edges);
    sortEdges(edges);
    string to, from;
    int to_comp, from_comp; // graph componets
    for(Edge& edge : edges){
        to = edge.to;
        from = edge.from;
        to_comp = nodes.find(to);
        from_comp = nodes.find(from);
        if (to_comp != from_comp)
            nodes.makeUnion(to_comp, from_comp);
    }
}

/*************************************
 * Driver code
 *************************************/
int main(int agrc, char** argv)
{

    list<string> nodes = readNodes(argv[1]);
    list<Edge> edges = readEdges(argv[1]);
    Disjoint collection(nodes);

    maxSpanningTree(collection, edges);
    vector<list<string>> groups = collection.getGroups();
    cout << "There are " << groups.size() << " groups"<< endl;
    for(int i = 0; i < groups.size(); i++){
        cout << endl;
        cout << "Group " << i+1 << ":"<< endl;
        list<string> group = groups[i];
        cout << "size of group: " << group.size() << endl;
        for (string s: group){
            cout << s << " ";
        }
        cout << endl;
    }
    // we need to build disjoint sets
    return 0;
}
