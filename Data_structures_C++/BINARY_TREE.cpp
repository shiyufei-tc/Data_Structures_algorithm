#include <deque>
#include <iostream>

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
    BinaryTreeNode<T> clear(BinaryTreeNode<T> *Node)
    {
        if (Node == nullptr)
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
        if (this->root == nullptr)
        {
            this->root = new_node;
            return;
        }
        std::deque<T> pending;
        pending.push_back(this->root);
        while (!pending.empty())
        {
            BinaryTreeNode<T> *Node = pending.pop_front();
            if (Node->left == nullptr)
            {
                Node->left = new_node;
                return
            }
            pending.push_back(Node->left);
            if (Node->right == nullptr)
            {
                Node->right = new_node;
                return;
            }
            pending.push_back(Node->right);
        }
    }

    void breadth_first()
    {
        if (this->root == nullptr)
        {
            return;
        }

        std::deque<T> pending;
        pending.push_back(this->root);

        while (!pending.empty())
        {
            BinaryTreeNode<T> *Node = pending.pop_front();
            std::cout << Node->item << " ";
            if (Node->left != nullptr)
            {
                pending.push_back(Node->left);
            }
            if (Node->right != nullptr)
            {
                pending.push_back(Node->right);
            }
        }
    }

    BinaryTreeNode<T> preorder(BinaryTreeNode<T> *Node = this->root)
    {
        if (this->root == nullptr)
            return;
        std::cout << Node->item << " ";
        preorder(Node->left);
        preorder(Node->right);
    }

    BinaryTreeNode<T> inorder(BinaryTreeNode<T> *Node = this->root)
    {
        if (this->root == nullptr)
            return;
        inorder(Node->left);
        std::cout << Node->item << " ";
        inorder(Node->right);
    }

    BinaryTreeNode<T> postorder(BinaryTreeNode<T> *Node = this->root)
    {
        if (this->root == nullptr)
            return;
        postorder(Node->left);
        postorder(Node->right);
        std::cout << Node->item << " ";
    }
};
