/*
8462
Sqrt decomposition, Mo's algorithm
http://highalps.tistory.com/11
*/

#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <stdlib.h>
using namespace std;
#define ll long long
int h;
struct dot {
	int l, r,id;
	bool operator<(const dot&A)const {
		return l / h == A.l / h ? r < A.r : l / h < A.l / h;
	}
}query[100001];
ll res[100001];
int cnt[1000001];
ll move(int t, int val) { cnt[val] += t; return ((ll)2 * (ll)t*(ll)cnt[val] - 1)*(ll)val; }
int main()
{
	int n, k, l, r;
	scanf("%d %d", &n, &k);
	h = sqrt(n);
	vector <ll>a(n + 1,0);
	for (int i = 1; i <= n; i++)scanf("%lld", &a[i]);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &query[i].l, &query[i].r);
		query[i].id = i;
	}sort(query, query + k);

	ll sum = 0;
	l = query[0].l, r = query[0].r;
	for (int i = l; i <= r; i++)sum += move(1, a[i]);
	res[query[0].id] = sum;

	for (int i = 1; i < k; i++)
	{
		while (l > query[i].l)sum += move(1, a[--l]);
		while (l < query[i].l)sum += move(-1, a[l++]);
		while (r > query[i].r)sum += move(-1, a[r--]);
		while (r < query[i].r)sum += move(1, a[++r]);
		res[query[i].id] = sum;
	}
	for (int i = 0; i < k; i++)printf("%lld\n", res[i]);
	return 0;
}