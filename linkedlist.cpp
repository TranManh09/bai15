#include <iostream>
using namespace std;

struct NodeBase
{
    NodeBase* next;
    virtual void print() = 0;
};

template <typename T>
struct Node : public NodeBase
{
    T data;
    void print()
    {
        cout << data << " ";
    }
};

class linkedlist
{
private:
    NodeBase* head;
public:
    linkedlist() : head(nullptr) {}
    ~linkedlist()
    {
        NodeBase* current = head;
        while (current != nullptr)
        {
            NodeBase* next = current->next;
            delete current;
            current = next;
        }
    }

    template <typename T>
    void push_front(T x)
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = x;
        newNode->next = head;
        head = newNode;
    }

    template <typename T>
    void push_back(T x)
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = x;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            NodeBase* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void pop_front()
    {
        if (head)
        {
            NodeBase* current = head;
            head = head->next;
            delete current;
        }
    }

    void pop_back()
    {
        if (head == nullptr)
            return;

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            NodeBase* current = head;
            while (current->next->next != nullptr)
            {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
    }

    void print_node()
    {
        NodeBase* current = head;
        while (current != nullptr)
        {
            current->print();
            current = current->next;
        }
        cout << endl;
    }

    size_t len()
    {
        int count = 0;
        NodeBase *current = head;
        while (current != nullptr)
        {
            count ++;
            current = current->next;
        }
        return count;
        
    }
    template <typename T>
    void insert(T x, size_t pos)
    {
        size_t n = len();
        if (pos < 1 || pos > n + 1)
        {
            cout << "Vi tri chen khong hop le";
            return;
        }
        if (pos == 1)
        {
            push_front(x);
        }
        else if (pos == n + 1)
        {
            push_back(x);
        }
        else
        {
            Node<T>* newNode = new Node<T>;
            newNode->data = x;

            NodeBase* current = head;
            for (size_t i = 1; i < pos - 1; i++)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    
    void erase(size_t pos)
    {
        size_t n = len();
        if (pos < 1 || pos > n + 1)
        {
            cout << "Vi tri chen khong hop le";
            return;
        }
        if (pos == 1)
        {
            pop_front();
        }
        else if (pos == n + 1)
        {
            pop_back();
        }
        else
        {
            NodeBase* current = head;
            for (size_t i = 1; i < pos - 1; i++)
            {
                current = current->next;
            }
            NodeBase* nodeToDelete = current->next;
            current->next = nodeToDelete->next;
            delete nodeToDelete;
        }
    }
};

int main()
{
    linkedlist myList;
    myList.push_front(5);
    myList.push_front(3.14);
    myList.push_back("Hello");
    myList.insert(7,2);
    myList.print_node();
    myList.erase(3);
    myList.print_node();
    return 0;
}