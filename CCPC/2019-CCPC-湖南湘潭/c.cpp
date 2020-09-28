#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
#define unit 200

int brr[maxn];
int crr[maxn];

struct BIT{
	int a[maxn];

	void Init() {
		memset(a, 0, sizeof a);
	}

	void update(int x, int val) {
		for (; x < maxn; x += x & -x) {
			a[x] += val;
		}
	}
	
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
}bit;

struct node {
	int l, r, pos;
	node(){}
	node(int l, int r, int pos):l(l),r(r), pos(pos) {};
	bool operator < (const node &other) {
		if(l / unit == other.l / unit) {
			return r < other.r;
		}
		return l / unit < other.l / unit;
	}
}q[maxn];

int n, Q, k;
int arr[maxn];
ll ans[maxn];
ll tmp;

void Hash() {
	sort(brr + 1, brr + 1 + brr[0]);
	brr[0] = unique(brr + 1, brr + 1 + brr[0]) - brr - 1;	
	for (int i = 1; i <= crr[0]; ++i) {
		crr[i] = lower_bound(brr + 1, brr + 1 + brr[0], crr[i]) - brr;
	}
}

int get(ll x) {
	return lower_bound(brr + 1, brr + 1 + brr[0], x) - brr;
}

void Add(ll x) {
	tmp += bit.query(crr[3 * x]) - bit.query(crr[3 * x - 2]);
	bit.update(crr[3 * x - 1], 1);
}

void Del(ll x) {
	bit.update(crr[3 * x - 1], -1);
	tmp -= bit.query(crr[3 * x]) - bit.query(crr[3 * x - 2]);
}

void solve() {
	tmp = 0;
	int L = 1, R = 0;
	for (int i = 1; i <= Q; ++i) {
		while(R < q[i].r) Add(++R);
		while(R > q[i].r) Del(R--);
		while(L < q[i].l) Del(L++);
		while(L > q[i].l) Add(--L);
		ans[q[i].pos] = tmp;
	}
}

int main() {
	scanf("%d%d%d", &n, &Q, &k);
	brr[0] = 0;
	crr[0] = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", arr + i);
		brr[++brr[0]] = arr[i] - k - 1;
		brr[++brr[0]] = arr[i];
		brr[++brr[0]] = arr[i] + k;
		crr[++crr[0]] = arr[i] - k - 1;
		crr[++crr[0]] = arr[i];
		crr[++crr[0]] = arr[i] + k;
	}
	Hash();
	bit.Init();
	for (int i = 1; i <= Q; ++i) {
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].pos = i;
	}
	sort(q + 1, q + 1 + Q);
	solve();
	for (int i = 1; i <= Q; ++i) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}
