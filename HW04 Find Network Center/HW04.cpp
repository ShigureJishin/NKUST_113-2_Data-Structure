/*
請設計一程式，此程式可以不斷地輸入一網路資訊，在此我們使用網路節點個數n 以及一圖 G(V,E)來代表一個網路，
此圖 G(V,E)使用 adjacency matrix 來表示，當輸入的網路節點個數n≦0時則程式結束。
圖上的節點 u ∈ V 代表網路節點u，
圖上的線 u, v 則代表節點 u 與節點 v 之間可互相溝通，
節點 u 到節點 v 的躍距數(以 hopu, v 來表示之)在此定義為圖上節點 u至少需要經過多少條線才可到達節點 v 。
對每一個節點 u 而言，此節點 u 到網路中其他節點 v 的
最長躍距數可以用maxhop(u, v)來表示，當一個節點 x 被稱作是網路中心時，
此 節 點 的 maxhop(x, v) 要 小 於 或 等 於 其 他 節 點 y 的 maxhop(y, v) ， 
即maxhop(x, v) ≦ maxhop(y, v) for all y ∈ V。若輸入的網路為一連通網路時，
請印出此圖的網路中心節點(可能不只一個點，請依照節點編號由小到大排好)，
若輸入的網路不是一個連通網路時(即對於網路中任兩個節點 u, v 而言，兩節點
之間不存在一連通路徑)，請印出”disconnected”。

最優的中心包括：
1. 所有等距
2. 最小 hop 數
*/
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#define DEBUG 1 // debug mode

using namespace std;

// 節點結構
struct Node {
  int num;       // 節點編號
  int maxHop;    // 該節點到其他所有節點的最長 hop 數（最少要經過幾條邊）

  Node(int val) {
    num = val;  // 設定節點編號
    maxHop = 0; // 初始化最長 hop 數為0 
  }
};

void bfsHopMatrix(const vector<vector<int>>& graph, vector<vector<int>>& hop) {
    int n = graph.size();
    
    // 初始化 hop 矩陣
    hop.assign(n, vector<int>(n, -1));

    // 自己到自己的 hop 數為0
    for (int i = 0; i < n; ++i) {
        hop[i][i] = 0; 
    }

    // 從 0 到 n-1 的每個節點進行躍遷數計數
    for (int src = 0; src < n; ++src) {
        vector<int> q;                  // 暫存路徑
        vector<bool> visited(n, false); // 訪問旗標
        visited[src] = true;            // 標記起點已訪問
        q.push_back(src);

        while (!q.empty()) {
            int u = q.front();
            q.erase(q.begin()); // 模擬 pop()

            // 每當發現一個未拜訪的相鄰節點 v，
            // 就設定 hop[src][v] = hop[src][u] + 1，代表 v 是從 u 走一步來的。
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] && !visited[v]) {
                    visited[v] = true;
                    hop[src][v] = hop[src][u] + 1; 
                    q.push_back(v);
                }
            }
        }
    }
}

// 檢查是否為連通圖
bool isConnected(const vector<vector<int>>& hop) {
    int n = hop.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (hop[i][j] == -1)
                return false;
    return true;
}

int main() {
    int n;
    while (cin >> n && n > 0) {
        // 讀取網路節點數量
        vector<vector<int>> network(n, vector<int>(n, 0));

        // 讀取網路節點矩陣
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> network[i][j];

        
        vector<vector<int>> hop;
        bfsHopMatrix(network, hop);

         if (!isConnected(hop)) {
            cout << "disconnected" << endl;
            continue;
        }

        // 初始化每個節點
        vector<Node> nodes;
        for (int i = 0; i < n; ++i)
            nodes.push_back(Node(i));

        // 找出每個節點的最遠節點的 hop 數
        for (int i = 0; i < n; ++i) {
            int maxH = 0;
            for (int j = 0; j < n; ++j)
                maxH = max(maxH, hop[i][j]);
            nodes[i].maxHop = maxH;
        }

        // 找出最小 maxHop
        int minHop = nodes[0].maxHop; // 假設第一個節點的 maxHop 數是最小
        for (int i = 1; i < n; ++i)
            minHop = min(minHop, nodes[i].maxHop); // 找到最小的 maxHop 數

        // 找出中心節點，(minHop 是最小的 maxHop 數)
        vector<int> centers;
        for (int i = 0; i < n; ++i)
            if (nodes[i].maxHop == minHop)
                centers.push_back(nodes[i].num);

        // 輸出中心節點
        for (int i = 0; i < centers.size(); ++i) {
            if (i > 0) cout << " ";
            cout << centers[i];
        }

        cout << endl;
        network.clear(); // 清除網路矩陣
        hop.clear();     // 清除 hop 矩陣
    }
    return 0;
}