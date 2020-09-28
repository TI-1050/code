#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i16;
const int N = 1e5 + 7;
 
int pr[N], pn;
bitset<N> np;
void init() {
    for(int i = 2; i < N; i++) {
        if(!np[i]) pr[pn++] = i;
        for(int j = 0; j < pn && i * pr[j] < N; j++) {
            np[i * pr[j]] = 1;
            if(i % pr[j] == 0) break;
        }
    }
}
ll getpp(int p) {
    ll ret = 1;
     
    for(int i = 0; i < pn && pr[i] * pr[i] <= p; i++) {
        if(p % pr[i] == 0) {
            ret *= (pr[i] - 1ll) * (pr[i] + 1);
            p /= pr[i];
            while(p % pr[i] == 0) p /= pr[i], ret *= pr[i];
        }
    }
    if(p != 1) ret *= (p - 1ll) * (p + 1);
    return ret;
}
#define rep(i, n) for(int i = 0; i < n; i++)
int mod;
struct Mat {
    static const int S = 2;
    int e[S][S];
    void clear() { memset(e, 0, sizeof e);}
    Mat() { clear();}
    void E() { clear(); rep(i, S) e[i][i] = 1;}
    void init(int _e[][S]) {
        rep(i, S) rep(j, S) e[i][j] = _e[i][j];
    }
    Mat operator * (const Mat &r) {
        Mat ret;
        rep(i, S)rep(k, S) if(e[i][k])
            rep(j, S) ret.e[i][j] = (ret.e[i][j]+1ll*e[i][k]*r.e[k][j])%mod;
        return ret;
    }
    Mat operator ^ (ll n) {
        Mat ret, a = *this;
        ret.E();
        for(; n; n>>=1, a=a*a)
            if(n&1) ret = ret*a;
        return ret;
    }
} A, B;
 
const int MM = 1e6 + 7;
char s[MM];
 
int main() {
    init();
    int x[2], a, b;
    scanf("%d%d%d%d", &x[1], &x[0], &a, &b);
    A.e[0][0] = a, A.e[0][1] = 1;
    A.e[1][0] = b, A.e[1][1] = 0;
    scanf("%s%d", s, &mod);
    int len = strlen(s);
    ll ord = getpp(mod), r = 0;
	cout << "# " << ord << endl;
    for(int i = 0; i < len; i++) {
        r = ((i16)r * 10 + s[i] - '0') % ord;
    }
	cout << r << endl;
    B = A ^ r;
    ll res = 0;
    for(int i = 0; i < 2; i++)
        res = (res + 1ll*x[i]*B.e[i][1])%mod;
    printf("%lld\n", res);
    return 0;
}
