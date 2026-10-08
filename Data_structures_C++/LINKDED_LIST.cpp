#include <iostream>
#include <vector>

/**
 * @brief 单链表节点模板类。
 *
 * 该结构表示单链表中的一个节点，包含数据域 item 和指向下一个节点的指针 next。
 * 采用模板设计，能够存储任意类型的数据（如 int、double、std::string 等）。
 *
 * @tparam T 节点存储的数据类型。
 */
template <typename T>
class SingleNode
{
public:
    T item;              // 节点中存储的数据
    SingleNode<T> *next; // 指向下一个节点的指针，末尾为 nullptr

    /**
     * @brief 构造函数，初始化节点数据和后继指针。
     *
     * @param item 节点要保存的值。
     */
    SingleNode(T item)
    {
        this->item = item;
        this->next = nullptr;
    }
};

/**
 * @brief 单链表模板类（带头结点实现）。
 *
 * 这是一个典型的单向链式存储结构，使用带头结点的方式管理链表。
 * 头结点本身不存储业务数据，仅作为链表入口，便于统一处理插入、遍历和判空等操作。
 *
 * 设计特点：
 * - 支持在表尾追加元素
 * - 支持批量添加数据（顺序插入与逆序插入两种方式）
 * - 支持判空、求长度、遍历
 * - 使用动态内存分配，析构函数负责释放链表节点
 *
 * @tparam T 链表元素类型。
 */
template <typename T>
class LINKDED_LIST
{
public:
    SingleNode<T> *head; // 头指针，指向头结点，不存储真实元素

    /**
     * @brief 默认构造函数。
     *
     * 创建一个带头结点的空链表。头结点的 item 使用 T() 进行默认值初始化，
     * 这样可以保证在未插入任何有效数据时，head 指向一个合法对象。
     */
    LINKDED_LIST()
    {
        // 1. 为链表创建一个头结点，head 始终指向这个哨兵节点。
        // 2. 该头结点不保存业务数据，仅用于统一处理链表的起始位置。
        this->head = new SingleNode<T>(T());
    }

    /**
     * @brief 析构函数。
     *
     * 从头结点开始依次释放所有节点，避免内存泄漏。
     * 释放顺序为：当前节点 -> next 节点 -> 直到 nullptr。
     */
    ~LINKDED_LIST()
    {
        // 释放链表中的每一个节点，避免出现内存泄漏。
        SingleNode<T> *current = this->head;
        while (current != nullptr)
        {
            // 先保存当前节点，再移动到下一个节点，最后删除当前节点。
            SingleNode<T> *temp = current;
            current = current->next;
            delete temp;
        }
    }

    /**
     * @brief 批量追加元素，保持输入顺序不变。
     *
     * 该方法会先遍历到链表尾部，再按 my_list 中元素的顺序依次追加到链表末尾。
     * 因为元素是按 vector 的顺序插入，因此最终链表中元素顺序与 my_list 保持一致。
     *
     * @param my_list 待追加的元素集合。
     */
    void PUSH_no_reverse_AllDATA(std::vector<T> &my_list)
    {
        // 先移动到尾部节点，然后按 vector 中的数据顺序依次追加。
        SingleNode<T> *current = this->head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        for (auto data : my_list)
        {
            // 每次创建一个新节点，并把它接到尾部。
            SingleNode<T> *new_node = new SingleNode<T>(data);
            current->next = new_node;
            current = current->next;
        }
    }

    /**
     * @brief 批量追加元素，并将新元素按逆序插入链表头部。
     *
     * 例如，输入 vector = [1, 2, 3] 时，链表最终顺序为 3 -> 2 -> 1。
     * 这是因为每次都把新节点插入到 head->next 位置，后加入的节点会被放在前面。
     *
     * @param my_list 待逆序插入的元素集合。
     */
    void PUSH_reverse_ALLDATA(std::vector<T> &my_list)
    {
        // 头插法：每次都把新节点插在 head 后面，从而实现逆序存储。
        // 若 my_list = [1, 2, 3]，最终链表顺序是 3 -> 2 -> 1。
        for (auto data : my_list)
        {
            SingleNode<T> *new_node = new SingleNode<T>(data);
            new_node->next = this->head->next;
            this->head->next = new_node;
        }
    }

    /**
     * @brief 判断链表是否为空。
     *
     * 对于带头结点的实现，当 head->next == nullptr 时，说明链表中没有有效数据节点，
     * 故链表为空。
     *
     * @return true 如果链表为空；false 如果含有至少一个数据节点。
     */
    bool is_empty()
    {
        // 由于使用头结点，所以真正的数据节点为空时，head->next 必为 nullptr。
        return this->head->next == nullptr;
    }

    /**
     * @brief 获取链表长度。
     *
     * 从 head->next 开始遍历，累计所有有效节点的数量。
     * 该长度不包含头结点本身。
     *
     * @return 链表中元素个数。
     */
    int get_length()
    {
        int count = 0;
        // 从第一个真实节点开始遍历，统计数据节点数量，不包含头结点本身。
        SingleNode<T> *current = this->head->next;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    /**
     * @brief 遍历并输出链表中的所有元素。
     *
     * 从第一个真实数据节点开始，依次访问直到尾部，
     * 使用 std::cout 逐个输出元素，每个元素后跟一个空格。
     * 该函数不改变链表结构，仅用于调试或展示数据。
     */
    void travel()
    {
        // 从第一个真实元素开始遍历，直到尾部 nullptr。
        SingleNode<T> *current = this->head->next;
        while (current != nullptr)
        {
            std::cout << current->item << " ";
            current = current->next;
        }
    }

    /**
     * @brief 在链表尾部追加一个新元素。
     *
     * 若链表为空，则直接将新节点作为第一个真实数据节点挂在 head 后面；
     * 若链表非空，则遍历到尾节点，再将新节点接在最后一个节点的 next 上。
     *
     * @param item 待插入的元素值。
     */
    void append(T item)
    {
        // 1. 创建新的数据节点；
        // 2. 若当前为空链表，则让头结点直接指向它；
        // 3. 否则，找到尾节点并把新节点挂到尾部。
        SingleNode<T> *new_node = new SingleNode<T>(item);
        if (is_empty())
        {
            this->head->next = new_node;
            return;
        }

        SingleNode<T> *current = this->head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new_node;
    }
};