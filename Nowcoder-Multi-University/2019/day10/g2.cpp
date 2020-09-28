#include<bits/stdc++.h>
using namespace std;
 
const int maxn=400;
 
struct point{
    double x,y;
};
 
point a[maxn];
 
int n;
 
double ans=0;
 
double d[maxn];
 
void solve(double k){
    for(int i=1;i<=n;i++)d[i]=(k*a[i].x-a[i].y)/sqrt(k*k+1);
    sort(d+1,d+1+n);
    ans=max(ans,d[n/2+1]-d[n/2]);
}
 
int main(){
    //ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        double k=(a[j].y-a[i].y)/(a[j].x-a[i].x);
        solve(k);
        solve(-1/k);   
    }
    printf("%.15lf",ans/2);
}
