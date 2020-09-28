#include <bits/stdc++.h>
using namespace std;

#define ll long long
mt19937_64 rd(time(0));
ll x, y, l, r;
char op[10];
ll random(ll l, ll r) {
	return (rd() % (r - l + 1) + l);
}
void out(ll x) {
	printf("%lld\n", x);
	fflush(stdout);
}

int main() {
	x = random(100, 99999900); out(x);
	scanf("%s", op + 1);
	l = 1, r = 1000000000;
	switch(op[1]) {
		case '>' :
			for (int i = 1; i <= 29; ++i) {
				out(x - i);
				scanf("%*s");
			}
			l = 1, r = x - 30;
			break;
		case '<' :
			for (int i = 1; i <= 29; ++i) {
				out(x + i);
				scanf("%*s");
			}
			l = x + 30, r = 1000000000;
			break;
		case '=' :
			assert(0);
			break;
	}

	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
		out(mid);
		scanf("%s", op + 1);
		switch(op[1]) {
			case '<' :
				r = mid - 1;
				break;
			case '>' :
				l = mid + 1;
				break;
			case '=' :
				return 0;
		}		
	}
	return 0;
}
