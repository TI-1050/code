#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

const int N = 2e5 + 10;
const int DLEN = 1;
const int MAXN = 9;
class BigNum {
public :
	int a[N], len;
	BigNum() { len = 1; memset(a, 0, sizeof a); }
	BigNum(const char *);
	BigNum(const BigNum &);
	BigNum operator + (const BigNum &) const;
	int operator == (const BigNum &T) const;
	void print();
};
void BigNum::print() {
	printf("%d", a[len - 1]);
	for (int i = len - 2; i >= 0; --i)
		printf("%d", a[i]);
	printf("\n");
}
BigNum::BigNum(const BigNum &T):len(T.len) {
	int i;
	memset(a, 0, sizeof a);
	for (i = 0; i < len; ++i)
		a[i] = T.a[i];
}
BigNum::BigNum(const char *s) {
	int t, k, index, L, i;
	memset(a, 0, sizeof a);
	L = strlen(s);
	len = L / DLEN;
	if (L % DLEN) len++;
	index = 0;
	for (i = L - 1; i >= 0; i -= DLEN) {
		t = 0;
		k = i - DLEN + 1;
		if (k < 0) k = 0;
		for (int j = k; j <= i; ++j) {
			t = t * 10 + s[j] - '0';
		}
		a[index++] = t;
	}
}
BigNum BigNum::operator + (const BigNum &T) const {
	BigNum t(*this);
	int i, big;
	big = T.len > len ? T.len : len;
	for (i = 0; i < big; ++i) {
		t.a[i] += T.a[i];
		if (t.a[i] > MAXN) {
			t.a[i + 1]++;
			t.a[i] -= MAXN + 1;
		}
	}
	if (t.a[big] != 0) {
		t.len = big + 1;
	} else t.len = big;
	return t;
}
int BigNum::operator== (const BigNum &T) const {
	int cnt = 0;
	int i = 0, j = 0;
	for (; i < len; ++i) {
		if (a[i]) break;
		++cnt;
	}
	if (len - i != T.len) return -1;
	for (; i < len; ++i, ++j) {
		if (a[i] != T.a[j]) 
			return -1;
	}
	return cnt;
}
bool equals(BigNum &A, BigNum &B) {
	if (A.len != B.len) return 0;
	for (int i = 0; i < A.len; ++i)
		if (A.a[i] != B.a[i])
			return 0;
	return 1;
}
BigNum A, B, C;
int x, y, z, sta;
char a[N], b[N], c[N];

inline void out(int x, int y, int z) {
	int Min = min(x, min(y, z));
	printf("%d %d %d\n", x - Min, y - Min, z - Min);
}

inline void run() {
	scanf("%s%s%s", a, b, c);
	x = y = z = 0; 
	for (int i = strlen(a) - 1; i >= 0; --i) {
		if (a[i] == '0') ++x;
		else {
			a[i + 1] = 0;
			break;
		}
	}
	for (int i = strlen(b) - 1; i >= 0; --i) {
		if (b[i] == '0') ++y;
		else {
			b[i + 1] = 0;
			break;
		}
	}
	for (int i = strlen(c) - 1; i >= 0; --i) {
		if (c[i] == '0') ++z;
		else {
			c[i + 1] = 0;
			break;
		}
	}
	int num = max(x, max(y, z));
	//a + b
	A = BigNum(a); B = BigNum(b); C = BigNum(c);
	sta = (A + B == C);
	if (sta != -1) {
		out(num - x, num - y, num - z + sta);
		return;
	}
	
	//a后缀
	int cnt = 0, i = strlen(a) - 1, j = strlen(c) - 1, tmp;
	while (a[i] == c[j] && i >= 0 && j >= 0) {
		++cnt;
		--i; --j;
	} 
	while (i == -1 && j >= 0 && c[j] == '0') {
		++cnt;
		--j;
	}
	tmp = strlen(b); 
	for (i = 0; i < cnt; ++i) {
		b[tmp + i] = '0';
	}
	b[tmp + cnt] = 0;
	A = BigNum(a); B = BigNum(b); C = BigNum(c);
	sta = (A + B == C);
	if (sta != -1) {
		out(num - x, num - y + cnt, num - z + sta);
		return;	
	}

	//b后缀
	b[tmp] = 0; 
	cnt = 0, i = strlen(b) - 1, j = strlen(c) - 1;
	while (b[i] == c[j] && i >= 0 && j >= 0) {
		++cnt;
		--i; --j;
	}
	while (i == -1 && j >= 0 && c[j] == '0') {
		++cnt;
		--j;
	}
	tmp = strlen(a);
	for (i = 0; i < cnt; ++i) {
		a[tmp + i] = '0';
	}
	a[tmp + cnt] = 0;
	A = BigNum(a); B = BigNum(b); C = BigNum(c);
	sta = (A + B == C);
	if (sta != -1) {
		out(num - x + cnt, num - y, num - z + sta);
		return;
	}
	puts("-1");
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) run();
	return 0;
}
