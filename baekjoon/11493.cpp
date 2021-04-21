#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define MAX 987654321
vector <vector <int> > ary;
vector <int> temp;
vector <vector <int> >adj;
int MIN(int a, int b)
{
	return a < b ? a : b;
}
struct MCMF
{
	int totalflow, totalcost, V;
	vector <vector <int> > vec, flow, capacity, cost;
	MCMF(int v) : V(v), totalflow(0), totalcost(0)
	{
		flow = capacity = cost = vector <vector <int> >(V, vector<int>(V, 0));
		vec = vector<vector <int> >(V);
	}
	void add_edge(int a, int b, int cap, int co)
	{
		vec[a].push_back(b);
		this->capacity[a][b] = cap;
		this->cost[a][b] = co;
	}
	void matching(int S, int E, int n) // �÷��̵�-���ȷ� �Ÿ� ���
	{
		for (int i = 1; i <= n; i++)adj[i][i] = 0;

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					adj[i][j] = MIN(adj[i][j], adj[i][k] + adj[k][j]);

		for (int i = 0; i < vec[S].size(); i++)
		{
			int u = vec[S][i];
			for (int j = 0; j < temp.size(); j++)
			{
				int v = temp[j];
				add_edge(u, v, 1, adj[u][v - n]);
				add_edge(v, u, 0, -adj[u][v - n]);
			}
		}


	}
	int excute(int S, int E) // SPFA algorithm
	{
		int a, b;
		vector <int> dist(V, MAX);
		vector <int> parent(V, -1);
		vector <bool> chk(V, false);
		queue <int> que;
		que.push(S);
		dist[S] = 0;
		while (!que.empty())
		{
			a = que.front(); que.pop();
			chk[a] = false;
			for (int i = 0; i < vec[a].size(); i++)
			{
				b = vec[a][i];
				if (capacity[a][b] - flow[a][b] > 0 && (dist[b] >= MAX || dist[b] > dist[a] + cost[a][b]))
				{
					parent[b] = a;
					dist[b] = dist[a] + cost[a][b];
					if (!chk[b]) {
						chk[b] = true;
						que.push(b);
					}
				}
			}
		}//while
		if (dist[E] < MAX)
		{
			totalflow++;
			totalcost += dist[E];
			for (int v = E; v != S; v = parent[v])
			{
				flow[parent[v]][v] += 1;
				flow[v][parent[v]] -= 1;
			}
		}
		return dist[E];
	}
};

int main()
{
	int t, n, m, S, E;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		ary = vector <vector <int> >(n + 1);
		adj = vector <vector <int> >(n + 1, vector<int>(n + 1, MAX));
		temp = vector <int>();
		for (int i = 0, a, b; i < m; i++)
		{
			scanf("%d %d", &a, &b);
			ary[a].push_back(b);
			ary[b].push_back(a);
			adj[a][b] = 1;
			adj[b][a] = 1;
		}
		S = 0, E = 2 * n + 1;
		MCMF mcmf(2 * n + 2);
		for (int i = 1, v; i <= n; i++)
		{
			scanf("%d", &v);
			if (v) {
				mcmf.add_edge(i + n, E, 1, 0); // ������ ��ũ����
				temp.push_back(i + n);
			}

		}
		for (int i = 1, v; i <= n; i++)
		{
			scanf("%d", &v);
			if (v) {
				mcmf.add_edge(S, i, 1, 0); // �ҽ��� ���ο���
			}
		}
		mcmf.matching(S, E, n);

		while (mcmf.excute(S, E) < MAX) {}
		printf("%d\n", mcmf.totalcost);
	}
	return 0;

}