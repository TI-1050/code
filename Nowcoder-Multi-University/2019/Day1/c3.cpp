#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;

int a[N], p[N], n, m, cnt[N], lim[N];
long long x, y, tot, res, g;

long long gcd(long long x, long long y) {
  return y == 0 ? x : gcd(y, x % y);
}

void modify(long long a, long long b, long long c, long long d) {
  x = b * d * x + a * d + b * c;
  y = b * y * d;
}

int main() {
  while(~scanf("%d%d", &n, &m)) {
    y = m * m;
    tot = 0;
    x = 0;
    for(int i = 0; i <= 2*m; ++i)
      cnt[i] = lim[i] = 0;
    for(int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]);
      if(a[i] < 0) {
        p[i] = 0;
        x += 1LL * a[i] * a[i];
      }
      else {
        tot += a[i];
        p[i] = a[i];
      }
    }
    if(tot < m) {
      res = m - tot;
      for(int i = 1; i <= n; ++i) {
        if(a[i] < 0)
          cnt[-a[i]]++;
        else
          cnt[0]++;
      }
      for(int i = 0; i <= 2*m; ++i) {
        if(i)
          cnt[i] += cnt[i - 1];
        if(cnt[i] >= res) {
          modify(res * res, 1LL * cnt[i], res * i * 2LL, 1);
          break;
        }
        else {
          res -= cnt[i];
          x += cnt[i] * 1LL * ((i + 1) * (i + 1) - (i * i));
        }
      }
    }
    else if(tot > m) {
      res = tot - m;
      for(int i = 1; i <= n; ++i) {
        if(a[i] > 0) {
          lim[a[i]]++;
          cnt[0]++;
        }
      }
      for(int i = 0; i <= 2*m; ++i) {
        if(i)
          cnt[i] += cnt[i - 1];
        cnt[i] -= lim[i];
        if(cnt[i] >= res) {
          modify(res * res, 1LL * cnt[i], res * i * 2LL, 1LL);
          break;
        }
        else {
          res -= cnt[i];
          x += cnt[i] * 1LL * ((i + 1) * (i + 1) - (i * i));
        }
      }
    }
	cout << x << " " << y << endl;
    g = gcd(x, y);
    x /= g;
    y /= g;
    printf("%lld", x);
    if(y != 1)
      printf("/%lld", y);
    printf("\n");
  }
  return 0;
}
