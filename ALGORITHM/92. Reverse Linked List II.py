# 单链表节点：val 保存节点值，next 指向下一个节点。
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseBetween(self, head: ListNode | None, left: int, right: int) -> ListNode | None:
        """原地反转链表中位置 ``left`` 到 ``right`` 的连续节点。

        位置按 1 开始计数。算法使用哑节点 ``dum``，使得反转区间从第一个
        节点开始时也能统一处理。先将 ``cur`` 移动到反转区间前一个节点，
        记为 ``prev``；``tail`` 保存区间第一个节点，因为反转后它会成为
        区间尾节点。

        随后使用头插法：每轮取出当前待处理节点 ``cur``，将它插入到
        ``prev`` 后面。这样 ``prev`` 后面的部分始终是已经反转的前缀，
        而 ``tail`` 后面仍连接着尚未处理的节点。完成所有插入后，将
        ``tail`` 连接到剩余链表，得到完整结果。

        Args:
            head: 链表头节点，可以为 ``None``。
            left: 反转区间的起始位置，位置从 1 开始。
            right: 反转区间的结束位置，位置从 1 开始。

        Returns:
            反转指定区间后的链表头节点。

        Complexity:
            时间复杂度 O(n)，额外空间复杂度 O(1)。
        """
        # 哑节点位于真实头节点之前，统一处理 left == 1 的情况。
        dum=ListNode(0,head)
        # cur 最终指向反转区间前驱节点。
        cur=dum
        count=0
        # 移动到第 left-1 个位置，即区间前驱所在位置。
        while count<left-1:
            cur=cur.next
            count+=1
        # prev 是反转区间前驱；tail 是区间首节点，反转后成为区间尾节点。
        prev=cur
        tail=prev.next
        # 需要移动多少个后继节点到 prev 后面。
        num=right-left
        if num>0:
            # 从区间第二个节点开始，依次执行头插。
            cur=cur.next.next
        else:
            # left == right 时区间只有一个节点，无需反转。
            return dum.next
        for _ in range(num):
            # 保存待处理节点的原后继，避免改链后丢失剩余链表。
            the_next=cur.next
            # 将当前节点插入已反转部分的最前端：
            # 原结构为 prev -> ... -> cur，调整后 cur -> 原首节点。
            cur.next=prev.next
            prev.next=cur
            # 继续处理原链表中的下一个节点。
            cur=the_next
        # tail 已是反转区间尾部，将它接回尚未处理的后续部分。
        tail.next=cur
        # 哑节点的后继是处理后的真实头节点。
        return dum.next