#include <iostream>

using namespace std;

template<class Type>

class DoubleLinked
{
	struct node
	{
		Type item;
		node* next, * pre;
	};
	node* head, * tail, * current;
	int counter;
public:

	DoubleLinked()
	{
		head = NULL;
		tail = NULL;
		current = NULL;
		counter = 0;
	}

	void pushtail(Type item)
	{
		node* newnode = new node;
		newnode->item = item;
		if (counter == 0)
		{
			newnode->next = newnode->pre = NULL;
			head = tail = newnode;
		}

		else
		{
			newnode->next = NULL;
			newnode->pre = tail;
			tail->next = newnode;
			tail = newnode;
		}
		counter++;
	}

	void pushhead(Type item)
	{
		node* newnode = new node;
		newnode->item = item;
		if (counter == 0)
		{
			newnode->next = newnode->pre = NULL;
			head = tail = newnode;
		}

		else
		{
			newnode->next = head;
			newnode->pre = NULL;
			head->pre = newnode;
			head = newnode;
		}
		counter++;
	}

	void pushat(Type item,int pos) //pos starts from 0
	{
		node* newnode = new node;
		newnode->item = item;
		if (pos == 0)
		{
			newnode->next = newnode->pre = NULL;
			head = tail = newnode;
			counter++;
		}

		else if (pos > counter)
		{
			cout << "out of range!\n push as tail at postion "<< counter + 1<<endl;
			pushtail(item);
		}

		else if (pos < 0)
		{
			cout << "out of range!\n push as head at postion 0.\n";
			pushhead(item);
		}

		else
		{
			current = head;
			for (int i = 1; i < pos; i++)
			{
				current = current->next;
			}
			newnode->next = current->next;
			newnode->pre = current;
			current->next = newnode;
			counter++;
		}
	}

	void poptail()
	{
		if (counter == 0)
			cout << "list is empty!\n";

		else
		{
			current = tail->pre;
			tail->pre=current->pre;
			current = tail;
			tail = tail->pre->next;
			tail->next = NULL;
			delete current;
			counter--;
		}
	}

	void pophead()
	{
		if (counter == 0)
			cout << "list is empty!\n";

		else
		{
			current = head->next;
			head->next = current->next;
			current = head;
			head = head->next->pre;
			head->pre = NULL;
			delete current;
			counter--;
		}
	}

	void poptarget(Type target)  // use for list with no duplicated items
	{
		if (counter == 0)
			cout << "list is empty!\n";

		else if (target == head->item)
			pophead();

		else if (target == tail->item)
			poptail();

		else
		{
			current = head;
			while (current != NULL && current->item!=target)
			{
				current = current->next;
			}
			current->pre->next = current->next;
			current->next->pre = current->pre;
			delete current;
			counter--;
		}
	}

	void popat(int pos) //pos starts from 0
	{
		if (counter == 0)
			cout << "list is empty!\n";

		else if (pos<0 || pos>counter)
			cout << "selected postion is out of list's range!\n";

		else if (pos ==0)
			pophead();

		else if (pos == counter)
			poptail();

		else 
		{
			current = head;
			for (int i = 1; i <= pos; i++)
			{
				current = current->next;
			}
			current->pre->next = current->next;
			current->next->pre = current->pre;
			delete current;
			counter--;
		}
	}

	void gettail()
	{
		cout << "the last item at this list is " << tail->item << " at positon " << counter << endl;
	}

	void gethead()
	{
		cout << "the first item at this list is " << head->item << " at positon 0\n";
	}
	
	void gettarget(Type target) // if there is duolicated target, it will print the postion of the first.
	{
		int pos = 0;
		current = head;
		while (current != NULL && current->item != target)
		{
			current = current->next;
			pos++;
		}
		if (current == NULL || current->item != target)
			cout << "item doesn't exist in this list!\n";
		else
			cout << "the target " << current->item << " found at pos " << pos << endl;
	}

	void getat(Type pos)  //search by pos	//pos starts from 0
	{
		if (pos<0 || pos>counter)
			cout << "selected postion is out of list's range!\n";

		else if (pos == 0)
			gethead();

		else if (pos == counter)
			gettail();

		else
		{
			current = head;
			for (int i = 1; i <= pos; i++)
			{
				current = current->next;
			}
			cout << current->item << " is found at this positon ("<<pos<<")\n";
		}
	}

	void display()
	{
		if (counter == 0)
			cout << "this list is empty!\n";
		cout << "[ ";
		for (current = head; current != NULL; current = current->next)
		{
			cout << current->item<< " ";
		}
		cout << "]\n";
	}

	void clearlsit()
	{
		if (counter == 0)
			cout << "list is allready empty!\n";

		else
		{
			for (int i = 0; i <= counter; i++)
			{
				current = head;
				head = head->next;
				if (head == NULL)
					break;
				free(current);
			}
			counter = 0;
		}
	}
};

int main()
{
	DoubleLinked<int> ob;
	ob.pushtail(60);
	ob.pushtail(50);
	ob.pushtail(40);
	ob.pushtail(30);
	ob.pushtail(20);
	ob.pushhead(70);
	ob.pushhead(80);
	ob.pushhead(90);
	ob.pushhead(100);
	ob.pushat(45, 5);

	ob.display();

	ob.pophead();
	ob.poptail();
	ob.popat(2);
	ob.poptarget(90);

	ob.display();

	ob.gethead();
	ob.gettail();
	ob.gettarget(50);
	ob.getat(4);

	ob.clearlsit();
	ob.display();
	
}
