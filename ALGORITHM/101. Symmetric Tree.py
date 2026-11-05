# 二叉树节点：val 保存节点值，left 和 right 分别指向左右子树。
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isSymmetric(self, root: TreeNode | None) -> bool:
        """判断二叉树是否关于根节点的中心轴对称。

        对称性不能只比较同一层节点的值，还必须比较它们所在的镜像位置。
        因此将根节点的左、右子树作为一对进行递归判断：左子树的左孩子
        必须对应右子树的右孩子，左子树的右孩子必须对应右子树的左孩子。
        两个节点都为空时该组镜像位置成立；只有一个为空，或两个节点值不等
        时，该组位置不对称。

        Args:
            root: 待判断的二叉树根节点。当前实现要求 root 不为 None。

        Returns:
            左右子树互为镜像时返回 True，否则返回 False。

        Complexity:
            时间复杂度 O(n)，每个节点最多参与一次镜像比较；递归栈空间
            复杂度 O(h)，其中 n 为节点数，h 为树高。
        """
        # 根节点本身位于对称轴上，只需判断其左右子树是否互为镜像。
        return self.judge_val(root.left,root.right)

    def judge_val(self,left_N:TreeNode|None,right_N:TreeNode|None)->bool:
        """递归判断两个节点及其子树是否互为镜像。

        对一对镜像节点，必须同时满足三个条件：节点同时存在且值相等；
        左节点的左子树与右节点的右子树镜像；左节点的右子树与右节点的
        左子树镜像。递归调用交换左右方向，正是对称位置关系的体现。

        Args:
            left_N: 镜像比较中的左侧节点。
            right_N: 镜像比较中的右侧节点。

        Returns:
            两棵子树互为镜像时返回 True，否则返回 False。
        """
        # 两个节点都存在时，先比较当前值，再递归比较两组交叉子树。
        if left_N!=None and right_N!=None:
            if left_N.val==right_N.val and self.judge_val(left_N.left,right_N.right) and self.judge_val(left_N.right,right_N.left):
                return True
            else:
                return False
        # 两个镜像位置都为空，说明这一对位置满足对称条件。
        elif left_N==None and right_N==None:
            return True
        # 只有一侧为空时，镜像结构不同，必然不对称。
        else:
            return False
