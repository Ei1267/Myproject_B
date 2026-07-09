#include "../include/Graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

std::string getDataPath() {
    std::filesystem::path testPath(__FILE__);
    return testPath.parent_path().parent_path().append("data").string();
}

void printTestResult(const std::string& testName, bool passed) {
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << testName << std::endl;
}

bool testAddVertex() {
    Graph g(5);
    
    int idx0 = g.addVertex("A");
    int idx1 = g.addVertex("B");
    int idx2 = g.addVertex("C");
    
    bool result = (idx0 == 0) && (idx1 == 1) && (idx2 == 2);
    result &= g.getVertexCount() == 3;
    
    int duplicate = g.addVertex("A");
    result &= duplicate == -1;
    
    return result;
}

bool testRemoveVertex() {
    Graph g(5);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 5);
    
    bool result = g.removeVertex(1);
    result &= g.getVertexCount() == 2;
    result &= g.getVertexName(0) == "A";
    result &= g.getVertexName(1) == "C";
    
    bool invalid = g.removeVertex(-1);
    result &= !invalid;
    
    return result;
}

bool testAddEdgeDirected() {
    Graph g(5, true);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 5);
    
    bool result = g.hasEdge(0, 1);
    result &= g.hasEdge(1, 2);
    result &= !g.hasEdge(1, 0);
    result &= !g.hasEdge(2, 1);
    result &= g.getEdgeWeight(0, 1) == 10;
    
    return result;
}

bool testAddEdgeUndirected() {
    Graph g(5, false);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    
    g.addEdge(0, 1, 10);
    
    bool result = g.hasEdge(0, 1);
    result &= g.hasEdge(1, 0);
    result &= g.getEdgeWeight(0, 1) == 10;
    result &= g.getEdgeWeight(1, 0) == 10;
    
    return result;
}

bool testRemoveEdge() {
    Graph g(5);
    g.addVertex("A");
    g.addVertex("B");
    g.addEdge(0, 1, 10);
    
    bool result = g.removeEdge(0, 1);
    result &= !g.hasEdge(0, 1);
    result &= !g.hasEdge(1, 0);
    
    bool invalid = g.removeEdge(-1, 0);
    result &= !invalid;
    
    return result;
}

bool testDFS() {
    Graph g(5);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    
    std::vector<int> result;
    g.dfs(0, result);
    
    bool found = false;
    for (int v : result) {
        if (v == 3) {
            found = true;
            break;
        }
    }
    
    return found && result.size() == 4;
}

bool testBFS() {
    Graph g(5);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    
    std::vector<int> result;
    g.bfs(0, result);
    
    bool found = false;
    for (int v : result) {
        if (v == 3) {
            found = true;
            break;
        }
    }
    
    return found && result.size() == 4;
}

bool testDijkstra() {
    Graph g(5);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addVertex("E");
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 4);
    
    std::vector<int> path;
    int distance = 0;
    
    bool result = g.dijkstra(0, 4, path, distance);
    result &= distance == 11;
    result &= path.size() == 4;
    result &= path[0] == 0;
    result &= path.back() == 4;
    
    return result;
}

bool testDijkstraNoPath() {
    Graph g(3);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addEdge(0, 1, 5);
    
    std::vector<int> path;
    int distance = 0;
    
    bool result = !g.dijkstra(0, 2, path, distance);
    return result;
}

bool testCycleDetectionDirected() {
    Graph g(4, true);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);
    
    return g.hasCycle();
}

bool testCycleDetectionUndirected() {
    Graph g(4, false);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    
    return g.hasCycle();
}

bool testNoCycle() {
    Graph g(4);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    
    return !g.hasCycle();
}

bool testLoadFromFile() {
    Graph g(10);
    std::string dataPath = getDataPath();
    std::string filePath = dataPath + "/graph.txt";
    bool result = g.loadFromFile(filePath);
    
    result &= g.getVertexCount() == 5;
    result &= g.hasEdge(0, 1);
    result &= g.getEdgeWeight(0, 1) == 10;
    result &= !g.isDirectedGraph();
    
    return result;
}

bool testLoadFromInvalidFile() {
    Graph g(10);
    std::string dataPath = getDataPath();
    std::string filePath = dataPath + "/nonexistent.txt";
    bool result = !g.loadFromFile(filePath);
    return result;
}

bool testVertexIndexLookup() {
    Graph g(5);
    g.addVertex("Alice");
    g.addVertex("Bob");
    g.addVertex("Charlie");
    
    bool result = g.getVertexIndex("Bob") == 1;
    result &= g.getVertexIndex("Nonexistent") == -1;
    result &= g.getVertexName(0) == "Alice";
    result &= g.getVertexName(2) == "Charlie";
    
    return result;
}

int main() {
    std::cout << "=== 图数据结构单元测试 ===" << std::endl << std::endl;
    
    int passed = 0;
    int total = 0;
    
    total++; passed += testAddVertex() ? 1 : 0;
    printTestResult("添加顶点", testAddVertex());
    
    total++; passed += testRemoveVertex() ? 1 : 0;
    printTestResult("删除顶点", testRemoveVertex());
    
    total++; passed += testAddEdgeDirected() ? 1 : 0;
    printTestResult("有向图添加边", testAddEdgeDirected());
    
    total++; passed += testAddEdgeUndirected() ? 1 : 0;
    printTestResult("无向图添加边", testAddEdgeUndirected());
    
    total++; passed += testRemoveEdge() ? 1 : 0;
    printTestResult("删除边", testRemoveEdge());
    
    total++; passed += testDFS() ? 1 : 0;
    printTestResult("深度优先遍历", testDFS());
    
    total++; passed += testBFS() ? 1 : 0;
    printTestResult("广度优先遍历", testBFS());
    
    total++; passed += testDijkstra() ? 1 : 0;
    printTestResult("Dijkstra最短路径", testDijkstra());
    
    total++; passed += testDijkstraNoPath() ? 1 : 0;
    printTestResult("Dijkstra无路径", testDijkstraNoPath());
    
    total++; passed += testCycleDetectionDirected() ? 1 : 0;
    printTestResult("有向图环检测", testCycleDetectionDirected());
    
    total++; passed += testCycleDetectionUndirected() ? 1 : 0;
    printTestResult("无向图环检测", testCycleDetectionUndirected());
    
    total++; passed += testNoCycle() ? 1 : 0;
    printTestResult("无环图检测", testNoCycle());
    
    total++; passed += testLoadFromFile() ? 1 : 0;
    printTestResult("从文件加载", testLoadFromFile());
    
    total++; passed += testLoadFromInvalidFile() ? 1 : 0;
    printTestResult("无效文件加载", testLoadFromInvalidFile());
    
    total++; passed += testVertexIndexLookup() ? 1 : 0;
    printTestResult("顶点索引查找", testVertexIndexLookup());
    
    std::cout << std::endl << "=== 测试结果: " << passed << "/" << total << " 通过 ===" << std::endl;
    
    return (passed == total) ? 0 : 1;
}
