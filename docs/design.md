# 图数据结构（邻接矩阵存储）设计文档

## 1. 需求分析

### 1.1 项目背景
本项目实现基于邻接矩阵存储结构的图数据结构，用于解决图的表示、遍历和基本算法问题。邻接矩阵是图的经典存储方式之一，适合稠密图的表示，具有随机访问速度快的优点。

### 1.2 功能需求

| 需求编号 | 功能描述 | 优先级 | 需求来源 |
| :--- | :--- | :--- | :--- |
| REQ-001 | 支持有向图和无向图两种类型 | 高 | 基本需求 |
| REQ-002 | 支持顶点的添加、删除和查询 | 高 | 基本操作 |
| REQ-003 | 支持边的添加、删除和查询 | 高 | 基本操作 |
| REQ-004 | 支持图的深度优先遍历（DFS） | 高 | 遍历算法 |
| REQ-005 | 支持图的广度优先遍历（BFS） | 高 | 遍历算法 |
| REQ-006 | 支持计算两顶点间的最短路径（Dijkstra算法） | 高 | 路径算法 |
| REQ-007 | 支持检测图中是否存在环 | 中 | 图性质检测 |
| REQ-008 | 支持打印邻接矩阵 | 中 | 调试需求 |
| REQ-009 | 支持从文件加载图数据 | 中 | 数据持久化 |

### 1.3 非功能需求

| 需求编号 | 描述 | 优先级 |
| :--- | :--- | :--- |
| NFR-001 | 时间复杂度：顶点操作 O(1)，边操作 O(1) | 高 |
| NFR-002 | 空间复杂度：O(n²)，其中 n 为顶点数 | 高 |
| NFR-003 | 代码需通过单元测试 | 高 |

## 2. 数据结构设计

### 2.1 邻接矩阵原理

邻接矩阵是一个 n×n 的二维数组，其中 n 是图中顶点的数量。对于图 G=(V, E)：

- `matrix[i][j] = w`：表示顶点 i 到顶点 j 存在一条权重为 w 的边
- `matrix[i][j] = 0`（或特殊值）：表示顶点 i 到顶点 j 不存在边
- 对于无向图，矩阵是对称的：`matrix[i][j] = matrix[j][i]`

### 2.2 类设计

#### 2.2.1 Graph 类

| 成员变量 | 类型 | 访问权限 | 描述 |
| :--- | :--- | :--- | :--- |
| `matrix` | `int**` | private | 邻接矩阵指针 |
| `vertexCount` | `int` | private | 当前顶点数量 |
| `maxVertexCount` | `int` | private | 最大顶点容量 |
| `isDirected` | `bool` | private | 是否为有向图 |
| `vertexNames` | `std::string*` | private | 顶点名称数组 |

| 成员函数 | 返回类型 | 描述 |
| :--- | :--- | :--- |
| `Graph(int maxCount, bool directed = false)` | - | 构造函数，初始化指定容量的图 |
| `~Graph()` | - | 析构函数，释放资源 |
| `addVertex(const std::string& name)` | `int` | 添加顶点，返回顶点索引 |
| `removeVertex(int index)` | `bool` | 删除指定索引的顶点 |
| `addEdge(int from, int to, int weight = 1)` | `bool` | 添加边（有权重） |
| `removeEdge(int from, int to)` | `bool` | 删除边 |
| `getEdgeWeight(int from, int to)` | `int` | 获取边的权重 |
| `hasEdge(int from, int to)` | `bool` | 判断是否存在边 |
| `getVertexName(int index)` | `std::string` | 获取顶点名称 |
| `getVertexIndex(const std::string& name)` | `int` | 根据名称获取顶点索引 |
| `getVertexCount()` | `int` | 获取顶点数量 |
| `printMatrix()` | `void` | 打印邻接矩阵 |
| `dfs(int start, std::vector<int>& result)` | `void` | 深度优先遍历 |
| `bfs(int start, std::vector<int>& result)` | `void` | 广度优先遍历 |
| `dijkstra(int start, int end, std::vector<int>& path, int& distance)` | `bool` | Dijkstra最短路径算法 |
| `hasCycle()` | `bool` | 检测图中是否存在环 |
| `loadFromFile(const std::string& filename)` | `bool` | 从文件加载图数据 |

### 2.3 文件格式设计

图数据文件采用文本格式，每行表示一条边，格式如下：

```
# 注释行
vertex_count: 5
directed: true
A B 10
A C 5
B D 1
C B 3
C D 2
D E 4
```

| 字段 | 格式 | 说明 |
| :--- | :--- | :--- |
| `vertex_count` | `vertex_count: n` | 顶点数量 |
| `directed` | `directed: true/false` | 是否有向图 |
| 边数据 | `from to weight` | 边的起点、终点和权重（权重可选，默认为1） |

## 3. 接口设计

### 3.1 头文件结构

```
include/
└── Graph.h          # 图类声明
```

### 3.2 核心接口详解

#### 3.2.1 构造函数

```cpp
Graph(int maxCount, bool directed = false);
```

**参数**：
- `maxCount`：图的最大顶点容量
- `directed`：是否为有向图，默认为无向图

**前置条件**：`maxCount > 0`

**后置条件**：创建一个空图，邻接矩阵初始化为全0

---

#### 3.2.2 添加顶点

```cpp
int addVertex(const std::string& name);
```

**参数**：
- `name`：顶点名称

**返回值**：
- 成功：返回新顶点的索引（0-based）
- 失败：返回 -1（容量已满或名称重复）

**前置条件**：图未达到最大容量，名称不重复

**后置条件**：顶点添加成功，邻接矩阵对应行和列初始化为0

---

#### 3.2.3 添加边

```cpp
bool addEdge(int from, int to, int weight = 1);
```

**参数**：
- `from`：起点顶点索引
- `to`：终点顶点索引
- `weight`：边的权重，默认为1

**返回值**：
- `true`：添加成功
- `false`：添加失败（顶点索引无效）

**前置条件**：`from` 和 `to` 均为有效顶点索引

**后置条件**：
- 有向图：`matrix[from][to] = weight`
- 无向图：`matrix[from][to] = matrix[to][from] = weight`

---

#### 3.2.4 深度优先遍历

```cpp
void dfs(int start, std::vector<int>& result);
```

**参数**：
- `start`：起始顶点索引
- `result`：输出参数，存储遍历结果

**前置条件**：`start` 为有效顶点索引

**后置条件**：`result` 包含从 `start` 开始的DFS遍历序列

---

#### 3.2.5 广度优先遍历

```cpp
void bfs(int start, std::vector<int>& result);
```

**参数**：
- `start`：起始顶点索引
- `result`：输出参数，存储遍历结果

**前置条件**：`start` 为有效顶点索引

**后置条件**：`result` 包含从 `start` 开始的BFS遍历序列

---

#### 3.2.6 Dijkstra最短路径

```cpp
bool dijkstra(int start, int end, std::vector<int>& path, int& distance);
```

**参数**：
- `start`：起点顶点索引
- `end`：终点顶点索引
- `path`：输出参数，存储路径（顶点索引序列）
- `distance`：输出参数，存储最短距离

**返回值**：
- `true`：存在路径
- `false`：不存在路径

**前置条件**：`start` 和 `end` 均为有效顶点索引

**后置条件**：若存在路径，`path` 包含最短路径，`distance` 为路径总权重

---

#### 3.2.7 环检测

```cpp
bool hasCycle();
```

**返回值**：
- `true`：图中存在环
- `false`：图中不存在环

**前置条件**：图已初始化

**后置条件**：返回图的环检测结果

---

#### 3.2.8 从文件加载

```cpp
bool loadFromFile(const std::string& filename);
```

**参数**：
- `filename`：数据文件路径

**返回值**：
- `true`：加载成功
- `false`：加载失败（文件不存在或格式错误）

**前置条件**：文件存在且格式正确

**后置条件**：图数据从文件加载完成

## 4. 算法设计

### 4.1 DFS（深度优先遍历）

**算法思想**：使用栈（递归调用栈），从起始顶点出发，尽可能深地访问顶点，直到无法继续再回溯。

**时间复杂度**：O(V + E)
**空间复杂度**：O(V)

```
DFS(v):
    mark v as visited
    add v to result
    for each neighbor u of v:
        if u is not visited:
            DFS(u)
```

### 4.2 BFS（广度优先遍历）

**算法思想**：使用队列，从起始顶点出发，逐层访问所有邻接顶点。

**时间复杂度**：O(V + E)
**空间复杂度**：O(V)

```
BFS(v):
    create queue Q
    mark v as visited
    enqueue v to Q
    while Q is not empty:
        u = dequeue Q
        add u to result
        for each neighbor w of u:
            if w is not visited:
                mark w as visited
                enqueue w to Q
```

### 4.3 Dijkstra（最短路径算法）

**算法思想**：贪心算法，每次选择距离起点最近的未访问顶点，更新其邻接顶点的距离。

**时间复杂度**：O(V²)（未优化版本）
**空间复杂度**：O(V)

```
Dijkstra(start, end):
    initialize distance[] with infinity
    distance[start] = 0
    initialize visited[] as false
    initialize predecessor[] as -1
    
    for i from 0 to V-1:
        u = vertex with minimum distance not visited
        mark u as visited
        
        if u == end:
            break
            
        for each neighbor v of u:
            if not visited[v] and distance[v] > distance[u] + weight(u,v):
                distance[v] = distance[u] + weight(u,v)
                predecessor[v] = u
                
    reconstruct path from predecessor[]
```

### 4.4 环检测

**算法思想**：对于有向图使用DFS检测后向边；对于无向图检测访问过程中遇到的已访问非父节点。

**时间复杂度**：O(V + E)
**空间复杂度**：O(V)

## 5. 测试用例设计

### 5.1 单元测试覆盖矩阵

| 测试模块 | 测试场景 | 预期结果 |
| :--- | :--- | :--- |
| 顶点管理 | 添加顶点 | 返回正确索引 |
| 顶点管理 | 添加重复名称顶点 | 返回 -1 |
| 顶点管理 | 删除顶点 | 返回 true，邻接矩阵更新 |
| 边管理 | 添加边（有向图） | 只有单向边被添加 |
| 边管理 | 添加边（无向图） | 双向边被添加 |
| 边管理 | 删除边 | 返回 true，边被移除 |
| 边管理 | 查询不存在的边 | 返回 0 或 false |
| DFS遍历 | 连通图DFS | 返回完整遍历序列 |
| DFS遍历 | 非连通图DFS | 返回可达顶点序列 |
| BFS遍历 | 连通图BFS | 返回完整层序遍历序列 |
| Dijkstra | 存在路径 | 返回最短路径和距离 |
| Dijkstra | 不存在路径 | 返回 false |
| 环检测 | 有环图 | 返回 true |
| 环检测 | 无环图 | 返回 false |
| 文件加载 | 有效文件 | 返回 true，图数据正确加载 |
| 文件加载 | 无效文件 | 返回 false |

### 5.2 测试数据

#### 测试图结构

```
无向图示例：
    A ---10--- B
    |         |
    5         1
    |         |
    C ---3----|
    |
    2
    |
    D ---4--- E

有向图示例（带环）：
    A --> B --> C
    ^           |
    |           v
    +----------- D
```

## 6. 项目结构

```
MyprojectB/
├── include/
│   └── Graph.h          # 图类头文件
├── src/
│   └── Graph.cpp        # 图类实现
├── tests/
│   └── test_graph.cpp   # 单元测试
├── docs/
│   └── design.md        # 设计文档
├── data/
│   └── graph.txt        # 测试数据文件
└── README.md            # 项目说明
```

## 7. 编码规范

### 7.1 命名规范

| 类型 | 命名规则 | 示例 |
| :--- | :--- | :--- |
| 类名 | 大驼峰 | `Graph` |
| 成员变量 | 小驼峰，前缀可选 | `matrix`, `vertexCount` |
| 成员函数 | 小驼峰 | `addVertex`, `printMatrix` |
| 常量 | 全大写，下划线分隔 | `MAX_VERTEX_COUNT` |
| 局部变量 | 小驼峰 | `result`, `distance` |

### 7.2 注释规范

- 头文件中每个类和函数必须有Doxygen风格注释
- 源文件中复杂算法逻辑必须有行内注释
- 关键变量和条件判断必须有注释说明

### 7.3 异常处理

- 无效参数检查：顶点索引越界、空指针等
- 返回值约定：失败返回 -1 或 false，成功返回有效索引或 true
- 资源管理：使用智能指针或在析构函数中释放动态分配内存

## 8. 依赖与编译

### 8.1 依赖项

| 依赖 | 版本 | 用途 |
| :--- | :--- | :--- |
| C++ Standard | C++11 或更高 | 核心语言支持 |
| gtest | 1.10+ | 单元测试框架（可选） |

### 8.2 编译命令

```bash
# 编译源码
g++ -c src/Graph.cpp -I include -o obj/Graph.o

# 编译测试
g++ tests/test_graph.cpp obj/Graph.o -I include -o bin/test_graph

# 运行测试
./bin/test_graph
```

## 9. 风险评估

| 风险编号 | 风险描述 | 影响程度 | 缓解措施 |
| :--- | :--- | :--- | :--- |
| RISK-001 | 邻接矩阵空间复杂度高（O(n²)） | 中 | 限制最大顶点数量，提供动态扩容机制 |
| RISK-002 | 删除顶点需要移动大量数据 | 中 | 使用懒删除策略或标记删除 |
| RISK-003 | Dijkstra算法未优化（O(n²)） | 低 | 对于小规模图可接受，必要时引入优先队列优化 |
| RISK-004 | 文件格式解析错误 | 低 | 增加格式校验和错误提示 |

## 10. 版本计划

| 版本 | 内容 |
| :--- | :--- |
| v1.0 | 基础功能：顶点/边管理、邻接矩阵打印、DFS/BFS遍历 |
| v1.1 | 算法功能：Dijkstra最短路径、环检测 |
| v1.2 | 扩展功能：文件加载/保存、动态扩容 |
