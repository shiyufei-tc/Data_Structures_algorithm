#include <vector>

class Solution
{
public:
    /**
     * @brief 求元素和至少为 target 的最短连续子数组长度。
     *
     * 使用滑动窗口 [left, right] 维护当前连续区间及其元素和 sum。
     * 每轮将右端元素加入窗口；当窗口和达到目标时，记录当前长度，然后
     * 不断移除左端元素，尝试缩短仍满足条件的窗口。该方法利用 nums 中
     * 元素均为正整数这一前提：扩展窗口只会增加和，收缩窗口只会减少和，
     * 因而左右边界单向移动即可找到最短可行区间。
     *
     * is_none 用于区分“没有找到可行区间”和“最短区间长度等于数组长度”，
     * 避免仅通过初始 result 值判断是否找到答案。
     *
     * @param target 连续子数组的和需要达到的正整数目标值。
     * @param nums 由正整数组成的输入数组。
     * @return 满足和 >= target 的最短连续子数组长度；不存在时返回 0。
     *
     * @complexity 时间 O(n)，左右指针各最多遍历数组一次；额外空间 O(1)，
     *             其中 n 为 nums 的长度。
     */
    int minSubArrayLen(int target, std::vector<int> &nums)
    {
        // result 初始为数组长度；sum 保存当前窗口和，left 是窗口左边界。
        int sum = 0, result = static_cast<int>(nums.size()), left = 0;
        // 记录是不是没有符合的子数组。
        bool is_none = true;

        // 逐个扩展右边界，将新元素加入窗口。
        for (int right = 0; right < static_cast<int>(nums.size()); ++right)
        {
            sum += nums[right];

            // 窗口满足目标时，持续移除左侧元素以寻找更短的可行窗口。
            while (sum >= target)
            {
                // 更新当前已知的最短长度。
                if (result > (right - left + 1))
                    result = right - left + 1;
                // 当前窗口有效；即使长度等于初始值，也能正确标记已找到答案。
                is_none = false;
                // 移除左端元素并右移左边界，继续尝试缩短窗口。
                sum -= nums[left];
                left++;
            }
        }
        // 若从未出现满足条件的窗口，则按题意返回 0。
        return is_none ? 0 : result;
    }
};