#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "random.hpp"
using namespace std;
using Random = effolkronium::random_static;
void guide() {
  int m = 6;
  cout << "-------------\n";
  for (int i = 0; i < 3; i++) {
    cout << "| ";
    for (int j = 1; j <= 3; j++) {
      cout << j + m << " | ";
    }
    cout << "\n-------------\n";
    m -= 3;
  }
} 
void display(vector<char> &board) {
  int m = 6;
  system("CLS");
  cout << "-------------\n";
  for (int i = 0; i < 3; i++) {
    cout << "| ";
    for (int j = 0; j < 3; j++) {
      cout << board[j + m] << " | ";
    }
    cout << "\n-------------\n";
    m -= 3;
  }
}
bool whoGoesFirst() {  
    return (Random::get<bool>());
}
bool chkspace(vector<int> op, int choice) {
  if (find(op.begin(), op.end(), choice) != op.end()) return true;
  else return false;
}
void player(vector<int> &op, vector<char> &board) {
p_select:
  cout << "\nPlease select an open space: ";
  for (auto &i : op) cout << i << " ";
  cout << endl;
  int ps{};
  cin >> ps;
  if (chkspace(op, ps)) {
    board[ps - 1] = 'X';
    auto it = find(op.begin(), op.end(), ps);
    int idx = distance(op.begin(), it);
    op.erase(op.begin() + idx);
  }
  else if (!chkspace(op, ps)) { 
    cout << "Invalid. Try again." << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    goto p_select;
  }
}
void cpu(vector<int> &op, vector<char> &board) {
  srand(time(0));
  int cpu_s = rand() % (op.size());
  int Cs = op[cpu_s];
  board[Cs - 1] = 'O';
  auto it = find(op.begin(), op.end(), Cs);
  int idx = distance(op.begin(), it);
  op.erase(op.begin() + idx);
}
bool checkWin(vector<char> &v, char a) {  
  const int win[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6} 
  };
  for (auto &i: win) {  
    if (v[i[0]] == a && v[i[1]] == a && v[i[2]] == a) 
      return true;  
  }
  return false;
}
bool won(vector<char> &v) {
  if (checkWin(v, 'X')) {
    cout << "\nYou win!" << endl;
    return false;  
  } else if (checkWin(v, 'O')) {
    cout << "\nComputer wins!" << endl;
    return false;  
  }
  return true;
}
void player_vs_cpu() { 
  while (true) {
    vector<int> op = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<char> board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    display(board);
    switch (whoGoesFirst()) {
    case 0:
      while (won(board) && op.size() != 0){ 
        display(board);
        cout << "You go first." << endl;
        player(op, board);
        if (won(board) && op.size() != 0)
          cpu(op, board);
        else break;
      }
      break;
    case 1:
        while (won(board) && op.size() != 0){ 
        cpu(op, board);
        display(board);
        cout << "Computer goes first." << endl;
        if (won(board) && op.size() != 0)
          player(op, board);
        else break;
      }
      break;
    }
    display(board);
    won(board);
    if (op.size() == 0) cout << "\nTie!" << endl; 
      cout << "Play again? (y/n): ";
      char retry{};
      cin >> retry;
      if (retry == 'y'){}
      else break;
  }  
  cout << "Thanks for playing!" << endl;
}
int main() {
  cout << "========= Tic Tac Toe! =========\n";
  guide();
  cout << "Press Any Button To Start!\n";
  string t; cin >> t;
  player_vs_cpu();
}