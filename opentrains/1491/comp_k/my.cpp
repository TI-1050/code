#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
using ll = long long;
using ull = unsigned long long;
using B = bitset<N>; 
int q, lens, lent, unit;  
char s[N], t[N];  
B S[26], G, All; 
vector <B> T;

struct Hash{
	static ull base[N];
	static void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i)
			base[i] = base[i - 1] * 131;
	}
	ull a[N];
	inline void gao(char *s) {
		a[0] = 0;
		for (int i = 1; s[i]; ++i)
			a[i] = a[i - 1] * 131 + s[i];
	}
	inline ull get(int l, int r) {
		return a[r] - a[l - 1] * base[r - l + 1];
	}
}hs, ht;
ull Hash::base[N] = {0};

struct ExKMP {
	int Next[N];
	int extend[N];
	//下标从1开始
	void get_Next(char *s) {
		int lens = strlen(s + 1), p = 1, pos;
		//Next[1]要特殊考虑
		Next[1] = lens;
		while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
		//Next[2]初始化
		Next[pos = 2] = p - 1;
		for (int i = 3; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			//第一种情况
			if (len + i < p + 1) Next[i] = len;
			//第二种情况
			else {
				//找到对于子串最靠后已经匹配的位置
				int j = max(p - i + 1, 0);
				//暴力匹配
				while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
				p = i + (Next[pos = i] = j) - 1; 
			}
		}
	}

	void work(char *s, char *t) {
		get_Next(t);
		int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
		while (p <= lent && s[p] == t[p]) ++p;
		p = extend[pos = 1] = p - 1;
		for (int i = 2; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			if (len + i < p + 1) extend[i] = len;
			else {
				int j = max(p - i + 1, 0);
				while (i + j <= lens && j <= lent && t[j + 1] == s[i + j]) ++j;
				p = i + (extend[pos = i] = j) - 1;
			}
		}
	}
}exkmp;

//exkmp + Hash
inline ll gao1() {
	if (lent > lens) return 0;
	if (lent == 1) return lens;
	ll res = 0;
	ht.gao(t);
	exkmp.work(s, t);  
	for (int i = 1; i + lent - 1 <= lens; ++i) {
		int end = i + lent - 1;
		int nx = i + exkmp.extend[i] + 1;
		if (nx > end) ++res;
		else if (hs.get(nx, end) == ht.get(exkmp.extend[i] + 2, lent)) 
				++res;
		
	}
	return res;
}

inline ll gao2() {
	if (lent == 1) return lens;
	T[lent + 1] = All;
	for (int i = lent; i >= 1; --i) {
		T[i] = (T[i + 1] >> 1) & S[t[i] - 'a'];
	}
	ll res = 0;
	G.set();	
	for (int i = 1; i <= lent; ++i) {
		res += ((G << 2) & T[i + 1]).count();
		G = (G << 1) & (S[t[i] - 'a']);
//		cout << res << " " << i << endl;
	}
//	cout << G.count() << endl;
	res -= 1ll * (lent - 1) * G.count();
	return res;
}

int main() {
	Hash::init();
	T.clear(); T.resize(N / 64 + 10);
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%s", s + 1); lens = strlen(s + 1); unit = lens / 64; 
		hs.gao(s);
		for (int i = 0; i < 26; ++i) S[i].reset();
		for (int i = 1; s[i]; ++i) S[s[i] - 'a'][i] = 1;
		All.set(); 
		All = (All << (lens + 1));
		All.flip(); All[0] = 1; All[lens + 1] = 1; 
		scanf("%d", &q); 
		while (q--) {
			scanf("%s", t + 1); lent = strlen(t + 1);
			ll res = 0;
			res = gao1();
		//	if (lent >= unit) res = gao1();
		//	else res = gao2();
			printf("%lld\n", res);
		}
	}
	return 0;
}
