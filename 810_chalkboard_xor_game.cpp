class Solution {
public:
    bool xorGame(vector<int>& nums) {
        // Calculate XOR of all elements
        int totalXor = 0;
        for (int num : nums) {
            totalXor ^= num;
        }
        
        // Alice wins if:
        // 1. Initial XOR is 0 (she wins immediately), OR
        // 2. Array has even length (she can always avoid losing)
        return totalXor == 0 || nums.size() % 2 == 0;
    }
};