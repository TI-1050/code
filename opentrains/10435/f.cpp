#include<bits/stdc++.h>
 
typedef long long ll;
 
using namespace std;
 
const int maxn = 1e5 + 10;
 
ll n;
int num;
ll l[maxn], r[maxn];
map<ll, int>mp;
 
void DFS(ll n)
{
	if(mp.count(n)) return ;
	if(n == 1)
	{
		mp[n] = num++;
		return ;
	}
	ll half = n / 2;
	DFS(half);
	DFS(n - half);
	mp[n] = num++;
	l[num - 1] = mp[n - half];
	r[num - 1] = mp[half];
}
 
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		mp.clear();
		num = 0;
		l[0] = -1, r[0] = -1;
		DFS(n);
		printf("%d\n", num);
		for(int i = 0; i < num; ++i) printf("%lld %lld\n", l[i], r[i]);
		printf("%d\n", num - 1);
	}
	return 0;
}
