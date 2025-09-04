#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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

void printInorder(TreeNode* root, vector<int>& result) {
    if (!root) {
        result.push_back(-1); // Use -1 to represent null
        return;
    }
    result.push_back(root->val);
    printInorder(root->left, result);
    printInorder(root->right, result);
}

void printTree(TreeNode* root) {
    vector<int> result;
    printInorder(root, result);
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        if (result[i] == -1) {
            cout << "null";
        } else {
            cout << result[i];
        }
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]";
}

int main() {
    Solution sol;
    
    cout << "Test case 1: n = 3" << endl;
    vector<TreeNode*> trees3 = sol.generateTrees(3);
    cout << "Output: [";
    for (int i = 0; i < trees3.size(); i++) {
        printTree(trees3[i]);
        if (i < trees3.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    
    cout << "\nTest case 2: n = 1" << endl;
    vector<TreeNode*> trees1 = sol.generateTrees(1);
    cout << "Output: [";
    for (int i = 0; i < trees1.size(); i++) {
        printTree(trees1[i]);
        if (i < trees1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    
    return 0;
}