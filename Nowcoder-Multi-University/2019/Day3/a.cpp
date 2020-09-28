#include <bits/stdc++.h>
using namespace std; 
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 2e5 + 10, U = 1e3 + 10, unit = 600;
int n, m, q;
int vis[N], degree[N];
pII edge[N];  
vector <int> vec[N]; 
int isHasUnit[U], isHasSin[N];
int Hash[N], ran; 

void read(int &res) {
    res = 0; char c;
    while (!isdigit(c = getchar()));
    while (isdigit(c)) res = res * 10 + c - '0', c = getchar(); 
}

namespace DivideUnit {
	int pos[N], posl[U], posr[U]; 
	int valBig[U][U], valBigOri[U][U];
    int id[N];	
	//两侧暴力 
	void force(int l, int r) {
	    for (int i = l, u, v; i <= r; ++i) {
	        isHasSin[i] ^= 1;
	        u = edge[i].fi, v = edge[i].se;  
			//对于大点直接更新其边的块状态		
	        if (vis[u])
	            valBig[id[u]][pos[i]] ^= Hash[v];
	        if (vis[v])
	            valBig[id[v]][pos[i]] ^= Hash[u];
	    }
	}
	//更新操作
	void update(int l, int r) {
	    if (pos[l] == pos[r]) force(l, r);
	    else {
	        force(l, posr[pos[l]]);
			//整块状态翻转
	        for (int i = pos[l] + 1; i < pos[r]; ++i) isHasUnit[i] ^= 1;
	        force(posl[pos[r]], r); 
	    }
	}
	int query(int u) {
	    int res = 0;
	    if (vis[u]) {
	        for (int i = 1; i <= pos[m]; ++i) {
				//直接异或上单点更新的状态
	            res ^= valBig[id[u]][i];
				//如果整块翻转了，那么再异或上这块的原来的异或值
	            if (isHasUnit[i]) res ^= valBigOri[id[u]][i];
	        }
	    } else {
			//小点
	        for (auto it : vec[u]) {
				//如果单个更新次数和区间更新次数异或为１，说明没有抵消掉，需要更新
	            if (isHasSin[it] ^ isHasUnit[pos[it]]) {
	                int v = edge[it].fi == u ? edge[it].se : edge[it].fi;
	                res ^= Hash[v];
	            }
	        }
	    }
	    return res;
	}
	void init() {
	    for (int i = 1; i <= 200000; ++i) {
	        pos[i] = (i - 1) / unit + 1;
	        if (i == 1 || pos[i] != pos[i - 1]) posl[pos[i]] = i;
	        posr[pos[i]] = i;
	    }
	}
	void gao() {
		*id = 0;
        for (int i = 1; i <= n; ++i) if (degree[i] >= unit) {
            vis[i] = 1;
            id[i] = ++*id;
            for (int j = 1; j <= pos[m]; ++j)
                valBig[id[i]][j] = 0, valBigOri[id[i]][j] = 0;  
        }
		//初始化大点的边块的状态
        for (int i = 1, u, v; i <= m; ++i) {
            u = edge[i].fi; v = edge[i].se;
            if (vis[u]) {
                valBig[id[u]][pos[i]] ^= Hash[v];
                valBigOri[id[u]][pos[i]] ^= Hash[v];
            } else vec[u].push_back(i);
            if (vis[v]) {
                valBig[id[v]][pos[i]] ^= Hash[u];
                valBigOri[id[v]][pos[i]] ^= Hash[u];
            } else vec[v].push_back(i);
        } 
	}
}

int main() {
    for (int i = 1; i <= 100000; ++i) {
        ran *= 233;
        ran += 17;    
        Hash[i] = ran; 
    }
	DivideUnit::init();
	int T; scanf("%d", &T);
    while (T--) {
		scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) degree[i] = 0, vis[i] = 0, vec[i].clear();
        for (int i = 1; i <= m; ++i) isHasSin[i] = 1; 
        for (int i = 1; i <= DivideUnit::pos[m]; ++i) isHasUnit[i] = 0; 
        for (int i = 1, u, v; i <= m; ++i) {
            read(u), read(v);
            edge[i] = pII(u, v);
            ++degree[u];
            ++degree[v]; 
        }
		DivideUnit::gao();
        read(q);
        for (int qq = 1, op, x, y; qq <= q; ++qq) {
            read(op), read(x), read(y);
            if (op == 1) DivideUnit::update(x, y);
            else putchar((DivideUnit::query(x) == DivideUnit::query(y)) + '0');
        }
        puts("");
    }
    return 0;
}
