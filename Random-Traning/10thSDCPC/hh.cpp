#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

struct node {
	int l, r;
	node(){}
	node(int l, int r):l(l), r(r){}
	bool operator < (const node &other) const {
		if (l == other.l) return r < other.r;
		else return l < other.l;
	}
}arr[maxn];

int n;

int main() {
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		int Min = 1e9 + 10;
		int Max = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d", &arr[i].l, &arr[i].r);
			Min = min(Min, arr[i].l);
			Max = max(Max, arr[i].r);
		}
		sort(arr + 1, arr + 1 + n);
		int ans = 0;
		priority_queue<int, vector<int>, greater<int> >q;
		int pos = 0;
		for (int i = Min; i <= Max; ++i) {
			while(pos <= n && arr[pos].l <= i) q.push(arr[pos++].r);
			while(!q.empty() && q.top() < i) q.pop();
			if(!q.empty()) {
				ans++;
				q.pop();
			}
			if(q.empty()) {
				if(pos > n) {
					break;
				}
				i = max(i, arr[pos].l - 1);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
