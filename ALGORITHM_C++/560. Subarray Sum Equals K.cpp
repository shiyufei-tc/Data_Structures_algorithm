#include<vector>
#include<unordered_map>

class Solution
{
public:
    /**
     * @brief 统计和恰好等于 k 的连续子数组数量。
     *
     * 使用前缀和频次表。若当前位置的前缀和为 sum，那么每个此前出现过的
     * sum - k 都对应一个以当前位置结尾、元素和恰好为 k 的连续子数组。
     * 哈希表保存已扫描前缀和的出现次数，因此可在一次遍历中统计所有解；
     * 这种方法也适用于包含零或负数的数组。
     *
     * 表中初始的 {0, 1} 表示空前缀和为 0 出现一次，从而能够统计从数组
     * 起点开始的目标子数组。每轮先查询再记录当前前缀和，避免将空区间计入。
     *
     * @param nums 输入整数向量，可以包含正数、零或负数。
     * @param k 目标连续子数组和。
     * @return 和恰好等于 k 的连续子数组数量。
     *
     * @complexity 平均时间 O(n)，额外空间 O(n)，其中 n 为 nums 的长度。
     */
    int subarraySum(std::vector<int> &nums, int k)
    {
        // sum 是扫描到当前位置时的前缀和；count 累计已经统计的子数组数量。
        int count = 0, sum = 0;
        // 频次表只保存当前位置之前的前缀和；空前缀和 0 对应从数组下标 0 开始的区间。
        std::unordered_map<int, int> hash_map{{0, 1}};
        for (auto num : nums)
        {
            // 将当前元素纳入前缀和，相当于固定当前下标作为所有候选子数组的右端点。
            sum += num;
            
            // 固定右端点后，每个更早的前缀位置都对应一个可能的左端点；
            // 该区间和 = 当前前缀和 - 左端点之前的前缀和。
            // 因而区间和为 k 的充要条件是：更早的前缀和等于 sum-k。
            // 表中 sum-k 的频次就是满足条件的左端点数，也就是以当前位置结尾的子数组数；
            // 将这些相同前缀和的左端点合并计数，避免为每个右端点重新枚举所有左端点。
            count += hash_map.contains(sum - k) ? hash_map.at(sum - k) : 0;

            // 查询后才登记当前前缀，维持“表内均为更早前缀”的不变量，
            // 从而只统计非空子数组（尤其避免 k=0 时把当前位置与自身配对）。
            auto find_it = hash_map.find(sum);
            hash_map[sum] = (find_it == hash_map.end() ? 0 : find_it->second) + 1;
        }
        return count;
    }
};