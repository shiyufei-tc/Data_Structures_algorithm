#include <iostream>
#include <vector>

/**
 * @brief 单链表中的一个节点。
 *
 * 节点由数据成员 item 和后继指针 next 组成。链表通过 next 将节点按顺序
 * 串接起来；尾节点的 next 为 nullptr。该类型本身不负责管理后继节点的内存，
 * 节点的创建和释放由链表类负责。
 *
 * @tparam T 节点中保存的数据类型。
 */
template <typename T>
class SingleNode
{
public:
    T item;              // 当前节点保存的数据。
    SingleNode<T> *next; // 后继节点；若当前节点为尾节点则为 nullptr。

    /**
     * @brief 创建一个节点并初始化其数据和后继指针。
     *
     * 新节点的 next 初始化为空指针，因此构造完成时它尚未链接到其他节点。
     *
     * @param item 要保存在节点中的值。
     */
    SingleNode(T item)
    {
        this->item = item;
        this->next = nullptr;
    }
    SingleNode()
    {
        this->item = nullptr_t;
        this->next = nullptr;
    }
};

/**
 * @brief 使用哨兵头结点管理的单向链表。
 *
 * head 始终指向一个不保存业务数据的哨兵节点；实际元素从 head->next 开始，
 * 空链表满足 head->next == nullptr。哨兵节点让首元素插入、删除等操作可以
 * 统一按“修改前驱节点的 next”处理。
 *
 * 本类动态创建节点，并在析构时释放当前链表中的全部节点。作为模板类型，
 * T 需要可默认构造（用于哨兵节点）；调用 travel、search 或 remove 时，
 * T 还需分别支持流输出、相等比较等相应操作。
 *
 * @tparam T 链表数据节点保存的数据类型。
 */
template <typename T>
class LINKDED_LIST
{
public:
    SingleNode<T> *head; // 指向哨兵头结点；业务数据从 head->next 开始。

    /**
     * @brief 构造一个空的带头结点链表。
     *
     * 动态创建哨兵节点，并将 head 指向该节点。哨兵节点的 item 仅为满足
     * 节点构造而默认初始化，不代表链表中的有效元素；其 next 初始为空，
     * 因而构造后的链表不包含任何数据节点。
     *
     * @complexity 时间 O(1)，额外空间 O(1)。
     */
    LINKDED_LIST()
    {
        // 创建哨兵节点，后续的实际元素都链接在它的 next 后面。
        this->head = new SingleNode<T>();
    }

    /**
     * @brief 释放链表拥有的全部节点。
     *
     * 从哨兵节点开始沿 next 遍历。删除当前节点之前先保存后继指针，
     * 这样释放当前节点后仍能继续访问链表的剩余部分。析构后，链表中的
     * 哨兵节点和所有数据节点均已释放。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为数据节点数量。
     */
    ~LINKDED_LIST()
    {
        // 从哨兵节点开始，逐个释放整条链上的节点。
        SingleNode<T> *current = this->head;
        while (current != nullptr)
        {
            // 必须先记下后继节点，否则删除 current 后无法继续遍历。
            SingleNode<T> *temp = current;
            current = current->next;
            delete temp;
        }
    }

    /**
     * @brief 将数组中的元素按原有顺序逐个追加到链表尾部。
     *
     * 先从哨兵节点找到当前尾节点，再按 vector 的迭代顺序创建并链接新节点。
     * 此操作保留链表原有内容；新追加部分的顺序与 my_list 一致。若输入为空，
     * 则链表保持不变。
     *
     * @param my_list 待追加的元素序列。
     *
     * @complexity 若原链表有 n 个元素、输入有 k 个元素，时间 O(n + k)，
     *             每次调用额外空间 O(1)（不计新建的 k 个链表节点）。
     */
    void PUSH_no_reverse_AllDATA(std::vector<T> &my_list)
    {
        // 找到当前尾节点；空链表时，哨兵节点本身就是待追加位置的前驱。
        SingleNode<T> *current = this->head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        // 按输入顺序逐个尾插，因此追加部分不会发生反转。
        for (auto data : my_list)
        {
            // 将新节点接到尾部，并将 current 更新为新的尾节点。
            SingleNode<T> *new_node = new SingleNode<T>(data);
            current->next = new_node;
            current = current->next;
        }
    }

    /**
     * @brief 将数组中的元素逐个头插到链表中。
     *
     * 每个新节点都插入到哨兵节点之后，因此这一批新元素在链表中的相对顺序
     * 与 my_list 相反。例如 [1, 2, 3] 会成为 3 -> 2 -> 1。新节点会位于
     * 调用前已有数据节点之前，原链表中元素的相对顺序保持不变。
     *
     * @param my_list 待插入的元素序列。
     *
     * @complexity 若输入有 k 个元素，时间 O(k)，额外空间 O(1)
     *            （不计新建的 k 个链表节点）。
     */
    void PUSH_reverse_ALLDATA(std::vector<T> &my_list)
    {
        // 头插法将每个新节点放在已有数据之前，故本批数据最终呈逆序。
        for (auto data : my_list)
        {
            SingleNode<T> *new_node = new SingleNode<T>(data);
            // 先接上当前首节点，再让哨兵节点指向新节点。
            new_node->next = this->head->next;
            this->head->next = new_node;
        }
    }

    /**
     * @brief 判断链表是否不含数据节点。
     *
     * 哨兵节点始终存在，因此只需检查它的 next：若 next 为空，哨兵之后没有
     * 任何业务数据节点；否则链表至少包含一个元素。
     *
     * @return 链表为空时为 true，否则为 false。
     *
     * @complexity 时间 O(1)，额外空间 O(1)。
     */
    bool is_empty()
    {
        // 头结点之后没有节点，即为空链表。
        return this->head->next == nullptr;
    }

    /**
     * @brief 统计链表中数据节点的数量。
     *
     * 从第一个数据节点开始沿 next 遍历，每访问一个节点就将计数加一。
     * 哨兵头结点不属于数据，因此不计入长度。
     *
     * @return 当前链表的数据元素个数。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为数据节点数量。
     */
    int get_length()
    {
        int count = 0;
        // 从首个数据节点开始，跳过不计入长度的哨兵节点。
        SingleNode<T> *current = this->head->next;
        while (current != nullptr)
        {
            // 统计当前数据节点，然后前进到后继节点。
            count++;
            current = current->next;
        }
        return count;
    }

    /**
     * @brief 按链表顺序将所有数据元素输出到标准输出。
     *
     * 从首个数据节点开始遍历至 nullptr，每个元素使用 std::cout 输出，
     * 并在元素后输出一个空格。该方法只读取链表，不改变节点或链接关系；
     * 因而 T 必须支持使用流插入运算符输出。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为数据节点数量。
     */
    void travel()
    {
        // 跳过哨兵节点，从第一个实际元素开始访问。
        SingleNode<T> *current = this->head->next;
        while (current != nullptr)
        {
            // 输出当前值及分隔空格，再移动到下一个节点。
            std::cout << current->item << " ";
            current = current->next;
        }
    }

    /**
     * @brief 在链表末尾追加一个数据节点。
     *
     * 创建保存 item 的新节点。若链表为空，新节点直接成为首个数据节点；
     * 否则从哨兵节点开始找到尾节点，并将新节点链接在其后。原有元素顺序
     * 不变，新节点成为新的尾节点。
     *
     * @param item 要追加到链表末尾的值。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为原数据节点数量；
     *             新建节点本身占用 O(1) 空间。
     */
    void append(T item)
    {
        // 为待追加的值创建一个后继为空的新节点。
        SingleNode<T> *new_node = new SingleNode<T>(item);
        if (is_empty())
        {
            // 空表中，哨兵节点直接链接到首个数据节点。
            this->head->next = new_node;
            return;
        }

        // 非空时遍历到最后一个数据节点。
        SingleNode<T> *current = this->head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        // 将新节点接在尾节点之后。
        current->next = new_node;
    }

    /**
     * @brief 在指定位置插入一个元素。
     *
     * 位置采用从 0 开始的下标：pos 为 0 时插入到第一个数据节点之前，
     * pos 等于当前长度时追加到链表末尾。通过从头结点开始前进 pos 步，
     * 找到新节点应当插入位置的前驱，再调整两个 next 指针完成插入。
     *
     * @param pos 插入位置，必须满足 0 <= pos <= 当前链表长度。
     * @param item 要插入的元素值。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为链表长度。
     */
    void insert(int pos, T item)
    {
        // 从哨兵头结点开始计步，最终 current 指向新节点的前驱。
        SingleNode<T> *current = this->head;
        SingleNode<T> *new_node = new SingleNode<T>(item);
        int count = 0;
        while (count < pos)
        {
            current = current->next;
            count++;
        }
        // 先连接新节点与后继，再让前驱指向新节点，避免断开原链表。
        new_node->next = current->next;
        current->next = new_node;
    }

    /**
     * @brief 删除链表中第一个值等于指定元素的节点。
     *
     * 从头结点开始检查后继节点；找到匹配值后绕过该节点，并释放其占用的
     * 内存。若链表中不存在该值，则不修改链表。
     *
     * @param item 要查找并删除的元素值。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为链表长度。
     */
    void remove(T item)
    {
        // 保留前驱指针，便于找到目标后直接调整其 next。
        SingleNode<T> *current = this->head;
        while (current->next != nullptr)
        {
            if (current->next->item == item)
            {
                // 先保存待删除节点，再从链表中摘除并释放它。
                SingleNode<T> *removed_node = current->next;
                current->next = removed_node->next;
                delete removed_node;
                break;
            }
            else
                current = current->next;
        }
    }

    /**
     * @brief 判断链表中是否存在指定元素。
     *
     * 从第一个数据节点开始逐个比较，遇到匹配值立即返回 true；遍历到链表
     * 末尾仍未匹配时返回 false。
     *
     * @param item 要查找的元素值。
     * @return 找到该值时返回 true，否则返回 false。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为链表长度。
     */
    bool search(T item)
    {
        // 跳过不存储业务数据的头结点，依次检查所有有效节点。
        SingleNode<T> *current = this->head->next;
        while (current != nullptr)
        {
            if (current->item == item)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    /**
     * @brief 原地反转链表中的数据节点。
     *
     * 逐个取出原链表头部的数据节点，并将其插入到哨兵头结点之后。
     * 每轮先保存尚未处理部分的首节点，再反转当前节点的 next 指向；
     * 完成后，原尾节点成为新的首节点。头结点本身始终保留，不参与反转。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为链表长度。
     */
    void Reverse1()
    {
        // node 指向尚未处理部分的首节点；先将头结点置为空链表状态。
        SingleNode<T> *node = this->head->next;
        this->head->next = nullptr;
        while (node != nullptr)
        {
            // 在改写当前节点指针前，保存原链表中下一个待处理节点。
            SingleNode<T> *next_node = node->next;
            // 将当前节点头插到已反转部分的最前端。
            node->next = this->head->next;
            this->head->next = node;
            node = next_node;
        }
    }
};