#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010
#define ALP 26
struct PAM{         
    int Next[N][ALP]; 
    int fail[N];      
    int cnt[N];       
    int sum[N];        
    int len[N];       
    int s[N];         
    int last;       
    int n;            
    int p;        
	int d[N], up[N];
	int pos[N], sze[N];	
 	vector<int> G[N]; 
    int newnode(int w){ 
        for(int i=0;i<ALP;i++)
            Next[p][i] = 0;
        cnt[p] = 0;
        len[p] = w;
        return p++;
    }
    void init(){
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1; 		 
        fail[0] = 1;
	}
    int get_fail(int x){ 
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }
    bool add(int c){
		bool F = 0;
        c -= 'a';
        s[++n] = c;
		int cur = get_fail(last);
		if(!Next[cur][c]){
            int now = newnode(len[cur]+2);
            fail[now] = Next[get_fail(fail[cur])][c];
            Next[cur][c] = now;
			d[now] = len[now] - len[fail[now]];
			up[now] = (d[fail[now]] == d[now] ? up[fail[now]] : now);  
			F = 1;
		}
        last = Next[cur][c];
        cnt[last]++;
		return F;
    }
	void build() {
		pos[0] = 0;
		for (int i = 0; i <= p; ++i) G[i].clear();
		for (int i = 0; i <= p; ++i) {
			if (i != 1) { 
				G[fail[i]].push_back(i);
			}
		}
	}
	void DFS(int x) {
		pos[x] = ++pos[0], sze[x] = 1;
		for (auto y : G[x]) {
			DFS(y);
			sze[x] += sze[y];    
		}
	}
}pam;

struct BIT {
	ll a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, ll v) {
		for (; x < N; x += x & -x) {
			a[x] += v;
		}
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
}bit;

struct SEG {
	int t[N << 2];
	void init() {
		memset(t, 0, sizeof t);
	}
	void update(int id, int l, int r, int x, int v) {
		if (l == r) {
			t[id] = max(t[id], v);
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) update(id << 1, l, mid, x, v);
		else update(id << 1 | 1, mid + 1, r, x, v);
		t[id] = max(t[id << 1], t[id << 1 | 1]);
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return t[id];
		}
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

int n, p[N];
char s[N];

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%s", s + 1);
		n = strlen(s + 1);
		pam.init();
		for (int i = 1; i <= n; ++i) {
			if (pam.add(s[i])) {
				p[i] = pam.p - 1;
			} else {
				p[i] = -1;
			}
		}
		pam.build(); pam.DFS(1);
		ll res = -pam.p + 2;
		bit.init(); seg.init();
		int now = 1;
		for (int i = 1; i <= n; ++i) {
			while (s[i] != s[i - pam.len[now] - 1]) now = pam.fail[now];
			now = pam.Next[now][s[i] - 'a'];
			for (int x = now; x; x = pam.fail[pam.up[x]]) {
				int l = max(1, seg.query(1, 1, pam.pos[0], pam.pos[x], pam.pos[x] + pam.sze[x] - 1) - pam.len[x] + 2);
				int r = i - pam.len[pam.up[x]] + 2;
				bit.update(l, 1);
				bit.update(r, -1);
			}
			seg.update(1, 1, pam.pos[0], pam.pos[now], i);
			if (p[i] != -1) {
				int l = i - pam.len[p[i]] + 1;
				res += bit.query(l);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
