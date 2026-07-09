#include "scenic_graph.h"

static int FindSpotIndex(Graph *graph, int spot_id) {
    for (int i = 0; i < graph->spot_count; i++) {
        if (graph->spots[i].spot_id == spot_id) {
            return i;
        }
    }
    return -1;
}

static int FindSpotByName(Graph *graph, const char *name) {
    for (int i = 0; i < graph->spot_count; i++) {
        if (strcmp(graph->spots[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

static int AddSinglePath(Graph *graph, int from_idx, int to_idx, int from_id, int to_id, int distance, const char *path_desc) {
    AdjNode *temp = graph->adj_list[from_idx];
    while (temp != NULL) {
        if (temp->spot_id == to_id) {
            return -1;
        }
        temp = temp->next;
    }
    
    AdjNode *new_node = (AdjNode*)malloc(sizeof(AdjNode));
    if (new_node == NULL) {
        printf("内存分配失败！\n");
        return -1;
    }
    new_node->spot_id = to_id;
    new_node->distance = distance;
    strncpy(new_node->path_desc, path_desc, MAX_DESC - 1);
    new_node->path_desc[MAX_DESC - 1] = '\0';
    new_node->next = NULL;
    
    if (graph->adj_list[from_idx] == NULL) {
        graph->adj_list[from_idx] = new_node;
    } else {
        temp = graph->adj_list[from_idx];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    return 0;
}

Graph* CreateGraph() {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }
    graph->spot_count = 0;
    graph->max_spot_id = 0;
    for (int i = 0; i < MAX_SPOTS; i++) {
        graph->adj_list[i] = NULL;
        memset(&graph->spots[i], 0, sizeof(Spot));
    }
    return graph;
}

int AddSpot(Graph *graph, const char *name, const char *description) {
    if (graph->spot_count >= MAX_SPOTS) {
        printf("景点数量已达上限！\n");
        return -1;
    }
    
    if (FindSpotByName(graph, name) != -1) {
        printf("景点名称已存在！\n");
        return -1;
    }
    
    int new_id = ++graph->max_spot_id;
    Spot *spot = &graph->spots[graph->spot_count];
    spot->spot_id = new_id;
    strncpy(spot->name, name, MAX_NAME - 1);
    spot->name[MAX_NAME - 1] = '\0';
    strncpy(spot->description, description, MAX_DESC - 1);
    spot->description[MAX_DESC - 1] = '\0';
    graph->spot_count++;
    
    printf("景点添加成功：ID=%d, 名称=%s\n", new_id, name);
    return new_id;
}

int AddPath(Graph *graph, int from_id, int to_id, int distance, const char *path_desc) {
    int from_idx = FindSpotIndex(graph, from_id);
    int to_idx = FindSpotIndex(graph, to_id);
    
    if (from_idx == -1) {
        printf("起点景点ID=%d不存在！\n", from_id);
        return -1;
    }
    if (to_idx == -1) {
        printf("终点景点ID=%d不存在！\n", to_id);
        return -1;
    }
    if (from_id == to_id) {
        printf("起点和终点不能相同！\n");
        return -1;
    }
    if (distance <= 0) {
        printf("路径距离必须大于0！\n");
        return -1;
    }
    
    int result1 = AddSinglePath(graph, from_idx, to_idx, from_id, to_id, distance, path_desc);
    int result2 = AddSinglePath(graph, to_idx, from_idx, to_id, from_id, distance, path_desc);
    
    if (result1 == -1 && result2 == -1) {
        printf("路径已存在！\n");
        return -1;
    }
    
    printf("路径添加成功：%d <-> %d (距离=%dm)\n", from_id, to_id, distance);
    return 0;
}

void DisplayGraph(Graph *graph) {
    printf("\n========== 景区图（邻接表）==========\n");
    if (graph->spot_count == 0) {
        printf("图为空，暂无景点\n");
        return;
    }
    
    for (int i = 0; i < graph->spot_count; i++) {
        Spot *spot = &graph->spots[i];
        printf("景点[%d] %s\n", spot->spot_id, spot->name);
        
        AdjNode *temp = graph->adj_list[i];
        if (temp == NULL) {
            printf("  -> 无相邻景点\n");
        } else {
            printf("  -> ");
            while (temp != NULL) {
                int to_idx = FindSpotIndex(graph, temp->spot_id);
                printf("[%d]%s (%dm, %s)", 
                       temp->spot_id,
                       to_idx != -1 ? graph->spots[to_idx].name : "未知",
                       temp->distance,
                       temp->path_desc);
                if (temp->next != NULL) {
                    printf(" -> ");
                }
                temp = temp->next;
            }
            printf("\n");
        }
    }
    printf("=====================================\n");
}

void DisplaySpotList(Graph *graph) {
    printf("\n========== 景点链表 ==========\n");
    if (graph->spot_count == 0) {
        printf("暂无景点\n");
        return;
    }
    
    printf("序号 | 景点ID | 名称 | 描述\n");
    printf("-----|--------|------|------\n");
    for (int i = 0; i < graph->spot_count; i++) {
        Spot *spot = &graph->spots[i];
        printf("%d | %d | %s | %s\n", 
               i + 1, 
               spot->spot_id, 
               spot->name, 
               spot->description);
    }
    printf("==============================\n");
}

void DestroyGraph(Graph *graph) {
    if (graph == NULL) return;
    
    for (int i = 0; i < graph->spot_count; i++) {
        AdjNode *temp = graph->adj_list[i];
        while (temp != NULL) {
            AdjNode *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph);
}