
#include <iostream>

#define null NULL

using namespace std;

template <class type>

class Queue
{
private:
	struct node
	{
		type data;
		node* next;
	};
	node* front, * rear, * current, * temp;
	int counter;
public:
	Queue() : front(null), rear(null), current(null), temp(null), counter(0) {}

	bool isEmpty()
	{
		return counter == 0;
	}

	void enqueue(type item)
	{
		node* newnode = new node;
		newnode->data = item;
		newnode->next = null;
		if (isEmpty())
		{
			front = rear = newnode;
		}
		else
		{
			rear->next = newnode;
			rear = newnode;
		}
		counter++;
		cout << item << " pushed\n";
	}

	void dequeue()// normal delete // delete front // FIFO theory
	{
		if (isEmpty())
			cout << "Empty queue!\n";
		else
		{
			temp = front;
			front = front->next;
			delete temp;
			temp = null;
			counter--;
			cout << "front deleted\n";
		}
	}

	type& getfront()//return element in the front
	{
		return front->data;
	}

	type& getrear()//return element at the end
	{
		return rear->data;
	}

	type& search(int item)//return a random element
	{
		if (isEmpty())
			cout << "Empty queue!\n";
		else
		{
			current = front;
			while (current->data != item)
			{
				current = current->next;
			}
			if (current == null)
				cout << "this item (" << item << ") does not exist in this queue!\n";
			else
			{
				cout << item << " found\n";
				return current->data;
			}
		}
	}

	void display()
	{
		current = front;
		cout << "Elements in this queue [ ";
		while (current != null)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << "]\n";
	}

	void clear() 
	{
		current = front;
		while (current != null)
		{
			temp = current;
			current = current->next;
			delete temp;
			temp = null;
		}
	}

	~Queue()
	{
		clear();
	}
};

int main()
{
    std::cout << "Hello World!\n";

	Queue<int> ob;
	ob.enqueue(10);
	ob.enqueue(20);
	ob.enqueue(30);
	ob.enqueue(40);
	ob.enqueue(50);
	cout << ob.getfront() << "	" << ob.getrear() << "\n";
	cout << ob.search(30) << endl;
	ob.dequeue();
	ob.display();
}

