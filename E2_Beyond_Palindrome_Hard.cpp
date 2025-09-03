#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        // Key insight: f(s) removes all "10" pairs, leaving only unmatched 0s and 1s
        // The result is always of form 0^a 1^b where a,b >= 0
        // For f(s) = f(rev(s)), we need both to have same a and b values
        
        // Let's think of it as: how many 0s and 1s survive the deletion process?
        // A 0 survives if it's not matched with any 1 to its right
        // A 1 survives if there are no 0s to its left to match with
        
        // dp[i][j] = number of ways to build string of length i 
        // where j represents the "balance" = (unmatched 0s) - (unmatched 1s)
        // But we need to be more careful about what this balance means
        
        vector<long long> dp(n + 1, 0);
        vector<long long> ndp(n + 1, 0);
        
        dp[0] = 1; // Empty string
        
        for (int i = 0; i < n; i++) {
            fill(ndp.begin(), ndp.end(), 0);
            
            for (int balance = 0; balance <= i; balance++) {
                if (dp[balance] == 0) continue;
                
                // Add '0' - increases the number of unmatched 0s
                if (balance + 1 <= n) {
                    ndp[balance + 1] = (ndp[balance + 1] + dp[balance]) % MOD;
                }
                
                // Add '1' - either matches with an unmatched 0 or becomes unmatched
                if (balance > 0) {
                    // Matches with a previous unmatched 0
                    ndp[balance - 1] = (ndp[balance - 1] + dp[balance]) % MOD;
                } else {
                    // No 0 to match with, but this doesn't increase balance
                    // because we're counting net effect
                    ndp[balance] = (ndp[balance] + dp[balance]) % MOD;
                }
            }
            dp = ndp;
        }
        
        long long result = 0;
        for (int i = 0; i <= n; i++) {
            result = (result + dp[i]) % MOD;
        }
        
        cout << result << "\n";
    }
    
    return 0;
}