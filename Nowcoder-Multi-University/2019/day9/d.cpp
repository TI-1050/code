#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
const int N = 110;
int n;
ull a[N], s;
map <ull, int> mp; 

void out(int mask, int n) {
	for (int i = 0; i < n; ++i) {
		putchar(((mask >> i) & 1) ? '1' : '0');
	}
}

int main() {
	while (scanf("%d%llu", &n, &s) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%llu", a + i);
	    if (n == 1) {
			if (s == a[1]) puts("1");
			else puts("0");
		} else {
			int mid = n / 2;
			vector <ull> al, ar;
			for (int i = 1; i <= mid; ++i) al.push_back(a[i]);
			for (int i = mid + 1; i <= n; ++i) ar.push_back(a[i]);
			mp.clear();
			int szel = (int)al.size(), szer = (int)ar.size();
			for (int i = 0; i < (1 << szel); ++i) {
				ull tot = 0;
				for (int j = 0; j < szel; ++j) {
					if ((i >> j) & 1)
						tot += al[j];
				}
			//	if (i == (1 << szel) - 1) cout << tot << endl;
				mp[tot] = i; 
			}
			for (int i = 0; i < (1 << szer); ++i) {
				ull tot = 0;
				for (int j = 0; j < szer; ++j) {
					if ((i >> j) & 1) 
						tot += ar[j]; 
				}
			//	if (i == (1 << szer) - 1) cout << tot << endl;
				if (mp.find(s - tot) != mp.end()) {
					out(mp[s - tot], szel);
					out(i, szer);
					puts("");
					break;
				}
			}
		}
	}
	return 0;
}
