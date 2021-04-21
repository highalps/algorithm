#include <stdio.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;
#define ll long long
const int MAX = 500000 * 4000 + 1;
vector <int> s, c, num;
vector <bool> _chk, chk;

struct edge {
	int v, c;
	bool operator<(const edge&A)const {
		return c > A.c;
	}
};
vector <int> dp;
vector <vector <int> >vec;
int start, p;
struct graph {

	vector < vector <int> > group, foward, back;
	vector <bool> visit;
	stack <int> stk;
	int n;
	graph(int v) :n(v) {}
	void init() {
		visit = vector <bool>(n + 1, false);
		foward = back = vector <vector <int> >(n + 1, vector <int>());
	}
	void add_edge(int a, int b) {
		foward[a].push_back(b);
		back[b].push_back(a);
	}
	void dfs(int v) {
		visit[v] = true;
		for (int i = 0; i < foward[v].size(); i++) {
			int u = foward[v][i];
			if (!visit[u])dfs(u);
		}
		stk.push(v);
	}
	void dfs_back(int v) {
		visit[v] = false;
		for (int i = 0; i < back[v].size(); i++) {
			int u = back[v][i];
			if (visit[u])dfs_back(u);
		}
		group[group.size() - 1].push_back(v);
		s[group.size() - 1] += c[v];
		num[v] = group.size() - 1;
		chk[num[v]] = chk[num[v]] | _chk[v];
	}
	void make()
	{
		for (int i = 1; i <= n; i++) {
			if (!visit[i])dfs(i);
		}

		while (!stk.empty()) {
			int v = stk.top(); stk.pop();
			if (visit[v]) {
				group.push_back(vector <int>());
				dfs_back(v);
			}
		}
		vec.resize(group.size());
		for (int v = 1; v <= n; v++) {
			for (int j = 0; j < foward[v].size(); j++) {
				int u = foward[v][j];
				if (num[v] == num[u])continue;
				vec[num[v]].push_back(num[u]);
			}
		}
	}
};

int dy(int v)
{
	int &ret = dp[v];
	if (ret != -1)return dp[v];
	ret = s[v];
	for (int i = 0; i < vec[v].size(); i++) {
		int u = vec[v][i];
		ret = max(ret, s[v] + dy(u));
	}
	if (ret == s[v])if (!chk[v])ret = -987654321;
	return ret;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	s = c = num = vector <int>(n + 2);
	_chk = chk = vector<bool>(n + 2, false);
	graph G(n);
	G.init();
	for (int i = 0, a, b; i < m; i++) {
		scanf("%d %d", &a, &b);
		G.add_edge(a, b);
	}
	for (int i = 1; i <= n; i++)scanf("%lld", &c[i]);
	scanf("%d %d", &start, &p);
	for (int i = 0, v; i < p; i++) {
		scanf("%d", &v); _chk[v] = true;
	}

	G.make();

	int V = G.group.size();
	dp = vector <int>(V, -1);
	printf("%d\n", dy(num[start]));
}