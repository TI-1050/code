/*
f[dis][距离=dis的有k个点][左边还有x个没BFS到][右边还有y个没BFS到]
x not include 1
*/
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=35;
int Case,n,m,all,mx,P,i,j,k,l,x,y,z,o,t,now;
int f[N*2][N][N][N],w[N][N][N],C[N][N],p[N];
int ans;
inline void up(int&a,int b){a=a+b<P?a+b:a+b-P;}
inline void upl(int&a,ll b){a=(a+b)%P;}
int po(int a,int b){
  int t=1;
  for(;b;b>>=1,a=1LL*a*a%P)if(b&1)t=1LL*t*a%P;
  return t;
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d%d",&n,&m,&P);
    all=n+m;
    mx=max(n,m);
    ans=0;
    p[0]=1;
    p[1]=po(2,P-2);
    for(i=2;i<=mx;i++)p[i]=1LL*p[i-1]*p[1]%P;
    for(C[0][0]=i=1;i<=mx;i++)for(C[i][0]=j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
    for(i=0;i<=mx;i++)for(j=0;j<=i;j++)C[i][j]=1LL*C[i][j]*p[i]%P;
    for(i=1;i<=mx;i++)for(j=0;j<=mx;j++)for(k=0;k<=mx;k++)w[i][j][k]=0;
    for(i=1;i<=mx;i++)w[0][i][0]=1;
    for(i=0;i<mx;i++)for(j=1;j<=mx;j++)for(k=0;k<=j;k++)if(w[i][j][k]){
      now=w[i][j][k];
      for(x=0;x<=j-k;x++){
        upl(w[i+1][j][k+x],1LL*now*C[j-k][x]);
      }
    }
    for(i=0;i<all;i++)for(j=1;j<=mx;j++)
      for(k=0;k<=n;k++)for(l=0;l<=m;l++)
        f[i][j][k][l]=0;
    f[0][1][n-1][m]=1;
    for(i=0;i<all;i++)for(j=1;j<=mx;j++){
      if(i&1){
        //right->left
        for(k=0;k<=n;k++)for(l=0;l<=m;l++)if(f[i][j][k][l]){
          now=f[i][j][k][l];
          upl(ans,1LL*now*i*j);
          for(x=1;x<=k;x++)upl(f[i+1][x][k-x][l],1LL*now*w[j][k][x]);
        }
      }else{
        //left->right
        for(k=0;k<=n;k++)for(l=0;l<=m;l++)if(f[i][j][k][l]){
          now=f[i][j][k][l];
          for(x=1;x<=l;x++)upl(f[i+1][x][k][l-x],1LL*now*w[j][l][x]);
        }
      }
    }
    ans=(ans%P+P)%P;
    ans=1LL*ans*po(m,P-2)%P;
    printf("%d\n",ans);
  }
}
