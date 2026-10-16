#include <vector>

class Solution
{
public:
    /**
     * @brief 将数组中的元素整体向右轮转 k 个位置。
     *
     * 轮转后，原下标 i 的元素位于 (i + k) % length。由于轮转 length
     * 次与不轮转等价，先用取模将 k 归约到 [0, length) 范围内。随后将每个
     * 元素写入临时数组中的目标位置，最后复制回 nums。
     *
     * 空数组不需要处理，函数会直接返回。nums 会被原地更新，但实现使用
     * 与输入等长的临时数组保存重排结果。
     *
     * @param nums 待轮转的整数数组。
     * @param k 向右轮转的非负位置数。
     *
     * @complexity 时间 O(n)，额外空间 O(n)，其中 n 为数组长度。
     */
    void rotate(std::vector<int> &nums, int k)
    {
        // 保存数组长度；空数组没有可轮转的元素，提前返回以避免取模零。
        int length = nums.size();
        if (length == 0)
            return;

        // 轮转 length 位等价于不轮转，只需处理余数部分。
        k = k % length;

        // 临时数组用于放置每个元素轮转后的目标位置。
        std::vector<int> temp(length);

        // 原下标 index 的元素右移 k 位后，落在循环数组下标 (index + k) % length。
        for (int index = 0; index < length; index++)
        {
            temp[(index + k) % length] = nums[index];
        }

        // 将重排后的结果写回输入数组，完成原地更新。
        for (int index = 0; index < length; index++)
        {
            nums[index] = temp[index];
        }
    }
};