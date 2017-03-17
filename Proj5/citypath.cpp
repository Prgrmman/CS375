#include <iostream>
#include <list>
#include <sstream>
#include <set>
#include <fstream>
#include <map>
#include <algorithm>
#include "Heap.hpp"
#include "Graph.hpp"

using namespace std;


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
    int distance;
    stringstream ss;
    while(getline(file, line)){
        ss.clear();
        ss.str(line);
        Edge edge;
        ss >> from >> to >> distance;
        edge.to = to;
        edge.from = from;
        edge.distance = distance;
        edges.push_back(edge);
    }
    file.close();
    return edges;
}
// reads the nodes from file
vector<string> readNodes(string filename)
{
    fstream file;
    vector<string> result;
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
/******************
 * Helper code
 * ***************/

Edge findEdge(string u, string v, list<Edge>& edges)
{
    Edge result = {"","",-1};
    for (Edge& edge : edges){
        if ((u == edge.to && v == edge.from) || (u == edge.from && v == edge.to)){
            result = edge;
            break;
        }
    }
    return result;
}

bool validEdge(Edge& e)
{
    return e.distance != -1;
}

vector<int> makePath(int s, int f, vector<int>& tree)
{
    vector<int> result;
    while(tree[s] != f){
        result.push_back(s);
        s = tree[s];
    }
    result.push_back(s);
    result.push_back(f);
    return result;
}

vector<string> stringPath(vector<int>& path, map<int, string>& nodemap)
{
    vector<string> result;
    for(int i : path)
        result.push_back(nodemap.at(i));
    return result;
}



/***********************
 * Main driver code
 * *********************/

int main(int argc, char ** argv)
{
    list<Edge> edges = readEdges(argv[1]);
    vector<string> nodes = readNodes(argv[1]);
    map<int,string> nodemap;
    vector<Node> nodeIds;
    vector<unsigned int> distances;
    vector<int> parentTree; // used to represent shortest path tree 

    for(int i = 0; i < nodes.size(); i++){
        Node n = {i, uint(-1) };
        nodemap.insert(make_pair(i,nodes[i]));
        parentTree.push_back(i);
        nodeIds.push_back(n);
        distances.push_back(uint(-1));
    }
    // init heap and graph
    Heap PQ(nodeIds);
    Graph graph(edges, nodes);

    // do Dijkstra's
    PQ.decKey(0,0); // set a as the source node
    distances[0] = 0;
    parentTree[0] = 0;
    string to, from;
    while(PQ.size() != 0){ // while PQ not empty
        Node near = PQ.extractMin();
        for(int v : graph.getAdj(near.name)){
            to = nodemap.at(near.name);
            from = nodemap.at(v);
            Edge edge = findEdge(to,from,edges); 
            if (validEdge(edge) && distances[v] > near.distance + edge.distance){
                distances[v] = near.distance + edge.distance;
                // For debug purposes:
                PQ.decKey(v, distances[v]);
                parentTree[v] = near.name;
            }
        }
    }
    // find path from d to i using a
    // frind path from d to a
    cout << "Finding the shortest path between d and i that goes through a" << endl;
    vector<int> path1 = makePath(3,0,parentTree); // path from d to a
    vector<int> path2 = makePath(8,0,parentTree); // path from i to a
    path2.pop_back();
    reverse(path2.begin(), path2.end());
    path1.insert(path1.end(), path2.begin(), path2.end());

    vector<string> path = stringPath(path1, nodemap);

    for(string s : path){
        cout << s << ", ";
    }
    cout << endl;
    int totalDistance = distances[3] + distances[8];
    cout << "Total distance for that path was " << totalDistance << endl;

}
