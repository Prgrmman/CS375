#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
#include <string>
#include "Node.hpp"
#include <map>

struct Edge
{
    std::string to;
    std::string from;
    int distance;
};

struct G_node
{
    int name;
    std::vector<int> adj;

};

class Graph
{
    private:
        std::vector<G_node> nodes;
    public:
        Graph(std::list<Edge>, std::vector<std::string>);
        std::vector<int> getAdj(int);
        std::string toString();
};


#endif
