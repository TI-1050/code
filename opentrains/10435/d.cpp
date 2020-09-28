#include<bits/stdc++.h>
 
using namespace std;
 
const int maxn = 3e5 + 10;
 
struct node1{
	int l, r, id, lmax;
	node1(){}
	node1(int id,int l,int r, int lmax):id(id), l(l), r(r), lmax(lmax){}
	bool operator < (const node1 &other) const
	{
		return lmax < other.lmax;
	//	if(lmax == other.lmax) return l < other.l;
	//	else return lmax < other.lmax;
	}
}arr[maxn];
 
struct node2{
	int l, r ,id;
	node2(){}
	node2(int id, int l, int r) :id(id), l(l), r(r){}
	bool operator < (const node2 &other) const
	{
		return r < other.r;
	}
}brr[maxn];
 
int n, m;
vector<int>G1[maxn], G2[maxn];
vector<int>vec;
vector<int>ans;
int du1[maxn], du2[maxn];
 
void Init()
{
	for(int i = 0; i < maxn; ++i) G1[i].clear(), G2[i].clear(), du1[i] = 0, du2[i] = 0;
}
 
bool judge()
{
	queue<int>q;
	vec.clear();
	for(int i = 1; i <= n; ++i) 
	{
		if(du1[i] == 0) q.push(i);
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vec.push_back(u);
		for(auto it : G1[u])
		{
			if(--du1[it] == 0) q.push(it);
		}
	}
//	cout << vec.size() << endl;
	return vec.size() == n;
}
 
bool solve()
{
	ans.clear();
	priority_queue<node2>q1;
	priority_queue<node1>q2;
	for(int i = 1; i <= n; ++i) if(du2[i] == 0) q1.push(brr[i]);
	for(int cas = n; cas >= 1; --cas)
	{
		while(!q1.empty() && q1.top().r >= cas)
		{
			q2.push(arr[q1.top().id]);
			q1.pop();
		}
		if(q2.empty()) return false;
		node1 now = q2.top();
		q2.pop();
		if(now.l > cas) return false;
		ans.push_back(now.id);
		for(auto it : G2[now.id])
		{
			if(--du2[it] == 0) q1.push(brr[it]);
		}
	}
	return true;
}
 
void work()
{
	if(!judge()) 
	{
		puts("-1");
		return ;
	}
	for(auto u : vec)
	{
		for(auto it : G1[u])
		{
			arr[it].lmax = max(arr[it].lmax, arr[u].lmax);
		}
	}
	if(!solve()) puts("-1");
	else 
	{
		for(int i = ans.size() - 1; i >= 0; --i) printf("%d\n", ans[i]);
	}
}
 
int main()
{
	while(~scanf("%d %d" ,&n, &m))
	{
		Init();
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d %d", &arr[i].l, &arr[i].r);
			arr[i].lmax = arr[i].l, arr[i].id = i;
			brr[i].l = arr[i].l, brr[i].r = arr[i].r, brr[i].id = i;
		}
		for(int i = 1, u, v; i <= m; ++i)
		{
			scanf("%d %d", &u, &v);
			G1[u].push_back(v);
			G2[v].push_back(u);
			du1[v]++;
			du2[u]++;
		}
		work();	
	}
	return 0;
}
