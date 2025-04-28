#include <iostream>
#include <vector>
#define DEBUG 0

using namespace std;

struct Point {
    int z, y, x;
};

// 迷宮
vector<vector<vector<int>>> input;
int X, Y, Z;
int startZ, startY, startX, endZ, endY, endX;

// 6 個移動方向
Point directions[6] = {
    {0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}
};

vector<Point> path; // 當前路徑
vector<vector<Point>> allPaths; // 所有找到的路徑


#if DEBUG
void delay_ms(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000))
        ;
}

void printMaze(int z, int y, int x)
{
    cout << "\033[2J\033[H"; // 清空畫面 (適用於 Windows / Linux / macOS)

    for (int layer = 0; layer < Z; layer++)
    {
        cout << "Layer " << layer << ":\n";
        for (int row = 0; row < Y; row++)
        {
            for (int col = 0; col < X; col++)
            {
                if (layer == z && row == y && col == x)
                    cout << "P "; // 目前位置
                else if (layer == endZ && row == endY && col == endX)
                    cout << "E "; // end
                else if (input[layer][row][col] == 5)
                    cout << "- "; // 回溯點
                // else if (input[layer][row][col] == 3)
                //   cout << ". "; // 可走的路
                else if (input[layer][row][col] == 0)
                    cout << "# "; // 路
                else if (input[layer][row][col] == 7)
                    cout << "* "; // 探索中
                else
                    cout << "? "; // 其他未知
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << "Current Position: (" << z << ", " << y << ", " << x << ")\n";
    delay_ms(20); // 延遲 200 毫秒
}
#endif // DEBUG

void findPaths(int z, int y, int x) {
    // 超出邊界或遇到障礙物，返回
    if (z < 0 || z >= Z || y < 0 || y >= Y || x < 0 || x >= X || input[z][y][x] != 0)
        return;

    // 記錄當前節點
    path.push_back({ z, y, x });
    input[z][y][x] = 7; // 標記為已訪問

    // 如果到達終點，記錄路徑
    if (z == endZ && y == endY && x == endX) {
        allPaths.push_back(path);
#if DEBUG
       cout << "Found path: ";
        for (const auto& p : path) {
            cout << "(" << p.z << ", " << p.y << ", " << p.x << ") ";
        }
        cout << endl;
#endif // DEBUG
    }
    else {
        // 嘗試所有方向
        for (const auto& dir : directions) {
            findPaths(z + dir.z, y + dir.y, x + dir.x);

#if DEBUG
            printMaze(z, y, x);
#endif
        }
    }

    // 回溯：移除當前節點並恢復迷宮狀態
    path.pop_back();
    input[z][y][x] = 0;
}

int main() {
    while (1){
        input.clear();
        path.clear();
        allPaths.clear();

#if DEBUG
        cout << "Enter maze dimensions (Z Y X): ";
#endif
        
        cin >> Z >> Y >> X;

        input.resize(Z, vector<vector<int>>(Y, vector<int>(X)));

        if (X <= 0 || Y <= 0 || Z <= 0)
            break;

#if DEBUG
        cout << "Enter maze data:\n";
#endif
        
        for (int z = 0; z < Z; z++) {
            for (int y = 0; y < Y; y++) {
                for (int x = 0; x < X; x++) {
                    cin >> input[z][y][x];
                }
            }
        }

#if DEBUG
        cout << "Enter start position (Z Y X): ";
#endif
        cin >> startZ >> startY >> startX;
        startZ--;

#if DEBUG
        cout << "Enter end position (Z Y X): ";
#endif
        cin >> endZ >> endY >> endX;
        endZ--;

#if DEBUG
        cout << "Finding all paths...\n";
#endif      
        findPaths(startZ, startY, startX);

#if DEBUG
        if (allPaths.empty()) {
            cout << "No path found.\n";
        }
        else {
            cout << "Total paths found: " << allPaths.size() << endl;
        }
#endif
        cout << allPaths.size() << endl;

    }

    return 0;
}