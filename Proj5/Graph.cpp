#include "Graph.hpp"

/*
 * Implementation of Graph class
 */
using namespace std;
// Constructor
Graph::Graph(list<Edge> edges, vector<string> nodes)
{
    map<string, int> nodemap; // make node map and init empty graph nodes
    for(int i = 0; i < nodes.size(); i++){
        nodemap.insert(make_pair(nodes[i],i));
        G_node gnode = {i,{}};
        this->nodes.push_back(gnode);
    }
    for(Edge& edge : edges){
        int to = nodemap.at(edge.to);
        int from = nodemap.at(edge.from);
        this->nodes[to].adj.push_back(from);
        this->nodes[from].adj.push_back(to);
    }
    
    
}

vector<int> Graph::getAdj(int node)
{
    return nodes[node].adj;
}

string Graph::toString()
{
    string result = "";
    for (G_node& g : nodes){
        result += "\nNode :" + to_string(g.name) + "\n"
            + "adjacent to: ";
        for(int i: g.adj){
            result += to_string(i) + " ";
        }
    }
    return result;
}
