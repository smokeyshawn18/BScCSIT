/*
 * ============================================================
 *  OBJECTIVE:
 *   Write a C program to find the Minimum Spanning Tree (MST)
 *   of a weighted undirected graph using Prim's Algorithm.
 * ============================================================
 *  PRIM'S ALGORITHM — Minimum Spanning Tree (MST)
 * ============================================================
 * THEORY:
 *   A Minimum Spanning Tree (MST) is a subset of edges of a
 *   connected, weighted, undirected graph that connects all
 *   vertices together with the minimum possible total edge
 *   weight, without forming any cycle.
 *
 *   Prim's Algorithm grows the MST one vertex at a time by
 *   always picking the cheapest edge that connects a visited
 *   vertex to an unvisited vertex, similar to how Dijkstra's
 *   algorithm works for shortest paths.
 *
 *   It starts from any source vertex, then greedily selects
 *   the minimum weight edge crossing the cut (visited vs
 *   unvisited vertices) at each step until all vertices are
 *   included in the MST.
 *
 *   The algorithm maintains a key[] array (minimum edge weight
 *   to reach each vertex) and a parent[] array (to track which
 *   edge was chosen), updating them as new vertices are added.
 *
 * TIME COMPLEXITY:
 *   O(V²)        — Using adjacency matrix (implemented here)
 *   O(E log V)   — Using min-heap / priority queue
 *   where V = number of vertices, E = number of edges
 *
 * SPACE COMPLEXITY:
 *   O(V²)  — Adjacency matrix storage
 *   O(V)   — key[], parent[], inMST[] arrays
 * ============================================================
 */

#include <stdio.h>
#include <limits.h>   /* For INT_MAX */

#define MAX_V 10

/* Function: min_key
 * Finds the vertex with the minimum key value
 * from the set of vertices not yet included in MST.
 *
 * Time  : O(V)
 */
int min_key(int key[], int inMST[], int V) {
    int min = INT_MAX, min_idx = -1;

    for (int v = 0; v < V; v++) {
        if (inMST[v] == 0 && key[v] < min) {
            min = key[v];
            min_idx = v;
        }
    }
    return min_idx;
}

/* Function: prim_mst
 * Computes the MST of a graph represented as adjacency
 * matrix graph[V][V] using Prim's Algorithm.
 *
 * Time  : O(V²)
 * Space : O(V)
 */
void prim_mst(int graph[MAX_V][MAX_V], int V) {
    int parent[MAX_V];   /* Stores MST edges         */
    int key[MAX_V];      /* Minimum edge weight      */
    int inMST[MAX_V];    /* Tracks included vertices */

    /* Initialize all keys to infinity, none in MST */
    for (int i = 0; i < V; i++) {
        key[i]   = INT_MAX;
        inMST[i] = 0;
    }

    /* Start from vertex 0 */
    key[0]    = 0;
    parent[0] = -1;   /* Root has no parent */

    for (int count = 0; count < V - 1; count++) {
        /* Pick the minimum key vertex not yet in MST */
        int u = min_key(key, inMST, V);
        inMST[u] = 1;   /* Include u in MST */

        /* Update key[] and parent[] for adjacent vertices */
        for (int v = 0; v < V; v++) {
            /* graph[u][v] != 0 means edge exists      */
            /* !inMST[v]       means v not yet in MST  */
            /* graph[u][v] < key[v] means cheaper edge */
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v]    = graph[u][v];
            }
        }
    }

    /* Print MST edges and total weight */
    printf("\nMST Edges (Vertex -- Vertex : Weight)\n");
    printf("--------------------------------------\n");

    int total = 0;
    for (int i = 1; i < V; i++) {
        printf("  %d  --  %d  :  %d\n", parent[i], i, graph[parent[i]][i]);
        total += graph[parent[i]][i];
    }
    printf("--------------------------------------\n");
    printf("  Total MST Weight : %d\n", total);
}

int main() {
    int V;
    printf("PRIM'S MST ALGORITHM\n");

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    if (V <= 0 || V > MAX_V) {
        printf("Invalid! Enter between 1 and %d.\n", MAX_V);
        return 1;
    }

    int graph[MAX_V][MAX_V];

    printf("Enter adjacency matrix (%d x %d)\n", V, V);
    printf("(Enter 0 if no edge between vertices)\n\n");

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("  Edge weight [%d][%d]: ", i, j);
            scanf("%d", &graph[i][j]);
        }
    }

    /* Print entered adjacency matrix */
    printf("\nAdjacency Matrix:\n");
    printf("     ");
    for (int i = 0; i < V; i++) printf("%4d", i);
    printf("\n     ");
    for (int i = 0; i < V; i++) printf("----");
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("  %d |", i);
        for (int j = 0; j < V; j++)
            printf("%4d", graph[i][j]);
        printf("\n");
    }

    prim_mst(graph, V);
    return 0;
}