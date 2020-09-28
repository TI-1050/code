#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
const int C=2730,S=5;
const int N=222222;
int n,m,i,j,k;
int len[N];
ll pr[N][30][2];
ll pool[N];
ll ans;
int cnt;
ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}
ll mul(ll a, ll b, ll n){return (a * b - (ll)(a / (long double) n * b + 1e-3) * n + n) % n;}
ll pow(ll a, ll b, ll n){
    ll d = 1;
    a %= n;
    while(b){
        if(b & 1) d = mul(d, a, n);
        a = mul(a, a, n);
        b >>= 1;
    }
    return d;
}
bool check(ll a, ll n){
    ll m = n - 1, x, y; int i, j = 0;
    while(! (m & 1)) m >>= 1, j ++;
    x = pow(a, m, n);
    for(i = 1; i <= j; x = y, i ++){
        y = pow(x, 2, n);
        if((y == 1) && (x != 1) && (x != n - 1)) return 1;
    }
    return y != 1;
}
bool miller_rabin(int times, ll n){
    ll a;
    if(n == 1) return 0;
    if(n == 2) return 1;
    if(! (n & 1)) return 0;
    while(times --) if(check(rand() % (n - 1) + 1, n)) return 0;
    return 1;
}
ll pollard_rho(ll n, int c){
    ll i = 1, k = 2, x = rand() % n, y = x, d;
    while(1){
        i ++, x = (mul(x, x, n) + c) % n, d = gcd(y - x, n);
        if(d > 1 && d < n) return d;
        if(y == x) return n;
        if(i == k) y = x, k <<= 1;
    }
}
void findfac(ll n, int c){
    if(n == 1) return;
    if(miller_rabin(S, n)){
        pool[++cnt]=n;
        return;
    }
    ll m = n;
    while(m == n) m = pollard_rho(n, c --);
    findfac(m, c), findfac(n / m, c);
}
ll num[222222];
ll nowp[50];
ll pw[50][100];
int lim[50];
int tot;
int now[50];
int cntdiv;
ll divisor[3000000];
int f[3000000];
void dfs(int x,ll y){
    if(x==tot){
        divisor[++cntdiv]=y;
        return;
    }
    for(int i=0;i<=lim[x];i++)dfs(x+1,y*pw[x][i]);
}
inline int getid(ll x){return lower_bound(divisor+1,divisor+cntdiv+1,x)-divisor;}
void solve(int S){
    int i,j,k;
    if(num[S]==1)return;
    cnt=0;
    findfac(num[S],C);
    sort(pool+1,pool+cnt+1);len[S]=0;
    for(j=1;j<=cnt;j=k){
        for(k=j;k<=cnt&&pool[j]==pool[k];k++);
        pr[S][len[S]][0]=pool[j];
        pr[S][len[S]][1]=k-j;
        len[S]++;
    }
    tot=len[S];
    for(j=0;j<tot;j++){
        nowp[j]=pr[S][j][0];
        lim[j]=pr[S][j][1];
        for(pw[j][0]=k=1;k<=lim[j];k++){
            pw[j][k]=pw[j][k-1]*nowp[j];
        }
    }
    cntdiv=0;
    dfs(0,1);
    sort(divisor+1,divisor+cntdiv+1);
    for(i=1;i<=cntdiv;i++)f[i]=0;
    for(i=1;i<=n;i++){
        ll val=1;
        ll x=num[i];
        for(k=0;k<tot;k++)if(x%nowp[k]==0){
            int B=0;
            while(x%nowp[k]==0)x/=nowp[k],B++;
            val*=pw[k][min(B,lim[k])];
        }
        f[getid(val)]++;
    }
    for(i=0;i<tot;i++){
        int x=nowp[i];
        for(j=k=cntdiv;j;j--)if(divisor[j]%x==0){
            ll goal=divisor[j]/x;
            while(divisor[k]>goal)k--;
		//	assert(divisor[k] == goal);
            f[k]+=f[j];
        }
    }
    for(i=1;i<=cntdiv;i++)if(f[i]>=m)ans=max(ans,divisor[i]);
}
int main(){
    scanf("%d%d",&n,&m);
    m=n-m;//keep >=m numbers
    for(i=1;i<=n;i++){
        ll x;
        scanf("%lld",&x);
        num[i]=x;
        /*cnt=0;
        findfac(x,C);
        sort(pool+1,pool+cnt+1);
        for(j=1;j<=cnt;j=k){
            for(k=j;k<=cnt&&pool[j]==pool[k];k++);
            pr[i][len[i]][0]=pool[j];
            pr[i][len[i]][1]=k-j;
            len[i]++;
        }*/
    }
    ans=1;
    for(int ___=8;___;___--){
        int x=rand()%n+1;
        solve(x);
    }
    printf("%lld",ans);
}
