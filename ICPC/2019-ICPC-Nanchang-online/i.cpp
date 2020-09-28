#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, m, a[N], b[N];
ll f[N], g[N];  
ll sum[N];  
int Sta[N], top;
ll h[N];

ll work1() { 
	b[m + 1] = -INF;
	b[0] = -INF;
	sum[0] = 0;
	for (int i = 1; i <= m; ++i) {
		sum[i] = sum[i - 1] + b[i];
	}
	top = 0; 
	Sta[++top] = 0; 
	h[0] = sum[0];
	for (int i = 1; i <= m; ++i) {
		while (top && b[i] <= b[Sta[top]]) {    
			top--;  
		}
		h[Sta[top]] = min(h[Sta[top]], sum[i]);   
		f[i] = h[Sta[top]];
		Sta[++top] = i;
		h[i] = sum[i]; 
	}	
	top = 0;
	Sta[++top] = m + 1;
	h[m + 1] = sum[m]; 
	for (int i = m; i >= 1; --i) {
		while (top && b[i] <= b[Sta[top]]) {
			top--; 
		}
		h[Sta[top]] = max(h[Sta[top]], sum[i]);
		g[i] = h[Sta[top]];
		Sta[++top] = i;
		h[i] = sum[i - 1];   
	}
	ll res = 0;
	for (int i = 1; i <= m; ++i) {
		res = max(res, (g[i] - f[i]) * b[i]);     
	}
	return res;
}


ll work2() {
	b[m + 1] = -INF;
	b[0] = -INF; 
	sum[0] = 0;
	for (int i = 1; i <= m; ++i) {
		sum[i] = sum[i - 1] + b[i];
	}
	top = 0; 
	Sta[++top] = 0;    
	h[0] = sum[0]; 
	for (int i = 1; i <= m; ++i) {   
		while (top && b[i] <= b[Sta[top]]) {    
			top--;  
		}
		h[Sta[top]] = max(h[Sta[top]], sum[i]);   
		f[i] = h[Sta[top]];
		Sta[++top] = i;
		h[i] = sum[i]; 
	}	
	top = 0;
	Sta[++top] = m + 1;
	h[m + 1] = sum[m]; 
	for (int i = m; i >= 1; --i) {
		while (top && b[i] <= b[Sta[top]]) {
			top--; 
		}
		h[Sta[top]] = min(h[Sta[top]], sum[i]);
		g[i] = h[Sta[top]];
		Sta[++top] = i;
		h[i] = sum[i - 1];   
	}
	ll res = 0;
	for (int i = 1; i <= m; ++i) {
		res = max(res, (g[i] - f[i]) * b[i]);     
	}
	return res;
}


int main() {
	while (scanf("%d", &n) != EOF) {
		m = n;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
		}
		ll res = work1();
		res = max(res, work2());
		printf("%lld\n", res);
	}
	return 0;
}
