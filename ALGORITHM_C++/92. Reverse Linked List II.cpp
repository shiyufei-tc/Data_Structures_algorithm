/**
 * @brief 单链表节点。
 *
 * val 保存节点值，next 指向下一个节点；尾节点的 next 为 nullptr。
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
     * @brief 原地反转链表中位置 left 到 right 的连续节点。
     *
     * 位置按 1 开始计数。使用哑节点 dum 统一处理反转区间从第一个节点
     * 开始的情况。先将 cur 移动到区间前驱，记为 prev；保存区间首节点
     * tail，因为反转后它会成为该区间的尾节点。
     *
     * 随后采用头插法：每轮取出当前待处理节点 cur，并将它插入 prev
     * 之后。循环过程中，prev 后面是已经反转的部分，tail 后面连接着
     * 尚未处理的部分。全部节点插入完成后，将 tail 连接到剩余链表。
     *
     * @param head 链表头节点，可以为 nullptr。
     * @param left 反转区间起始位置，位置从 1 开始。
     * @param right 反转区间结束位置，位置从 1 开始。
     * @return 完成区间反转后的链表头节点。
     *
     * @complexity 时间 O(n)，额外空间 O(1)。
     */
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        // 哑节点位于真实头节点之前，统一处理 left == 1 的场景。
        ListNode dum(0, head);
        // cur 用于定位反转区间前驱。
        auto cur = &dum;
        int count = 0;
        // 移动到第 left-1 个位置，使 cur 指向区间前驱。
        while (count < left - 1)
        {
            count += 1;
            cur = cur->next;
        }
        // prev 是区间前驱；tail 是区间首节点，反转后成为区间尾节点。
        auto prev = cur;
        auto tail = prev->next;
        // 区间长度减一，表示需要将多少个后继节点头插到 prev 后面。
        int num = right - left;
        if (num == 0)
            // left == right 时只有一个节点，链表无需改变。
            return dum.next;
        // 从区间第二个节点开始逐个取节点进行头插。
        cur = cur->next->next;
        for (int _ = 0; _ < num; ++_)
        {
            // 先保存原后继，避免修改 cur->next 后丢失未处理节点。
            auto the_next = cur->next;
            // 将 cur 插入已反转部分的最前端，形成 prev -> cur -> 原首节点。
            cur->next = prev->next;
            prev->next = cur;
            // 继续处理原链表中的下一个节点。
            cur = the_next;
        }
        // tail 已成为反转区间尾部，接回区间之后的剩余链表。
        tail->next = cur;
        // 哑节点的后继就是完成处理后的真实头节点。
        return dum.next;
    }
};