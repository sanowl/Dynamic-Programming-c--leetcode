class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        int jumps = 0, currentEnd = 0, farthest = 0;
        
        for (int i = 0; i < n - 1; i++) {
            int newFarthest = i + nums[i];
            if (newFarthest > farthest) {
                farthest = newFarthest;
            }
            
            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
                if (currentEnd >= n - 1) return jumps;
            }
        }
        
        return jumps;
    }
};