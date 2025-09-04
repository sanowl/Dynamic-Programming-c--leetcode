class Solution {
public:
    map<pair<int, int>, vector<TreeNode*>> memo;
    
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return helper(1, n);
    }
    
private:
    vector<TreeNode*> helper(int start, int end) {
        vector<TreeNode*> result;
        
        if (start > end) {
            result.push_back(nullptr);
            return result;
        }
        
        if (memo.count({start, end})) {
            return memo[{start, end}];
        }
        
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> leftTrees = helper(start, i - 1);
            vector<TreeNode*> rightTrees = helper(i + 1, end);
            
            for (TreeNode* left : leftTrees) {
                for (TreeNode* right : rightTrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        
        memo[{start, end}] = result;
        return result;
    }
};