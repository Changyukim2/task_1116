#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];
int parent[MAX_VERTICES];

int get_min_vertex(int n) {
    int v, i;
    for (i = 0; i < n; i++) {
        if (!selected[i]) {
            v = i;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        if (!selected[i] && (distance[i] < distance[v]))
            v = i;
    }
    return (v);
}

void prim(GraphType* g, int s) {
    int i, u, v;

    for (u = 0; u < g->n; u++) {
        distance[u] = INF;
        selected[u] = FALSE;
    }
    distance[s] = 0;
    parent[s] = -1;

    for (i = 0; i < g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = TRUE;
        if (distance[u] == INF)
            return;
        printf("정점 %d 추가\n", u);
        if (parent[u] != -1) {
            printf("간선 (%d, %d) 추가, 비용: %d\n", parent[u], u, g->weight[parent[u]][u]);
        }

        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF) {
                if (!selected[v] && g->weight[u][v] < distance[v]) {
                    distance[v] = g->weight[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}

int main(void) {
    GraphType g = { 7,
        {{ 0, 29, INF, INF, INF, 10, INF },
         { 29,  0, 16, INF, INF, INF, 15 },
         { INF, 16, 0, 12, INF, INF, 17 },
         { INF, INF, 12, 0, 22, INF, 18 },
         { INF, INF, INF, 22, 0, 30, 25 },
         { 10, INF, INF, INF, 30, 0, INF },
         { INF, 15, 17, 18, 25, INF, 0 }}
    };

    prim(&g, 0);

    int totalCost = 0;
    for (int i = 0; i < g.n; i++) {
        if (parent[i] != -1) {
            totalCost += g.weight[parent[i]][i];
        }
    }

    printf("MST의 총 비용: %d\n", totalCost);

    int maxEdgeCost = 0;
    int maxEdgeStart, maxEdgeEnd;
    for (int i = 0; i < g.n; i++) {
        if (parent[i] != -1 && g.weight[parent[i]][i] > maxEdgeCost) {
            maxEdgeCost = g.weight[parent[i]][i];
            maxEdgeStart = parent[i];
            maxEdgeEnd = i;
        }
    }

    printf("가장 비용이 많이 드는 간선: (%d, %d), 비용: %d\n", maxEdgeStart, maxEdgeEnd, maxEdgeCost);

    return 0;
}
