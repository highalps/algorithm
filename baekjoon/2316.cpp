#include <stdio.h>

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define MAX 987654321

struct MF {
  int V, totalflow;
  vector<vector<int>> vec, flow, capacity;
  MF(int V) : V(V), totalflow(0) {
    vec = vector<vector<int>>(V);
    flow = capacity = vector<vector<int>>(V, vector<int>(V, 0));
  }
  void add_edge(int a, int b, int c) {
    vec[a].push_back(b);
    this->capacity[a][b] = c;
  }
  void execute(int S, int E) {
    vector<int> parent(V);
    while (1) {
      vector<bool> chk(V, false);
      queue<int> que;
      que.push(S);
      chk[S] = true;
      while (!que.empty() && !chk[E]) {
        int a = que.front();
        que.pop();
        for (int i = 0; i < vec[a].size(); i++) {
          int b = vec[a][i];
          if (!chk[b] && capacity[a][b] - flow[a][b] > 0) {
            chk[b] = true;
            parent[b] = a;
            que.push(b);
          }
        }
      }
      if (!chk[E]) break;
      totalflow++;
      for (int v = E; v != S; v = parent[v]) {
        flow[parent[v]][v]++;
        flow[v][parent[v]]--;
      }
    }
  }
};

int main() {
  int n, p;
  scanf("%d %d", &n, &p);
  MF mf(n * 2 + 2);
  for (int i = 0; i < n; i++) {
    mf.add_edge(i * 2, i * 2 + 1, i <= 1 ? MAX : 1);
  }
  for (int i = 0, a, b; i < p; i++) {
    scanf("%d %d", &a, &b);
    a--, b--;
    mf.add_edge(a * 2 + 1, b * 2, 1);
    mf.add_edge(b * 2, a * 2 + 1, 1);
  }
  mf.execute(0, 3);
  printf("%d\n", mf.totalflow);
}