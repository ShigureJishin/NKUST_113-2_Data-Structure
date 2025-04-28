/*
請設計一程式，此程式可以不斷地輸入多組測試資料，每組測試資料為若干節點
的集合，各節點間以white space (空白字元)分隔，每組測試資料最後以”()”代
表該組測試資料的結束。此程式持續輸入資料直到測試資料不包括任何節點資料
為止(即只有”()”)。請根據各組測試資料判斷是否可以構成一棵二元樹，如果輸
入的各組測試資料可以構成一個二元樹的話，請輸出此二元樹後序走訪後的結
果，如果輸入的節點無法合理構成一個二元樹的話，請輸出wrong data。 

錯誤狀況包括：
1. 沒有根節點
2. 節點資料重複
3. 節點資料不合法(例如：L、R 以外字符)
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define DEBUG 0 // debug mode

using namespace std;

// 節點結構
struct Node {
  int data;         // 節點資料
  string direction; // 節點方向
  Node* left;      // 左子樹指標
  Node* right;     // 右子樹指標

  Node(int val, string dir) {
    // 建構子，初始化節點資料和左右子樹指標
    data = val;
    direction = dir;
    left = nullptr;
    right = nullptr;
  }
};

Node *findNode(Node *root, const string dir) {
  Node *tempNode = root; 

  // 0個字元，表示是根節點
  if (dir.length() == 0) { 
    return tempNode;
  }
  // 根據字元往下走訪
  for (int i = 0; i < dir.length(); i++) {
    if (dir[i] == 'L') {
      tempNode = tempNode->left;
    } else if (dir[i] == 'R') { 
      tempNode = tempNode->right;
    } else {
      return nullptr; // 如果不是L或R，則返回空指標
    }
  }

  return tempNode; // 返回找到的節點
}

void printPostorder(Node* root) {
  if (!root) return;

  printPostorder(root->left);  // 遞迴走訪左子樹
  printPostorder(root->right); // 遞迴走訪右子樹

  cout << root->data << " ";
}

bool isDuplicate(const string key, vector<string> strList) {
  for (int i = 0; i < strList.size(); i++) {
    if (strList[i] == key) {
      return true; // 找到重複資料
    }
  }
  return false; // 沒有重複資料
}

int main() {
  string input;      // 讀取一行資料的字串
  bool vaild = true; // 二元樹是否合法的標記
  vector<Node *> nodeList; // 節點的列表
  vector<string> nodeDirList; // 用來儲存節點方向的字串列表，用以確認重複資料
  Node* root = nullptr; // 根節點指標

  while (true)
  {
    // Inatialize
    vaild = true;
    input = "";
    nodeList.clear();
    nodeDirList.clear();
    root = nullptr;

    // 讀取一行資料
    getline(cin, input);  

    #if DEBUG
    cout << "input: " << input << endl; // debug
    #endif

    if (input == "()") break; // *結束程式 exit program

    Node *tempNode = nullptr; // 暫存節點指標
    stringstream ss(input);
    string nodeStr;

    // 讀取每個節點資料
    while (ss >> nodeStr) {
      if (nodeStr == "()") break; // 一組測試資料結尾

      // 1. 解析節點資料
      int data = stoi(nodeStr.substr(1, nodeStr.find(",") - 1)); // 取得節點資料
      string direction = nodeStr.substr(nodeStr.find(",") + 1, nodeStr.find(")") - nodeStr.find(",") - 1); // 取得方向字串

      // 2. 建立新節點
      tempNode = new Node(data, direction);
      nodeList.push_back(tempNode); // 將新節點加入節點列表

      // 3. 如果是否有重複的方向字串
      if (isDuplicate(direction, nodeDirList)) {
        vaild = false;
        break;
      }
      else {
        nodeDirList.push_back(direction); // 將方向字串加入列表
      }

      // 4. 是否根節點
      if (direction == "")
        root = tempNode; 
    }

    // *沒有根節點，跳過執行下一組
    if (root == nullptr || vaild == false) {
      cout << "wrong data" << endl;
      continue;
    }

    // (1) 依照字串長度整理，小到大排序
    for (int i = 0; i < nodeList.size(); i++) {
      for (int j = i + 1; j < nodeList.size(); j++) {
        if (nodeList[i]->direction.length() > nodeList[j]->direction.length()) {
          Node* temp = nodeList[i];
          nodeList[i] = nodeList[j];
          nodeList[j] = temp;
        }
      }
    }

    #if DEBUG
    cout << "nodeList size: " << nodeList.size() << endl;
    cout << "nodeList: ";
    for (int i = 0; i < nodeList.size(); i++) {
      cout << nodeList[i]->data << " ";
    }
    cout << endl;
    #endif

    // 依照方向字串長度來建立二元樹
    for (int i = 0; i < nodeList.size(); i++) {
      if (nodeList[i]->direction.length() == 0) {
        // 如果方向字串長度為0，表示是根節點，則跳過
        continue;
      }
      // 取得左右子樹的節點指標
      tempNode = findNode(root, nodeList[i]->direction.substr(0, nodeList[i]->direction.length() - 1));

      // 根據最後一個字元決定是左子樹還是右子樹, 空指標表示不合法
      if (tempNode == nullptr) {
        vaild = false; // 樹不合法
        cout << "wrong data" << endl;
        break;
      }
      else if (nodeList[i]->direction.back() == 'L') {
        tempNode->left = nodeList[i];
      } else if (nodeList[i]->direction.back() == 'R') {
        tempNode->right = nodeList[i];
      }
    }

    if (!vaild) {
      continue; // 樹不合法，跳過執行下一組
    }

    // 後序走訪並輸出結果
    printPostorder(root);
    cout << endl;
  }

  system("pause");
  return 0;
}