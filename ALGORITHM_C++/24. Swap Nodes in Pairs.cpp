/**
 * @brief 单链表节点。
 *
 * val 保存节点数据，next 指向下一个节点；尾节点的 next 为 nullptr。
 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    /**
     * @brief 将链表中的相邻节点成对交换，并返回新的头节点。
     *
     * 使用位于原头节点之前的哑节点 dum，使第一对节点和后续节点对都能
     * 按相同方式处理，即每一对都有哑节点。每轮中，prev 指向待交换节点对的前驱，left 和
     * right 指向这一对节点。通过调整指针，将
     *
     *     prev -> left -> right -> 后继
     *
     * 重连为：
     *
     *     prev -> right -> left -> 后继
     *
     * 交换后 left 已成为当前节点对的末节点，因此将 prev 移动到 left，
     * 继续处理下一对。循环要求至少存在两个节点；若最后只剩一个节点，
     * 则该节点保持原位置。
     *
     * @param head 链表头节点，可以为 nullptr。
     * @return 成对交换后的链表头节点；空链表返回 nullptr。
     *
     * @complexity 时间 O(n)，每个节点只参与有限次指针调整；额外空间 O(1)。
     */
    ListNode *swapPairs(ListNode *head)
    {
        // 哑节点位于真实头节点之前，为第一对节点提供统一的前驱。
        ListNode dum(0, head);
        // prev 始终指向当前待交换节点对之前的节点。
        auto prev = &dum;
        // 剩余节点至少为两个时，才能完成一对节点的交换。
        while (prev->next != nullptr and prev->next->next != nullptr)
        {
            // 当前待交换的两个节点为 left -> right。
            auto left = prev->next;
            auto right = left->next;

            // 依次调整三个连接，形成 prev -> right -> left -> 原后继。
            left->next = right->next;
            right->next = left;
            prev->next = right;

            // 交换后 left 位于这对节点末尾，作为下一轮的前驱节点。
            prev = left;
        }
        // 哑节点的后继指向交换后的真实头节点。
        return dum.next;
    }
};