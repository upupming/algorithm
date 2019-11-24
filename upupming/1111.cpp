// Dijkstra algorithm, on both distance & time
// Needs to output the path traversal
#include <iostream>
#include <climits>

using namespace std;

int n, m, l[510][510], t[510][510], src, dest, parent[510], dist[510], ti[510];
bool visited[510];

void relax(int u, int v, int w, int w1, int *arr, int *arr1) {
    if (arr[v] > arr[u] + w || (arr[v] == arr[u] + w && arr1[v] - w1 > arr1[u]) ) {
        arr[v] = arr[u] + w;
        arr1[v] = arr1[u] + w1;
        parent[v] = u;
    }
}
string print(int current) {
    if (current == src) {
        return to_string(src);
    } else {
        return print(parent[current]) + " -> " + to_string(current);
    }
}

int main() {
    fill(l[0], l[0] + 510 * 510, INT_MAX);
    fill(t[0], t[0] + 510 * 510, INT_MAX);

    cin >> n >> m;
    int v1, v2, way, length, time;
    for (int i = 0; i < m; i++) {
        cin >> v1 >> v2 >> way >> length >> time;
        if (way) {
            l[v1][v2] = length;
            t[v1][v2] = time;
        } else {
            l[v1][v2] = l[v2][v1] = length;
            t[v1][v2] = t[v2][v1] = time;
        }
    }
    cin >> src >> dest;
    // cout << src << ", " << dest << endl;
    fill(visited, visited + 510, false);
    fill(dist, dist + 510, INT_MAX);
    fill(ti, ti + 510, INT_MAX);
    dist[src] = 0;
    // Dijkstra
    while(true) {
        int minDist = INT_MAX, minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }
        if (minIndex == -1) break;
        // cout << minIndex << endl;
        visited[minIndex] = true;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && l[minIndex][i] != INT_MAX) {
                relax(minIndex, i, l[minIndex][i], t[minIndex][i], dist, ti);
            }
        }
    }
    string a = print(dest);
    int tmp = dist[dest];

    // Just a copy
    fill(visited, visited + 510, false);
    fill(dist, dist + 510, INT_MAX);
    fill(ti, ti + 510, INT_MAX);
    dist[src] = 0;
    // Dijkstra
    while(true) {
        int minDist = INT_MAX, minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }
        if (minIndex == -1) break;
        visited[minIndex] = true;
        for (int i = 0; i < n; i++) {
            // 1 用来表示路径点数
            if (!visited[i] && t[minIndex][i] != INT_MAX) {
                relax(minIndex, i, t[minIndex][i], 1, dist, ti);
            }
        }
    }
    string b = print(dest);

    if (a == b) {
        cout << "Distance = " << tmp << "; Time = " << dist[dest] << ": " << b << endl;
    } else {
        cout << "Distance = " << tmp << ": " << a << endl;
        cout << "Time = " << dist[dest] << ": " << b << endl;
    }
    return 0;
}