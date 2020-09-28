#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<time.h>
#include<assert.h>
#include<iostream>
using namespace std;
typedef __int128 LL;
typedef pair<int,int>pi;
const int Maxn=2020,Maxe=200020;
LL Inf=1LL<<60;
LL pw[15];
int ne;
int n,s,t;
vector<int>G[Maxn];
struct E{
    int v,c;
    LL w;
    E(){}
    E(int v,int c,LL w):v(v),c(c),w(w){}
}e[Maxe];
void add(int u,int v,int c,LL w){
    e[ne]=E(v,c,w);
    G[u].push_back(ne++);
    e[ne]=E(u,0,-w);
    G[v].push_back(ne++);
}
int pre[Maxn],pe[Maxn],inq[Maxn];
LL d[Maxn];
bool spfa(){
    for(int i=0;i<=t;i++)d[i]=Inf,inq[i]=0;
    d[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=0;i<G[u].size();i++){
            int id=G[u][i];
            int v=e[id].v;
            LL w=e[id].w;
            int c=e[id].c;
            if(!c)continue;
            if(d[v]>d[u]+w){
                pre[v]=u;
                pe[v]=id;
                d[v]=d[u]+w;
                if(!inq[v]){q.push(v);inq[v]=1;}
            }
        }
        inq[u]=0;
    }
    return d[t]<0;
}
int rep[100];
int cho[Maxn];
void costflow(){
    LL ans=0;
    while(spfa()){
        ans-=d[t];
        for(int i=t;i!=s;i=pre[i]){
            e[pe[i]].c--;
            e[pe[i]^1].c++;
        }
    }
    for(int i=0;i<10;i++)rep[10-i]=ans%1001,ans/=1001;
    for(int i=1;i<=10;i++)printf("%d%c",rep[i],i==10?'\n':' ');
    for(int i=1;i<=n;i++){
        cho[i]=0;
        for(int j=0;j<G[i].size();j++){
            int id=G[i][j];
            if(e[id].v!=s&&(!e[id].c)){
                cho[i]=e[id].v-n;
            }
        }
    }
    for(int i=1;i<=n;i++)printf("%d%c",cho[i],i==n?'\n':' ');
}
int main(){
  //  freopen("medals.in","r",stdin);
  //  freopen("medals.out","w",stdout);
    pw[0]=1;
    Inf*=Inf;
    for(int i=1;i<=11;i++)pw[i]=pw[i-1]*1001;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int k;scanf("%d",&k);
        for(int j=0;j<k;j++){
            int id,rk;
            scanf("%d%d",&id,&rk);
            add(i,id+n,1,-pw[10-rk]);
        }
        add(s,i,1,0);
    }
    s=0;t=n+1000+1;
    for(int i=n+1;i<t;i++)add(i,t,1,0);
    costflow();
    return 0;
}
