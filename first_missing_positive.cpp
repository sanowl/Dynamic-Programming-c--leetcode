#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Main solution - O(n) time, O(1) space
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
    
    // Alternative cyclic sort approach
    int firstMissingPositiveCyclicSort(vector<int>& nums) {
        int n = nums.size();
        
        // Place each positive number i at index i-1
        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        // Find first missing positive
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        
        return n + 1;
    }
    
    // Brute force approach for comparison - O(n²) time
    int firstMissingPositiveBruteForce(vector<int>& nums) {
        int n = nums.size();
        
        for (int i = 1; i <= n + 1; i++) {
            bool found = false;
            for (int j = 0; j < n; j++) {
                if (nums[j] == i) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return i;
            }
        }
        
        return n + 1;
    }
};

// Test function
void runTests() {
    Solution sol;
    
    cout << "Testing First Missing Positive Solutions:" << endl;
    cout << endl;
    
    // Test case 1
    vector<int> nums1 = {1, 2, 0};
    vector<int> nums1_copy1 = nums1, nums1_copy2 = nums1;
    cout << "Test 1: [1,2,0]" << endl;
    cout << "Main solution: " << sol.firstMissingPositive(nums1) << endl;
    cout << "Cyclic sort: " << sol.firstMissingPositiveCyclicSort(nums1_copy1) << endl;
    cout << "Brute force: " << sol.firstMissingPositiveBruteForce(nums1_copy2) << endl;
    cout << "Expected: 3" << endl << endl;
    
    // Test case 2
    vector<int> nums2 = {3, 4, -1, 1};
    vector<int> nums2_copy1 = nums2, nums2_copy2 = nums2;
    cout << "Test 2: [3,4,-1,1]" << endl;
    cout << "Main solution: " << sol.firstMissingPositive(nums2) << endl;
    cout << "Cyclic sort: " << sol.firstMissingPositiveCyclicSort(nums2_copy1) << endl;
    cout << "Brute force: " << sol.firstMissingPositiveBruteForce(nums2_copy2) << endl;
    cout << "Expected: 2" << endl << endl;
    
    // Test case 3
    vector<int> nums3 = {7, 8, 9, 11, 12};
    vector<int> nums3_copy1 = nums3, nums3_copy2 = nums3;
    cout << "Test 3: [7,8,9,11,12]" << endl;
    cout << "Main solution: " << sol.firstMissingPositive(nums3) << endl;
    cout << "Cyclic sort: " << sol.firstMissingPositiveCyclicSort(nums3_copy1) << endl;
    cout << "Brute force: " << sol.firstMissingPositiveBruteForce(nums3_copy2) << endl;
    cout << "Expected: 1" << endl << endl;
    
    // Test case 4 - edge case: single element
    vector<int> nums4 = {1};
    vector<int> nums4_copy1 = nums4, nums4_copy2 = nums4;
    cout << "Test 4: [1]" << endl;
    cout << "Main solution: " << sol.firstMissingPositive(nums4) << endl;
    cout << "Cyclic sort: " << sol.firstMissingPositiveCyclicSort(nums4_copy1) << endl;
    cout << "Brute force: " << sol.firstMissingPositiveBruteForce(nums4_copy2) << endl;
    cout << "Expected: 2" << endl << endl;
    
    // Test case 5 - edge case: all negative
    vector<int> nums5 = {-1, -2, -3};
    vector<int> nums5_copy1 = nums5, nums5_copy2 = nums5;
    cout << "Test 5: [-1,-2,-3]" << endl;
    cout << "Main solution: " << sol.firstMissingPositive(nums5) << endl;
    cout << "Cyclic sort: " << sol.firstMissingPositiveCyclicSort(nums5_copy1) << endl;
    cout << "Brute force: " << sol.firstMissingPositiveBruteForce(nums5_copy2) << endl;
    cout << "Expected: 1" << endl << endl;
    
    // Test case 6 - consecutive sequence
    vector<int> nums6 = {1, 2, 3, 4, 5};
    vector<int> nums6_copy1 = nums6, nums6_copy2 = nums6;
    cout << "Test 6: [1,2,3,4,5]" << endl;
    cout << "Main solution: " << sol.firstMissingPositive(nums6) << endl;
    cout << "Cyclic sort: " << sol.firstMissingPositiveCyclicSort(nums6_copy1) << endl;
    cout << "Brute force: " << sol.firstMissingPositiveBruteForce(nums6_copy2) << endl;
    cout << "Expected: 6" << endl << endl;
}

// Step-by-step explanation function
void explainAlgorithm() {
    cout << "Algorithm Explanation:" << endl;
    cout << "=====================" << endl;
    cout << "The key insight is that the first missing positive must be in range [1, n+1]" << endl;
    cout << "where n is the array length." << endl << endl;
    
    cout << "Main Algorithm Steps:" << endl;
    cout << "1. Replace all non-positive numbers and numbers > n with (n+1)" << endl;
    cout << "2. For each number x in the array:" << endl;
    cout << "   - Use x as an index (x-1) to mark presence" << endl;
    cout << "   - Make nums[x-1] negative to indicate x is present" << endl;
    cout << "3. Find first positive number at index i, return i+1" << endl;
    cout << "4. If all are negative, return n+1" << endl << endl;
    
    cout << "Example walkthrough with [3,4,-1,1]:" << endl;
    cout << "Step 1: [3,4,4,1] (replace -1 with 4+1=5, but we use 4 for simplicity)" << endl;
    cout << "Step 2: Process each number:" << endl;
    cout << "  - 3: make nums[2] negative -> [3,4,-4,1]" << endl;
    cout << "  - 4: skip (4 > n)" << endl;
    cout << "  - -4: abs(-4)=4, skip" << endl;
    cout << "  - 1: make nums[0] negative -> [-3,4,-4,1]" << endl;
    cout << "Step 3: First positive is at index 1, so answer is 1+1=2" << endl;
}

int main() {
    runTests();
    cout << endl;
    explainAlgorithm();
    
    return 0;
}