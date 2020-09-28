#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=50010,OFFSET=2000000;
int n,i,x,y,ce;
int g[N],v[N<<1],nxt[N<<1],ok[N<<1],ed,son[N],f[N],all,now,cnt;
ll ans;
struct E{
    int a,b,c;
    E(){}
    E(int _a,int _b,int _c){a=_a,b=_b,c=_c;}
}e[N];
struct W{
    int v,i,op,l,r;
    W(){}
    W(int _v,int _i,int _op,int _l,int _r){
        v=_v;
        i=_i;
        op=_op;
        l=_l;
        r=_r;
    }
}pool[OFFSET];
inline bool cmpw(const W&a,const W&b){
    if(a.v!=b.v)return a.v<b.v;
    return a.i<b.i;
}
inline bool cmp(const E&a,const E&b){return a.a<b.a;}
int bit[N],vis[N],POS;
inline void ins(int x){x++;for(;x<=n+1;x+=x&-x)if(vis[x]<POS)vis[x]=POS,bit[x]=1;else bit[x]++;}
inline int ask(int x){int t=0;for(x++;x;x-=x&-x)if(vis[x]==POS)t+=bit[x];return t;}
inline ll cal(){
    ll ret=0;
    sort(e+1,e+ce+1,cmp);
    int cp=0;
    for(int i=1;i<=ce;i++){
        pool[++cp]=W(e[i].a-e[i].c,i<<1,0,0,e[i].b);
        pool[++cp]=W(e[i].a-e[i].b-e[i].c+OFFSET,i<<1,0,e[i].b+1,n);
        pool[++cp]=W(e[i].b+e[i].c,i<<1|1,1,e[i].b,0);
        pool[++cp]=W(e[i].c+OFFSET,i<<1|1,1,e[i].b,0);
    }
    sort(pool+1,pool+cp+1,cmpw);
    for(int i=1;i<=cp;i++){
        if(i==1||pool[i].v!=pool[i-1].v)POS++;
        if(pool[i].op==1)ins(pool[i].l);
        else ret+=ask(pool[i].r)-ask(pool[i].l-1);
    }
    return ret;
}
inline void add(int x,int y){v[++ed]=y;nxt[ed]=g[x];ok[ed]=1;g[x]=ed;}
void findroot(int x,int y){
    son[x]=1;f[x]=0;
    for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y){
        findroot(v[i],x);
        son[x]+=son[v[i]];
        if(son[v[i]]>f[x])f[x]=son[v[i]];
    }
    if(all-son[x]>f[x])f[x]=all-son[x];
    if(f[x]<f[now])now=x;
}
void dfs(int x,int y,int dis,int ma,int mi){
    ma=max(ma,x);
    mi=min(mi,x);
    if(ma-mi==dis)ans++;
    e[++ce]=E(ma,mi,dis);
    for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfs(v[i],x,dis+1,ma,mi);
}
void dfs2(int x,int y,int dis,int ma,int mi){
    ma=max(ma,x);
    mi=min(mi,x);
    e[++ce]=E(ma,mi,dis);
    for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfs2(v[i],x,dis+1,ma,mi);
}
void solve(int x){
    int i;
    for(i=g[x];i;i=nxt[i])if(ok[i]){
        ce=0;
        dfs(v[i],x,1,x,x);
        ans-=cal();
    }
    ce=0;
    for(i=g[x];i;i=nxt[i])if(ok[i])dfs2(v[i],x,1,x,x);
    ans+=cal();
    for(i=g[x];i;i=nxt[i])if(ok[i]){
        ok[i^1]=0;
        f[0]=all=son[v[i]];
        findroot(v[i],now=0);
        solve(now);
    }
}
int main(){
    scanf("%d",&n);
    for(ed=i=1;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
    f[0]=all=n;
    findroot(1,now=0);
    solve(now);
    printf("%lld\n",ans+n);
}
