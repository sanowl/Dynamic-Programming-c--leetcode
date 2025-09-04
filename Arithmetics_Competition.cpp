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
        int n, m, q;
        cin >> n >> m >> q;
        
        vector<long long> a(n), b(m);
        
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }
        
        // Sort in descending order to pick highest values first
        sort(a.begin(), a.end(), greater<long long>());
        sort(b.begin(), b.end(), greater<long long>());
        
        // Create prefix sums for efficient range sum queries
        vector<long long> prefix_a(n + 1, 0), prefix_b(m + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefix_a[i + 1] = prefix_a[i] + a[i];
        }
        
        for (int i = 0; i < m; i++) {
            prefix_b[i + 1] = prefix_b[i] + b[i];
        }
        
        for (int i = 0; i < q; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            
            long long max_sum = 0;
            
            // Try all possible distributions
            // Take k cards from Vadim, z-k cards from Kostya
            for (int k = 0; k <= min(x, z); k++) {
                int kostya_cards = z - k;
                
                // Check if Kostya can provide required cards
                if (kostya_cards <= y && kostya_cards <= m) {
                    long long current_sum = prefix_a[k] + prefix_b[kostya_cards];
                    max_sum = max(max_sum, current_sum);
                }
            }
            
            cout << max_sum << "\n";
        }
    }
    
    return 0;
}