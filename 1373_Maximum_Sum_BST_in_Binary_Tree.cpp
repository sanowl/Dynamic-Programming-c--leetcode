class Solution {
public:
    int maxSumBST(TreeNode* root) {
        int maxSum = 0;
        
        function<tuple<bool, int, int, int>(TreeNode*)> dfs = [&](TreeNode* node) -> tuple<bool, int, int, int> {
            if (!node) {
                return {true, 0, INT_MAX, INT_MIN};
            }
            
            auto [leftValid, leftSum, leftMin, leftMax] = dfs(node->left);
            auto [rightValid, rightSum, rightMin, rightMax] = dfs(node->right);
            
            if (leftValid && rightValid && leftMax < node->val && node->val < rightMin) {
                int currentSum = leftSum + rightSum + node->val;
                maxSum = max(maxSum, currentSum);
                return {true, currentSum, min(leftMin, node->val), max(rightMax, node->val)};
            }
            
            return {false, 0, 0, 0};
        };
        
        dfs(root);
        return maxSum;
    }
};