#include <bits/stdc++.h>
using namespace std;
int n;
double x[305],y[305],d[305],res;
inline void get(double k) {
    // y = kx
    // kx - y = 0
    for (int i=0;i<n;++i) d[i]=(k*x[i]-y[i])/sqrt(k*k+1);
    sort(d,d+n);
    res=max(res,(d[n/2]-d[n/2-1])/2);
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i)
        cin>>x[i]>>y[i];
    for (int i=0;i<n;++i) d[i]=x[i];
    sort(d,d+n);
    res=max(res,(d[n/2]-d[n/2-1])/2);
    for (int i=0;i<n;++i) d[i]=y[i];
    sort(d,d+n);
    res=max(res,(d[n/2]-d[n/2-1])/2);
    for (int i=0;i<n;++i)
        for (int j=i+1;j<n;++j) if (x[i]!=x[j]&&y[i]!=y[j]) {
            double k=(y[j]-y[i])/(x[j]-x[i]);
            get(k);
            k=-1.0/k;
            get(k);
        }
    printf("%.12f\n",res);
    return 0;
}
