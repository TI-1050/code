#include<bits/stdc++.h>
using namespace std;

int main() {
    std::bitset<1001> B;
	B.set(2);
	cout << B << endl;
   // B.set(2); B.set(4); B.set(233);
    for(int i = B._Find_first(); i != B.size(); i = B._Find_next(i)) 
        std::cout << i << ' ';
}
