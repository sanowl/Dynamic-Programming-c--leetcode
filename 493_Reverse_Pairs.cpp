class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> temp(n);
        
        function<int(int, int)> mergeSort = [&](int left, int right) -> int {
            if (left >= right) return 0;
            
            int mid = left + (right - left) / 2;
            int count = mergeSort(left, mid) + mergeSort(mid + 1, right);
            
            int i = left, j = mid + 1;
            while (i <= mid) {
                while (j <= right && (long long)nums[i] > 2LL * nums[j]) {
                    j++;
                }
                count += j - (mid + 1);
                i++;
            }
            
            i = left; j = mid + 1; int k = left;
            while (i <= mid && j <= right) {
                if (nums[i] <= nums[j]) {
                    temp[k++] = nums[i++];
                } else {
                    temp[k++] = nums[j++];
                }
            }
            
            while (i <= mid) temp[k++] = nums[i++];
            while (j <= right) temp[k++] = nums[j++];
            
            for (int i = left; i <= right; i++) {
                nums[i] = temp[i];
            }
            
            return count;
        };
        
        return mergeSort(0, n - 1);
    }
};