#include<iostream>
#include<vector>
template<typename T>
class SingleNode
{
public:
    T item;
    SingleNode<T> *next;

    SingleNode(T item)
    {
        this->item = item;
        this->next = nullptr;
    }
};

template <typename T>
class LINKDED_LIST
{
public:
    SingleNode<T> *head;

    LINKDED_LIST()
    {
        this->head = new SingleNode<T>(T());
    }

    ~LINKDED_LIST()
    {
        SingleNode<T> *current = this->head;
        while (current != nullptr)
        {
            SingleNode<T> *temp = current;
            current = current->next;
            delete temp;
        }
    }

    void PUSH_no_reverse_AllDATA(std::vector<T> &my_list)
    {
        SingleNode<T> *current = this->head;
        while (current->next!=nullptr)
        {
            current = current->next;
        }
        for (auto data : my_list)
        {
            SingleNode<T> *new_node = new SingleNode<T>(data);
            current->next = new_node;
            current = current->next;
        }
    }

    void PUSH_reverse_ALLDATA(std::vector<T> &my_list)
    {
        for (auto data : my_list)
        {
            SingleNode<T> *new_node = new SingleNode<T>(data);
            new_node->next = this->head->next;
            this->head->next = new_node;
        }
    }

    bool is_empty()
    {
        return this->head->next == nullptr;
    }

    int get_length()
    {
        int count = 0;
        SingleNode<T> *current = this->head->next;
        while (current!=nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    void travel()
    {
        SingleNode<T> *current = this->head->next;
        while (current!=nullptr)
        {
            std::cout << current->item << " ";
            current = current->next;
        }
    }

    void append(T item)
    {
        SingleNode<T> *new_node = new SingleNode<T>(item);
        if (is_empty())
        {
            this->head->next = new_node;
            return;
        }

        SingleNode<T> *current = this->head;
        while (current->next!=nullptr)
        {
            current = current->next;
        }
        current->next = new_node;
    }
};