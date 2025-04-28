/*
數字n來代表此圖總共有多少節點，並用n×n筆資料
來表示圖上各個節點之間是否存在一個共用邊(1代表有共用邊，0則代表無)，

題目: 找出最大節點數，所有節點無共用邊
*/
#include <iostream>
#include <vector>

using namespace std;

bool CheckPoint(const int node, vector<int> PointList, const vector<vector<int>> SourceList)
{
  for (int i = 0; i < PointList.size(); i++)
  {
    if (SourceList[node][PointList[i]] == 1 && SourceList[PointList[i]][node] == 1)
    {
      return false;
    }
  }

  return true;
}

void findMaxPoint(const int start, const int end, int *max, vector<int> *PointList, const vector<vector<int>> SourceList) {
  if (PointList->size() > *max) {
    *max = PointList->size();
  }

  // 做法: 從節點0 ~ n-1依序尋找，透過回朔(移除節點，添加下一個節點)來找出所有節點組合
  for (int i = start; i < end; i++) {
    if ( CheckPoint(i, *PointList, SourceList) ) {
      PointList->push_back(i);
      findMaxPoint(i + 1, end, max, PointList, SourceList); // 遞迴尋找，繼續往下找
      PointList->pop_back(); // 回溯，嘗試其他的節點組合
    }
  }
}

int main() {
  int n;
  vector<int> Source;   // one line (一維陣列)
  vector<vector<int>> SourceList; // all lines (二維陣列)

  cin >> n;
  while (n > 0)
  {
    // Inatialize
    Source.clear(); 
    SourceList.clear();

    // Read each line
    for (int i = 0; i < n; i++)
    {
      Source.clear();
      for (int j = 0; j < n; j++)
      {
        int temp;
        cin >> temp;
        Source.push_back(temp);
      }

      SourceList.push_back(Source);
    }

    #if 0
    // Debug print each line
    cout << "\n[DEBUG]" << endl;
    cout << "n: " << n << endl;
    cout << "SourceList: " << endl;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cout << SourceList[i][j] << " ";
      }
      cout << endl;
    }
    #endif

    int MaxPoint = 0;      // 紀錄最大節點數
    vector<int> PointList; // 緩存-紀錄節點 (無共用邊)
    PointList.clear();     // 清空

    findMaxPoint(0, n, &MaxPoint, &PointList, SourceList);

    cout << MaxPoint << endl;
    cin >> n;
  }

  system("pause");
  return 0;
}