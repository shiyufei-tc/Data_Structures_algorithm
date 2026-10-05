class SingleNode:
    """保存单链表中一个节点的数据及其后继节点引用。"""

    def __init__(self,item):
        """创建数据域为 item、暂时没有后继节点的新节点。

        参数：item，节点要保存的数据。
        返回：无；实例的 next 初始为 None。
        说明：None 表示节点当前尚未连接后继节点。
        """
        # next 为 None 表示当前节点尚未连接后继节点
        self.item=item
        self.next=None


class SingleLinkedList:
    """通过 head 引用维护首节点的单链表。"""

    def __init__(self,node:SingleNode=None):
        """使用可选的 node 作为首节点；未传入时创建空链表。

        参数：node，可选的首节点，默认值 None。
        返回：无；实例通过 head 保存首节点引用。
        说明：head 为 None 时链表为空。
        """
        # head 为 None 是空链表唯一需要判断的状态
        self.head:SingleNode=node

    def is_empty(self):
        """返回链表当前是否没有任何节点。

        参数：无。
        返回：bool；head 为 None 时返回 True，否则返回 False。
        说明：仅检查首节点引用，不遍历链表。
        """
        return self.head is None

    def length(self):
        """返回从 head 可达的节点数量，不改变链表结构。

        参数：无。
        返回：int；链表中的节点数量。
        说明：空链表返回 0。
        """
        current=self.head
        count=0
        # 判断当前节点本身，保证空链表安全且尾节点也会被计数
        while current is not None:
            count+=1
            current=current.next
        return count

    def travel(self):
        """从 head 开始按顺序逐行输出每个节点的数据。"""
        current=self.head
        # 先处理当前节点再前进，避免遗漏 next 为 None 的尾节点
        while current is not None:
            print(current.item)
            current=current.next

    def add_front(self,item):
        """创建保存 item 的节点，并将它连接为新的首节点。"""
        new_node=SingleNode(item)
        # 先保存原首节点的连接，再更新 head，避免原链表丢失
        new_node.next=self.head
        self.head=new_node

    def append(self,item):
        """创建保存 item 的节点，并将它连接到链表末尾。"""
        new_node=SingleNode(item)
        if self.is_empty():
            self.head=new_node
        else:
            current=self.head
            while current.next is not None:
                current=current.next
            # 尾节点必须指向新节点本身，而不是新节点初始为 None 的 next
            current.next=new_node

    def insert(self,pos:int,item):
        """按零基位置插入 item；越过两端时分别按头插或尾插处理。"""
        if pos<=0:
            self.add_front(item)
        elif pos>=self.length():
            self.append(item)
        else:
            new_node=SingleNode(item)
            current=self.head
            count=0
            # 让 current 停在 pos 的前一位，才能把新节点接入两侧之间
            while count<pos-1:
                current=current.next
                count+=1
            # 先接住原后半段，再让前一节点指向新节点，避免链路丢失
            new_node.next=current.next
            current.next=new_node

    def remove(self,item):
        """删除首个值等于 item 的节点；成功返回 True，否则返回 False。"""
        current=self.head
        previous=None
        while current is not None:
            if current.item==item:
                # 删除首节点需更新 head；其余位置由 previous 跨过 current
                if current==self.head:
                    self.head=current.next
                    return True
                else:
                    previous.next=current.next
                    return True
            else:
                previous=current
                current=current.next
        return False

    def search(self,item):
        """返回链表中是否存在值等于 item 的节点，不改变链表结构。"""
        current=self.head
        while current is not None:
            if current.item==item:
                return True
            else:
                current=current.next
        return False

if __name__=="__main__":
    node1=SingleNode(10)
    my_linked_list=SingleLinkedList(node1)
    my_linked_list.is_empty()
    my_linked_list.length()
    my_linked_list.travel()
    my_linked_list.add_front(1)
    my_linked_list.append(20)
    my_linked_list.insert(2,15)
    my_linked_list.remove(10)
    my_linked_list.search(15)
