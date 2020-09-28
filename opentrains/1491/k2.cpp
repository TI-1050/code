#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
using ull = unsigned long long;
using ll = long long;
int q, lens, lent;
char s[N], t[N];  
typedef unsigned long long ull;
struct Hash {  
	static ull base[N]; 
	static void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i)
			base[i] = base[i - 1] * 131; 
	}
	ull a[N]; 
	//最好改成从1开始，因为查询区间Hash值是前缀和形式
	inline void gao(char *s) {  
		a[0] = 0; 
		for (int i = 1; s[i]; ++i) {
			a[i] = a[i - 1] * 131 + s[i]; 
		}	
	}
	inline ull get(int l, int r) { 
		return a[r] - a[l - 1] * base[r - l + 1]; 
	}
}hs, ht;
ull Hash::base[N] = {0}; 
vector <string> 

void go() {
	cin >> (s + 1) >> q;
	for (int i = 1; i <= q; ++i) {
			
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); 
	Hash::init(); 
	int _T; cin >> _T;
	while (_T--) go();
	return 0;
}
