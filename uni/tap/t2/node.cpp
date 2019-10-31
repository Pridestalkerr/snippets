#include <cstddef>

class Node
{
	int value_;
public:
	Node *left_;
	Node *right_;
	Node *parent_;

	Node(const int value)
		:
		value_(value),
		left_(NULL),
		right_(NULL),
		parent_(NULL)
	{};

	static Node* push(Node *node, const int value)
	{
		//trace back to head
		while(node->parent_ != NULL)
			node = node->parent_;

		while(true) //simulate recursion
		{
			if(value < node->value_)
			{
				if(node->left_ == NULL)
				{
					node->left_ = new Node(value);
					return node->left_;
				}
				else
					node = node->left_;
			}
			else
			{
				if(node->right_ == NULL)
				{
					node->right_ = new Node(value);
					return node->right_;
				}
				else
					node = node->right_;
			}
		}
	};

	static Node* removeNodes(Node *node, const int value)
	{
		Node *root = NULL;
		//trace back to head
		while(node->parent_ != NULL)
			node = node->parent_;

		while(true) //simulate recursion
		{
			if(value == node->value_)
			{
				//right left strategy
				if(node->right_ == NULL)
				{
					root = node->left_; //could be null, we dont care (that means the tree is empty)
					delete node;
				}
				else
				{
					root = node;
					node = node->right_;
					prev = node->right_;
					while(node->left_ != NULL)
					{
						prev = node;
						node = node->left_;
					}
					
					if(node == prev)
					{
						
					}
					delete node;
				}

			}
			else if(value < node->value_)
			{
				if(node->left_ == NULL)
				{
					node->left_ = new Node(value);
					return node->left_;
				}
				else
					node = node->left_;
			}
			else
			{
				if(node->right_ == NULL)
				{
					node->right_ = new Node(value);
					return node->right_;
				}
				else
					node = node->right_;
			}
		}

	};
};

int main()
{
	Node *root = new Node(5);

	Node::push(root, 2);
	Node::push(root, 8);

	return 0;
}