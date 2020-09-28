#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N], res;
//0　表示头部插入　１表示尾部插入
int up[2][N]; 
int down[2][N]; 

void gao(int l, int r) {
	int pos = l;
	for (int i = l + 1; i <= r; ++i) {
		if (a[i] < a[pos]) pos = i;
	}
	//左边下降，右边上升
	int isdown = 1, isup = 1;
	for (int i = l + 1; i < pos; ++i) {
		if (a[i] > a[i - 1]) {
			isdown = 0;
			break;
		}
	}
	for (int i = pos + 1; i < r; ++i) {
		if (a[i] > a[i + 1]) {
			isup = 0;
			break;
		}
	}
	if (isdown == 0 && isup == 0) {
		res = -1;
		return;
	}
	if (isdown == 1 && isup == 1) {
		for (int i = l; i <= pos; ++i) {
			down[0][++down[0][0]] = a[i];
		}
		for (int i = r; i > pos; --i) {
			up[1][++up[1][0]] = a[i];
		}
		return;
	   //左边下降	
	} else if (isdown == 1) {
		for (int i = l; i < pos - 1; ++i) {
			down[0][++down[0][0]] = a[i];
		}
		up[0][++up[0][0]] = a[pos];
		if (pos == l) {
			gao(pos + 1, r);
		} else {
			swap()
		}
	} else {
	
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		res = 0; up[0][0] = up[1][0] = 0; down[0][0] = down[1][0] = 0;  
		gao(1, n);
		if (res == -1) {
			puts("NO");
		} else {
			puts("YES");
		}
	}
	return 0;
}
