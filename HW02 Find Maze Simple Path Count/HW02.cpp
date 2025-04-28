/*
請根據所輸入的迷宮內容(包括迷宮層數、大小、迷宮圖、一起始點以及一終點)，
請顯示所有有可能的路徑(simple paths)數目(可往上、下、左或右方向走訪，以
及往上下層移動)，此程式需能不斷輸入迷宮內容，並顯示其所有有可能的路徑
數目，直到輸入的迷宮大小邊長小於或等於0。 
PS. Simple path為一路徑，且路徑中的節點不會重複。
*/
#include <iostream>
#include <vector>

using namespace std;

struct Point {
  int x;
  int y;
  int z;
};

enum PointType {
  VALID,        // 有效的座標
  START,        // 起點
  WALL,         // 是牆壁
  ENDPOINT,     // 終點
  VISITED,      // 已經走過的座標
  OUT_OF_BOUNDS // 超出邊界
};

enum Direction {
  NONE, // 無方向
  UP,
  DOWN,
  LEFT,
  RIGHT,
  FORWARD,
  BACKWARD
};

PointType CheckNextPoint(const int x, const int y, const int z, const vector<Point> PointList, const vector<vector<vector<int>>> Map)
{
  int zSize = Map.size();
  int ySize = Map[0].size();
  int xSize = Map[0][0].size();

  if (x < 0 || x >= xSize || y < 0 || y >= ySize || z < 0 || z >= zSize)
    return OUT_OF_BOUNDS;
  else if (Map[z][y][x] == 3)
    return ENDPOINT;
  else if (Map[z][y][x] == 1)
    return WALL;
  else
    for (int i = 0; i < PointList.size(); i++) {
      if (PointList[i].x == x && PointList[i].y == y && PointList[i].z == z)
        return VISITED;
    }

  return VALID;
}

void findMaxPath(const int x, const int y, const int z,const Direction from, int *max, vector<Point> *PointList, const vector<vector<vector<int>>> Map) {
  // Point 檢查
  if (from != NONE) {

    PointType status = CheckNextPoint(x, y, z, *PointList, Map);

    #if 0
    cout << "x: " << x << ", y: " << y << ", z: " << z << endl;
    cout << "status: " << status << endl;
    #endif

    if (status == OUT_OF_BOUNDS || status == WALL || status == VISITED)
      return;
    else if (status == ENDPOINT) {
      *max += 1;
      return;
    }
  }

  #if 0
  // Debug print each line
  cout << "\n[DEBUG]" << endl;
  cout << "PointList size: " << PointList->size() << endl;
  cout << "PointList: " << endl;
  for (int i = 0; i < PointList->size(); i++) {
    cout << PointList->at(i).x << ", " << PointList->at(i).y << ", " << PointList->at(i).z << endl;
  }
  cout << "x: " << x << ", y: " << y << ", z: " << z << endl;
  cout << "from: " << from << endl;
  #endif

  // 有效座標，記錄當前座標
  Point tempP;
  tempP.x = x;
  tempP.y = y;
  tempP.z = z;
  PointList->push_back(tempP);
 
  // 往上、下、左、右、前、後走訪
  findMaxPath(x + 1, y, z, LEFT, max, PointList, Map); 
  findMaxPath(x - 1, y, z, RIGHT, max, PointList, Map);
  findMaxPath(x, y + 1, z, BACKWARD, max, PointList, Map);
  findMaxPath(x, y - 1, z, FORWARD, max, PointList, Map);
  findMaxPath(x, y, z + 1, DOWN, max, PointList, Map);
  findMaxPath(x, y, z - 1, UP, max, PointList, Map);

  PointList->pop_back();
}

int main() {
  int mazeLayer, mazeRow, mazeCol;  // 迷宮的層數、行數、列數
  int startLayer, startRow, startCol; // 起始點
  int endLayer, endRow, endCol;     // 終點
  vector<int> Source;               // one line (一維陣列, 存放迷宮的一行)
  vector<vector<int>> SourceList;   // 2D array (二維陣列, 存放迷宮的一層)
  vector<vector<vector<int>>> Map;  // 3D array (三維陣列, 存放迷宮)

  while (true)
  {
    // Inatialize
    Source.clear(); 
    SourceList.clear();
    Map.clear();

    // Input Maze Size
    cin >> mazeLayer >> mazeRow >> mazeCol;
    if (mazeLayer <= 0 || mazeRow <= 0 || mazeCol <= 0) 
      break;
    
    // Input Maze
    for (int z = 0; z < mazeLayer; z++)
    {
      SourceList.clear();
      for (int y = 0; y < mazeRow; y++)
      {
        Source.clear();
        for (int x = 0; x < mazeCol; x++)
        {
          int temp;
          cin >> temp;
          Source.push_back(temp);
        }
        SourceList.push_back(Source);
      }
      Map.push_back(SourceList);
    }
      
    // Input Start Point
    cin >> startLayer >> startRow >> startCol;
    startLayer--;
    Map[startLayer][startRow][startCol] = 2;

    // Input End Point
    cin >> endLayer >> endRow >> endCol;
    endLayer--;
    Map[endLayer][endRow][endCol] = 3;

    #if 0
    // Debug print each line
    cout << "\n[DEBUG]" << endl;
    cout << "Start Point: " << startLayer << ", " << startRow << ", " << startCol << endl;
    cout << "End Point: " << endLayer << ", " << endRow << ", " << endCol << endl;
    cout << "mazeLayer: " << mazeLayer << ", mazeRow: " << mazeRow << ", mazeCol: " << mazeCol << endl;
    cout << "Map size: " << Map.size() << endl;
    cout << "Map:" << endl;
    for (int z = 0; z < mazeLayer; z++)
    {
      for (int y = 0; y < mazeRow; y++)
      {
        for (int x = 0; x < mazeCol; x++)
        {
          cout << Map[z][y][x] << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
    #endif

    int maxPath = 0;      // 紀錄最大路徑
    vector<Point> PointList; // 紀錄路徑
    PointList.clear();   // 清空路徑

    // 將起始點加入路徑
    Point tempP;
    tempP.x = startCol;
    tempP.y = startRow;
    tempP.z = startLayer;
    PointList.push_back(tempP); 

    findMaxPath(startCol, startRow, startLayer, NONE, &maxPath, &PointList, Map);
    cout << maxPath << endl;
  }

  system("pause");
  return 0;
}