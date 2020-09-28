#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int f[N], pri[N], check[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) pri[++*pri] = i;
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}

void gao(int l, int r) {
	for (int i = l; i <= r; ++i) {
		f[pri[i]] = -1;
	}
}

void clear(int l, int r) {
	for (int i = l; i <= r; ++i) {
		f[pri[i]] = 0;
	}
}

int gogogo() {
	int S = 0, G = 0, H = 0, pos_G = -1, pos_H = -1;
	for (int i = 1; i <= 1000000; ++i) {
		if (!f[i]) {
			if (!check[i]) f[i] = 1;
			else {
				for (int j = 1; ; ++j) {
					if (i % pri[j] == 0) {
						f[i] = f[pri[j]] * f[i / pri[j]];
						break;
					}
				}
			}
		}
		S += f[i];
		if (S > G) {
			G = S;
			pos_G = i;
		} 
		if (S < H) {
			H = S;
			pos_H = i;
		}
	}
	return max(abs(H), abs(G));
//	cout << G << " " << pos_G << endl;
//	cout << H << " " << pos_H << endl;
}

int main() {
	sieve();
	cout << *pri << endl;
	memset(f, 0, sizeof f);
	f[1] = 1;
	int Min = 1e9, pos = -1; 
	for (int i = 0; i < (1 << 15); ++i) {
		clear(1, 20);
		for (int j = 0; j < 15; ++j)
			if ((i >> j) & 1) {
				gao(j + 1, j + 1);
			}
		int t = gogogo();
		if (t < Min) {
			Min = t;
			pos = i;
		}
		if (Min <= 20) break; 	
	}
	cout << Min << " " << pos << endl;
//	gao(20, 25);
//	gao(30, 35);
//	gao(40, 45);
//	gao(50, 55);
//	gao(60, 65);
//	gao(70, 75);
//	gao(80, 85);
//	gao(90, 95);
//	gao(100, 107);
//	gao(200, 250);
//	for (int i = 1000; i + 30 <= 1000000; i += 1000)
//		gao(i, i + 30);
	return 0;
}
