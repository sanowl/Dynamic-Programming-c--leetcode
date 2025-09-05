class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        // If k is 0, Alice doesn't draw any cards, so she has 0 points (≤ n)
        if (k == 0 || n >= k + maxPts - 1) {
            return 1.0;
        }
        
        // dp[i] = probability of getting exactly i points
        vector<double> dp(k + maxPts, 0.0);
        dp[0] = 1.0; // Start with 0 points with probability 1
        
        double windowSum = 1.0; // Sum of probabilities for current window
        double result = 0.0;
        
        for (int i = 1; i <= k + maxPts - 1; i++) {
            // Calculate probability of getting exactly i points
            dp[i] = windowSum / maxPts;
            
            // If we have k or more points, we stop drawing
            if (i < k) {
                windowSum += dp[i];
            } else {
                // If i >= k and i <= n, add to result
                if (i <= n) {
                    result += dp[i];
                }
            }
            
            // Remove the leftmost element from sliding window
            if (i >= maxPts) {
                windowSum -= dp[i - maxPts];
            }
        }
        
        return result;
    }
};