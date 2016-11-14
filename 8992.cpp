#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <math.h>
#include <queue>
#include <memory.h>
#include <set>
using namespace std;
#define ll long long
#define MAX 987654321
int mf, mc;
struct MCMF
{
	int totalflow, totalcost, V;
	vector <vector <int> > flow, vec, capacity, cost;
	MCMF(int n) : V(n), totalcost(0), totalflow(0)
	{
		capacity = cost = flow = vector<vector <int> >(V, vector<int>(V, 0));
		vec = vector <vector <int> >(n);
	}

	void addedge(int a, int b, int co, int cap)
	{
		vec[a].push_back(b);
		this->cost[a][b] = co;
		this->capacity[a][b] = cap;
	}

	int excute(int S, int E)
	{
		int a, b;
		vector <int> dist(V, MAX);
		vector <int> parent(V, -1);
		vector <bool> chk(V, false);
		queue <int> que;
		dist[S] = 0;
		que.push(S);
		while (!que.empty())
		{
			a = que.front(); que.pop();
			chk[a] = false;
			for (int i = 0; i < vec[a].size(); i++)
			{
				b = vec[a][i];
				if (capacity[a][b] - flow[a][b] > 0 && (dist[b] >= MAX || dist[b] > dist[a] + cost[a][b]))
				{
					dist[b] = dist[a] + cost[a][b];
					parent[b] = a;
					if (!chk[b])
					{
						chk[b] = true;
						que.push(b);
					}
				}

			}
		}
		if (dist[E] < MAX)
		{
			// if (dist[E] > 0)return MAX;
			totalcost += dist[E];
			totalflow++;
			for (int v = E; v != S; v = parent[v])
			{
				flow[parent[v]][v] += 1;
				flow[v][parent[v]] -= 1;
			}
		}
		return dist[E];
	}
};
struct dot {
	int a, b, c, d, cost;
	dot() {}
	dot(int a, int  b, int c, int d, int cost) :a(a), b(b), c(c), d(d), cost(cost) {}
};

int main()
{
	int t, n, m;
	scanf("%d", &t);
	while (t--)
	{
		int a, b, c, d, e;
		scanf("%d %d", &n, &m);
		vector <dot> R, C;
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
			if (c < a)swap(a, c);
			R.emplace_back(a, b, c, d, e);
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
			if (d < b)swap(b, d);
			C.emplace_back(a, b, c, d, e);
		}
		MCMF mcmf(n + m + 2);
		int S = 0, E = n + m + 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (R[i].a <= C[j].a && C[j].a <= R[i].c && C[j].b <= R[i].b && R[i].b <= C[j].d) {
					mcmf.addedge(i + 1, n + j + 1, -R[i].cost*C[j].cost, 1);
					mcmf.addedge(n + j + 1, i + 1, R[i].cost*C[j].cost, 0);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			mcmf.addedge(S, i + 1, 0, 1);
			mcmf.addedge(i + 1, S, 0, 0);
		}
		for (int i = 0; i < m; i++) {
			mcmf.addedge(n + i + 1, E, 0, 1);
			mcmf.addedge(E, n + i + 1, 0, 0);
		}
		while (mcmf.excute(S, E) < MAX) {}
		printf("%d %d\n", mcmf.totalflow, -mcmf.totalcost);
	}
}