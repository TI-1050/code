#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const int M = 100100;

ld f[M];
ld sumf[M];

int g[M];

void add(int at, int val) {
  for (int i = at; i < M; i |= (i + 1))
    g[i] += val;
}

int sum(int r) {
  int ans = 0;
  for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
    ans += g[i];
  return ans;
}

int sum(int l, int r) {
  return sum(r) - sum(l - 1);
}

void pre() {
  f[1] = 1;
  sumf[1] = 1;
  for (int n = 2; n < M; ++n) {

    /*
    for (int j = 1; j <= n; ++j)
      if (f[n - j] + 1 >= f[n - 1])
        f[n] += (f[n - j] + 1) / n;
      else
        f[n] += f[n - 1] / n;
    */

    int k = lower_bound(f, f + n, f[n - 1] - 1) - f;

    f[n] = ((sumf[n - 1] - sumf[k - 1] + (n - k)) + k * f[n - 1]) / n;
    
    sumf[n] = sumf[n - 1] + f[n];
  }
	for (int i = 1; i <= 100000; ++i)
		cout << i << " " << f[i] << endl;
//  cerr << f[100000] << endl;
}


int main() {
  pre();

  int n, last = 0;
  cin >> n;

  for (int i = 1; i <= n; ++i)
    add(i, 1);

  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    if (x <= last) {
  //    cout << 0 << endl;
      continue;
    }
    
    int rem = sum(last + 1, n);
    int to = sum(x + 1, n);

    //cerr << rem << " " << to << endl;

    if (f[to] + 1 >= f[rem - 1]) {
  //    cout << 1 << endl;
	  ++cnt;
      last = x;
    } else {
    //  cout << 0 << endl;
    }

    add(x, -1);
  }
  cout << cnt << endl;
}

