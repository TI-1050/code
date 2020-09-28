#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
#include <bits/stdc++.h>

using namespace std;

const int N_ = 300500;
int mapping[N_];
int height[N_];
int width[N_];
vector<int> minuses[N_];
int current_minuses_sum[N_];
int C;

int main() {
#ifdef IN_MY_COMPUTER
  freopen("example.in", "r", stdin);
#endif

  int N; scanf("%d", &N);
  vector<int> H(N); for(int &x : H) scanf("%d", &x);
  long long L, R; scanf(INT64 "" INT64, &L, &R);
  
  vector<pair<int, int>> bounds(N);
  {
    struct state {
      int x, h;
    };
    {
      stack<state> stk;
      for(int i = 0; i < N; i++) {
        state s{i, H[i]};
        while(!stk.empty() && stk.top().h >= s.h) {
          s.x = stk.top().x;
          stk.pop();
        }
        stk.push(s);
        bounds[i].first = s.x;
      }
    }
    {
      stack<state> stk;
      for(int i = N-1; i >= 0; i--) {
        state s{i, H[i]};
        while(!stk.empty() && stk.top().h >= s.h) {
          s.x = stk.top().x;
          stk.pop();
        }
        stk.push(s);
        bounds[i].second = s.x;
      }
    }
  }

  vector<int> ord(N);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](const int &x, const int &y) {
    return tie(bounds[x], x) < tie(bounds[y], y);
  });

  {
    for(int i = 0; i < N; C++) {
      int j = i;
      vector<int> &arr = minuses[C];
      height[C] = H[ord[i]];
      while(j < N && bounds[ord[i]] == bounds[ord[j]]) {
        mapping[ord[j]] = C;
        arr.push_back(ord[j]);
        j += 1;
      }
      pair<int, int> &intv = bounds[ord[i]];
      width[C] = intv.second - intv.first + 1;
    
      arr.push_back(intv.second + 1);
      for(int x = int(arr.size()) - 1; x >= 0; x--) {
        arr[x] -= (x-1 >= 0 ? arr[x-1] : (intv.first - 1)) + 1;
        current_minuses_sum[C] += arr[x];
      }
      arr.erase(
        remove_if(arr.begin(), arr.end(), [](const int &x) { return x == 0; }),
        arr.end()
      );
      sort(arr.begin(), arr.end());
      i = j;
    }
  }

  auto sum1 = [&](long long l, long long r) {
    return r * (r+1) / 2 - l * (l-1) / 2;
  };

  long long low = 1, high = 1e15, ans = 1e15, cur = 1e15;
  while(low <= high) {
    long long mid = (low + high) / 2;
    long long cnt = 0;
    for(int p = 0; p < C; p++) {
      int b = (int)min(mid / height[p], (long long)width[p]);
      if(b > 0) cnt += sum1(width[p] - b + 1, width[p]);
      for(int m : minuses[p]) cnt -= sum1(m - min(b, m) + 1, m);
    }
    
    if(cnt >= L) {
      ans = mid;
      high = mid - 1;
      cur = cnt;
    }else {
      low = mid + 1;
    }
  }
  
  fprintf(stderr, "C = %d\n", C);

  long long x = L;
  for(; x <= cur && x <= R; x++) {
    printf(INT64 " ", ans);
  }

  if(x > R) return 0;

  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
  
  for(int i = 0; i < C; i++) {
    int b = (int)min(ans / height[i], (long long)width[i]);
    for(int m : minuses[i]) {
      current_minuses_sum[i] -= min(m+1, b) - 1;
    }
    pq.emplace((long long)(b+1) * height[i], i);
  }

  int num_rep = 0;
  while(!pq.empty() && x <= R) {
    long long a; int p; tie(a, p) = pq.top(); pq.pop();
    long long b = a / height[p];
    if(b > width[p]) {
      continue;
    }
      num_rep += 1;

    pq.emplace(a + height[p], p);

    int t = distance(
      minuses[p].begin(),
      lower_bound(minuses[p].begin(), minuses[p].end(), (int)b-1)
    );
    current_minuses_sum[p] -= minuses[p].size() - t;
    
    long long cnt_diff = width[p] - b + 1 - current_minuses_sum[p];
    
    while(cnt_diff > 0 && x <= R) {
      printf(INT64 " ", a);
      x += 1;
      cnt_diff -= 1;
    }
    
  }
  fprintf(stderr, "num_rep = %d\n", num_rep);

  return 0;
}
