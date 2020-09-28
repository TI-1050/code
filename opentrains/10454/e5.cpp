
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
// Problem         : Hammering (NAIPC 2019)
// Author          : Darcy Best
// Expected Result : AC
// Complexity      : O( 2^n * (m^2 + m*n) )

// Pick a set of rows to consider. For each set, determine which
// columns are monotonic and then do a DP to count the number of
// monotonic sequences.

#include <iostream>
#include <vector>
using namespace std;

int main(){
  int n, m; cin >> n >> m;

  vector<vector<int> > A(n, vector<int>(m));
  for(auto& v : A)
    for(auto& x : v)
      cin >> x;

  vector<vector<int> > comp(m,vector<int>(m));
  for(int j1=0;j1<m;j1++)
    for(int j2=0;j2<m;j2++)
      for(int i=0;i<n;i++)
        if(A[i][j1] < A[i][j2])
          comp[j1][j2] |= (1 << i);

  vector<vector<long long> > DP(m, vector<long long>(1 << n));

  long long ans = 0;
  for(int rows_bM=1;rows_bM<(1 << n);rows_bM++){
    vector<bool> good_col(m, true);
    int in_my_col[n];
    for(int c=0;c<m;c++){
      int idx = 0;
      for(int r=0;r<n;r++)
        if((rows_bM >> r) & 1)
          in_my_col[idx++] = A[r][c];
      for(int i=0;i+2<idx;i++)
        if(!(in_my_col[i] < in_my_col[i+1] && in_my_col[i+1] < in_my_col[i+2]) &&
           !(in_my_col[i] > in_my_col[i+1] && in_my_col[i+1] > in_my_col[i+2]))
          good_col[c] = false;
      if(good_col[c]) ans++;
    }

    for(int en=0;en<m;en++)
      for(int st=0;st<en;st++)
        if(good_col[st] && good_col[en]){
          int cmp = comp[st][en] & rows_bM;
          DP[en][cmp] += DP[st][cmp] + 1; // +1 for the 2 column subgrid
        }

    for(int en=0;en<m;en++)
      for(int st=0;st<en;st++)
        if(good_col[st] && good_col[en]){
          int cmp = comp[st][en] & rows_bM;
          ans += DP[en][cmp];
          DP[en][cmp] = 0;
        }
  }

  cout << ans << endl;
}
