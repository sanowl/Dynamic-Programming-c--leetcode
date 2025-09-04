class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Replace non-positive numbers and numbers > n with n+1
        for (int i = 0; i < n; i++) {
            if (nums[i] <= 0 || nums[i] > n) {
                nums[i] = n + 1;
            }
        }
        
        // Step 2: Mark presence of numbers by making corresponding indices negative
        for (int i = 0; i < n; i++) {
            int num = abs(nums[i]);
            if (num <= n) {
                // Make the number at index (num-1) negative to mark presence
                if (nums[num - 1] > 0) {
                    nums[num - 1] = -nums[num - 1];
                }
            }
        }
        
        // Step 3: Find first positive number, its index+1 is the answer
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        
        // If all positions are marked, the answer is n+1
        return n + 1;
    }
};