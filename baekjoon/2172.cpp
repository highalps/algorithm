#include <limits.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
#define ll long long

int dp[21][21][21][21][21];
int ar[21][21];
bool chk[21][21][21][21];
const int ud[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int lr[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int n;

int dy(int L, int a, int b, int x, int y) {
  if (L == 2) {
    if (a == x && b == y) return 0;
    if (abs(a - x) <= 1 && abs(b - y) <= 1)
      return 1;
    else
      return 0;
  }
  if (L == 1) {
    if (a == x && b == y)
      return 1;
    else
      return 0;
  }
  int &ret = dp[L][a][b][x][y];
  if (ret != -1) return ret;
  ret = 0;
  for (int q = 0; q < 8; q++) {
    int _a = a + ud[q], _b = b + lr[q];
    if (_a < 0 || _a >= n || _b < 0 || _b >= n) continue;
    for (int p = 0; p < 8; p++) {
      int _x = x + ud[p], _y = y + lr[p];
      if (_x < 0 || _x >= n || _y < 0 || _y >= n) continue;
      if (ar[_a][_b] == ar[_x][_y]) ret += dy(L - 2, _a, _b, _x, _y);
    }
  }
  return ret;
}

int main() {
  memset(dp, 0xff, sizeof(dp));
  int L;
  scanf("%d %d", &n, &L);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &ar[i][j]);
    }
  }
  int R = 0;
  for (int a = 0; a < n; a++) {
    for (int b = 0; b < n; b++) {
      for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
          if (ar[a][b] == ar[x][y]) R += dy(L, a, b, x, y);
        }
      }
    }
  }
  printf("%d\n", R);
}