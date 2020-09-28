#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int M = 23;
int n, q;
char s[N];
struct DA {
	int t1[N], t2[N], c[N];
	int sa[N];
	int Rank[N];
	int height[N];
	int str[N];
	int n, m;
	void init(char *s, int m, int n) {
		this->m = m;
		this->n = n;
		for (int i = 0; i < n; ++i) str[i] = s[i];
		str[n] = 0;
	}
	bool cmp(int *r, int a, int b, int l) {
		return r[a] == r[b] && r[a + l] == r[b + l];
	}
	void work() {
		++n;
		int i, j, p, *x = t1, *y = t2;
		for (i = 0; i < m; ++i) c[i] = 0;
		for (i = 0; i < n; ++i) c[x[i] = str[i]]++;
		for (i = 1; i < m; ++i) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
		for (j = 1; j <= n; j <<= 1) {
			p = 0;
			//直接利用sa数组排序第二关键字
			//后面的j个数第二关键字为空的最小
			for (i = n - j; i < n; ++i) {
				y[p++] = i;
			}
			for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
			//这样数组y保存的就是按照第二关键字排序的结果
			//基数排序第一关键字
			for (i = 0; i < m; ++i) c[i] = 0;
			for (i = 0; i < n; ++i) c[x[y[i]]]++;
			for (i = 1; i < m; ++i) c[i] += c[i - 1];
			for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
			//根据sa和x数组计算新的x数组
			swap(x, y);
			p = 1; x[sa[0]] = 0;
			for (i = 1; i < n; ++i) {
				x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
			}
			if (p >= n) break;
			//下次基数排序的最大值
			m = p;
		}
		int k = 0;
		--n;
		for (i = 0; i <= n; ++i) Rank[sa[i]] = i;
		//build height
		for (i = 0; i < n; ++i) {
			if (k) --k;
			j = sa[Rank[i] - 1];
			while (str[i + k] == str[j + k]) ++k;
			height[Rank[i]] = k; 
		}
	}
	struct RMQ {
		int Min[N][M]; 
		int mm[N];
		void init(int n, int *b) {
			mm[0] = -1;
			for (int i = 1; i <= n; ++i) {
				mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
				Min[i][0] = b[i];
			}
			for (int j = 1; j <= mm[n]; ++j) {
				for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
					Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
				}
			}
		}
		int queryMin(int x, int y) {
			int k = mm[y - x + 1];
			return min(Min[x][k], Min[y - (1 << k) + 1][k]);  
		}
	}rmq;
	void initrmq() {
		rmq.init(n, height);
	}
	int lcp(int x, int y) {
		if (x == y) return 1e9;
		if (x > y) swap(x, y);
		++x;
		return rmq.queryMin(x, y);   
	}
}da;

int getl(int x, int len) {
	int l = 1, r = x, res = x;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (da.lcp(x, mid) >= len) {
			res = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return res;
}

int getr(int x, int len) {
	int l = x, r = n, res = x;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (da.lcp(x, mid) >= len) {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return res;
}

struct SEG {
	struct node {
		int sum, ls, rs;
		node() {
			ls = rs = sum = 0;
		} 
	}t[N * 50];
	int rt[N], cnt;
	void init() { 
		cnt = 0; 
		memset(rt, 0, sizeof rt);
	}
	void build(int &id, int l, int r) {
		id = ++cnt;
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid);
		build(t[id].rs, mid + 1, r);  
	}
	void up(int id) {
		int ls = t[id].ls, rs = t[id].rs;
		t[id].sum = 0;
		if (ls) t[id].sum += t[ls].sum;
		if (rs) t[id].sum += t[rs].sum; 
	}
	void update(int &now, int pre, int l, int r, int pos) {
		now = ++cnt;
		t[now] = t[pre];  
		if (l == r) {
			++t[now].sum; 
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[now].ls, t[pre].ls, l, mid, pos);
		else update(t[now].rs, t[pre].rs, mid + 1, r, pos);
		up(now);
	}
	int query(int tl, int tr, int l, int r, int k) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		int lsum = t[t[tr].ls].sum - t[t[tl].ls].sum;	
	//	cout << l << " " << r << " " << lsum << " " << k << endl;
		if (lsum >= k) {
			return query(t[tl].ls, t[tr].ls, l, mid, k);
		} else {
			return query(t[tl].rs, t[tr].rs, mid + 1, r, k - lsum); 
		}
	}
}seg;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &q);
		scanf("%s", s);
		da.init(s, 220, n);
		da.work(); da.initrmq();
		seg.init(); seg.build(seg.rt[0], 1, n);  
		for (int i = 1; i <= n; ++i)
			seg.update(seg.rt[i], seg.rt[i - 1], 1, n, da.sa[i] + 1);
	//	for (int i = 1; i <= n; ++i) cout << da.Rank[i] << endl;
		for (int i = 1, x, l, r, k, len; i <= q; ++i) {
			scanf("%d%d%d", &l, &r, &k);
			len = r - l + 1; 
			x = da.Rank[l - 1];  
			int L = getl(x, len);
			int R = getr(x, len);
		//    cout << x << " " << k << " " << L << " " << R << endl;	
			if (R - L + 1 < k) puts("-1");
			else printf("%d\n", seg.query(seg.rt[L - 1], seg.rt[R], 1, n, k));   
		}
	}
	return 0;
}
