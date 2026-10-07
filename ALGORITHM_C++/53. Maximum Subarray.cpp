#include <algorithm>
#include <vector>
class Solution
{
public:
    /**
     * @brief 返回整数数组中连续非空子数组的最大和。
     *
     * 使用 Kadane 算法从左向右扫描数组。sum 表示以当前扫描位置结尾的
     * 候选子数组之和。每加入一个元素，就用当前和更新全局最大值；若当前和
     * 为负数，则将其清零，从下一个元素开始构造候选子数组，因为负前缀只会
     * 降低后续子数组的和。
     *
     * 全局最大值以数组中的最大元素初始化，因此即使所有元素都是负数，也能
     * 返回最大的单元素子数组，而不会错误地返回 0。
     *
     * @param nums 至少包含一个整数的数组。
     * @return 连续非空子数组的最大元素和。
     *
     * @complexity 时间 O(n)，额外空间 O(1)，其中 n 为数组长度。
     */
    int maxSubArray(std::vector<int> &nums)
    {
        // 以数组最大元素初始化结果，确保全负数输入也能得到正确答案。
        auto max = *std::max_element(nums.begin(), nums.end());
        // 当前候选子数组的累计和。
        auto sum = 0;

        // 逐个将元素加入当前候选子数组，并维护已见到的最大子数组和。
        for (auto num : nums)
        {
            sum += num;
            // 当前累计和对应一个以本位置结尾的子数组，检查它是否为全局最优。
            max = std::max(max, sum);

            // 负和作为后续子数组的前缀只会降低总和，因此丢弃并从下一个元素重算。
            if (sum < 0)
            {
                sum = 0;
            }
        }
        return max;
    }
};