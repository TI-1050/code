#include<bits/stdc++.h>
 
using namespace std;
 
const int maxn = 5e3 + 10;
 
int n;
int vis[maxn];
int sg[maxn];
 
void Init()
{
	sg[2] = sg[3] = 1;
	for(int i = 4; i < maxn; ++i)
	{
		memset(vis, 0, sizeof vis);
		for(int j = 0; j <= i - 2; ++j)
		{
			vis[sg[j] ^ sg[i - j - 2]] = 1;	
		}
		for(int j = 0; ; j++) if(!vis[j])
		{
			sg[i] = j;
			break;
		}
	}
}
 
int main()
{
	Init();
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		puts(sg[n] ? "First" : "Second");	
	}
	return 0;
}
