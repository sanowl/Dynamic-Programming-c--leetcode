class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.length();
        int m = key.length();
        
        unordered_map<char, vector<int>> positions;
        for (int i = 0; i < n; i++) {
            positions[ring[i]].push_back(i);
        }
        
        vector<vector<int>> memo(m, vector<int>(n, -1));
        
        function<int(int, int)> dp = [&](int keyIdx, int ringPos) -> int {
            if (keyIdx == m) return 0;
            if (memo[keyIdx][ringPos] != -1) return memo[keyIdx][ringPos];
            
            int result = INT_MAX;
            for (int pos : positions[key[keyIdx]]) {
                int steps = min(abs(pos - ringPos), n - abs(pos - ringPos));
                result = min(result, steps + 1 + dp(keyIdx + 1, pos));
            }
            
            return memo[keyIdx][ringPos] = result;
        };
        
        return dp(0, 0);
    }
};