#include <algorithm>
#include <vector>

class Solution
{
public:
    /**
     * @brief 找出数组中所有和为 0 的不重复三元组。
     *
     * 先将 nums 原地升序排序，再依次固定一个元素，并在其右侧区间使用
     * 左右指针查找另外两个数。三数之和大于 0 时右指针左移以减小总和；
     * 小于 0 时左指针右移以增大总和。找到解后记录三元组，并移动两指针。
     *
     * 排序后，相同的固定值只处理一次；每次找到解后跳过左右两侧的重复值，
     * 从而避免重复三元组。当固定值大于 0 时，后续值也都大于 0，可提前结束。
     *
     * @param nums 输入整数向量；本函数会对其原地排序。
     * @return 所有和为 0 的不重复三元组，且每个三元组均为非递减顺序。
     *
     * @complexity 时间 O(n^2)（排序为 O(n log n)）；除返回结果外，
     *             双指针搜索额外空间 O(1)。
     */
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
    {
        // 排序后可利用单调性移动双指针，并按相邻元素跳过重复值。
        std::vector<std::vector<int>> result;
        std::sort(nums.begin(), nums.end());

        // 依次固定三元组的第一个数，剩余两个数在其右侧区间中查找。
        for (int index = 0; index < nums.size(); ++index)
        {
            // 固定值大于 0 时，后续值也都大于 0，不可能再组成和为 0 的三元组。
            if (nums[index] > 0)
                break;
            // 相同的固定值只搜索一次，避免重复结果。
            if (index > 0 && nums[index] == nums[index - 1])
                continue;

            // left_index 和 right_index 从固定位置两侧向中间收缩。
            int left_index = index + 1, right_index = static_cast<int>(nums.size()) - 1;
            while (left_index < right_index)
            {
                int sum = nums[index] + nums[left_index] + nums[right_index];
                if (sum > 0)
                    // 总和过大，移动右指针以减小总和。
                    right_index -= 1;
                else if (sum < 0)
                    // 总和过小，移动左指针以增大总和。
                    left_index += 1;
                else
                {
                    // 找到一组解；排序保证三元组自身按非递减顺序排列。
                    result.push_back(std::vector<int>{nums[index], nums[left_index], nums[right_index]});
                    right_index -= 1;
                    left_index += 1;

                    // 跳过重复的左侧元素，避免重复生成相同三元组。
                    while (left_index < right_index && nums[left_index] == nums[left_index - 1])
                        left_index += 1;
                    // 跳过重复的右侧元素，避免重复生成相同三元组。
                    while (left_index < right_index && nums[right_index] == nums[right_index + 1])
                        right_index -= 1;
                }
            }
        }
        return result;
    }
};