# 图数据结构（邻接矩阵存储）

基于邻接矩阵存储结构的图数据结构实现，支持有向图/无向图、顶点/边管理、图遍历算法（DFS/BFS）、最短路径算法（Dijkstra）和环检测等功能。

## 项目结构

```
MyprojectB/
├── include/
│   └── Graph.h          # 图类头文件（接口声明）
├── src/
│   └── Graph.cpp        # 图类源文件（实现）
├── tests/
│   └── test_graph.cpp   # 单元测试
├── data/
│   └── graph.txt        # 测试数据文件
├── docs/
│   └── design.md        # 设计文档
└── README.md            # 项目说明
```

## 功能特性

- ✅ **图类型支持**：有向图和无向图
- ✅ **顶点管理**：添加、删除、查询顶点
- ✅ **边管理**：添加、删除、查询边（支持权重）
- ✅ **图遍历**：深度优先遍历（DFS）、广度优先遍历（BFS）
- ✅ **最短路径**：Dijkstra算法
- ✅ **环检测**：有向图和无向图环检测
- ✅ **文件加载**：从文本文件加载图数据
- ✅ **矩阵打印**：打印邻接矩阵

## 编译与运行

### 环境要求

- C++11 或更高版本编译器（g++、MSVC等）
- Windows/Linux/macOS

### 编译命令

```bash
# 进入项目目录
cd MyprojectB

# 创建编译目录
mkdir -p obj bin

# 编译源码
g++ -c src/Graph.cpp -I include -o obj/Graph.o

# 编译测试程序
g++ tests/test_graph.cpp obj/Graph.o -I include -o bin/test_graph

# 运行测试
./bin/test_graph
```

### Windows PowerShell

```powershell
New-Item -ItemType Directory -Path "obj","bin" -Force
g++ -c src/Graph.cpp -I include -o obj/Graph.o
g++ tests/test_graph.cpp obj/Graph.o -I include -o bin/test_graph.exe
.\bin\test_graph.exe
```

## 使用示例

```cpp
#include "Graph.h"
#include <iostream>

int main() {
    Graph g(5, false);
    
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 3);
    
    g.printMatrix();
    
    std::vector<int> path;
    int distance = 0;
    if (g.dijkstra(0, 2, path, distance)) {
        std::cout << "最短路径长度: " << distance << std::endl;
        for (int v : path) {
            std::cout << g.getVertexName(v) << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
```

## 接口说明

| 方法 | 说明 |
| :--- | :--- |
| `Graph(int maxCount, bool directed)` | 构造函数，创建指定容量的图 |
| `addVertex(name)` | 添加顶点，返回索引 |
| `removeVertex(index)` | 删除顶点 |
| `addEdge(from, to, weight)` | 添加边 |
| `removeEdge(from, to)` | 删除边 |
| `hasEdge(from, to)` | 判断是否存在边 |
| `getEdgeWeight(from, to)` | 获取边权重 |
| `dfs(start, result)` | 深度优先遍历 |
| `bfs(start, result)` | 广度优先遍历 |
| `dijkstra(start, end, path, distance)` | 最短路径 |
| `hasCycle()` | 检测环 |
| `printMatrix()` | 打印邻接矩阵 |
| `loadFromFile(filename)` | 从文件加载图 |

## 文件格式

图数据文件格式示例：

```
# 注释行
vertex_count: 5
directed: false
A B 10
A C 5
B D 1
C B 3
C D 2
D E 4
```

## 算法复杂度

| 操作 | 时间复杂度 |
| :--- | :--- |
| 添加顶点 | O(n) |
| 删除顶点 | O(n²) |
| 添加边 | O(1) |
| 删除边 | O(1) |
| DFS/BFS | O(V+E) |
| Dijkstra | O(V²) |
| 环检测 | O(V+E) |

## 设计文档

详细设计文档请查看 [docs/design.md](docs/design.md)

## 许可证

MIT License
