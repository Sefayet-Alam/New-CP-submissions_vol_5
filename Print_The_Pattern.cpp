#include <bits/stdc++.h>


using namespace std;

string generatePattern(int n) {
    if (n == 1) return "A";
    string prev = generatePattern(n - 1);
    return prev + char('A' + n - 1) + prev;
}

int main() {
    int n;
    cin >> n;
    cout << generatePattern(n);
    return 0;
}

