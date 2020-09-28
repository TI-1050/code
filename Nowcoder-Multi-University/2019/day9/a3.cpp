#include<bits/stdc++.h>
using namespace std;
const int N = 2e3+20;
const int mod = 1e9 + 7;
int n, k, a[N << 1], b[N << 1], c[N << 1], h[N], tp[N << 1], ans, lim;
inline void add(int &x,int y){
	x += y;
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}
inline void mul(int *A,int *B){
	for(int i = 0; i <= lim; i++)tp[i]=0;
	for(int i = 0; i <= k; i++)
		for(int j = 0; j <= k; j++)
			tp[i+j] = (tp[i+j] + 1ll * A[i] * B[j]) % mod;
	for(int i = lim; i >= k; i--){
		for(int j = 0; j < k; j++)
			tp[i-k+j] = (tp[i-k+j] + 1ll * tp[i] * a[k-j]) % mod;
		tp[i] = 0;
	}
	for(int i = 0;i <= lim; i++) A[i] = tp[i];
}
inline void power(int *A,int B,int *C){
	for(; B; B >>= 1,mul(A,A)) if(B & 1) mul(C,A);
}
int main(){
	scanf("%d%d", &n, &k); lim = k << 1; 
	for(int i = 1; i <= k; i++) {
		scanf("%d", a + i);
		a[i] = (a[i] % mod + mod) % mod;
	}
	for(int i = 0; i < k; i++) {
		scanf("%d", h + i);
		h[i] = (h[i] % mod + mod) % mod;
	}
	if(n < k) {
		printf("%d\n", h[n]); 
		return 0;
	}
	b[0] = 1; c[1] = 1; power(c,n,b);
	for(int i = 0; i < k; i++) add(ans,1ll * b[i] * h[i] % mod);
	printf("%d\n",ans);
}
