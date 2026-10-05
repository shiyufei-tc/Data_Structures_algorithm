from __future__ import annotations

from collections import deque
from collections.abc import Iterator
from dataclasses import dataclass
from typing import Generic, TypeVar


T = TypeVar("T")


@dataclass
class BinaryTreeNode(Generic[T]):
    """二叉树节点。

    每个节点包含一个值，以及指向左右子节点的引用。
    这种结构可以表示任意二叉树，适合用作递归遍历和层序遍历的基础。

    Attributes:
        value: 节点存储的数据。
        left: 左子节点，默认为 None。
        right: 右子节点，默认为 None.
    """
    value: T
    left: BinaryTreeNode[T] | None = None
    right: BinaryTreeNode[T] | None = None


class BinaryTree(Generic[T]):
    """二叉树数据结构。

    该类支持以下操作：
    - 以层序方式插入节点
    - 广度优先遍历（按层访问）
    - 先序遍历（根 -> 左 -> 右）
    - 中序遍历（左 -> 根 -> 右）
    - 后序遍历（左 -> 右 -> 根）
    """

    def __init__(self) -> None:
        """初始化一棵空二叉树。"""
        # 根节点为空时，树中没有任何元素。
        self.root: BinaryTreeNode[T] | None = None

    def add_level_order(self, value: T) -> None:
        """按层序方式插入新节点。

        先从根节点开始，按照广度优先的顺序寻找第一个空的左右子节点位。
        这样插入的结果会尽量保持树的“完全二叉树”形态。

        Args:
            value: 要插入的节点值。
        """
        # 创建新节点，准备插入树中。
        new_node = BinaryTreeNode(value)
        root = self.root

        # 如果树为空，则新节点成为根节点。
        if root is None:
            self.root = new_node
            return

        # 使用队列模拟层序遍历，按层检查节点。
        pending: deque[BinaryTreeNode[T]] = deque([root])

        while pending:
            # 取出队首节点，检查它的左右子节点是否为空。
            current = pending.popleft()

            # 左子节点为空，则插入新节点并结束。
            if current.left is None:
                current.left = new_node
                return
            # 左子节点非空，则继续加入队列，以便后续处理其子树。
            pending.append(current.left)

            # 右子节点为空，则插入新节点并结束。
            if current.right is None:
                current.right = new_node
                return
            # 右子节点非空，则继续加入队列。
            pending.append(current.right)

    def breadth_first(self) -> Iterator[T]:
        """广度优先遍历：按层访问所有节点。

        采用队列实现，先访问当前层节点，再访问下一层节点。
        适合按层输出树结构，常用于二叉树的层序遍历。

        Yields:
            每个节点的值，按从上到下、从左到右的顺序输出。
        """
        root = self.root
        if root is None:
            return

        # 队列记录当前等待访问的节点。
        pending: deque[BinaryTreeNode[T]] = deque([root])

        while pending:
            # 取出队首节点并访问其值。
            current = pending.popleft()
            yield current.value

            # 先加入左子节点，再加入右子节点，保证层内从左到右的顺序。
            if current.left is not None:
                pending.append(current.left)
            if current.right is not None:
                pending.append(current.right)

    def preorder(self) -> Iterator[T]:
        """先序遍历：根 -> 左 -> 右。

        递归思想：先访问当前节点，再访问左子树，最后访问右子树。
        常用于复制树、前序序列化等场景。

        Yields:
            节点值，顺序为根、左、右。
        """

        def walk(node: BinaryTreeNode[T] | None) -> Iterator[T]:
            # 递归基：节点为空时直接返回。
            if node is None:
                return

            # 先访问当前节点。
            yield node.value
            # 再遍历左子树。
            yield from walk(node.left)
            # 最后遍历右子树。
            yield from walk(node.right)

        return walk(self.root)

    def inorder(self) -> Iterator[T]:
        """中序遍历：左 -> 根 -> 右。

        递归思想：先遍历左子树，再访问当前节点，最后访问右子树。
        对二叉搜索树而言，中序遍历可以得到升序序列。

        Yields:
            节点值，顺序为左、中、右。
        """

        def walk(node: BinaryTreeNode[T] | None) -> Iterator[T]:
            if node is None:
                return

            # 先处理左子树，再访问当前节点。
            yield from walk(node.left)
            yield node.value
            yield from walk(node.right)

        return walk(self.root)

    def postorder(self) -> Iterator[T]:
        """后序遍历：左 -> 右 -> 根。

        递归思想：先处理左右子树，最后访问当前节点。
        常用于删除树、后序计算和子树处理。

        Yields:
            节点值，顺序为左、右、根。
        """

        def walk(node: BinaryTreeNode[T] | None) -> Iterator[T]:
            if node is None:
                return

            # 先访问左右子树，最后访问当前节点。
            yield from walk(node.left)
            yield from walk(node.right)
            yield node.value

        return walk(self.root)
