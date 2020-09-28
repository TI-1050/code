#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
using ll = long long;
using ull = unsigned long long;
const int N = 5e4 + 5;
//下标从0开始 使用前需初始化
template <size_t MAXN>
struct Bitset {
    typedef unsigned long long ull; 
    const static int _BitNum = 64;
    const static ull _INF = (1ull << 63) - 1 + (1ull << 63); 
	int _len, _Size;
	ull _Ary[MAXN / _BitNum + 5];
	int _firstsize;
    ull _upceil;
	int num[MAXN / _BitNum + 5];

	Bitset() {};

	void init(int len) {
		_len = len;
    	_Size = _len / _BitNum + ((_len % _BitNum) == 0 ? 0 : 1);
        memset(_Ary, 0, sizeof (_Ary[0]) * (_Size + 1));
        _firstsize = _len % _BitNum;
		if (!_firstsize) _upceil = _INF;
		else  _upceil |= (1ull << _firstsize) - 1;
		if (!_firstsize) _firstsize = _BitNum;
    }

    void reset() { init(_len); }

	//operators                                                    
    void rtmve(const int &_v) {
        for (int i = _Size - 1; i >= _v; --i) this->_Ary[i] = this->_Ary[i - _v];
        for (int i = _v - 1; ~i; --i) this->_Ary[i] = 0;
    }
    
    void lftmve(const int &_v) {
        for (int i = 0; (i + _v) < _Size; ++i) this->_Ary[i] = this->_Ary[i + _v];
        for (int i = _Size - _v; i < _Size; ++i) this->_Ary[i] = 0;
    }
   
    Bitset& operator<<=(int _v) {
        if (_v < 0) {
            *this >>= -_v;
            return *this;
        }
        this->lftmve(_v / _BitNum);
        _v %= _BitNum;
        ull _tp = 0, _Pos = _BitNum - _v;
        for (int  i = 1; i <= _v; ++i) _tp |= 1ull << (_BitNum - i);
        ull _Lstv = 0;
        for (int i = _Size - 1; ~i; --i) {
            ull _Tp_Lstv = (_Ary[i] & _tp) >> _Pos;
            _Ary[i] <<= _v;
            _Ary[i] |= _Lstv;
            _Lstv = _Tp_Lstv;
        }
        this->_Ary[0] &= _upceil;
        return *this;
    }
    
    Bitset& operator>>=(int _v) {
        if (_v < 0) {
            *this <<= -_v;
            return *this;
        }
        this->rtmve(_v / _BitNum);
        _v %= _BitNum;
        ull _tp = (1ull << _v)- 1;
        ull _Lstv = 0, __Pos = _BitNum - _v;
        for (int i = 0; i < _Size; ++i) {
            ull _Tp_Lstv = (_Ary[i] & _tp) << __Pos;
            _Ary[i] >>= _v;
            _Ary[i] |= _Lstv;
            _Lstv = _Tp_Lstv;
        }
        this->_Ary[0] &= _upceil;
        return *this;
    }
   
	Bitset& operator&=(const Bitset &_others) {
		for (int i = _Size - 1; ~i; --i) {
			this->_Ary[i] &= _others._Ary[i];
		}
		return *this;
	}

    Bitset operator&(const Bitset &_others) const {
        Bitset _ret = *this;
		return _ret &= _others;
    }
	
	Bitset& operator|=(const Bitset &_others) {
		for (int i = _Size - 1; ~i; --i) {
			this->_Ary[i] |= _others._Ary[i];
		}
		return *this;
	}

    Bitset operator|(const Bitset &_others) const {
        Bitset _ret = *this; 
		return _ret |= _others;
    }

	Bitset& operator^=(const Bitset &_others) {
		for (int i = _Size - 1; ~i; --i) {
			this->_Ary[i] ^= _others._Ary[i];
		}
		return *this;
	}
    
    Bitset operator^(const Bitset &_others) const {
        Bitset _ret = *this;
		return _ret ^= _others;
    }
    
    Bitset operator~() const {
        Bitset _ret;
        for (int i = _Size - 1; ~i; --i) {
            _ret._Ary[i] = ~this->_Ary[i];
        }
        _ret._Ary[0] &= _upceil;
        return _ret;
    }
   
   	//MAXN很大时不可用	
    Bitset operator<<(const int &_v) const {
        Bitset x = *this;
		return x <<= _v;
    }

    Bitset operator>>(const int &_v) const {
        Bitset x = *this;
        return x >>= _v;
    }
    
	//member functions
    void __GetPos(const ull &_pos, int &__Pos, int &_v) {
        __Pos = _Size - _pos / _BitNum - 1;
        _v = _pos % _BitNum;
    }
    
    void set() {
        for (int i = 0; i < _Size; ++i) this->_Ary[i] = _INF;
        this->_Ary[0] &= _upceil;
    }
    
    void set(const int &_pos, const bool val = true) {
		if (_pos >= _len) return;
        int __Pos , _v;
        __GetPos(_pos,__Pos,_v);
        if (val) {
            this->_Ary[__Pos] |= (1ull << (_v));
        } else {
            this->_Ary[__Pos] |= (1ull << (_v));
            this->_Ary[__Pos] ^= (1ull << (_v));
        }
    }
    
    int test(const int &_pos) {
		if (_pos >= _len) return 0;
        int __Pos , _v;
        __GetPos(_pos,__Pos,_v);
        return this->_Ary[__Pos] & (1ull << (_v)) ? 1 : 0;
    }
    
    bool any() {
        for (int i = _Size - 1; ~i; --i) if (this->_Ary[i]) return true;
        return false;
    }
    
    bool none() {
        return !this->any();
    }
    
    int count() {
        int _cnt = 0;
        for (int i = _Size - 1; ~i; --i) _cnt += __builtin_popcountll(this->_Ary[i]);          
        return _cnt;
    }
    
    void flip() {
        *(this) = ~(*this);
    }
    
    void flip(const int &_pos) {
		if (_pos >= _len) return;
        if (this->test(_pos)) this->set(_pos, false);
        else this->set(_pos, true);
    }

    void preWork() {
		num[_Size] = 0;
		for (int i = _Size - 1; ~i; --i) num[i] = num[i + 1] + __builtin_popcountll(_Ary[i]);
    }

    int ask(const int &x) {
        if(x > _len) return 0;  
		int blockid = _Size - x / _BitNum;
		int ans = num[blockid];
		if (x % _BitNum) {
			int remind = x % _BitNum;
			--blockid;
			ans += __builtin_popcountll(_Ary[blockid] & ((1ull << remind) - 1));
		}
		return ans;
    }

    int ask(int l, int r) {
		if (l > r) return 0;
		++l, ++r;
		//preWork();
		return ask(r) - ask(l - 1);
    }

	int find_first() {
		for (int i = _Size - 1; ~i; --i) {
			int tmp = __builtin_ffsll(_Ary[i]);
			if (tmp) {
				return tmp + _BitNum * (_Size - 1 - i) - 1;
			}
		}
		return -1;
	}

	int find_next(int pos) {
		++pos; 
		int tar = _Size - ((pos + _BitNum - 1) / _BitNum); 
		ull buk = _Ary[tar];
		if (pos % _BitNum == 0) _Ary[tar] = 0;
		else _Ary[tar] &= _INF - ((1ull << (pos % _BitNum)) - 1);
		for (int i = tar; ~i; --i) {
			int tmp = __builtin_ffsll(_Ary[i]);
			if (tmp) {
				_Ary[tar] = buk;
				return tmp + _BitNum * (_Size - 1 - i) - 1;
			}
		}
		_Ary[tar] = buk;
		return -1;	
	}
    
	//changing functions  从左->右  高位->低位
    std::string to_string() {
        std::string _ret;
        _ret.clear();
        for (int i = 0; i < _Size; ++i) {
            for (int j = (i ? _BitNum : _firstsize) - 1; ~j; --j) _ret += (this->_Ary[i] & (1ull << j)) ? '1' : '0';
        }
        return _ret;
    }
    
    unsigned int to_ulong() {
        return this->_Ary[_Size - 1];
    }
};
Bitset <N> bs[N], bg[N];
int n, m, q, f[N];
vector <vector<int>> G; 
struct Tarjan {
	int Low[N], DFN[N], sta[N], Belong[N], num[N], d[N], scc; 
	bool Insta[N];
	void dfs(int u) {
		Low[u] = DFN[u] = ++*Low;
		sta[++*sta] = u;
		Insta[u] = 1;
		for (auto &v : G[u]) {
			if (!DFN[v]) {
				dfs(v);
				Low[u] = min(Low[u], Low[v]);
			} else if (Insta[v]) {
				Low[u] = min(Low[u], DFN[v]);
			}
		}
		if (Low[u] == DFN[u]) {
			++scc;
			int v;
			do {
				v = sta[(*sta)--];
				Insta[v] = 0;
				Belong[v] = scc;
				++num[scc];
			} while (v != u);
		}
	}
	void gao() {
		memset(DFN, 0, sizeof DFN);
		memset(Insta, 0, sizeof Insta);
		memset(num, 0, sizeof num);
		memset(d, 0, sizeof d);
		scc = *sta = *Low = 0;
		for (int i = 1; i <= n; ++i) if (!DFN[i]) dfs(i);	
		vector <vector<int>> H(scc + 1), bk(scc + 1);
		for (int i = 1; i <= scc; ++i) bg[i].init(n + 1); 
		for (int u = 1; u <= n; ++u) {
			bk[Belong[u]].push_back(u);
			for (auto &v : G[u]) {
				if (Belong[u] == Belong[v]) {
					continue;
				}
				H[Belong[v]].push_back(Belong[u]);
				++d[Belong[u]];
			}
		}
		queue <int> que;
		for (int i = 1; i <= scc; ++i) if (!d[i]) que.push(i);
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (auto &it : bk[u]) {
				bg[u].set(it); 
			}
			for (auto &v : H[u]) {
				bg[v] |= bg[u];
				if (--d[v] == 0) {
					que.push(v);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			bs[i] = bg[Belong[i]]; 
			bs[i].set(i);
			bs[i].preWork();
		}
	}
}tarjan;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d", &n, &m, &q);
		G.clear(); G.resize(n + 1); 
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
		}
		tarjan.gao();
	//	for (int i = 1; i <= n; ++i) bs[i].print();
		int len = 1, cnt = 1;
		while (len < n * 2) len <<= 1, ++cnt;  
		while (q--) {
			ll K; int res = 0; scanf("%lld", &K); --K; 
			memset(f, 0, sizeof f); 
			for (int i = cnt; i >= 0; --i) {
				//试着放1 
				ll num = 0;
				int bit = 1 << i; 
				for (int j = 1; j <= n; ++j) {
					if (((j >> i) & 1) == 0) { 
						f[j] |= bit; 
					}
					num += bs[j].ask(f[j], min(n, (f[j] | (bit - 1)))); 
					if (((j >> i) & 1) == 0) {
						f[j] ^= bit;
					}
				}
				if (K >= num) {
					K -= num; 
					for (int j = 1; j <= n; ++j) {
						if ((j >> i) & 1) {
							f[j] |= bit;
						}
					}
				} else {
					res |= bit; 
					for (int j = 1; j <= n; ++j) {
						if (((j >> i) & 1) == 0) {
							f[j] |= bit;
						}
					}
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
