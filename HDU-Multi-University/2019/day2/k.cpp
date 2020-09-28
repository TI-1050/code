#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define INF 0x3f3f3f3f
int n, q, a[N];
int vec[55], tr[55];

struct SEG {
    struct node {
        int Max, pos;
        node() {
            Max = -INF;
            pos = 0;
        }
        node (int Max, int pos) : Max(Max), pos(pos) {}
        node operator + (const node &other) const {
            node res = node();
            if (Max < other.Max) {
                res.Max = other.Max;
                res.pos = other.pos;
            } else {
                res.Max = Max;
                res.pos = pos;
            }
            return res;
        }
    }t[N << 2], res;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node(a[l], l);
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos, int x) {
        if (l == r) {
            t[id] = node(x, l);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(id << 1, l, mid, pos, x);
        else update(id << 1 | 1, mid + 1, r, pos, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res + t[id];
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) query(id << 1, l, mid, ql, qr);
        if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
    }
}seg;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        seg.build(1, 1, n);
        int l, r;
        while (q--) {
            scanf("%d%d", &l, &r);
            vec[0] = 0;
			tr[0] = 0;
			int len = min(50, r - l + 1);
            for (int i = 1; i <= len; ++i) {
                seg.res = SEG::node();
                seg.query(1, 1, n, l, r);
                seg.update(1, 1, n, seg.res.pos, -INF);
				tr[++tr[0]] = seg.res.Max;
				vec[++vec[0]] = seg.res.pos;
            }
            ll res = -1;
            for (int i = tr[0] - 2; i >= 1; --i) {
                ll A = tr[i], B = tr[i + 1], C = tr[i + 2];
                if (A + B > C) {
                    res = max(res, A + B + C);
                }
            }
            printf("%lld\n", res);
			for (int i = 1; i <= vec[0]; ++i) {
				seg.update(1, 1, n, vec[i], a[vec[i]]);
			}
        }
    }
    return 0;
}
