#include <stdio.h>
#include <string.h>
#include <vector>
#include <limits.h>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <memory.h>
using namespace std;
#define ll long long

int a[2][41];
ll dp[2][801][801];
const int w = 400;
bool tog;
int main()
{
	int n;
	int as = 0, _as = 0, bs = 0, _bs = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a[0][i], &a[1][i]);
		if (a[0][i] >= 0)as += a[0][i];
		else _as -= a[0][i];
		if (a[1][i] >= 0)bs += a[1][i];
		else _bs -= a[1][i];
	}
	dp[tog][w][w] = 1;
	for (int k = 0; k < n; k++) {
		tog = !tog;
		memset(dp[tog], 0, sizeof(dp[tog]));
		for (int i = w + as; i >= w - _as; i--) {
			for (int j = w + bs; j >= w - _bs; j--) {
				dp[tog][i][j] += dp[!tog][i - a[0][k]][j - a[1][k]] + dp[!tog][i][j];
			}
		}
	}
	printf("%lld\n", dp[tog][w][w] - 1);
}