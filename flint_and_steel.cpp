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
        int n;
        cin >> n;
        vector<int> e(n);
        
        for (int i = 0; i < n; i++) {
            cin >> e[i];
        }
        
        vector<bool> dead(n, false);
        vector<int> detonations;
        
        while (true) {
            // Find leftmost alive creeper
            int leftmost = -1;
            for (int i = 0; i < n; i++) {
                if (!dead[i]) {
                    leftmost = i;
                    break;
                }
            }
            
            // If no alive creepers, we're done
            if (leftmost == -1) break;
            
            // Find the best creeper to detonate
            int best = -1;
            int furthest_reach = -1;
            
            for (int i = 0; i < n; i++) {
                if (!dead[i] && e[i] > 0) {
                    // Check if this creeper can kill the leftmost alive creeper
                    if (abs(i - leftmost) < e[i]) {
                        // Calculate the rightmost position this creeper can reach
                        int right_reach = i + e[i] - 1;
                        if (right_reach >= n - 1) right_reach = n - 1;
                        
                        // We want the creeper that can reach furthest right
                        // If tied, prefer the leftmost one
                        if (right_reach > furthest_reach || 
                           (right_reach == furthest_reach && (best == -1 || i < best))) {
                            furthest_reach = right_reach;
                            best = i;
                        }
                    }
                }
            }
            
            // If no creeper can kill the leftmost, it's impossible
            if (best == -1) {
                detonations.clear();
                break;
            }
            
            // Detonate the best creeper
            detonations.push_back(best + 1); // 1-indexed
            
            // Kill all creepers in range
            for (int j = 0; j < n; j++) {
                if (abs(best - j) < e[best]) {
                    dead[j] = true;
                }
            }
        }
        
        // Check if all creepers are dead
        bool all_dead = true;
        for (int i = 0; i < n; i++) {
            if (!dead[i]) {
                all_dead = false;
                break;
            }
        }
        
        if (!all_dead) {
            cout << -1 << "\n";
        } else {
            cout << detonations.size() << "\n";
            for (int i = 0; i < detonations.size(); i++) {
                cout << detonations[i];
                if (i < detonations.size() - 1) cout << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}