#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 510;
ll L[N], k; int n;
string s[N];
__int128 x;

char gao(int cur, ll k) {
	if (cur <= 3) {
		return s[cur][k - 1]; 
	}
	if (k <= L[cur - 2]) {
		return gao(cur - 2, k);
	} else if (k <= L[cur - 2] + L[cur - 3]) {
		return gao(cur - 3, k -= L[cur - 2]);
	} else {
		return gao(cur - 2, k -= L[cur - 2] + L[cur - 3]);
	}
}

int main() {
	s[1] = "COFFEE";
	s[2] = "CHICKEN";
	s[3] = s[1] + s[2];
    s[4] = s[2] + s[3];
	s[5] = s[3] + s[4];
//	cout << s[4] << endl;
//	cout << s[5] << endl;	
	L[1] = 6; L[2] = 7;
	for (int i = 3; i <= 70; ++i) {
		L[i] = L[i - 1] + L[i - 2];
	}
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	int _T; cin >> _T;
	while (_T--) {
		cin >> n >> k;
		n = min(n, 62); 
		string res = "";
		for (ll i = 0; k + i <= L[n] && i < 10; ++i) {
			res += gao(n, k + i);
		}
		cout << res << "\n";
	}
	return 0;
}
