#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<long long> h(n);
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        
        // dp[i][j] = minimum attacks to kill mobs from i to j (inclusive)
        vector<vector<long long>> dp(n, vector<long long>(n, 0));
        
        // Base case: single mobs
        for (int i = 0; i < n; i++) {
            dp[i][i] = h[i];
        }
        
        // Fill dp table for increasing lengths
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                
                // Option 1: Kill all mobs individually
                long long sum = 0;
                for (int k = i; k <= j; k++) {
                    sum += h[k];
                }
                dp[i][j] = sum;
                
                // Option 2: Kill mob k first (k from i to j)
                for (int k = i; k <= j; k++) {
                    long long cost = h[k]; // Cost to kill mob k
                    
                    // Left part: mobs i to k-1 (unaffected)
                    if (k > i) {
                        cost += dp[i][k-1];
                    }
                    
                    // Right part: mobs k+1 to j (they fall)
                    if (k < j) {
                        // Calculate fall damage for mob k+1
                        long long fall_damage = k; // Number of mobs below k+1 in original stack
                        long long new_health = max(0LL, h[k+1] - fall_damage);
                        
                        if (new_health > 0) {
                            // If mob k+1 survives, we need to solve for k+1 to j with updated health
                            vector<long long> new_h;
                            new_h.push_back(new_health);
                            for (int m = k+2; m <= j; m++) {
                                new_h.push_back(h[m]);
                            }
                            
                            // Create temporary dp for the new segment
                            int sz = new_h.size();
                            vector<vector<long long>> temp_dp(sz, vector<long long>(sz, 0));
                            
                            // Base case
                            for (int p = 0; p < sz; p++) {
                                temp_dp[p][p] = new_h[p];
                            }
                            
                            // Fill temp dp
                            for (int temp_len = 2; temp_len <= sz; temp_len++) {
                                for (int p = 0; p <= sz - temp_len; p++) {
                                    int q = p + temp_len - 1;
                                    
                                    // Kill all individually
                                    long long temp_sum = 0;
                                    for (int r = p; r <= q; r++) {
                                        temp_sum += new_h[r];
                                    }
                                    temp_dp[p][q] = temp_sum;
                                    
                                    // Try killing each mob first
                                    for (int r = p; r <= q; r++) {
                                        long long temp_cost = new_h[r];
                                        if (r > p) temp_cost += temp_dp[p][r-1];
                                        if (r < q) temp_cost += temp_dp[r+1][q];
                                        temp_dp[p][q] = min(temp_dp[p][q], temp_cost);
                                    }
                                }
                            }
                            
                            cost += temp_dp[0][sz-1];
                        } else {
                            // Mob k+1 dies from fall damage, continue chain
                            // This creates a recursive fall situation
                            // For simplicity, we'll handle this case by simulation
                            vector<long long> remaining;
                            for (int m = k+1; m <= j; m++) {
                                remaining.push_back(h[m]);
                            }
                            
                            // Simulate fall damage chain
                            long long current_fall = k;
                            int idx = 0;
                            while (idx < remaining.size()) {
                                remaining[idx] -= current_fall;
                                if (remaining[idx] <= 0) {
                                    remaining.erase(remaining.begin() + idx);
                                    current_fall = 1; // Next fall damage is 1
                                } else {
                                    break;
                                }
                            }
                            
                            // Add cost for remaining mobs (kill individually)
                            for (long long rem_h : remaining) {
                                cost += rem_h;
                            }
                        }
                    }
                    
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
        
        cout << dp[0][n-1] << "\n";
    }
    
    return 0;
}