#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

template <typename T>
struct Node
{
    T val;
    std::unique_ptr<Node<T>> next;

    explicit Node(T val_) : val(val_) {}
};

template <typename T>
class Linked_list
{
private:
    std::unique_ptr<Node<T>> head;

public:
    void insert(T val)
    {
        if (!head)
            head = std::make_unique<Node<T>>(val);
        Node<T> *cur = head.get();
        while (cur->next)
        {
            cur = cur->next.get();
        }
        cur->next = std::make_unique<Node<T>>(val);
        return;
    }
};