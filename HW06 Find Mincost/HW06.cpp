#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define INF 2147483647 // INT_MAX 的值（32-bit int）

void dfs(int u, const vector<vector<int>>& adj, const vector<int>& weights,
         vector<int>& minCost, vector<vector<int>>& paths,
         vector<bool>& visited, int currentCost, vector<int> path, int s) {
  visited[u] = true;
  path.push_back(u); // 將目前節點加入路徑

  for (int v = 0; v < adj.size(); ++v) {
    // 如果 v 是 u 的鄰接節點，且 v 不是起點 s(0)，且未被訪問過
    if (v != u && adj[u][v] > 0 && !visited[v]) {
      int nextCost = currentCost + adj[u][v]; // 從 u 到 v 的邊的成本
      if (u != s) nextCost += weights[u];     // 中繼節點要加權重

      if (nextCost < minCost[v]) {
        minCost[v] = nextCost; // 更新到 v 的最小成本
        paths[v] = path;       // 記錄路徑（到 v 的最佳路徑）
        dfs(v, adj, weights, minCost, paths, visited, nextCost, path, s);
      }
    }
  }   

  visited[u] = false;
}

int main() {
  int n;

  while (cin >> n && n > 0) {
    // 讀取權重
    vector<int> weights(n);
    for (int i = 0; i < n; ++i)
      cin >> weights[i];
    // 讀取矩陣
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        cin >> adj[i][j];
    // 讀取起點
    int s;
    cin >> s;   

    // 初始化最小成本和路徑
    vector<int> minCost(n, INF);
    vector<vector<int>> paths(n); // 每個節點的最短路徑
    minCost[s] = 0;
    paths[s] = {s}; // 起點自己的路徑是自己

    vector<bool> visited(n, false);
    dfs(s, adj, weights, minCost, paths, visited, 0, {}, s);

    // 輸出結果
    for (int i = 0; i < n; ++i) {
      if (minCost[i] == INF)
        cout << "infinity" << " ";
      else {
        cout << minCost[i] << " ";
#if DEBUG
        cout << "Path: ";
        for (int j = 0; j < paths[i].size(); ++j) {
          cout << paths[i][j];
          if (j < paths[i].size() - 1)
            cout << " -> ";
        }
        cout << " -> " << i << endl;
#endif
      }
    }

    cout << endl;
  }

    return 0;
}
