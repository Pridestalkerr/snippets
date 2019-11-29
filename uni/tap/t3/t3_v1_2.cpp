#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Node
{
public:
    int data_; 
    Node *left_, *right_;

    Node(const int data)
        :
        data_(data),
        left_(NULL),
        right_(NULL)
    {};
};

Node* buildTree(std::vector <int> &inorder, std::vector <int> &postorder, int i_start, int i_end, int &p_root, std::unordered_map <int, int> &inorder_lookup)
{

    if(i_start > i_end)
        return NULL;

    int val = postorder[p_root];

    if(inorder_lookup[val] < i_start || inorder_lookup[val] > i_end)
    {
        std::cout << "nu"; 
        exit(-1);
    }

    Node *node = new Node(val);
    --p_root;

    if(i_start == i_end)
        return node;

    //post = SDR : right before left otherwise p_root will break
    node->right_ = buildTree(inorder, postorder, inorder_lookup[val] + 1, i_end, p_root, inorder_lookup);
    node->left_ = buildTree(inorder, postorder, i_start, inorder_lookup[val] - 1, p_root, inorder_lookup);

    return node;
}

void preOrder(Node* node) 
{
    if(node == NULL) 
        return; 
    std::cout << node->data_ << ' '; 
    preOrder(node->left_); 
    preOrder(node->right_); 
} 

int main(int argc, char **argv)
{
    std::ifstream file(argv[1]);
    int n;
    file >> n;

    std::unordered_map <int, int> inorder_lookup; //node, index inside vector
    std::vector <int> inorder;
    std::vector <int> postorder;
    inorder.reserve(n);
    postorder.reserve(n);

    for(int i = 0; i < n; ++i)
    {
        int val;
        file >> val;
        postorder.push_back(val);
    }
    for(int i = 0; i < n; ++i)
    {
        int val;
        file >> val;
        inorder.push_back(val);
        inorder_lookup[val] = i;
    }

    int p_root = n - 1;
    Node* root = buildTree(inorder, postorder, 0, n - 1, p_root, inorder_lookup);
  
    preOrder(root);

	return 0;
}