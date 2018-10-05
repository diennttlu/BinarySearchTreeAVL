#ifndef node_h
#define node_h
#include <math.h>
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

	int GetBalance(Node<T> *root) const
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
};
#endif
