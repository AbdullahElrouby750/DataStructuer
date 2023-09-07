#include <iostream>
#include <stack>

using namespace std;

stack<char> ro;

template<class Type>

class AVL_Tree
{
private: //private members.
	struct node
	{
		Type data;
		node* left;
		node* right;
		node* parent;
	};
	node* current, * currenttail, * min, * max, * root, * target, * temp, * newroot;
	int level, leafcount, halfParentcount, fullparentcount, nodecount;


public: //public functions
	AVL_Tree() : current(NULL), min(NULL), max(NULL), root(NULL), currenttail(NULL), target(NULL), temp(NULL), newroot(NULL), level(0), leafcount(0), halfParentcount(0), fullparentcount(0), nodecount(0) {}

	void push(Type item) //insert an item
	{
		node* newnode = new node;
		newnode->data = item;
		newnode->left = newnode->right = newnode->parent = NULL;
		if (root == NULL) //tree is empty
		{
			root = newnode;
			cout << item << " pushed\n";
			return;
		}
		else
		{
			current = root;

			while (current != NULL)
			{
				if (current->data == item)
				{
					cout << item << " already exist in the tree. No duplicates are allowed!\n";
					return;
				}
				currenttail = current;
				if (item < current->data)
					current = current->left;
				else
					current = current->right;
			}
			newnode->parent = currenttail;
			if (item < currenttail->data)
			{
				currenttail->left = newnode;
				cout << item << " pushed\n";
			}
			else
			{
				currenttail->right = newnode;
				cout << item << " pushed\n";
			}
		}
		BalanceTree(root);
	}

	bool get(Type item)
	{
		level = 0;
		int check = get(root, item);
		if (check == 1)
		{
			cout << item << " exist in level " << level << endl;
		}
		return check;
	}

	void pop(Type item)
	{
		int check = remove(root, item);
		if (check == 0)
		{
			cout << item << " not in found in the tree! \n";
			return;
		}

		else
		{
			if (target->left == NULL && target->right == NULL)//target is a leaf
			{
				if (target == currenttail->left)
					currenttail->left = NULL;
				else
					currenttail->right = NULL;
				delete target;
				target = NULL;
				cout << item << " deleted!\n";
			}

			else if (target->left == NULL && target->right != NULL)//target has a right node only
			{
				if (currenttail->left == target)
				{
					currenttail->left = target->right;
				}
				if (currenttail->right == target)
				{
					currenttail->right = target->right;
				}
				delete target;
				target = NULL;
				cout << item << " deleted!\n";
			}

			else if (target->left != NULL && target->right == NULL)//target has a left node only
			{
				if (currenttail->left == target)
				{
					currenttail->left = target->left;
				}
				if (currenttail->right == target)
				{
					currenttail->right = target->left;
				}
				delete target;
				target = NULL;
				cout << item << " deleted!\n";
			}

			else//target is a full parent
			{
				getmin(target->right);
				if (temp->data > target->left->data && temp->data <= target->right->data)
				{
					if (target->right == temp)
					{

						temp->left = target->left;
						target->data = temp->data;
						target->right = temp->right;
					}
					else
					{
						temp->right = target->right;
						temp->left = target->left;
						target->data = temp->data;
					}
				}
				else
				{
					getmax(target->left);

					if (temp->data > target->left->data && temp->data <= target->right->data)
					{
						if (target->left == temp)
						{
							temp->right = target->right;
							target->data = temp->data;
							target->left = temp->left;
						}
						else
						{
							temp->right = target->right;
							temp->left = target->left;
							target->data = temp->data;

						}
					}
				}

				delete temp;
				temp = NULL;
				cout << item << " deleted!\n";
				return;
			}
		}

		BalanceTree(root);
	}

	void getmin()
	{
		level = 0;
		node* p;
		p = getmin(root);
		cout << "min is " << p->data << endl;
	}

	void getmax()
	{
		level = 0;
		node* p;
		p = getmax(root);
		cout << "max is " << p->data << endl;
	}

	void pre_orderDisplay()
	{
		cout << "the element in the tree in pre-order [ ";
		pre_order(root);
		cout << "]\n";

	}

	void in_orderDisplay()
	{
		cout << "the element in the tree in in-order [ ";
		in_order(root);
		cout << "]\n";

	}

	void post_orderDisplay()
	{
		cout << "the element in the tree in post-order [ ";
		post_order(root);
		cout << "]\n";

	}

	void Levelcount()
	{
		int levelcount = height(root);
		cout << "there is " << levelcount << " level(s) in this tree\n";
	}

	void Leafcount()
	{
		leafcount = 0;
		COUNT(root);
		cout << "there is " << leafcount << " leaf-node(s) in this tree\n";
	}

	void Halfparentcount()
	{
		halfParentcount = 0;
		COUNT(root);
		cout << "there is " << halfParentcount << " half-parent node(s) in this tree\n";
	}

	void Fullparentcount()
	{
		fullparentcount = 0;
		COUNT(root);
		cout << "there is " << fullparentcount << " full-parent node(s) in this tree\n";
	}

	void Nodecount()
	{
		nodecount = 0;
		COUNT(root);
		cout << "there is " << nodecount << " node(s) in this tree\n";
	}

	void clearAllTree()
	{
		clear(root);
		cout << "tree cleared \n";
	}

	void clearSubTree(Type item)
	{
		if (get(root, item))
		{
			if (currenttail->left == target)
			{
				clear(target);
				currenttail->left = NULL;
			}
			if (currenttail->right == target)
			{
				clear(target);
				currenttail->right = NULL;
			}

			cout << "sub - tree cleared \n";
		}
		else
			cout << "this element dos not exist in the tree!\n";
	}

private://privet functions

	bool get(node* cur, Type item) //search for an item
	{

		if (cur == NULL)
			return false;
		else if (cur->data == item)
		{
			target = cur;
			return true;
		}
		else if (item < cur->data)
		{
			level++;
			currenttail = cur;
			return get(cur->left, item);
		}
		else
		{
			level++;
			currenttail = cur;
			return get(cur->right, item);
		}
	}

	bool remove(node* cur, Type item) //search for an item to delete
	{

		if (cur == NULL)
			return false;
		else if (cur->data == item)
		{
			target = cur;
			return true;
		}
		else if (item < cur->data)
		{
			currenttail = cur;
			return get(cur->left, item);
		}
		else
		{
			currenttail = cur;
			return get(cur->right, item);
		}
	}

	void COUNT(node* Root)// to count nodes/leaves
	{
		if (Root != NULL)
		{
			nodecount++;
			if (Root->left == NULL && Root->right == NULL)//count leaf
				leafcount++;
			if ((Root->left == NULL && Root->right != NULL) || (Root->left != NULL && Root->right == NULL))//count halfparent
				halfParentcount++;
			if (Root->left != NULL && Root->right != NULL)
				fullparentcount++;

			COUNT(Root->left);
			COUNT(Root->right);
		}
	}

	int Max(Type x, Type y)//compare between two numbers
	{
		return	x >= y ? x : y;
	}

	int height(node* Root)//calculate height
	{
		if (Root == NULL)
			return 0;
		else
			return 1 + Max(height(Root->left), height(Root->right));
	}

	void pre_order(node* Root) //display tree in(root - left - right)
	{
		if (Root != NULL)
		{
			cout << Root->data << "  ";
			pre_order(Root->left);
			pre_order(Root->right);
		}
	}

	void in_order(node* Root) //display tree in(left - root - right)
	{
		if (Root != NULL)
		{
			pre_order(Root->left);
			cout << Root->data << "  ";
			pre_order(Root->right);
		}
	}

	void post_order(node* Root) //display tree in(left - right - root)
	{
		if (Root != NULL)
		{
			pre_order(Root->left);
			pre_order(Root->right);
			cout << Root->data << "  ";
		}
	}

	node* getmin(node* p)//get max element
	{
		while (p != NULL)
		{
			level++;
			temp = p;
			p = p->left;
		}
		return temp;
	}

	node* getmax(node* p)//get minimum element
	{
		while (p != NULL)
		{
			level++;
			temp = p;
			p = p->right;
		}
		return temp;
	}

	void BalanceTree(node* Root)
	{
		if (Root != NULL)
		{	

			if (Root == currenttail->left)
				ro.push('l');
			else if (Root == currenttail->right)
				ro.push('r');

			if (!(Root->left == NULL && Root->right == NULL))
				currenttail = Root;

			BalanceTree(Root->left);
			BalanceTree(Root->right);
			int x = height(Root->left) - height(Root->right);
			if (x < -1 || x > 1)
			{
				char arr[2]{};
				arr[0] = ro.top();
				ro.pop();
				arr[1] = ro.top();

				//detect the imbalance type
				if (arr[0] == 'l' && arr[1] == 'l')
					LL_rotation(Root);
				else if (arr[0] == 'l' && arr[1] == 'r')
					LR_rotation(Root);
				else if (arr[0] == 'r' && arr[1] == 'r')
					RR_rotation(root);
				else  if (arr[0] == 'r' && arr[1] == 'l')
					RL_rotation(Root);
			}
		}
	}

	void RR_rotation(node* Root)
	{
		//use RR-rotation directly
		newroot = Root->right;

		if (Root != root)
		{

			if (Root->parent->right == Root)
				Root->parent->right = newroot;
			else
				Root->parent->left = newroot;
		}

		Root->right = newroot->left;
		newroot->left = Root;
		newroot->parent = Root->parent;
		if (Root->right != NULL)
			Root->right->parent = Root;
		Root->parent = newroot;
		if (Root == root)
			root = newroot;
	}

	void RL_rotation(node* Root)
	{
		//turn to RR-imbalance
		temp = Root->right;
		newroot = temp->left;
		temp->left = newroot->right;
		Root->right = newroot;
		newroot->right = temp;

		//use RR-rotation
		RR_rotation(Root);
	}

	void LL_rotation(node* Root)
	{
		//LL-rotation directly
		newroot = Root->left;

		if (Root != root)
		{
			if (Root->parent->right == Root)
				Root->parent->right = newroot;
			else
				Root->parent->left = newroot;
		}
		
		Root->left = newroot->right;
		newroot->right = Root;
		newroot->parent = Root->parent;
		if (Root->left != NULL)
			Root->left->parent = Root;
		Root->parent = newroot;
		if (Root == root)
			root = newroot;
	}

	void LR_rotation(node* Root)
	{
		//turn to LL-imbalance
		temp = Root->left;
		newroot = temp->right;
		temp->right = newroot->left;
		Root->left = newroot;
		newroot->left = temp;

		//use LL-rotation
		LL_rotation(Root);
	}

	void clear(node*& p)
	{
		if (p != NULL)
		{
			clear(p->left);
			clear(p->right);
			delete p;
			p = NULL;
		}
	}

};//binary search tree end

int main()
{
	AVL_Tree<int> ob;
	ob.push(100);
	ob.push(90);
	ob.push(80);
	ob.push(70);
	ob.push(60);
	ob.push(50);
	ob.push(40);
	ob.push(30);
	ob.push(20);
	ob.push(10);

	ob.in_orderDisplay();

	ob.pop(40);
	ob.pop(50);
	ob.pop(60);

	ob.in_orderDisplay();

	cin.get();
}