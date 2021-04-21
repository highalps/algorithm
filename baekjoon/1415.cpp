#include <stdio.h>
#include <string.h>
#include <vector>
#include <limits.h>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;
#define ll long long
const int MAX = 500000 + 1;
bool p[MAX] = { true,true,false, };
int cnt[10001];
ll dp[2][MAX];

int main()
{
	int s = 0, M = 0;
	for (int i = 2; i < MAX; i++) {
		if (p[i])continue;
		for (int j = 2; j*i < MAX; j++) {
			p[j*i] = true;
		}
	}
	int n;
	scanf("%d", &n);
	for (int i = 0, v; i < n; i++) {
		scanf("%d", &v);
		cnt[v]++; s += v; M = max(M, v);
	}
	bool tog = true;
	dp[tog][0] = cnt[0] + 1;
	for (int i = 1; i <= M; i++) {
		if (!cnt[i])continue;
		tog = !tog;
		memset(dp[tog], 0, sizeof(dp[tog]));
		for (int j = 0; j <= cnt[i]; j++) {
			for (int k = s; k >= i*j; k--) {
				if (k - i*j < 0)break;
				dp[tog][k] += dp[!tog][k - i*j];
			}
		}
	}
	ll R = 0;
	for (int i = 2; i <= s; i++) {
		if (!p[i])R += dp[tog][i];
	}
	printf("%lld\n", R);

}