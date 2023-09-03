
#include <iostream>

using namespace std;

#define null  NULL

template<class type>

class Stack
{
private:
    struct node
    {
        type data;
        node* next;
    };
    node* top, * current, * temp;
    int counter;
public:
    Stack() : top(null), current(null), temp(null), counter(0) {}

    void push(type item)
    {
        node* newnode = new node;
        newnode->data = item;
        newnode->next = top;
        top = newnode;
        counter++;
        cout << item << "pushed\n";
    }

    void pop()//delete top
    {
        if (counter == 0)
            cout << "this stack is empty\n";
        else
        {
            temp = top;
            top = top->next;
            delete temp;
            temp = null;
            counter--;
            cout << "top deleted from te stack\n";
        }
    }

    void checkthere(type item)//search if an item exist // counte if repeated
    {

        if (counter == 0)
            cout << "this stack is empty\n";
        else
        {
            int rank = 0, frequency = 0;
            current = top;
            while (current != null)
            {
                if (current->data == item)
                {
                    frequency++;
                    cout << item << "found " << rank << " block(s) away from the top\n";
                }
                rank++;
                current = current->next;
            }
            cout << "the total number of this item (" << item << ") exist in this stack is :: " << frequency << endl;

        }
    }

    type& getTop()//return item on the top
    {

        if (counter == 0)
            cout << "this stack is empty\n";
        else
            return top->data;
    }

    bool isEmpty()//check if empty
    {
        return counter == 0;
    }

    void clear()//clear the stack
    {
        while (top != null)
        {
            temp = top;
            top = top->next;
            delete temp;
        }
        temp = null;
    }

    ~Stack()
    {
        clear();
    }
};

int main()
{
    std::cout << "Hello World!\n";
    Stack<int> ob;
    ob.push(10);
    ob.push(20);
    ob.push(30);
    ob.push(40);
    ob.push(10);
    ob.checkthere(10);
}
