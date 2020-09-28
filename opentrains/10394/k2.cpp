#include<cstdio>
#include<string>
#include<algorithm>
#include<map>
#include<iostream>
using namespace std;
const int N=180000;
int n,m,i;
int len[N];
int f[N],g[N];
string name[N],show[N],need[N];
map<string,int>pos;
string q[N];
int dp(int x){
    if(!x)return 0;
    if(f[x])return f[x];
    int A=f[x],B=0;
    for(int i=0;i<name[x].size();i++){
        string now=name[x];
        now.erase(i,1);
        int o=pos[now];
        if(!o)continue;
        int t=dp(o);
        if(t>A)A=t,B=o;
    }
    f[x]=A+1,g[x]=B;
    return f[x];
}
int main(){
    cin>>n;//n=10000
    for(i=0;i<n;i++)cin>>need[i];
    cin>>m;//173554
    m++;
    name[1]="";
    show[1]=".";
    for(i=2;i<=m;i++){
        cin>>name[i];
        show[i]=name[i];
    }
    for(i=1;i<=m;i++){
        sort(name[i].begin(),name[i].end());
        pos[name[i]]=i;//sorted
        len[i]=name[i].size();
    }
    for(i=0;i<n;i++){
        string now=need[i];
        sort(now.begin(),now.end());
        int x=pos[now];
        dp(x);
        int cnt=0;
        while(x){
            q[++cnt]=show[x];
            x=g[x];
        }
        q[1]=need[i];
        cout<<cnt<<endl;
        for(int j=1;j<=cnt;j++){
            cout<<q[j];
            if(j<cnt)cout<<" -> ";else cout<<endl;
        }
    }
}
