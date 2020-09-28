#include <bits/stdc++.h>
using namespace std;

char get(string &s) {
	if (s == "do") return 'a';
	if (s == "re") return 'b';
	if (s == "mi") return 'c';
	if (s == "fa") return 'd';
	if (s == "sol") return 'e';
	if (s == "la") return 'f';
	return 'g';
}
const int N = 3e6;
char s[N]; int n, head, tail, ql[N], qr[N], res[N];
typedef unsigned long long ull;
struct Hash {
	static ull base[N]; 
	static void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i)
			base[i] = base[i - 1] * 131;  
	}
	ull a[N]; 
	inline void gao(char *s) { 
		a[0] = s[0];
		for (int i = 1; s[i]; ++i) {
			a[i] = a[i - 1] * 131 + s[i]; 
		}	
	}
	inline ull get(int l, int r) {  
		return a[r] - a[l - 1] * base[r - l + 1]; 
	}
}hs;
ull Hash::base[N] = {0}; 

bool check(int x, int p) {
	return hs.get(ql[x], qr[x] - p) == hs.get(ql[x] + p, qr[x]); 
}

int main() {
	Hash::init(); 
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	while (cin >> n) {
		head = n + 10;
		tail = head - 1; 
		string str, op;
		for (int i = 1; i <= n; ++i) {
			cin >> op >> str;
			if (op == "a") {
				s[++tail] = get(str);
			} else {
				s[--head] = get(str); 
			}
			ql[i] = head; qr[i] = tail; 
		}
		s[tail + 1] = 0;
		hs.gao(s + head - 1); 
	//	cout << (s + head) << endl;
		for (int i = 1; i <= n; ++i) {
			ql[i] -= head - 1;
			qr[i] -= head - 1;
		}
		for (int i = 1; i <= n; ++i) res[i] = 0;
		for (int i = 1; i <= n; ++i) {
			int l = i, r = n, pos = -1;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (check(mid, i)) {
					l = mid + 1;
					pos = mid; 
				} else {
					r = mid - 1;
				}
			}
			++res[i]; --res[pos + 1];
		}
		for (int i = 1; i <= n; ++i) res[i] += res[i - 1];
		for (int i = 1; i <= n; ++i)
			printf("%d\n", res[i]); 
	}
	return 0;
}
