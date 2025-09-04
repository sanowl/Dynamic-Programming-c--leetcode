#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    // 2D DP Solution - O(m*n) space
    int numDistinct2D(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // dp[i][j] = number of ways to form t[0...j-1] using s[0...i-1]
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));
        
        // Base case: empty string t can be formed in 1 way from any string s
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 1;
        }
        
        // Fill the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // Always have the option to skip current character in s
                dp[i][j] = dp[i-1][j];
                
                // If characters match, we can also use the current character
                if (s[i-1] == t[j-1]) {
                    dp[i][j] += dp[i-1][j-1];
                }
            }
        }
        
        return (int)dp[m][n];
    }
    
    // Space Optimized Solution - O(n) space
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // Use 1D array to save space
        vector<long long> dp(n + 1, 0);
        dp[0] = 1; // Base case: empty string can be formed in 1 way
        
        for (int i = 1; i <= m; i++) {
            // Process from right to left to avoid overwriting values we need
            for (int j = n; j >= 1; j--) {
                if (s[i-1] == t[j-1]) {
                    dp[j] += dp[j-1];
                }
                // If characters don't match, dp[j] remains the same
            }
        }
        
        return (int)dp[n];
    }
    
    // Recursive solution with memoization for better understanding
    int numDistinctRecursive(string s, string t) {
        vector<vector<int>> memo(s.length() + 1, vector<int>(t.length() + 1, -1));
        return helper(s, t, 0, 0, memo);
    }
    
private:
    int helper(const string& s, const string& t, int i, int j, vector<vector<int>>& memo) {
        // Base cases
        if (j == t.length()) return 1; // Found a valid subsequence
        if (i == s.length()) return 0; // No more characters in s
        
        if (memo[i][j] != -1) return memo[i][j];
        
        // Always have the option to skip current character in s
        int result = helper(s, t, i + 1, j, memo);
        
        // If characters match, we can also use the current character
        if (s[i] == t[j]) {
            result += helper(s, t, i + 1, j + 1, memo);
        }
        
        return memo[i][j] = result;
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    string s1 = "rabbbit";
    string t1 = "rabbit";
    cout << "Test 1:" << endl;
    cout << "s = \"" << s1 << "\", t = \"" << t1 << "\"" << endl;
    cout << "2D DP: " << sol.numDistinct2D(s1, t1) << endl;
    cout << "1D DP: " << sol.numDistinct(s1, t1) << endl;
    cout << "Recursive: " << sol.numDistinctRecursive(s1, t1) << endl;
    cout << "Expected: 3" << endl << endl;
    
    // Test case 2
    string s2 = "babgbag";
    string t2 = "bag";
    cout << "Test 2:" << endl;
    cout << "s = \"" << s2 << "\", t = \"" << t2 << "\"" << endl;
    cout << "2D DP: " << sol.numDistinct2D(s2, t2) << endl;
    cout << "1D DP: " << sol.numDistinct(s2, t2) << endl;
    cout << "Recursive: " << sol.numDistinctRecursive(s2, t2) << endl;
    cout << "Expected: 5" << endl << endl;
    
    // Additional test case
    string s3 = "aaa";
    string t3 = "aa";
    cout << "Test 3:" << endl;
    cout << "s = \"" << s3 << "\", t = \"" << t3 << "\"" << endl;
    cout << "2D DP: " << sol.numDistinct2D(s3, t3) << endl;
    cout << "1D DP: " << sol.numDistinct(s3, t3) << endl;
    cout << "Recursive: " << sol.numDistinctRecursive(s3, t3) << endl;
    cout << "Expected: 3" << endl << endl;
    
    // Edge case: empty t
    string s4 = "abc";
    string t4 = "";
    cout << "Test 4:" << endl;
    cout << "s = \"" << s4 << "\", t = \"" << t4 << "\"" << endl;
    cout << "2D DP: " << sol.numDistinct2D(s4, t4) << endl;
    cout << "1D DP: " << sol.numDistinct(s4, t4) << endl;
    cout << "Recursive: " << sol.numDistinctRecursive(s4, t4) << endl;
    cout << "Expected: 1" << endl;
    
    return 0;
}