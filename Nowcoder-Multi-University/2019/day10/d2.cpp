#include <bits/stdc++.h>
using namespace std;

#define long long __int128
map<long long,bool> M;
const long long mod=1234577;
int n,tl,ftl;
long long a[100005],b[100005],fac[20];
struct node
{
    long long A,B,C;//mod A^B=C 
};
node t[1500005];
bool cmp(node x,node y)
{
    return x.A<y.A;
}

long long Mul(long long n,long long k)
{
    int i,x=0,y=0;
    for(i=1;i<19;++i) if(fac[i]>n)
    {
        x=i;break;
    }
    if(!x) x=19;
    for(i=1;i<19;++i) if(fac[i]>k)
    {
        y=i;break;
    }
    if(!y) y=19;
    return (x+y<=20);
}

long long mul(long long n,long long k,long long mod)
{
    long long ans=0;
    while(k)
    {
        if(k&1) ans=(ans+n)%mod;
        n=(n+n)%mod;
        k>>=1;
    }
    return ans;
}

long long F_p(long long x,long long y,long long z)
{
    long long bas=x%z,ret=1;
    while(y)
    {
        if(y&1) ret*=bas,ret%=z;
        bas*=bas,bas%=z;
        y>>=1;
    }
    return ret;
}

void insert(long long A,long long B,long long C)
{
    t[++tl].A=A,t[tl].B=B,t[tl].C=C;
}

void add(long long a,long long c)
{
    long long i,tmp,sq=sqrt(a);
    int cnt;
    for(i=2;i<=sq;++i)
    {
        cnt=0,tmp=1;
        while(a%i==0) ++cnt,a/=i,tmp*=i;
        if(cnt) insert(i,cnt,c%tmp);
        if(M[a]) break;
    }
    if(a>1) M[a]=1,insert(a,1,c%a);
}

void exgcd(long long a,long long b,long long &x,long long &y)
{
    if(!b)
    {
        x=1,y=0;
        return;
    }
    exgcd(b,a%b,x,y);
    long long tmp=x;
    x=y;
    y=tmp-a/b*y; 
}

long long CRT()
{
    long long x,y,k;
    long long M=a[1],ans=b[1];
    int i;
    for(i=2;i<=ftl;++i)
    {
        long long A=M,B=a[i],C=(b[i]-ans%B+B)%B;
        exgcd(A,B,x,y);
        x=mul(x,C,B);
        ans+=x*M;
        if(!Mul(M,B)) return ans; 
        else M*=B,ans=(ans%M+M)%M;
    }
    return ans;
}

int main()
{
    int i,l,r;
    fac[0]=1;
    for(i=1;i<19;++i) fac[i]=fac[i-1]*10;
    long long maxx,mm;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    { 
        scanf("%lld%lld",&a[i],&b[i]);
        if(a[i]==1) continue;
        add(a[i],b[i]); 
    }

    sort(t+1,t+tl+1,cmp);

    l=r=1;
    while(l<=tl)
    {
        maxx=t[l].B,mm=t[l].C;
        while(t[r+1].A==t[l].A)
        {
            ++r;
            if(t[r].B>maxx)
            {
                maxx=max(maxx,t[r].B);
                mm=t[r].C;
            }
        }
        a[++ftl]=pow(t[l].A,maxx),b[ftl]=mm;
        l=r+1,r=l;
    }

    printf("%lld\n",CRT());

    return 0;
}
