#include <iostream>
#include <vector>
#include <algorithm>
#define INT_MAX 2147483647 // INT_MAX 的值（32-bit int)

using namespace std;

int n;
vector<vector<int>> graph;  // adjacency matrix
int min_branch = INT_MAX;

void dfs(int edges_used, vector<int> degree, vector<bool> visited_nodes) {
    // 生成樹的條件：已經使用的邊數等於 n - 1
    if (edges_used == n - 1) { 
        int branch_count = 0;

        // 計算目前分支節點數
        for (int i = 0; i < n; i++)
            if (degree[i] > 1) branch_count++;

        // 更新最小分支數
        min_branch = min(min_branch, branch_count);
        return;
    }

    // 找一條邊加入樹（u,v），條件是加入後不成環
    for (int u = 0; u < n; u++) {
        if (!visited_nodes[u]) continue; // 只從樹中已有節點出發擴展

        for (int v = 0; v < n; v++) {
            if (graph[u][v] == 1 && !visited_nodes[v]) {
                // 更新狀態
                visited_nodes[v] = true;
                degree[u]++;
                degree[v]++;
                
                // 如果目前分支節點數已經超過 min_branch，直接回溯，因不是最優解
                int branch_count = 0;
                for (int i = 0; i < n; i++)
                    if (degree[i] > 1) branch_count++;
                if (branch_count < min_branch) {
                    dfs(edges_used + 1, degree, visited_nodes);
                }

                // 回溯
                visited_nodes[v] = false;
                degree[u]--;
                degree[v]--;
            }
        }
    }
}

int main() {
    while (cin >> n && n > 0) {
        graph.assign(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> graph[i][j];

        // 初始化最小分支數(類無限)
        min_branch = INT_MAX;

        vector<bool> visited_nodes(n, false);
        vector<int> degree(n, 0);

        // 從每個節點嘗試起點
        for (int start = 0; start < n; start++) {
            // 設置起點前，初始化狀態(路徑、分支數)
            visited_nodes.assign(n, false);
            degree.assign(n, 0);
            visited_nodes[start] = true;

            dfs(0, degree, visited_nodes);
        }

        cout << min_branch << endl;
    }
    return 0;
}
