#ifndef SCENIC_GRAPH_H
#define SCENIC_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPOTS 50
#define MAX_NAME 50
#define MAX_DESC 100

typedef struct {
    int spot_id;
    char name[MAX_NAME];
    char description[MAX_DESC];
} Spot;

typedef struct AdjNode {
    int spot_id;
    int distance;
    char path_desc[MAX_DESC];
    struct AdjNode *next;
} AdjNode;

typedef struct {
    Spot spots[MAX_SPOTS];
    AdjNode *adj_list[MAX_SPOTS];
    int spot_count;
    int max_spot_id;
} Graph;

Graph* CreateGraph();
int AddSpot(Graph *graph, const char *name, const char *description);
int AddPath(Graph *graph, int from_id, int to_id, int distance, const char *path_desc);
void DisplayGraph(Graph *graph);
void DisplaySpotList(Graph *graph);
void DestroyGraph(Graph *graph);

#endif