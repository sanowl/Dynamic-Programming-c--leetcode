#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
        // dp[i] represents the number of unique BSTs with i nodes
        vector<int> dp(n + 1, 0);
        
        // Base cases
        dp[0] = 1; // Empty tree
        dp[1] = 1; // Single node tree
        
        // Fill dp array using the recurrence relation
        for (int nodes = 2; nodes <= n; nodes++) {
            for (int root = 1; root <= nodes; root++) {
                // Left subtree has (root-1) nodes
                // Right subtree has (nodes-root) nodes
                dp[nodes] += dp[root - 1] * dp[nodes - root];
            }
        }
        
        return dp[n];
    }
};

// Alternative solution using Catalan number formula
class SolutionCatalan {
public:
    int numTrees(int n) {
        // The nth Catalan number is C(n) = (1/(n+1)) * C(2n, n)
        // Where C(2n, n) = (2n)! / (n! * n!)
        // We can compute this iteratively to avoid overflow
        
        long long result = 1;
        for (int i = 0; i < n; i++) {
            result = result * (2 * n - i) / (i + 1);
        }
        return result / (n + 1);
    }
};

int main() {
    Solution sol;
    SolutionCatalan solCat;
    
    cout << "Test case 1: n = 3" << endl;
    cout << "DP Solution: " << sol.numTrees(3) << endl;
    cout << "Catalan Solution: " << solCat.numTrees(3) << endl;
    
    cout << "\nTest case 2: n = 1" << endl;
    cout << "DP Solution: " << sol.numTrees(1) << endl;
    cout << "Catalan Solution: " << solCat.numTrees(1) << endl;
    
    cout << "\nAdditional test cases:" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << "n = " << i << ": " << sol.numTrees(i) << endl;
    }
    
    return 0;
}