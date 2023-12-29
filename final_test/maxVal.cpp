#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
    int32_t val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

std::vector<int32_t> largestValues(TreeNode* root) {
    std::vector<int32_t> result;
    if (root == nullptr) {
        return result;
    }
    
    std::queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        int32_t maxVal = INT32_MIN;
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            maxVal = std::max(maxVal, node->val);
            
            if (node->left != nullptr) {
                q.push(node->left);
            }
            
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        
        result.push_back(maxVal);
    }
    
    return result;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    std::vector<int32_t> result = largestValues(root);
    
    for (int32_t val : result) {
        std::cout << val << " ";
    }
    
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;
    
}
