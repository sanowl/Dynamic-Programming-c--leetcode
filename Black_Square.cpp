#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a1, a2, a3, a4;
    cin >> a1 >> a2 >> a3 >> a4;
    
    string s;
    cin >> s;
    
    int total = 0;
    for (char c : s) {
        if (c == '1') {
            total += a1;
        } else if (c == '2') {
            total += a2;
        } else if (c == '3') {
            total += a3;
        } else if (c == '4') {
            total += a4;
        }
    }
    
    cout << total << "\n";
    
    return 0;
}