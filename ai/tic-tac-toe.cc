#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int dfs(int d, char player, vector<string> &a, int &x, int &y)
{
  static const int dx[] = {1,1,1,0,0,0,2,2,2};
  static const int dy[] = {1,0,2,1,0,2,1,0,2};
  int xx, yy, ret = -2, optx = -1, opty = -1;
  REP(k, 9) {
    int i = dx[k], j = dy[k];
    if (a[i][j] == '_') {
      x = i;
      y = j;
      a[i][j] = player;
      if (a[i][0] == a[i][1] && a[i][1] == a[i][2] ||
          a[0][j] == a[1][j] && a[1][j] == a[2][j] ||
          i == j && a[0][0] == a[1][1] && a[1][1] == a[2][2] ||
          i == 2-j && a[0][2] == a[1][1] && a[1][1] == a[2][0])
        ret = 1, optx = i, opty = j;
      int t = - dfs(d+1, 'O'^'X'^player, a, xx, yy);
      if (t > ret)
        ret = t, optx = i, opty = j;
      a[i][j] = '_';
    }
  }
  if (ret == -2)
    ret = 0;
  if (~ optx)
    x = optx, y = opty;
  return ret;
}

int main()
{
  char player;
  vector<string> board;

  //If player is X, I'm the first player.
  //If player is O, I'm the second player.
  cin >> player;

  //Read the board now. The board is a 3x3 array filled with X, O or _.
  for(int i=0; i<3; i++) {
    string s; cin >> s;
    board.push_back(s);
  }

  int x, y;
  dfs(0, player, board, x, y);
  cout << x << ' ' << y << endl;
}
