# 单链表节点：val 保存节点值，next 指向下一个节点。
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def swapPairs(self, head: ListNode | None) -> ListNode | None:
        """将链表中的相邻节点成对交换，并返回新的头节点。

        算法使用一个位于原头节点之前的哑节点 ``dum``，统一处理第一对节点
        和后续节点对，即每一对都有哑节点。每轮令 ``prev`` 指向待交换节点对之前的节点，令
        ``left``、``right`` 分别指向这一对的第一个和第二个节点，然后按
        ``prev -> right -> left -> 后继`` 的顺序重新连接指针。

        交换完成后，``left`` 已成为这一对的第二个节点，因此将 ``prev``
        移动到 ``left``，即可继续处理下一对节点。循环条件要求当前节点
        后至少还有两个节点；若剩余一个节点，则保持其原有位置。

        Args:
            head: 链表头节点；可以为 ``None``。

        Returns:
            成对交换后的链表头节点。空链表返回 ``None``。

        Complexity:
            时间复杂度 O(n)，每个节点至多被访问和改链一次；额外空间复杂度 O(1)。
        """
        # 哑节点位于真实头节点之前，使第一对节点也有统一的前驱节点。
        dum=ListNode(0,head)
        # prev 始终指向当前待交换节点对之前的节点。
        prev=dum
        # 只有剩余节点数至少为 2 时，才能进行一次完整交换。
        while prev.next and prev.next.next:
            # 当前节点对为 left -> right。
            left=prev.next
            right=left.next
            # 先让 left 接到这一对之后，再让 right 接到 left，
            # 最后由前驱连接 right，形成 prev -> right -> left。
            left.next=right.next
            right.next=left
            prev.next=right
            # 交换后 left 是这一对的末节点，作为下一轮的前驱。
            prev=left
        # 哑节点的后继就是交换完成后的真实头节点。
        return dum.next
