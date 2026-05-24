# Kahn's Algorithm

An implementation of Kahn's Algorithm for Topological Sorting in C.

## Overview
Topological sorting for a Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge $uv$, vertex $u$ comes before $v$ in the ordering. This project demonstrates the algorithm using an adjacency list and in-degree tracking.

## Files
- [src/kahn.c](src/kahn.c): Main source code containing the algorithm implementation.

## Getting Started

### Prerequisites
- A C compiler (e.g., `gcc`)

### Compilation
To compile the program, run:
```powershell
gcc src/kahn.c -o kahn
```

### Execution
To run the executable:
```powershell
.\kahn.exe
```

## How it Works
1. Calculate the in-degree for each vertex.
2. Initialize a queue with all vertices having an in-degree of 0.
3. While the queue is not empty:
    - Dequeue a vertex and add it to the topological order.
    - For each neighbor of the dequeued vertex, decrement its in-degree.
    - If a neighbor's in-degree becomes 0, enqueue it.
4. If the topological order contains all vertices, the graph is a DAG.
