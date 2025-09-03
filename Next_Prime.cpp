#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int nextPrime(int n) {
    for (int i = n + 1; i <= 50; i++) {
        if (isPrime(i)) {
            return i;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    if (nextPrime(n) == m) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    
    return 0;
}