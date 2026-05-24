/*=============================================================
 * Mini Project: Kahn's Algorithm for Topological Sorting
 * Algorithm   : Kahn's Algorithm (BFS-based Topological Sort)
 * Author      : Akshay  |  USN: R24EQ007
 * Guide       : Prof. Divyashree Ma'am
 * Description : Demonstrates all 10 Test Cases from Section 6.3
 *               Each test case runs automatically and prints
 *               queue status, in-degree updates, and final output.
 *=============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 20

/* -------------------------------------------------------
 * Adjacency List Node
 * ------------------------------------------------------- */
struct Node {
    int dest;
    struct Node* next;
};

/* -------------------------------------------------------
 * Graph Structure
 * ------------------------------------------------------- */
struct Graph {
    int numVertices;
    struct Node* adjList[MAX_VERTICES];
    int inDegree[MAX_VERTICES];
};

/* -------------------------------------------------------
 * Queue Structure
 * ------------------------------------------------------- */
struct Queue {
    int items[MAX_VERTICES];
    int front, rear;
};

/* ============================================================
 * Module: Graph Creation
 * ============================================================ */
struct Graph* createGraph(int vertices) {
    struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        g->adjList[i] = NULL;
        g->inDegree[i] = 0;
    }
    return g;
}

/* ============================================================
 * Module: Add Directed Edge (src -> dest)
 * ============================================================ */
void addEdge(struct Graph* g, int src, int dest) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->dest = dest;
    node->next = g->adjList[src];
    g->adjList[src] = node;
    g->inDegree[dest]++;
}

/* ============================================================
 * Module: Queue Operations
 * ============================================================ */
void initQueue(struct Queue* q) { q->front = q->rear = -1; }
int  isEmpty(struct Queue* q)   { return q->front == -1; }

void enqueue(struct Queue* q, int val) {
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = val;
}

int dequeue(struct Queue* q) {
    int val = q->items[q->front++];
    if (q->front > q->rear) q->front = q->rear = -1;
    return val;
}

/* ============================================================
 * Helper: Print current queue contents
 * ============================================================ */
void printQueue(struct Queue* q) {
    if (isEmpty(q)) { printf("[ empty ]"); return; }
    printf("[ ");
    for (int i = q->front; i <= q->rear; i++)
        printf("%d ", q->items[i]);
    printf("]");
}

/* ============================================================
 * Module: Kahn's Algorithm (Simplified Output)
 * ============================================================ */
void kahnSort(struct Graph* g, const char* vertexLabels[]) {
    int V = g->numVertices;
    int tempIn[MAX_VERTICES];
    int order[MAX_VERTICES];
    int count = 0;
    struct Queue q;
    initQueue(&q);

    for (int i = 0; i < V; i++) tempIn[i] = g->inDegree[i];
    for (int i = 0; i < V; i++)
        if (tempIn[i] == 0) enqueue(&q, i);

    while (!isEmpty(&q)) {
        int v = dequeue(&q);
        order[count++] = v;
        struct Node* tmp = g->adjList[v];
        while (tmp) {
            tempIn[tmp->dest]--;
            if (tempIn[tmp->dest] == 0) enqueue(&q, tmp->dest);
            tmp = tmp->next;
        }
    }

    if (count != V) {
        printf("  Result: [ERROR] Cycle Detected! Order: ");
    } else {
        printf("  Result: ");
    }
    
    for (int i = 0; i < count; i++) {
        printf("%s", vertexLabels[order[i]]);
        if (i < count - 1) printf(" -> ");
    }
    printf("\n");
}

/* ============================================================
 * Helper: Print a separator banner for each test case
 * ============================================================ */
void printBanner(int tc, const char* category, const char* desc) {
    printf("TC-%02d | %-25s | ", tc, category);
}

/* ============================================================
 * Helper: Free graph memory
 * ============================================================ */
void freeGraph(struct Graph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        struct Node* cur = g->adjList[i];
        while (cur) { struct Node* nx = cur->next; free(cur); cur = nx; }
    }
    free(g);
}

/* ============================================================
 * MAIN: Run all 10 test cases
 * ============================================================ */
int main() {
    printf("--- KAHN'S ALGORITHM TOPOLOGICAL SORT TEST CASES ---\n");
    printf("Author: Akshay | USN: R24EQ007 | Guide: Prof. Divyashree\n\n");

    struct Graph* g;

    /* --------------------------------------------------------
     * TC-01: Normal DAG
     * Vertices: A(0) B(1) C(2) D(3) E(4)
     * Edges: A->C, B->C, C->D, D->E
     * -------------------------------------------------------- */
    printBanner(1, "Normal DAG", "5 vertices | Edges: A->C, B->C, C->D, D->E");
    {
        const char* labels[] = {"A","B","C","D","E"};
        g = createGraph(5);
        addEdge(g, 0, 2); /* A -> C */
        addEdge(g, 1, 2); /* B -> C */
        addEdge(g, 2, 3); /* C -> D */
        addEdge(g, 3, 4); /* D -> E */
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-02: Normal - Simple Linear Chain
     * Edges: 0->1, 1->2
     * -------------------------------------------------------- */
    printBanner(2, "Normal - Simple Linear", "3 vertices | Edges: 0->1, 1->2");
    {
        const char* labels[] = {"0","1","2"};
        g = createGraph(3);
        addEdge(g, 0, 1);
        addEdge(g, 1, 2);
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-03: Normal - Multiple Valid Topological Orders
     * Edges: 0->2, 1->2, 0->3, 1->3
     * -------------------------------------------------------- */
    printBanner(3, "Normal - Multi Order",
                "4 vertices | Edges: 0->2, 1->2, 0->3, 1->3");
    {
        const char* labels[] = {"0","1","2","3"};
        g = createGraph(4);
        addEdge(g, 0, 2);
        addEdge(g, 1, 2);
        addEdge(g, 0, 3);
        addEdge(g, 1, 3);
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-04: Boundary - Single Vertex, No Edges
     * -------------------------------------------------------- */
    printBanner(4, "Boundary - Single Vertex", "1 vertex | 0 edges");
    {
        const char* labels[] = {"V0"};
        g = createGraph(1);
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-05: Boundary - No Edges
     * -------------------------------------------------------- */
    printBanner(5, "Boundary - No Edges", "4 vertices | 0 edges (all in-degrees = 0)");
    {
        const char* labels[] = {"0","1","2","3"};
        g = createGraph(4);
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-06: Boundary - Linear Chain of 6
     * Edges: 0->1->2->3->4->5
     * -------------------------------------------------------- */
    printBanner(6, "Boundary - Linear Chain",
                "6 vertices | Edges: 0->1->2->3->4->5");
    {
        const char* labels[] = {"0","1","2","3","4","5"};
        g = createGraph(6);
        for (int i = 0; i < 5; i++) addEdge(g, i, i+1);
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-07: Extreme - Dense DAG (upper triangular)
     * 5 vertices, all edges i->j where i < j
     * -------------------------------------------------------- */
    printBanner(7, "Extreme - Dense DAG",
                "5 vertices | All forward edges (upper triangular, 10 edges)");
    {
        const char* labels[] = {"0","1","2","3","4"};
        g = createGraph(5);
        for (int i = 0; i < 5; i++)
            for (int j = i+1; j < 5; j++)
                addEdge(g, i, j);
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-08: Extreme - Sparse DAG
     * 10 vertices, only 2 edges: 0->9, 3->7
     * -------------------------------------------------------- */
    printBanner(8, "Extreme - Sparse DAG",
                "10 vertices | Only 2 edges: 0->9, 3->7");
    {
        const char* labels[] = {"0","1","2","3","4","5","6","7","8","9"};
        g = createGraph(10);
        addEdge(g, 0, 9);
        addEdge(g, 3, 7);
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-09: Cycle Detection - Simple Cycle
     * 3 vertices: 0->1, 1->2, 2->0
     * -------------------------------------------------------- */
    printBanner(9, "Cycle - Simple",
                "3 vertices | Edges: 0->1, 1->2, 2->0  (full cycle)");
    {
        const char* labels[] = {"0","1","2"};
        g = createGraph(3);
        addEdge(g, 0, 1);
        addEdge(g, 1, 2);
        addEdge(g, 2, 0);
        kahnSort(g, labels);
        freeGraph(g);
    }

    /* --------------------------------------------------------
     * TC-10: Cycle Detection - Complex Partial Cycle
     * 4 vertices: 0->1, 1->2, 2->3, 3->1  (cycle: 1->2->3->1)
     * -------------------------------------------------------- */
    printBanner(10, "Cycle - Partial",
                "4 vertices | Edges: 0->1, 1->2, 2->3, 3->1 (cycle: 1->2->3->1)");
    {
        const char* labels[] = {"0","1","2","3"};
        g = createGraph(4);
        addEdge(g, 0, 1);
        addEdge(g, 1, 2);
        addEdge(g, 2, 3);
        addEdge(g, 3, 1);
        kahnSort(g, labels);
        freeGraph(g);
    }

    printf("\nAll 10 Test Cases Executed Successfully.\n");

    return 0;
}