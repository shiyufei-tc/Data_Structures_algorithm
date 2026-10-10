#include<deque>

template <typename T>
class BinaryTreeNode
{
public:
    T item;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
    BinaryTreeNode(T item)
    {
        this->item = item;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename T>
class BINARYTREE
{
    private:
    void clear(BinaryTreeNode<T> *Node)
    {
        if(Node==nullptr)
            return;
        clear(Node->left);
        clear(Node->right);
        delete Node;
    }

public:
    BinaryTreeNode<T> *root;

    BINARYTREE()
    {
        this->root = nullptr;
    }

    ~BINARYTREE()
    {
        clear(this->root);
    }

    void add_level_order(T item)
    {
        BinaryTreeNode<T> *new_node = new BinaryTreeNode<T>();
        if(this->root==nullptr)
        {
            this->root = new_node;
            return;
        }
        std::deque<T> pending;
        while (!pending.empty())
        {
            BinaryTreeNode<T> *Node = pending.pop_front();
            if (Node->left==nullptr)
            {
                Node->left = new_node;
                return
            }
            pending.push_back(Node->left);
            if(Node->right==nullptr)
            {
                Node->right = new_node;
                return;
            }
            pending.push_back(Node->right);
        }
    }
};
