#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, k;
        cin >> n >> k;
        
        vector<int> s(n), t(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> t[i];
        }
        
        map<int, int> sCount, tCount;
        for (int x : s) {
            sCount[x % k]++;
        }
        for (int x : t) {
            tCount[x % k]++;
        }
        
        bool possible = true;
        for (auto& p : sCount) {
            if (p.second != tCount[p.first]) {
                possible = false;
                break;
            }
        }
        
        for (auto& p : tCount) {
            if (sCount[p.first] != p.second) {
                possible = false;
                break;
            }
        }
        
        cout << (possible ? "YES" : "NO") << "\n";
    }
    
    return 0;
}