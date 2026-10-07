class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        """返回整数数组中连续非空子数组的最大和。

        使用 Kadane 算法从左向右扫描数组。``the_sum`` 表示当前扫描位置
        结尾、且值得继续扩展的连续子数组之和；每读入一个数就扩展该和，
        并用它更新全局最大值。若当前和小于 0，则丢弃这段前缀并从后续元素
        重新开始，因为负前缀只会降低任何后续子数组的和。

        最大值初始化为数组中的最大元素，因此即使所有元素都为负数，也会
        返回最大的那个单元素子数组，而不是错误地返回 0。

        Args:
            nums: 至少包含一个整数的数组。

        Returns:
            连续非空子数组的最大元素和。

        Complexity:
            时间复杂度 O(n)，额外空间复杂度 O(1)，其中 n 为数组长度。
        """
        # 用数组最大元素初始化答案，以正确处理全负数数组。
        the_max=max(nums)
        # 当前候选子数组的累计和；负数前缀会在扫描过程中被丢弃。
        the_sum=0
        # 按顺序将每个元素加入当前候选子数组。
        for right in range(len(nums)):
            the_sum+=nums[right]
            # 当前候选和可能是截至目前的全局最大子数组和。
            the_max=max(the_max,the_sum)
            # 负的累计和只会拖累后续子数组，因此从下一个元素重新累计。
            if the_sum<0:
                the_sum=0
        return the_max
