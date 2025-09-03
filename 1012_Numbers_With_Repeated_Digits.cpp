class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        string s = to_string(n);
        int len = s.length();
        
        vector<vector<vector<int>>> memo(len, vector<vector<int>>(1 << 10, vector<int>(2, -1)));
        
        function<int(int, int, bool, bool)> dp = [&](int pos, int mask, bool tight, bool hasRepeated) -> int {
            if (pos == len) return hasRepeated ? 1 : 0;
            
            if (!tight && memo[pos][mask][hasRepeated] != -1) {
                return memo[pos][mask][hasRepeated];
            }
            
            int limit = tight ? s[pos] - '0' : 9;
            int result = 0;
            
            for (int d = 0; d <= limit; d++) {
                bool newTight = tight && (d == limit);
                bool newHasRepeated = hasRepeated || (mask & (1 << d));
                int newMask = mask | (1 << d);
                
                result += dp(pos + 1, newMask, newTight, newHasRepeated);
            }
            
            if (!tight) {
                memo[pos][mask][hasRepeated] = result;
            }
            
            return result;
        };
        
        return dp(0, 0, true, false);
    }
};