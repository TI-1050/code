#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl "\n"
#define psi pair <ll, int>
#define fi first
#define se second
#define iter list<psi>::iterator
int q, m;
list <psi> lis;   
unordered_map <ll, iter> mp; 

namespace IO
{
    const int S=(1<<22)+5;
    //Input Correlation
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
    }
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(!isdigit(c)) c=Get();
        while(isdigit(c)) s[tot++]=c,c=Get();
        s[tot++]='\0';
    }
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
		//输出换行
		putc('\n');
    }
    inline void prints(const char *s)
    {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
    inline void printd(int d,double x)
    {
        long long t=(long long)floor(x);
        print(t);putc('.');x-=t;
        while(d--)
        {
            double y=x*10;x*=10;
            int c=(int)floor(y);
            putc(c+'0');x-=floor(y);
        }
    }
}

ll change(char str[]){
    ll r;
    sscanf(str,"%lld",&r);
    return r+10000000000ll*(strlen(str)-1);
}

void No() {
	IO::prints("Invalid");
}

int main() {
	int T; T = IO::read();
	while (T--) {
		q = IO::read(); m = IO::read();
		mp.clear();
		lis.clear();  
		int op, v; char ts[20]; ll s;
		while (q--) {
			op = IO::read(); IO::reads(ts); v = IO::read();
	//		cout << op << " " << ts << " " << v << endl;
			s = change(ts);
			if (op == 0) {
				if (mp.find(s) == mp.end()) {
					lis.push_back(psi(s, v));
					mp[s] = lis.end(); --mp[s];
					IO::print(v);
				} else {
					v = (*mp[s]).se;
					IO::print(v);
					lis.erase(mp[s]);
					lis.push_back(psi(s, v));
					mp[s] = lis.end(); --mp[s];
				}
				if ((int)lis.size() > m) {
					mp.erase(lis.front().fi);
					lis.pop_front();  
				}
			} else { 
				if (mp.find(s) == mp.end()) No();
				else {
					iter pos = mp[s];
					if (v == 0) IO::print((*pos).se); 
					else if (v == -1) {
						if (pos == lis.begin()) No();
					    else {
							IO::print((*--pos).se);
						}
					} else {
						if (pos == --lis.end()) No();
						else {
							IO::print((*++pos).se);
						}
					}
				}
			}
		}
	}
	IO::flush();
	return 0;
}
