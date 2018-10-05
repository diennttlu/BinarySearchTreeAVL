#ifndef node_h
#define node_h
#include <math.h>
#include <limits.h>
template <class T>
struct Node
{
	T data;
	Node<T> *left;
	Node<T> *right;
	int height;
};

template <class T>

class TreeAVL
{
private:
	Node<T> *root;

	/*void MakeEmpty(Node<T> *root)
	{
		if(root == NULL)
            return;
        MakeEmpty(root->left);
        MakeEmpty(root->right);
        delete root;
	}*/
	Node<T>* Insert(T data, Node<T> *root)
	{
		if(root == NULL)
		{
			root = new Node<T>;
			root->data = data; 
			root->height = 0;
			root->left =NULL;
			root->right=NULL;
		}
		else if(data < root->data)
		{
			root->left = Insert(data,root->left);
			if(Height(root->left) - Height(root->right) == 2)
			{
				if(data < root->left->data)
					root = SingleRightRotate(root);
				else
					root = DoubleRightRotate(root);
			}
		}
		else if(data >  root->data)
		{
			root->right = Insert(data,root->right);
			if(Height(root->right) - Height(root->left)  == 2)
			{
				if(data > root->right->data)
					root = SingleLeftRotate(root);
				else
					root = DoubleLeftRotate(root);
			}
		}

		root->height = max(Height(root->left), Height(root->right)) +1; // update height after balance
		return root;
	};
	Node<T>* DeleteNodeOfTree(T data, Node<T>* &root)
    {
    	if(root == 0) // Base case: If the tree is empty
    		return root;
    	if(data < root->data)
    		root->left = DeleteNodeOfTree(data, root->left);
    	else if(data > root->data)
    		root->right =  DeleteNodeOfTree(data, root->right);
    	else
    	{
      		// node with only on child or no child
    		if(root->left == 0)
    		{
    			Node<T> *temp = root;
    			root = root->right;
         		delete temp;
         		return root;
         	}
    		else if(root->right == 0)
    		{
    			Node<T> *temp = root;
    			root = root->left;
    			delete temp;
    			return root;
    		}    		// node with two child: find min in right subtree;
    		root->data = FindMin(root->right);
    		root->right = DeleteNodeOfTree(root->data, root->right); 
    	}

    	root->height = max(Height(root->left),Height(root->right)) + 1;
    	int balance = GetBalance(root);
    	// single right rotate (left left)
    	if(balance > 1 && GetBalance(root->left) >= 0)
    		return SingleRightRotate(root);
    	// double right rotate (left right)
    	if(balance > 1 && GetBalance(root->left) < 0)
    		return DoubleRightRotate(root);
    	// single left rotate (right right)
    	if(balance < -1 && GetBalance(root->right) <= 0)
    		return SingleLeftRotate(root);
    	// double left rotate (right left)
    	if(balance < -1 && GetBalance(root->right) > 0)
    		return DoubleLeftRotate(root);
    	return root;
    };
	
	Node<T>* SingleRightRotate(Node<T>* &root)
	{
		Node<T>* u = root->left;
		root->left = u->right; // rotate
		u->right = root;
		// update heights
		root->height = max(Height(root->left), Height(root->right))+1;
		u->height = max(Height(u->left), root->height) +1;
		return u;
	};

	Node<T>* SingleLeftRotate(Node<T>* &root)
	{
		Node<T>* u = root->right; 
		root->right = u->left; // rotate
		u->left = root;
		// update heights
		root->height = max(Height(root->left), Height(root->right))+1; 
		u->height = max(Height(u->right), root->height) +1;
		return u;
	};

	Node<T>* DoubleLeftRotate(Node<T>* &root)
	{
		root->right = SingleRightRotate(root->right);
		return SingleLeftRotate(root);
	};

	Node<T>* DoubleRightRotate(Node<T>* &root)
	{
		root->left = SingleLeftRotate(root->left); // rotate left
		return SingleRightRotate(root); // After rotate right
	};

	int Height(Node<T> *root)
	{
		return (root == NULL ? -1 : root->height);
		
	};

	int GetBalance(Node<T> *root)
	{
		if(root == NULL)
			return 0;
		else
			return Height(root->left) - Height(root->right);
	};
	void Inorder(Node<T> *root) const
	{
		if(root != NULL)
		{
			cout<<root->data<<" ";
			Inorder(root->left);
			Inorder(root->right);
		}
	};
	void Preorder(Node<T> *root) const
	{
		if(root != NULL)
		{
	        Preorder(root->left);
	        cout << root->data << " ";
	        Preorder(root->right);
	    }
	};
	T FindMin(Node<T>* root)
	{
		if(root == 0)
			return INT_MIN;
		if(root->left != 0)
			return FindMin(root->left);
		return root->data;

	}
public:
	TreeAVL()
	{
		root = NULL;
	};
	void Insert(T data)
	{
		root = Insert(data,root);
	};
	void Inorder() const
	{
		Inorder(root);
		cout<<endl;
	};
	void Preorder() const
	{
		Preorder(root);
		cout<<endl;
	};
	void DeleteNodeOfTree(T data)
	{
		root = DeleteNodeOfTree(data,root);
	};
};
#endif
