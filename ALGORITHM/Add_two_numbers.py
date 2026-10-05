
class ListNode:
    def __init__(self, val=0, next=None):
        # 链表节点保存当前位的数字，以及指向下一位的引用。
        self.val = val
        self.next = next



class Solution:
    def addTwoNumbers(self, l1: ListNode | None, l2: ListNode | None) -> ListNode | None:
        """将两个逆序存储的非负整数相加，并返回结果链表。

        例如：2 -> 4 -> 3 表示 342，5 -> 6 -> 4 表示 465，
        相加后返回 7 -> 0 -> 8，即 807。

        每个链表节点代表一个数位，因此不需要把链表转换成整数：
        直接从个位开始相加，并把进位传递到下一位即可。
        """
        if not l1 and not l2:
            # 两个输入都为空时，返回一个空值节点作为结果。
            return ListNode(None)

        # 创建链表的头节点，current为当前操作的节点指针
        dummy_head = ListNode()
        current = dummy_head

        # carry 保存上一位相加产生的进位，初始时没有进位。
        carry = 0

        # 两条链表都还有节点时，逐位计算：当前位结果 = 总和 % 10，
        # 新的进位 = 总和 // 10。
        while l1 and l2:
            tol = l1.val + l2.val + carry

            # 取个位作为当前结果节点的值。
            val = tol % 10
            # 取十位及以上作为下一位需要携带的进位。
            carry = tol // 10

            # 创建一个新的节点保存当前位的结果，并将其链接到链表。
            current.next = ListNode(val)

            # 两个输入指针和结果指针同时向后移动一位。
            l1 = l1.next
            l2 = l2.next
            current = current.next

        # 如果 l1 更长，继续将 l1 当前位与进位相加。
        if l1:
            while l1:
                tol = l1.val + carry
                val = tol % 10
                carry = tol // 10
                current.next = ListNode(val)
                l1 = l1.next
                current = current.next

        # 如果 l2 更长，继续将 l2 当前位与进位相加。
        if l2:
            while l2:
                tol = l2.val + carry
                val = tol % 10
                carry = tol // 10
                current.next = ListNode(val)
                l2 = l2.next
                current = current.next

        # 如果最高位仍有进位，需要在结果链表末尾新增一个节点。
        if carry != 0:
            current.next = ListNode(carry)

        # 头节点本身不属于结果，返回它后面的第一个真实节点。
        return dummy_head.next






        