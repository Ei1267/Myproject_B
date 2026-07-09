#include "scenic_graph.h"
#ifdef _WIN32
#include <windows.h>
#endif

static void ClearInputBuffer() {
    while (getchar() != '\n');
}

static void Menu() {
    printf("\n===== 景区路径规划系统 =====\n");
    printf("1. 创建图\n");
    printf("2. 添加景点\n");
    printf("3. 添加路径\n");
    printf("4. 显示景区图\n");
    printf("5. 显示景点链表\n");
    printf("6. 退出\n");
    printf("请选择操作(1-6)：");
}

int main() {
    Graph *graph = NULL;
    int choice;
    char name[MAX_NAME];
    char desc[MAX_DESC];
    char path_desc[MAX_DESC];
    int from_id, to_id, distance;
    
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    
    while (1) {
        Menu();
        scanf("%d", &choice);
        ClearInputBuffer();
        
        switch (choice) {
            case 1:
                if (graph != NULL) {
                    DestroyGraph(graph);
                }
                graph = CreateGraph();
                if (graph != NULL) {
                    printf("图创建成功！\n");
                }
                break;
                
            case 2:
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                printf("请输入景点名称：");
                fgets(name, MAX_NAME, stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("请输入景点描述：");
                fgets(desc, MAX_DESC, stdin);
                desc[strcspn(desc, "\n")] = '\0';
                AddSpot(graph, name, desc);
                break;
                
            case 3:
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                printf("请输入起点景点ID：");
                scanf("%d", &from_id);
                printf("请输入终点景点ID：");
                scanf("%d", &to_id);
                printf("请输入路径距离(米)：");
                scanf("%d", &distance);
                ClearInputBuffer();
                printf("请输入路径描述：");
                fgets(path_desc, MAX_DESC, stdin);
                path_desc[strcspn(path_desc, "\n")] = '\0';
                AddPath(graph, from_id, to_id, distance, path_desc);
                break;
                
            case 4:
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                DisplayGraph(graph);
                break;
                
            case 5:
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                DisplaySpotList(graph);
                break;
                
            case 6:
                if (graph != NULL) {
                    DestroyGraph(graph);
                }
                printf("程序退出！\n");
                return 0;
                
            default:
                printf("无效选择，请重新输入！\n");
        }
    }
    
    return 0;
}