#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, j, k;
        cin >> n >> j >> k;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        int playerStrength = a[j - 1]; // Convert to 0-indexed
        
        // Count how many players have strength > player j's strength
        int stronger = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > playerStrength) {
                stronger++;
            }
        }
        
        // Player j can survive if there are at most k-1 players with higher strength
        if (stronger <= k - 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}