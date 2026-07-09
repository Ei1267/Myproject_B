#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

const int INF = 99999;

class Graph {
public:
    Graph(int maxCount, bool directed = false);
    ~Graph();
    
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    int addVertex(const std::string& name);
    bool removeVertex(int index);
    bool addEdge(int from, int to, int weight = 1);
    bool removeEdge(int from, int to);
    int getEdgeWeight(int from, int to);
    bool hasEdge(int from, int to);

    std::string getVertexName(int index);
    int getVertexIndex(const std::string& name);
    int getVertexCount();
    int getMaxVertexCount();
    bool isDirectedGraph();

    void printMatrix();

    void dfs(int start, std::vector<int>& result);
    void bfs(int start, std::vector<int>& result);
    bool dijkstra(int start, int end, std::vector<int>& path, int& distance);
    bool hasCycle();

    bool loadFromFile(const std::string& filename);

private:
    int** matrix;
    int vertexCount;
    int maxVertexCount;
    bool isDirected;
    std::string* vertexNames;

    void dfsHelper(int v, std::vector<bool>& visited, std::vector<int>& result);
    bool hasCycleHelper(int v, std::vector<bool>& visited, std::vector<bool>& recStack);
    bool hasCycleUndirected(int v, std::vector<bool>& visited, int parent);
};

#endif
