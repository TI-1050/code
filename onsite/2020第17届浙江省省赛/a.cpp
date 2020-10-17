#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int f[N];
int y[2], m[2], d[2]; 
int Mon[2][13] = {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
 
 
bool isLeap(int y) {
	if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) {
		return true;
	}
	return false;
}
 
int allD(int y) {
	if (isLeap(y)) return 366;
	else return 365;
}
 
int getAll(int y) {
	if (y / 10 == 202) return allD(y);
	if (y % 1000 == 202) return allD(y);
	int res = 1;
	if (y % 10 == 2) {
		if (isLeap(y)) res += 1;
		res += 28;
	} else {
		res += 1;
	}
	return res;
}
 
int calc(int y, int m, int d) {
	if (y / 10 == 202 || y % 1000 == 202) {
		int res = 0;
		int ok = isLeap(y);
		for (int i = 1; i < m; ++i) {
			res += Mon[ok][i];
		}
		res += d;
		return res;
	} 
	int res = 0;
	if (y % 10 == 2) {
		if (m == 2) res += d;
		else if (m > 2) res += int(isLeap(y)) + 28;
	} else {
		if (m == 2 && d >= 2) res += 1;
		else if (m > 2) res += 1;
	}
	if (m == 12 && d >= 2) res += 1;
	return res;
}
 
 int valid(int y, int m, int d) {
 	if (y / 10 == 202 || y % 1000 == 202) {
		return 1;
	} 
	if (m == 12 && d == 2) return 1;
	if (y % 10 == 2) {
		if (m == 2) return 1;	
	} else {
		if (m == 2 && d == 2) return 1;	
	}
	return 0;
 }
 
int main() {
 	for (int i = 2000; i <= 9999; ++i) {
		f[i] = f[i - 1] + getAll(i); 	
	}
//	cout << f[9999] << endl;
 	int _T; scanf("%d", &_T);
	while (_T--) {
 		for (int i = 0; i < 2; ++i) {
		 	scanf("%d %d %d", y + i, m + i, d + i);
		}
		int l = y[0], r = y[1];
		int res = 0;
		if (l < r) {
			res += f[r - 1] - f[l];
		}
		if (l == r) {
			res += calc(y[1], m[1], d[1]) - calc(y[0], m[0], d[0]) + valid(y[0], m[0], d[0]);
		} else {
			res += calc(y[0], 12, 31) - calc(y[0], m[0], d[0]) + valid(y[0], m[0], d[0]);
			res += calc(y[1], m[1], d[1]);
		}
		printf("%d\n", res);
	}
 	return 0;
}
