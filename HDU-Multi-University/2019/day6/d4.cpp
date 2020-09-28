#include <bits/stdc++.h>
using namespace std;

int main() {
	priority_queue <int, vector <int>, greater <int>> A;
	priority_queue <int, vector <int>, less <int>> B;
	A.push(1); A.push(2);
	B.push(1); B.push(2);
	cout << A.top() << endl;
	cout << B.top() << endl;
	return 0;
}
