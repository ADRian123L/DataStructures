#include "queue.hpp"
#include "stack.hpp"

// Breath First Search
void BFS(int G[][7], int start, int n) {
    int        i = start;
    queue<int> q;
    int        visited[7] = {0};
    std::cout << i << ", ";
    visited[i] = 1;
    q.enqueue(i);
    while (!q.isEmpty()) {
        i = q.getdeq();
        q.dequeue();
        for (int j = 1; j < n; ++j) {
            if (G[i][j] == 1 && visited[j] == 0) {
                std::cout << j << ", " << std::flush;
                q.enqueue(j);
                visited[j] = 1;
            }
        }
    }
}

// Depth First Search
void DFS(int G[][7], int start, int n) {
    static int visited[7] = {0};
    if (visited[start] == 1) {
        return;
    }
    std::cout << start << ", " << std::flush;
    visited[start] = 1;
    for (int j = 1; j < n; ++j) {
        if (G[start][j] == 1 && visited[j] == 0) {
            DFS(G, j, n);
        }
    }
    return;
}

// Depth First Search using stack
void DFS_STACK(int G[][7], int start, int n) {
    stack<int> s;
    int        visited[7] = {0};
    s.push(start);
    while (!s.isEmpty()) {
        int i = s.get();
        s.pop();
        if (!visited[i]) {
            std::cout << i << ", " << std::flush;
            visited[i] = 1;
            for (int j = n - 1; j > 0; --j) {
                if (G[i][j] == 1 && visited[j] == 0) {
                    s.push(j);
                }
            }
        }
    }
}




// Adjacency Matrix
int main() {
    int graph[][7] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0},
    };
    DFS_STACK(graph, 1, 7);
    return EXIT_SUCCESS;
}
