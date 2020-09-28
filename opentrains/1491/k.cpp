#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
using ll = long long;
using B = bitset<N>; 
int q, lens, lent, id[N];
char s[N], t[N];
B S[26], T[N / 10], G, H, All; 
inline void initT() {
	int now = 0;
	id[lent + 1] = ++now;
	T[now] = All;
	H.set(); 
	for (int i = lent; i >= 1; --i) {
		H = (H >> 1) & S[t[i] - 'a'];
		if ((lent + 1 - i) % 16 == 0) {
			id[i] = ++now;
			T[now] = H;
		} else id[i] = -1;  
	}
}

inline void getT(int p) {
	for (int i = p; i <= lent + 1; ++i) {
		if (id[i] != -1) {
			H = T[id[i]];
			for (int j = i - 1; j >= p; --j) {
				H = (H >> 1) & S[t[j] - 'a'];
			}
			break;
		}
	}
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%s", s + 1); lens = strlen(s + 1);
		for (int i = 0; i < 26; ++i) S[i].reset();
		for (int i = 1; s[i]; ++i) S[s[i] - 'a'][i] = 1;
		All.set(); 
		All = (All << (lens + 1));
		All.flip(); All[0] = 0; All[lens + 1] = 1;
		scanf("%d", &q); 
		while (q--) {
			scanf("%s", t + 1);
			lent = strlen(t + 1);
		    memset(id, -1, sizeof (id[0]) * (lent + 10));	
			G.set();  
			initT();  
			ll res = 0;  	
			for (int i = 1; i <= lent; ++i) {  
				getT(i + 1);  
				res += ((G << 2) & H).count();
				G = (G << 1) & (S[t[i] - 'a']);
			}
			res -= 1ll * (lent - 1) * G.count(); 
			printf("%lld\n", res);
		}
	}
	return 0;
}
