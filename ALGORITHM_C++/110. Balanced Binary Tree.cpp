#include <algorithm>

/**
 * @brief 二叉树节点。
 *
 * val 保存节点值，left 和 right 分别指向左右子树；空子树使用 nullptr 表示。
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution
{
public:
    // 记录后序遍历过程中是否发现过高度不平衡的节点。
    bool is_bal = true;

    /**
     * @brief 判断二叉树是否为高度平衡树。
     *
     * 高度平衡要求每个节点的左右子树高度差的绝对值都不超过 1。
     * 本实现通过后序遍历自底向上计算高度：只有先得到左右子树高度，
     * 才能判断当前节点是否平衡；随后将当前子树高度返回给父节点。
     *
     * is_bal 在遍历过程中累计记录所有节点的检查结果。即使某个节点已经
     * 失衡，递归仍会继续计算高度，因为祖先节点仍需要左右子树高度才能
     * 完成自身的检查。
     *
     * @param root 待判断的二叉树根节点，可以为 nullptr。
     * @return 所有节点均满足高度差不超过 1 时返回 true，否则返回 false。
     *
     * @complexity 时间 O(n)，每个节点访问一次；递归栈空间 O(h)，其中 n
     *             为节点数，h 为树高。
     */
    bool isBalanced(TreeNode *root)
    {
        // work 返回整棵树高度，并在递归过程中更新 is_bal。
        work(root);
        return is_bal;
    }

    /**
     * @brief 计算当前子树高度并检查其是否平衡。
     *
     * 对当前节点执行后序处理：先递归得到左、右子树高度，再比较两者差值。
     * 当前子树高度定义为 1 加上左右子树较大高度；空子树高度定义为 0。
     * 返回高度而不是仅返回布尔值，是因为父节点的平衡性依赖准确的子树高度。
     *
     * @param Node 当前子树根节点。
     * @return 当前子树的高度；空节点返回 0。
     */
    int work(TreeNode *Node)
    {
        // 空子树高度为 0，同时也是递归终止条件。
        if (!Node)
            return 0;

        // 后序遍历：先取得左右子树高度，再处理当前节点。
        int left = work(Node->left);
        int right = work(Node->right);

        // 当前节点平衡的必要条件是左右子树高度差不超过 1。
        if (std::abs(right - left) > 1)
            is_bal = false;

        // 将当前子树高度返回给父节点，用于父节点的平衡性判断。
        // 如果递归存在返回值，return写在最后
        return 1 + std::max(left, right);
    }
};