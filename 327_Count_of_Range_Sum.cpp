class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        vector<long long> sorted = prefix;
        sort(sorted.begin(), sorted.end());
        
        vector<int> bit(sorted.size() + 1, 0);
        
        function<int(long long)> getIndex = [&](long long val) -> int {
            return lower_bound(sorted.begin(), sorted.end(), val) - sorted.begin() + 1;
        };
        
        function<void(int)> update = [&](int idx) {
            while (idx < bit.size()) {
                bit[idx]++;
                idx += idx & (-idx);
            }
        };
        
        function<int(int)> query = [&](int idx) -> int {
            int result = 0;
            while (idx > 0) {
                result += bit[idx];
                idx -= idx & (-idx);
            }
            return result;
        };
        
        int result = 0;
        for (int i = 0; i <= n; i++) {
            long long sum = prefix[i];
            int left = getIndex(sum - upper);
            int right = getIndex(sum - lower + 1) - 1;
            result += query(right) - query(left - 1);
            update(getIndex(sum));
        }
        
        return result;
    }
};