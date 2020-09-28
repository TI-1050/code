#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9;
 
class Linear_Seq {
#define FOR(i,a,b) for(int i(a);i<=(b);++i)
#define SZ(x) ((int)(x).size())
using VI = vector<ll> ;
public:
    static const int N=10010;
    ll res[N],base[N],c[N],md[N];
    vector<int> Md;
    ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
	void mulEx(ll *a,ll *b,int k) {
        for(int i(0);i<k+k;++i) c[i]=0;
        for(int i(0);i<k;++i)if(a[i])for(int j(0);j<k;++j)
            c[i+j]=(c[i+j]+a[i]*b[j])%mod;
        for (int i(k+k-1);i>=k;--i) if (c[i])for(int j(0);j<SZ(Md);++j)
            c[i-k+Md[j]]=(c[i-k+Md[j]]-c[i]*md[Md[j]])%mod;
        copy(c,c+k,a) ;
    }
	// a 系数 b 初值 b[n+1]=a[0]*b[n]+...
    int solve(ll n,VI a,VI b) { 
        ll ans(0),cnt(0);
        int k(a.size());
        for(int i(0);i<k;++i) md[k-1-i]=-a[i];
        md[k]=1 ;  Md.clear() ;
        for(int i(0);i<k;++i) if (md[i]) Md.push_back(i);
        for(int i(0);i<k;++i) res[i] = base[i] = 0;
        res[0]=1;
        while ((1LL<<cnt)<=n) ++ cnt;
        for (int p(cnt);~p;-- p) {
            mulEx(res,res,k);
            if ((n>>p)&1) {
                for (int i(k-1);~i;--i) res[i+1]=res[i];res[0]=0;
                for(int j(0);j<SZ(Md);++j)
                    res[Md[j]]=(res[Md[j]]-res[k]*md[Md[j]])%mod;
            }
        }
        for(int i(0);i<k;++i) ans=(ans+res[i]*b[i])%mod;
        return ans+(ans<0?mod:0);
    }
    VI BM(VI s) {
        VI ret(1,1),B(1,1);
        int L(0),m(1),b(1);
        for(int n(0);n<SZ(s);++n) {
            ll d(0);
            for(int i(0);i<=L;++i)
                d=(d+(ll)ret[i]*s[n-i])%mod;
            if (!d) ++m;
            else if (2*L<=n) {
                VI T=ret;
                ll c(mod-d*powmod(b,mod-2)%mod);
                while (SZ(ret)<SZ(B)+m) ret.push_back(0);
                for (int i=0;i<SZ(B);++i)
                    ret[i+m]=(ret[i+m]+c*B[i])%mod;
                L=n+1-L; B=T; b=d; m=1;
            } else {
                ll c(mod-d*powmod(b,mod-2)%mod);
                while (ret.size()<B.size()+m) ret.push_back(0);
                for(int i=0;i<SZ(B);++i)
                    ret[i+m]=(ret[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return ret;
    }
    static void extand(VI &a, size_t d, ll value = 0) {
        if (d <= a.size()) return;
        a.resize(d, value);
    }
    static ll gcdEx(ll a, ll b, ll&x, ll& y) {
        if(!b) {x=1;y=0;return a;}
        ll d = gcdEx(b,a%b,y,x);
        y -= (a/b)*x;
        return d;
    }
    static ll CRT(const VI &c, const VI &m) {
        int n(c.size());
        ll M(1), ans(0);
        for (int i = 0; i < n; ++i) M *= m[i];
        for (int i = 0; i < n; ++i) {
            ll x,y,tM(M / m[i]);
            gcdEx(tM, m[i], x, y);
            ans = (ans + tM * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }
    static VI ReedsSloane(const VI &s, ll mod) {
        auto Inv = [](ll a, ll mod) {
            ll x, y;
            return gcdEx(a, mod, x, y)==1?(x%mod+mod)%mod:-1;
        };
        auto L = [](const VI &a, const VI &b) {
            int da = (a.size()>1||(a.size()== 1&&a[0]))?a.size()-1:-1000;
            int db = (b.size()>1||(b.size()== 1&&b[0]))?b.size()-1:-1000;
            return max(da, db + 1);
        };
        auto prime_power = [&](const VI &s, ll mod, ll p, ll e) {
            // linear feedback shift register mod p^e, p is prime
            vector<VI> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            VI t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);;
            pw[0] = 1;
            for (int i(pw[0] = 1); i <= e; ++i) pw[i] = pw[i - 1] * p;
            for (ll i(0); i < e; ++i) {
                a[i] = {pw[i]}; an[i] = {pw[i]};
                b[i] = {0}; bn[i] = {s[0] * pw[i] % mod};
                t[i] = s[0] * pw[i] % mod;
                if (!t[i]) {t[i] = 1; u[i] = e;}
                else for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
            }
            for (size_t k(1);k < s.size(); ++k) {
                for (int g(0); g < e; ++g) {
                    if (L(an[g], bn[g]) > L(a[g], b[g])) {
                        ao[g] = a[e-1-u[g]];
                        bo[g] = b[e-1-u[g]];
                        to[g] = t[e-1-u[g]];
                        uo[g] = u[e-1-u[g]];
                        r[g] = k - 1;
                    }
                }
                a = an; b = bn;
                for (int o(0); o < e; ++o) {
                    ll d(0);
                    for (size_t i(0); i < a[o].size() && i <= k; ++i)
                        d = (d + a[o][i] * s[k - i]) % mod;
                    if (d == 0) {t[o] = 1;u[o] = e;}
                    else {
                        for (u[o]=0, t[o]=d;!(t[o]%p);t[o]/=p ,++u[o]);
                        int g (e-1-u[o]);
                        if (!L(a[g], b[g])) {
                            extand(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % mod;
                        } else {
                            ll coef = t[o]*Inv(to[g],mod)%mod*pw[u[o]-uo[g]]%mod;
                            int m(k-r[g]);
                            extand(an[o],ao[g].size()+m);
                            extand(bn[o],bo[g].size()+m);
                            for (size_t i(0);i < ao[g].size(); ++i) {
                                an[o][i+m] -= coef*ao[g][i]%mod;
                                if (an[o][i + m]<0) an[o][i+m] += mod;
                            }
                            while (an[o].size() && !an[o].back()) an[o].pop_back();
                            for (size_t i(0); i < bo[g].size(); ++i) {
                                bn[o][i+m] -= coef*bo[g][i]%mod;
                                if (bn[o][i + m] < 0) bn[o][i + m] -= mod;
                            }
                            while (bn[o].size()&& !bn[o].back()) bn[o].pop_back();
                        }
                    }
                }
            }
            return make_pair(an[0], bn[0]);
        };
        vector<tuple<ll, ll, int> > fac;
        for (ll i(2); i*i <= mod; ++i)
            if (!(mod % i)) {
                ll cnt(0),pw(1);
                while (!(mod % i)) {mod /= i; ++cnt; pw *= i;}
                fac.emplace_back(pw, i, cnt);
            }
        if (mod > 1) fac.emplace_back(mod, mod, 1);
        vector<VI> as;
        size_t n = 0;
        for (auto &&x: fac) {
            ll mod, p, e;
            VI a, b;
            std::tie(mod, p, e) = x;
            auto ss = s;
            for (auto &&x: ss) x %= mod;
            std::tie(a, b) = prime_power(ss, mod, p, e);
            as.emplace_back(a);
            n = max(n, a.size());
        }
        VI a(n),c(as.size()),m(as.size());
        for (size_t i(0); i < n; ++i) {
            for (size_t j(0); j < as.size(); ++j) {
                m[j] = std::get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = CRT(c, m);
        }
        return a;
    }
    ll solve(VI a,ll n,ll mod,bool prime=true) {
        VI c;
        if(prime) c = BM(a);
        else c = ReedsSloane(a,mod);
        c.erase(c.begin());
        for(int i(0);i<SZ(c);++i) c[i] = (mod-c[i])%mod;
        return solve(n,c,VI(a.begin(),a.begin()+c.size()));
    }
}BM;

ll qpow(ll base, ll n) {
	ll res = 1;
	while(n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

ll sum;
ll a[1005];
int main() {
    ll n, m;
	while (cin >> n >> m) {
   		 a[0] = a[1] = 1;
   		 vector<ll> f;
   		 f.push_back(1);
   		 f.push_back(2);
   		 sum = 2;
   		 for (int i = 2; i < 1000; i++) {
   		     a[i] = (a[i-1] + a[i-2]) % mod;
   		     sum = (sum + qpow(a[i], m)) % mod;
   		     f.push_back(sum);                         
   		 }
		 //false-模数为合数
   		 cout << BM.solve(f,n-1,mod,false) << "\n";   
	}
    return 0;
}
