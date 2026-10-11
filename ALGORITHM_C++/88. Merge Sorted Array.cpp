#include <vector>
class Solution
{
public:
    /**
     * @brief 将两个非递减数组合并为一个非递减数组，并写回 nums1。
     *
     * nums1 的前 m 个元素和 nums2 的 n 个元素分别是两个已排序序列；
     * nums1 末尾预留的 n 个位置用于存放合并结果。算法从两个有效序列的
     * 末尾开始比较，每次将较大元素写入 nums1 当前可写的最末位置，再向前
     * 移动对应的读取下标。由后向前写入可避免覆盖 nums1 中尚未处理的元素。
     *
     * 循环只需持续到 nums2 的元素全部写入：若 nums1 仍有未处理元素，
     * 它们已经位于结果数组的正确位置，无须额外移动。
     *
     * @param nums1 容纳合并结果的数组；前 m 个元素为有序有效数据，且总长度
     *              至少为 m + n。
     * @param m nums1 中参与合并的有效元素个数。
     * @param nums2 参与合并的有序数组。
     * @param n nums2 中参与合并的元素个数。
     *
     * @pre m >= 0，n >= 0，nums1.size() >= m + n，且两个有效输入区间均按非递减顺序排列。
     * @post nums1 的前 m + n 个元素为两个输入序列的非递减合并结果。
     *
     * @complexity 最坏时间 O(m + n)，额外空间 O(1)。
     */
    void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n)
    {
        // 分别指向两个有效序列尚未处理部分的末尾，以及 nums1 的写入末尾。
        int index_m = m - 1, index_n = n - 1, nums1_index = static_cast<int>(nums1.size()) - 1;

        // nums2 尚有元素时继续合并；nums1 剩余元素已在结果中的正确位置。
        while (index_n >= 0)
        {
            // 若 nums1 还有有效元素且其末尾值较大，就先将它放到结果末尾。
            if (index_m >= 0 && nums1[index_m] > nums2[index_n])
            {
                nums1[nums1_index] = nums1[index_m];
                index_m -= 1;
            }
            else
            {
                // 否则将 nums2 的末尾值放入当前位置；相等时取 nums2 不影响排序。
                nums1[nums1_index] = nums2[index_n];
                index_n -= 1;
            }
            // 写入位置左移，为下一次选出的较大元素留出位置。
            nums1_index -= 1;
        }
    }
};