#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define LL long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define SZ(x) ((int)x.size())
const int M = 2e6 + 10;
const int N = 5e5 + 10;
struct E {
    int k;
    ll c;
    E(){}
    E( int _k, LL _c ):k(_k),c(_c){}
} es[M];

struct Flow {
    int n,m,dis[N];
    int qq[N],qr,ql;
    int ptr[N];
    vector<int> e[N];
    void init( int _n ) {
        n=_n; m=0;
        for ( int i=0; i<n; i++ ) {
            vector<int>tmp;
            e[i].swap(tmp);
        }
    }
    void addedge( int a, int b, LL c ) {
        e[a].push_back(m); es[m]=E(b,c); m++;
        e[b].push_back(m); es[m]=E(a,0); m++;
    }
    bool BFS() {
        memset(dis,-1,n*sizeof(int));
        ql=qr=0;
        qq[qr++]=0;
        dis[0]=0;
        while ( ql!=qr && dis[n-1]==-1 ) {
            int p=qq[ql++];
            for(auto& it:e[p]) {
                E ee=es[it];
                if ( ee.c==0 || dis[ee.k]!=-1 ) continue;
                dis[ee.k]=dis[p]+1;
                qq[qr++]=ee.k;
            }
        }
        return dis[n-1]!=-1;
    }
    LL go( int p, LL c ) {
        if ( p==n-1 ) return c;
        LL ret=0,tmp;
        for(int &i=ptr[p];i<SZ(e[p]);i++){
            auto it=e[p][i];
            E &ee=es[it];
            if ( ee.c==0 || dis[p]+1!=dis[ee.k] ) continue;
            tmp=go(ee.k,min(c-ret,(LL)ee.c));
            ret+=tmp; ee.c-=tmp; es[it^1].c+=tmp;
            if ( ret==c ) break;
        }
        if ( ret==0 ) dis[p]=-1;
        return ret;
    }
    LL maxflow() {
        LL ret=0;
        while ( BFS() ) {
            memset(ptr,0,n*sizeof(int));
            ret+=go(0,1LL<<60);
        }
        return ret;
    }
}dicnic;

int n, a[N];
bool isleft[N];
bool ispow2(int x) {
	return x && (x & (x - 1)) == 0;
}
int getbit(int x) {
	int res = 0;
	while (x) {
		res += x % 2;
		x /= 2;
	}
	return res & 1;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		int S = 0, T = n + 1; 
		dicnic.init(n + 2);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			isleft[i] = getbit(a[i]);
			if (isleft[i]) dicnic.addedge(S, i, 1);
			else dicnic.addedge(i, T, 1);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				if (ispow2(a[i] ^ a[j])) {
					if (isleft[i]) dicnic.addedge(i, j, 1);
					else dicnic.addedge(j, i, 1);
				}
			}
		}
		int num = n - dicnic.maxflow();
		vector <int> res;
		for (int i = 1; i <= n; ++i) {
			if (isleft[i]) {
				if (dicnic.dis[i] != -1) {
					res.push_back(a[i]);
				}
			} else {
				if (dicnic.dis[i] == -1) {
					res.push_back(a[i]); 
				}
			}
		}
		printf("%d\n", num);
		for (int i = 0; i < num; ++i)
			printf("%d%c", res[i], " \n"[i == num - 1]);
	}
	return 0;
}
