#include <bits/stdc++.h>
using namespace std;

mt19937_64 rd(time(0));
int x, y;
int random(int l, int r) {
	return (rd() % (r - l + 1) + l);
}
int random2(int l, int r) {
	return (rand() % (r - l + 1) + l);
}
void out(char c) {
	printf("%c\n", c);
	fflush(stdout);
}

int check(int l, int r, int x) {
	int cnt = 0;
	while (r - l >= 0) {
		++cnt;
		int mid = (l + r) >> 1;
		if (mid == x) {
			return cnt;
		} else if (mid > x) {
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return cnt;
}

int work(int l, int r) {
	int res = 0, Max = 0;
	int y, z;
	for (int _ = 0; _ < 100000; ++_) {
		if (_ & 1) {
			y = random(l, r);
		} else {
			y = random2(l, r);
		}
		y = random(l, r);
		z = check(l, r, y);
		if (z >= Max) {
			Max = z;
			res = y;
		}
	}
	return res;
}

int main() {
	srand(time(NULL));
	int l = 1, r = 1000000000;
	x = work(1, 1000000000);
	int cnt = 0;
	while (1) {
		++cnt;
		scanf("%d", &y);
		if (cnt >= 101) return 0;
		if (cnt <= 30 && x == y) {
			out('=');
			break;
		} else if (x > y) {
			l = max(l, y);
			out('>');
		} else {
			r = min(r, y);
			out('<');
		}
		x = work(l, r);
	}
	return 0;
}
