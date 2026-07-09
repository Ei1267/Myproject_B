#include "Graph.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>

Graph::Graph(int maxCount, bool directed) {
    maxVertexCount = maxCount;
    vertexCount = 0;
    isDirected = directed;

    matrix = new int*[maxVertexCount];
    for (int i = 0; i < maxVertexCount; i++) {
        matrix[i] = new int[maxVertexCount];
        for (int j = 0; j < maxVertexCount; j++) {
            matrix[i][j] = 0;
        }
    }

    vertexNames = new std::string[maxVertexCount];
}

Graph::~Graph() {
    for (int i = 0; i < maxVertexCount; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] vertexNames;
}

int Graph::addVertex(const std::string& name) {
    if (vertexCount >= maxVertexCount) {
        return -1;
    }

    for (int i = 0; i < vertexCount; i++) {
        if (vertexNames[i] == name) {
            return -1;
        }
    }

    vertexNames[vertexCount] = name;
    return vertexCount++;
}

bool Graph::removeVertex(int index) {
    if (index < 0 || index >= vertexCount) {
        return false;
    }

    for (int i = index; i < vertexCount - 1; i++) {
        vertexNames[i] = vertexNames[i + 1];
    }

    for (int i = index; i < vertexCount - 1; i++) {
        for (int j = 0; j < vertexCount; j++) {
            matrix[i][j] = matrix[i + 1][j];
        }
    }

    for (int i = 0; i < vertexCount; i++) {
        for (int j = index; j < vertexCount - 1; j++) {
            matrix[i][j] = matrix[i][j + 1];
        }
    }

    for (int i = 0; i < vertexCount; i++) {
        matrix[i][vertexCount - 1] = 0;
    }
    for (int j = 0; j < vertexCount; j++) {
        matrix[vertexCount - 1][j] = 0;
    }

    vertexCount--;
    return true;
}

bool Graph::addEdge(int from, int to, int weight) {
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
        return false;
    }

    matrix[from][to] = weight;
    if (!isDirected) {
        matrix[to][from] = weight;
    }

    return true;
}

bool Graph::removeEdge(int from, int to) {
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
        return false;
    }

    matrix[from][to] = 0;
    if (!isDirected) {
        matrix[to][from] = 0;
    }

    return true;
}

int Graph::getEdgeWeight(int from, int to) {
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
        return 0;
    }
    return matrix[from][to];
}

bool Graph::hasEdge(int from, int to) {
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
        return false;
    }
    return matrix[from][to] != 0;
}

std::string Graph::getVertexName(int index) {
    if (index < 0 || index >= vertexCount) {
        return "";
    }
    return vertexNames[index];
}

int Graph::getVertexIndex(const std::string& name) {
    for (int i = 0; i < vertexCount; i++) {
        if (vertexNames[i] == name) {
            return i;
        }
    }
    return -1;
}

int Graph::getVertexCount() {
    return vertexCount;
}

int Graph::getMaxVertexCount() {
    return maxVertexCount;
}

bool Graph::isDirectedGraph() {
    return isDirected;
}

void Graph::printMatrix() {
    std::cout << "\t";
    for (int i = 0; i < vertexCount; i++) {
        std::cout << vertexNames[i] << "\t";
    }
    std::cout << std::endl;

    for (int i = 0; i < vertexCount; i++) {
        std::cout << vertexNames[i] << "\t";
        for (int j = 0; j < vertexCount; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void Graph::dfsHelper(int v, std::vector<bool>& visited, std::vector<int>& result) {
    visited[v] = true;
    result.push_back(v);

    for (int i = 0; i < vertexCount; i++) {
        if (matrix[v][i] != 0 && !visited[i]) {
            dfsHelper(i, visited, result);
        }
    }
}

void Graph::dfs(int start, std::vector<int>& result) {
    result.clear();
    if (start < 0 || start >= vertexCount) {
        return;
    }

    std::vector<bool> visited(vertexCount, false);
    dfsHelper(start, visited, result);
}

void Graph::bfs(int start, std::vector<int>& result) {
    result.clear();
    if (start < 0 || start >= vertexCount) {
        return;
    }

    std::vector<bool> visited(vertexCount, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        result.push_back(v);

        for (int i = 0; i < vertexCount; i++) {
            if (matrix[v][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

bool Graph::dijkstra(int start, int end, std::vector<int>& path, int& distance) {
    path.clear();
    distance = 0;

    if (start < 0 || start >= vertexCount || end < 0 || end >= vertexCount) {
        return false;
    }

    if (start == end) {
        path.push_back(start);
        return true;
    }

    std::vector<int> dist(vertexCount, INF);
    std::vector<int> prev(vertexCount, -1);
    std::vector<bool> visited(vertexCount, false);

    dist[start] = 0;

    for (int i = 0; i < vertexCount; i++) {
        int u = -1;
        int minDist = INF;

        for (int j = 0; j < vertexCount; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1 || u == end) {
            break;
        }

        visited[u] = true;

        for (int v = 0; v < vertexCount; v++) {
            if (matrix[u][v] != 0 && !visited[v] && dist[v] > dist[u] + matrix[u][v]) {
                dist[v] = dist[u] + matrix[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[end] == INF) {
        return false;
    }

    distance = dist[end];

    int curr = end;
    while (curr != -1) {
        path.push_back(curr);
        curr = prev[curr];
    }

    std::reverse(path.begin(), path.end());
    return true;
}

bool Graph::hasCycleHelper(int v, std::vector<bool>& visited, std::vector<bool>& recStack) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        for (int i = 0; i < vertexCount; i++) {
            if (matrix[v][i] != 0) {
                if (!visited[i] && hasCycleHelper(i, visited, recStack)) {
                    return true;
                } else if (recStack[i]) {
                    return true;
                }
            }
        }
    }

    recStack[v] = false;
    return false;
}

bool Graph::hasCycleUndirected(int v, std::vector<bool>& visited, int parent) {
    visited[v] = true;

    for (int i = 0; i < vertexCount; i++) {
        if (matrix[v][i] != 0) {
            if (!visited[i]) {
                if (hasCycleUndirected(i, visited, v)) {
                    return true;
                }
            } else if (i != parent) {
                return true;
            }
        }
    }

    return false;
}

bool Graph::hasCycle() {
    std::vector<bool> visited(vertexCount, false);

    if (isDirected) {
        std::vector<bool> recStack(vertexCount, false);
        for (int i = 0; i < vertexCount; i++) {
            if (hasCycleHelper(i, visited, recStack)) {
                return true;
            }
        }
    } else {
        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i]) {
                if (hasCycleUndirected(i, visited, -1)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    bool directed = false;

    for (const std::string& l : lines) {
        if (l.empty() || l[0] == '#') {
            continue;
        }

        if (l.find("directed:") != std::string::npos) {
            std::istringstream iss(l);
            std::string key;
            std::string value;
            iss >> key >> value;
            directed = (value == "true");
        }
    }

    for (int i = 0; i < maxVertexCount; i++) {
        for (int j = 0; j < maxVertexCount; j++) {
            matrix[i][j] = 0;
        }
    }
    vertexCount = 0;
    isDirected = directed;

    for (const std::string& l : lines) {
        if (l.empty() || l[0] == '#') {
            continue;
        }

        if (l.find("vertex_count:") != std::string::npos || l.find("directed:") != std::string::npos) {
            continue;
        }

        std::istringstream iss(l);
        std::string fromName, toName;
        int weight = 1;

        iss >> fromName >> toName;
        iss >> weight;

        int fromIndex = getVertexIndex(fromName);
        if (fromIndex == -1) {
            fromIndex = addVertex(fromName);
        }

        int toIndex = getVertexIndex(toName);
        if (toIndex == -1) {
            toIndex = addVertex(toName);
        }

        addEdge(fromIndex, toIndex, weight);
    }

    return true;
}
