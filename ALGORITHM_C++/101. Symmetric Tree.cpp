#include<memory>

/**
 * @brief 二叉树节点。
 *
 * val 保存节点值，left 和 right 分别拥有当前节点的左右子树。
 */
struct TreeNode
{
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right) : val(x), left(std::move(left)), right(std::move(right)) {}
};
class Solution
{
public:
    /**
     * @brief 判断二叉树是否关于根节点的中心轴对称。
     *
     * 对称性要求根节点的左右子树互为镜像，而不仅是对应层的节点值相等。
     * 因此将根节点的左右子树作为一对传入 judge_val：左子树的左孩子对应
     * 右子树的右孩子，左子树的右孩子对应右子树的左孩子。两个对应位置
     * 都为空时满足镜像关系；只有一侧为空或节点值不同时则不对称。
     *
     * @param root 二叉树根节点。当前实现要求 root 不为 nullptr。
     * @return 左右子树互为镜像时返回 true，否则返回 false。
     *
     * @complexity 时间 O(n)，每个节点最多参与一次比较；递归栈空间 O(h)，
     *             其中 n 为节点数，h 为树高。
     */
    bool isSymmetric(std::unique_ptr<TreeNode> root)
    {
        // 根节点位于对称轴上，只需比较其左右子树的镜像关系。
        return judge_val(root->left, root->right);
    }

    /**
     * @brief 递归判断两个节点及其子树是否互为镜像。
     *
     * 一对镜像节点需要同时满足：两者同时存在且值相等；左节点的左子树
     * 与右节点的右子树镜像；左节点的右子树与右节点的左子树镜像。
     * 递归调用时交换左右方向，用于保持镜像位置的对应关系。
     *
     * @param left_N 镜像比较中的左侧节点。
     * @param right_N 镜像比较中的右侧节点。
     * @return 两棵子树互为镜像时返回 true，否则返回 false。
     */
    bool judge_val(const std::unique_ptr<TreeNode>& left_N, const std::unique_ptr<TreeNode>& right_N)
    {
        // 两个节点都存在时，比较值并递归检查两组交叉子树。
        if (left_N != nullptr && right_N != nullptr)
        {
            if (left_N->val == right_N->val && judge_val(left_N->left, right_N->right) && judge_val(left_N->right, right_N->left))
                return true;
            else
                return false;
        }
        // 两个镜像位置同时为空，说明这一对位置满足对称条件。
        else if (left_N == nullptr && right_N == nullptr)
            return true;
        // 只有一侧为空时，树的结构不再互为镜像。
        else
            return false;
    }
};