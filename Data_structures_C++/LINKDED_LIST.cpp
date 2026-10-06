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
};
