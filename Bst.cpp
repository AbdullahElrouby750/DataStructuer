#include <iostream>

using namespace std;

template<class Type>

class binarysearchtree
{
private: //private members.
	struct node
	{
		Type data;
		node* left;
		node* right;
	};
	node* current,* currenttail, * min, * max,* root,* target,* temp;
	int level, leafcount, halfParentcount, fullparentcount, nodecount;


public: //public functions
	binarysearchtree() : current(NULL), min(NULL), max(NULL),root(NULL),currenttail(NULL),target(NULL),temp(NULL), level(0),leafcount(0),halfParentcount(0),fullparentcount(0),nodecount(0) {}

	void push(Type item) //insert an item //update: use recursion instead...
	{
		node* newnode = new node;
		newnode->data = item;
		newnode->left = newnode->right = NULL;
		if (root == NULL) //tree is empty
		{
			root = newnode;
			cout << item << " pushed\n";
		}
		else
		{
			current = root;

			while (current != NULL)
			{
				if (current->data == item)
				{
					cout << item << " already exist in the tree. No dublicates are allowed!\n";
					return;
				}
				currenttail = current;
				if (item < current->data)
					current = current->left;
				else
					current = current->right;
			}
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

			else if (target->left ==NULL && target->right!=NULL)//target has a right node only
			{
				if (currenttail->left == target)
				{
					currenttail->left = target->right;
				}
				if (currenttail->right==target)
				{
					currenttail->right = target->right;
				}
				delete target;
				target = NULL;
				cout << item << " deleted!\n";
			}

			else if (target->left !=NULL && target->right==NULL)//target has a left node only
			{
				if (currenttail->left == target)
				{
					currenttail->left = target->left;
				}
				if (currenttail->right==target)
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
		cout << "the elementa in the tree in pre-order [ ";
		pre_order(root);
		cout << "]\n";

	}

	void in_orderDisplay()
	{
		cout << "the elementa in the tree in in-order [ ";
		in_order(root);
		cout << "]\n";

	}

	void post_orderDisplay()
	{
		cout << "the elementa in the tree in post-order [ ";
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
			if(Root->left != NULL && Root->right != NULL)
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

	node* getmax(node* p)//get minmum element
	{
		while (p != NULL)
		{
			level++;
			temp = p;
			p = p->right;
		}
		return temp;
	}

	void clear(node* &p)
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
	binarysearchtree<int> ob;
	ob.push(100);
	ob.push(90);
	ob.push(110);
	ob.push(70);
	ob.push(95);
	ob.push(101);
	ob.push(80);
	ob.push(90);
	ob.push(120);
	ob.push(81);
	ob.push(132);
	ob.push(87);
	ob.push(50);
	ob.push(30);
	ob.push(122);

	ob.pre_orderDisplay();
	ob.post_orderDisplay();
	ob.in_orderDisplay();

	ob.Nodecount();
	ob.Fullparentcount();
	ob.Halfparentcount();
	ob.Leafcount();
	ob.Levelcount();

	ob.getmax();
	ob.getmin();
	ob.get(90);
	ob.get(70);
    
	ob.pop(90);
	ob.pop(101);
	ob.pop(70);
	ob.pop(100);

	ob.pre_orderDisplay();

	ob.clearSubTree(95);
	ob.pre_orderDisplay();

	ob.clearAllTree();
	ob.pre_orderDisplay();
	
	cin.get();
}
