class Solution {
    
    // 2D DP Solution - O(m*n) space
    public boolean isInterleave2D(String s1, String s2, String s3) {
        int m = s1.length();
        int n = s2.length();
        
        // Check if lengths match
        if (m + n != s3.length()) {
            return false;
        }
        
        // dp[i][j] = true if first i chars of s1 and first j chars of s2 
        // can form first i+j chars of s3
        boolean[][] dp = new boolean[m + 1][n + 1];
        
        // Base case: empty strings
        dp[0][0] = true;
        
        // Fill first row: using only s2
        for (int j = 1; j <= n; j++) {
            dp[0][j] = dp[0][j-1] && s2.charAt(j-1) == s3.charAt(j-1);
        }
        
        // Fill first column: using only s1
        for (int i = 1; i <= m; i++) {
            dp[i][0] = dp[i-1][0] && s1.charAt(i-1) == s3.charAt(i-1);
        }
        
        // Fill the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int k = i + j - 1; // Current position in s3
                
                // Two ways to form s3[0...k]:
                // 1. Use s1[i-1] and previous state dp[i-1][j]
                // 2. Use s2[j-1] and previous state dp[i][j-1]
                dp[i][j] = (dp[i-1][j] && s1.charAt(i-1) == s3.charAt(k)) ||
                          (dp[i][j-1] && s2.charAt(j-1) == s3.charAt(k));
            }
        }
        
        return dp[m][n];
    }
    
    // Space Optimized Solution - O(min(m,n)) space
    public boolean isInterleave(String s1, String s2, String s3) {
        int m = s1.length();
        int n = s2.length();
        
        // Check if lengths match
        if (m + n != s3.length()) {
            return false;
        }
        
        // Make s2 the shorter string to optimize space
        if (m < n) {
            return isInterleave(s2, s1, s3);
        }
        
        // Now n <= m, so we use O(n+1) space
        boolean[] dp = new boolean[n + 1];
        
        // Base case
        dp[0] = true;
        
        // Fill first row: using only s2
        for (int j = 1; j <= n; j++) {
            dp[j] = dp[j-1] && s2.charAt(j-1) == s3.charAt(j-1);
        }
        
        // Fill row by row
        for (int i = 1; i <= m; i++) {
            // Update dp[0] for current row (using only s1)
            dp[0] = dp[0] && s1.charAt(i-1) == s3.charAt(i-1);
            
            for (int j = 1; j <= n; j++) {
                int k = i + j - 1; // Current position in s3
                
                // dp[j] represents dp[i][j] for current iteration
                // Before update: dp[j] = dp[i-1][j] (from previous row)
                // dp[j-1] = dp[i][j-1] (from current row, already updated)
                dp[j] = (dp[j] && s1.charAt(i-1) == s3.charAt(k)) ||
                        (dp[j-1] && s2.charAt(j-1) == s3.charAt(k));
            }
        }
        
        return dp[n];
    }
}

// Test class
class InterleaveStringTest {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        // Test case 1
        String s1_1 = "aabcc";
        String s2_1 = "dbbca";
        String s3_1 = "aadbbcbcac";
        System.out.println("Test 1:");
        System.out.println("s1: " + s1_1);
        System.out.println("s2: " + s2_1);
        System.out.println("s3: " + s3_1);
        System.out.println("2D DP Result: " + solution.isInterleave2D(s1_1, s2_1, s3_1));
        System.out.println("Optimized Result: " + solution.isInterleave(s1_1, s2_1, s3_1));
        System.out.println("Expected: true\n");
        
        // Test case 2
        String s1_2 = "aabcc";
        String s2_2 = "dbbca";
        String s3_2 = "aadbbbaccc";
        System.out.println("Test 2:");
        System.out.println("s1: " + s1_2);
        System.out.println("s2: " + s2_2);
        System.out.println("s3: " + s3_2);
        System.out.println("2D DP Result: " + solution.isInterleave2D(s1_2, s2_2, s3_2));
        System.out.println("Optimized Result: " + solution.isInterleave(s1_2, s2_2, s3_2));
        System.out.println("Expected: false\n");
        
        // Test case 3
        String s1_3 = "";
        String s2_3 = "";
        String s3_3 = "";
        System.out.println("Test 3:");
        System.out.println("s1: \"" + s1_3 + "\"");
        System.out.println("s2: \"" + s2_3 + "\"");
        System.out.println("s3: \"" + s3_3 + "\"");
        System.out.println("2D DP Result: " + solution.isInterleave2D(s1_3, s2_3, s3_3));
        System.out.println("Optimized Result: " + solution.isInterleave(s1_3, s2_3, s3_3));
        System.out.println("Expected: true\n");
        
        // Additional test case
        String s1_4 = "a";
        String s2_4 = "b";
        String s3_4 = "ab";
        System.out.println("Test 4:");
        System.out.println("s1: " + s1_4);
        System.out.println("s2: " + s2_4);
        System.out.println("s3: " + s3_4);
        System.out.println("2D DP Result: " + solution.isInterleave2D(s1_4, s2_4, s3_4));
        System.out.println("Optimized Result: " + solution.isInterleave(s1_4, s2_4, s3_4));
        System.out.println("Expected: true");
    }
}