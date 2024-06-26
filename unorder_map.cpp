#include <iostream>
#include <initializer_list>
#include <vector>
using namespace std;
#define SIZE 10

template <class T1, class T2>
class unorder_map
{
public:
    T1 a;
    T2 b;
    int count = 0;
    int end_index = 0;
    int start_index = 0;
    int size_of_unorder_map = 0;
    class iterator;

    typedef struct Node
    {
        T1 key;
        T2 value;
        Node *next;
    } Node;
    Node *head = nullptr;
    Node *tail = nullptr;
    Node *hash_table[SIZE] = {nullptr};

    int hash_function(const string &key)
    {
        int i = 0;
        int j = 9;
        while (key[i] != '\0')
        {
            j = (31 * j + key[i]) % SIZE;
            i++;
        }
        return j;
    }
    int hash_function(const int &key)
    {

        return key % SIZE;
    }

    // public:
    struct Pair
    {
        T1 first;
        T2 second;
    };
    unorder_map()
    {
        for (int i = 0; i < SIZE; i++)
        {
            hash_table[i] = nullptr;
        }
    }
    unorder_map(initializer_list<Pair> initList)
    {
        for (const auto &pair : initList)
        {
            insert(pair.first, pair.second);
        }
    }

    void insert(const T1 &key, const T2 &value)
    {
        int index = hash_function(key);

        cout << "insert: =  " << index << endl;
        /*get the first elements*/
        if (start_index == 0)
        {
            start_index = index;
        }
        /*get the end of elements*/
        end_index = index;
        /*find bucket count of unoerder map*/
        if (index > size_of_unorder_map)
        {
            size_of_unorder_map = index;
        }
        Node *newNode = new Node;

        newNode->key = key;
        newNode->value = value;
        newNode->next = nullptr;

        if (hash_table[index] == nullptr)
        {

            hash_table[index] = newNode;
            // head = newNode;
        }
        else
        {

            newNode->next = hash_table[index];
            hash_table[index] = newNode;
        }
    }

    void find(const T1 &key)
    {
        int index = hash_function(key);
        Node *temp = hash_table[index];
        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                cout << "Value for key " << temp->key << " is: " << temp->value << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Key " << key << " not found in the map." << endl;
    }

    bool empty()
    {
        for (int i = 0; i < SIZE; ++i)
        {
            if (hash_table[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }

    void erase(const T1 &key)
    {
        int index = hash_function(key);
        int count = 0;
        Node *current = nullptr;
        Node *temp = nullptr;
        // for (current = hash_table[index]; current != nullptr; current = current->next)
        // {
        //     count++;
        // }
        // if (hash_table[index]->next == nullptr)
        // {
        //     hash_table[index] = hash_table[index]->next;
        //     // delete hash_table[index];
        //     // hash_table[index] = nullptr;
        //     // return;
        // }
        // else if ()
        // {
        // }

        for (current = hash_table[index]; current != nullptr; current = current->next)
        {
            if (current->key == key)
            {
                if (temp == nullptr)
                {
                    hash_table[index] = current->next;
                    delete current;
                    break;
                }
                else
                {
                    temp->next = current->next;
                    delete current;
                    break;
                }
            }
            temp = current;
        }
    }

    int bucket_count()
    {
        return size_of_unorder_map + 1; //+1 because of the dummy node at each bucket.
    }
    iterator begin(int index)
    {
        Node *temp = hash_table[index];
        if (temp != nullptr)
        {
            return iterator(temp);
        }
        else
        {
            return 0;
        }
    }
    iterator begin()
    {
        Node *temp = hash_table[end_index];
        if (temp != nullptr)
        {
            return iterator(temp);
        }
        else
        {
            return 0;
        }
    }

    iterator end()
    {
        Node *temp = hash_table[start_index];
        if (temp != nullptr)
        {
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            return iterator(temp);
        }
        else
        {
            return 0;
        }
    }
    iterator end(int index)
    {
        Node *temp = hash_table[index];
        if (temp != nullptr)
        {
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            return iterator(temp);
        }
        else
        {
            return 0;
        }
    }
    void show_function()
    {
        int index = 0;
        Node *temp;
        for (int i = 0; i < 10; i++)
        {
            cout << "bucket #" << i << " contains: ";
            for (temp = hash_table[i]; temp != nullptr; temp = temp->next)
            {
                cout << "[" << temp->key << ":" << temp->value << "] ";
            }
            cout << endl;
        }
    }
};

template <class T1, class T2>
class unorder_map<T1, T2>::iterator
{
private:
    Node *current;
    int ab = 0;

public:
    iterator(Node *node) : current(node)
    {
    }
    Node *operator->() const
    {
        if (current != nullptr)
        {
            return current;
        }
        else
        {
            return 0;
        }

        // cout << current->key << " " << current->value << endl;
    }
    iterator &operator++()
    {
        if (current != nullptr)
        {
            current = current->next;
        }
        return *this;
    }

    // Overload the equality operator to check if two iterators are equal
    bool operator==(const iterator &other) const
    {
        if (current != nullptr)
        {
            return current == other.current;
        }
        else
        {
            return 0;
        }
    }

    // Overload the inequality operator to check if two iterators are not equal
    bool operator!=(const iterator &other) const
    {
        // Node *temp = nullptr;
        if (current != nullptr)
        {
            if (current->next != nullptr)
            {
                return current != other.current;
            }
            else
            {
                return current == other.current;
            }
        }
        else
        {
            return 0;
        }
    }
};
int main()
{
    // unorder_map<string, int> myMap2 = {{"abc", 2}, {"cab", 2}};
    unorder_map<string, string> myMap2 = {
        {"house", "maison"},

        {"apple", "pomme"},
        {"tree", "arbre"},
        {"door", "porte"},
        {"grapefruit", "pamplemousse"},
        {"book", "livre"}};
    myMap2.insert("test", "10");
    // myMap2.show_function();
    // for (unsigned i = 0; i < 9; ++i)
    // {
    //     auto it1 = myMap2.begin(i);
    //     auto it2 = myMap2.end(i);
    //     cout << "bucket #" << i << " contains: ";
    //     if (it1 == it2)
    //     {
    //         cout << "[" << it1->key << ":" << it1->value << "] ";
    //     }
    //     cout << endl;
    // }

    // myMap2.find("test");
    //  myMap2.find("cab");

    // check emty
    // std::cout << "Is the map empty? " << (myMap2.empty() ? "Yes" : "No") << std::endl;

    // display count of hash table
    // cout << myMap2.bucket_count() << endl;

    // auto it = myMap2.end();
    // cout << it->key << " " << it->value << endl;
    unsigned n = myMap2.bucket_count();
    for (unsigned i = 0; i < n; ++i)
    {
        std::cout << "bucket #" << i << " contains: ";
        for (auto it = myMap2.begin(i); it != myMap2.end(i); ++it)
        {
            cout << "[" << it->key << ":" << it->value << "] ";
        }
        cout << "\n";
    }
    cout << endl;

    myMap2.erase("house");
    for (unsigned i = 0; i < n; ++i)
    {
        std::cout << "bucket #" << i << " contains: ";
        for (auto it = myMap2.begin(i); it != myMap2.end(i); ++it)
        {
            cout << "[" << it->key << ":" << it->value << "] ";
        }
        cout << "\n";
    }
    return 0;
}
