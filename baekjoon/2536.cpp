#include <stdio.h>
#include <algorithm>
#include <memory.h>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
#define ll long long
struct edge {
	ll ax, ay, bx, by;
};
struct dot {
	ll x, y;
};
ll ccw(dot A, dot B, dot C) {
	return (A.x*B.y + B.x*C.y + C.x*A.y) - (A.y*B.x + B.y*C.x + C.y*A.x);
}
bool isintersect(edge A, edge B) {
	dot a = { A.ax,A.ay }, b = { A.bx,A.by }, c = { B.ax,B.ay }, d = { B.bx,B.by };
	if (ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c,d,a) * ccw(c,d,b) <= 0)return true;
	else return false;
}
int main()
{
	int n, m, k;
	ll ax, ay, bx, by, q, sx, sy, ex, ey;
	scanf("%d %d", &n, &m);
	scanf("%d", &k);
	vector <edge> A;
	for (int i = 0; i < k; i++) {
		scanf("%lld %lld %lld %lld %lld", &q, &ax, &ay, &bx, &by);
		if (ax > bx)swap(ax, bx);
		if (ay > by)swap(ay, by);
		A.push_back({ ax,ay,bx,by });
		
	}
	scanf("%lld %lld %lld %lld", &sx, &sy, &ex, &ey);
	vector <vector <int> >vec(A.size() + 1);
	vector <bool> chk(A.size() + 1, false);
	for (int i = 0; i < A.size()-1; i++) {
		for (int j = i + 1; j < A.size(); j++) {
			if (A[i].ax == A[i].bx && A[j].ax == A[j].bx) {
				if (A[i].by < A[j].ay || A[j].by < A[i].ay)continue;
				if (A[i].ay <= A[j].ay && A[j].by <= A[i].by)continue;
				if (A[j].ay <= A[i].ay && A[i].by <= A[j].by)continue;
			}
			if (A[i].ay == A[i].by && A[j].ay == A[j].by) {
				if (A[i].bx < A[j].ax || A[j].bx < A[i].ax)continue;
				if (A[i].ax <= A[j].ax && A[j].bx <= A[i].bx)continue;
				if (A[j].ax <= A[i].ax && A[i].bx <= A[j].bx)continue;
			}
			if (isintersect(A[i], A[j])) {
				vec[i].push_back(j);
				vec[j].push_back(i);
			}
		}
	}
	queue <dot> que;
	vector <bool> ter(A.size()+1, false);
	vector <int> dist(A.size() + 1, -1);
	for (int i = 0; i < A.size(); i++) {
		if (A[i].ax <= sx && sx <= A[i].bx && A[i].ay <= sy && sy <= A[i].by) {
			dist[i] = 0;
			que.push({ i,0 });
			chk[i] = true;
		}
		if (A[i].ax <= ex && ex <= A[i].bx && A[i].ay <= ey && ey <= A[i].by)ter[i] = true;
	}

	while (!que.empty()) {
		dot a = que.front(); que.pop();
		for (int i = 0; i < vec[a.x].size(); i++) {
			int b = vec[a.x][i];
			if (chk[b])continue;
			if (dist[b] == -1 || dist[b] > dist[a.x] + 1) {
				dist[b] = dist[a.x] + 1;
				que.push({ b,dist[b] });
				chk[b] = true;
			}
		}
	}
	int answer = 5001;
	for (int i = 0; i < ter.size(); i++) {
		if (ter[i])answer = min(answer, dist[i]);
	}
	printf("%d\n", answer + 1);
}


