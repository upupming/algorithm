#include <iostream>

using namespace std;
#define V 5
/* Let us create the following graph
  (0)-2-(1)-3-(2)
    6|  /8 5\  |7
  (3)--9---(4)
      9  */

int graph[V][V] = {{0, 2, 0, 6, 0},
                   {2, 0, 3, 8, 5},
                   {0, 3, 0, 0, 7},
                   {6, 8, 0, 0, 9},
                   {0, 5, 7, 9, 0}};

void prim() {
  // key 表示最小生成树到达点 V 的边权
  int parent[V], key[V];
  bool visited[V];
  for (int i = 0; i < V; i++) {
    visited[i] = false;
    key[i] = INT_MAX;
  }
  key[0] = 0;
  parent[0] = 0;
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
      if (!visited[i] && graph[u][i] != 0 && graph[u][i] < key[i]) {
        parent[i] = u;
        key[i] = graph[u][i];
      }
    }
  }
  
  for (int i = 1; i < V; i++) {
      cout << parent[i] << " - " << i << ": " << key[i] << endl;
  }
}

int main() {
  prim();
  return 0;
}
