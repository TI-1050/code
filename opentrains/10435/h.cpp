#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll GCD(ll a, ll b)
{
	return b == 0 ? a : GCD(b, a % b);
}
 
ll A, B, C, D;
 
int main()
{
	while(~scanf("%lld %lld %lld %lld", &A, &B, &C, &D))
	{
		ll ans = 0;
		for(int x = 1; x <= 999; ++x)
		{
			for(int y = 1; y <= 999; ++y)
			{
				if(GCD(x, y) != 1 || x + y >= 1000) continue;
				ll l1 = A / x, r1 = B / x;
				ll l2 = C / y, r2 = D / y;
				if(l1 * x < A) l1++;
				if(l2 * y < C) l2++;
				ll tmp = min(r1, r2) - max(l1, l2) + 1;
				if(tmp > 0)
				{
//					cout << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
					ans += tmp;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
