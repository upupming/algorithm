#include <climits>
#include <iostream>

using namespace std;
#define V 5
/* Let us create the following graph
  (0)-2-(1)-3-(2)
    6|  /8 5\  |7
    (3)--9---(4)
        */

// Prim vs Dijkstra: https://stackoverflow.com/a/14144397/8242705
// The special case can be 3 - 4 in the MST is 6 + 2 + 5 = 13 (see the results of `prim.cpp`),
// but in shortest path, it should be 9

int graph[V][V] = {{0, 2, 0, 6, 0},
                   {2, 0, 3, 8, 5},
                   {0, 3, 0, 0, 7},
                   {6, 8, 0, 0, 9},
                   {0, 5, 7, 9, 0}};
// find the shortest path from s to w
void dijkstra(int w, int s) {
    // key 表示最小生成树到达点 V 的边权
    int parent[V], key[V];
    bool visited[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        key[i] = INT_MAX;
    }
    key[s] = 0;
    while (true) {
        int u = -1, minKey = INT_MAX;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && key[i] < minKey) {
                u = i;
                minKey = key[i];
            }
        }
        if (u == -1) break;
        visited[u] = true;
        for (int i = 0; i < V; i++) {
            // This is the key difference with Prim
            // Prim don't calculate sum, but the value
            if (!visited[i] && graph[u][i] != 0 && key[u] + graph[u][i] < key[i]) {
                parent[i] = u;
                key[i] = key[u] + graph[u][i];
            }
        }
    }

    string path = "";
    for (int i = w; i != s; i = parent[i]) {
        path = to_string(parent[i]) + " - " + to_string(i) + ": " + to_string(key[i]) + "\n" + path;
    }
    cout << path << endl;
}

int main() {
    dijkstra(3, 4);
    dijkstra(1, 4);
    dijkstra(4, 1);
    dijkstra(2, 3);
    return 0;
}
