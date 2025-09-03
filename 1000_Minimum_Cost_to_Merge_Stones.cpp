class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if ((n - 1) % (k - 1) != 0) return -1;
        
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stones[i];
        }
        
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int step = k - 1;
        
        for (int len = k; len <= n; len++) {
            int maxI = n - len;
            for (int i = 0; i <= maxI; i++) {
                int j = i + len - 1;
                int minCost = INT_MAX;
                
                for (int t = i; t < j; t += step) {
                    int cost = dp[i][t] + dp[t + 1][j];
                    if (cost < minCost) minCost = cost;
                }
                
                if ((j - i) % step == 0) {
                    minCost += prefix[j + 1] - prefix[i];
                }
                
                dp[i][j] = minCost;
            }
        }
        
        return dp[0][n - 1];
    }
};