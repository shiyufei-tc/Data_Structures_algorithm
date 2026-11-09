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
     * @brief 使用归并排序将单链表按升序排列。
     *
     * 链表归并排序采用分治策略：
     * 1. 使用快慢指针找到链表中点，并将链表断开为左右两段。
     * 2. 递归左右两段，直到子链表为空或只包含一个节点。
     * 3. 调用 merge 将两个有序子链表合并为一个有序链表。
     *
     * 拆分时通过修改 next 指针断开链表，合并时直接复用原节点并重新连接，
     * 不需要创建与节点数量相关的额外数据节点。
     *
     * @param head 待排序的链表头节点，可以为 nullptr。
     * @return 按节点值升序排列后的链表头节点。
     *
     * @complexity 时间 O(n log n)，递归栈空间 O(log n)，其中 n 为节点数。
     */
    ListNode *sortList(ListNode *head)
    {
        // 空链表或单节点链表已经有序，是递归终止条件。
        if (head == nullptr || head->next == nullptr)
            return head;

        // slow 最终指向前半段尾部，fast 以两倍速度移动以寻找链表中点。
        auto slow = head;
        auto fast = head;
        while (fast->next && fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        // mid 是后半段头节点；断开 slow->next，得到两个独立子链表。
        auto mid = slow->next;
        slow->next = nullptr;

        // 递归处理左半段：sortList(head) 会继续拆分这段链表，直到每段只剩
        // 一个节点或为空；随后在回溯阶段将这些有序的小段逐层合并。
        // 递归处理右半段：sortList(mid) 与左半段执行完全相同的拆分和排序过程。
        // 两次递归调用返回时，head 和 mid 已分别指向两个独立的有序链表。
        // 最后调用 merge 合并这两个有序结果；merge 的返回值就是当前整段链表
        // 排序后的新头节点，并继续作为上一层递归的返回值。
        return merge(sortList(head), sortList(mid));
    }

    /**
     * @brief 合并两个已经按升序排列的单链表。
     *
     * 使用哑节点作为合并结果的起点。每轮比较两个当前节点，将较小节点
     * 接到结果链表尾部，并只移动被取出节点所在链表的指针。一个链表耗尽
     * 后，另一个链表剩余部分已经有序，可以整体接到结果末尾。
     *
     * 比较时使用 <=，当值相等时优先取 a 中的节点，从而保持相等节点的
     * 原有先后顺序。
     *
     * @param left 第一个升序链表。
     * @param right 第二个升序链表。
     * @return 合并后的升序链表头节点。
     *
     * @complexity 时间 O(m + n)，额外空间 O(1)，其中 m、n 为两个链表长度。
     */
    ListNode *merge(ListNode *left, ListNode *right)
    {
        // 哑节点不属于结果数据，只用于统一处理结果链表的首节点连接。
        ListNode dum;
        auto cur = &dum;
        // 每轮选择当前两个链表头部较小的节点接入结果链表。
        while (left && right)
        {
            if (left->val <= right->val)
            {
                cur->next = left;
                left = left->next;
            }
            else
            {
                cur->next = right;
                right = right->next;
            }
            cur = cur->next;
        }

        // 其中一个链表为空后，直接接入另一个链表的剩余有序部分。
        cur->next = left ? left : right;
        // 返回哑节点之后的第一个真实数据节点。
        return dum.next;
    }
};