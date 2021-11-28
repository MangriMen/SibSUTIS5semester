#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> edge;
typedef pair<int, edge> weightedEdge;

class Graph
{
private:
    vector<int> connectedComponents;
    vector<weightedEdge> baseGraph;
    vector<weightedEdge> minimalSpanningTree;

    void PrintGraph(const vector<weightedEdge>& graph);
public:
    Graph();
    void AddWeightedEdge(int u, int v, int weight);
    void ConnectComponents(int u, int v);
    int FindConnectedComponent(int i);
    void ResetMST();
    void PrintBaseGraph();
    void PrintMST();
    void Kruskal();
};

void Graph::PrintGraph(const vector<weightedEdge>& graph) {
    cout << "Edge : Weight" << endl;
    for (const weightedEdge& edge_ : graph) {
        cout << edge_.second.first << " - " << edge_.second.second << " : " << edge_.first << endl;
    }
}

Graph::Graph()
{
    baseGraph.clear();
    minimalSpanningTree.clear();
    connectedComponents.clear();
}

void Graph::AddWeightedEdge(int u, int v, int weight)
{
    baseGraph.push_back(make_pair(weight, edge(u, v)));
    ResetMST();
}

void Graph::ConnectComponents(int u, int v)
{
    connectedComponents[u] = connectedComponents[v];
}

int Graph::FindConnectedComponent(int index)
{ 
    if (index == connectedComponents[index])
    {
        return index;
    }

    return FindConnectedComponent(connectedComponents[index]);
}

void Graph::ResetMST() {
    minimalSpanningTree.clear();
    connectedComponents.clear();
    connectedComponents.resize(baseGraph.size(), 0);
    for (size_t i = 0; i < baseGraph.size(); i++)
    {
        connectedComponents[i] = i;
    }
}

void Graph::PrintBaseGraph()
{
    PrintGraph(baseGraph);
}

void Graph::PrintMST()
{
    PrintGraph(minimalSpanningTree);
}

void Graph::Kruskal()
{
    // Sort by weight
    sort(baseGraph.begin(), baseGraph.end());
    
    for (size_t i = 0; i < baseGraph.size(); i++)
    {
        int uRep = FindConnectedComponent(baseGraph[i].second.first);
        int vRep = FindConnectedComponent(baseGraph[i].second.second);
        if (uRep != vRep)
        {
            minimalSpanningTree.push_back(baseGraph[i]);
            ConnectComponents(uRep, vRep);
        }
    }
}

int main()
{
    Graph graph;

    graph.AddWeightedEdge(1, 2, 20);
    graph.AddWeightedEdge(2, 3, 5);
    graph.AddWeightedEdge(3, 4, 3);
    graph.AddWeightedEdge(4, 5, 17);
    graph.AddWeightedEdge(5, 6, 28);
    graph.AddWeightedEdge(6, 1, 23);
    graph.AddWeightedEdge(1, 7, 1);
    graph.AddWeightedEdge(7, 2, 4);
    graph.AddWeightedEdge(7, 3, 9);
    graph.AddWeightedEdge(7, 4, 16);
    graph.AddWeightedEdge(7, 5, 25);
    graph.AddWeightedEdge(7, 6, 36);

    graph.Kruskal();
    graph.PrintMST();
    
    return 0;
}