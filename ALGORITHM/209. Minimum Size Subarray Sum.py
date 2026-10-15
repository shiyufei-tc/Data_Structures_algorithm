class Solution:
    def minSubArrayLen(self, target: int, nums: list[int]) -> int:
        """返回元素和至少为 ``target`` 的最短连续子数组长度。

        使用滑动窗口维护当前区间 ``[left, right]`` 及其元素和 ``Sum``。
        每次将右端元素加入窗口；当窗口和达到目标时，记录当前长度，并不断
        移除左端元素以尝试缩短窗口。由于题目中的 ``nums`` 元素均为正整数，
        扩大窗口只会增加和，收缩窗口只会减少和，因此双指针扫描不会漏掉
        更短的可行区间。

        ``result`` 保存目前找到的最短长度，初始值为数组长度；``is_none``
        标记是否找到过满足条件的窗口，以便在没有可行子数组时返回 0。

        Args:
            target: 子数组元素和必须达到的正整数目标值。
            nums: 由正整数组成的输入列表。

        Returns:
            满足元素和大于或等于 ``target`` 的最短连续子数组长度；
            若不存在这样的子数组，则返回 0。

        Complexity:
            时间复杂度 O(n)，因为左右指针都只向右移动且各自最多遍历数组
            一次；额外空间复杂度 O(1)，其中 n 为 ``nums`` 的长度。
        """
        # result 记录当前最短长度；Sum 保存当前窗口的元素和。
        result,left,Sum=len(nums),0,0
        # 用标记是不是没有符合的子数组。
        is_none=True
        # 逐个扩展窗口右边界，将新元素纳入当前窗口。
        for right in range(len(nums)):
            Sum+=nums[right]
            # 当前窗口已满足目标时，尽量收缩左边界以寻找更短的可行窗口。
            while Sum>=target:
                # 保存更短或同样长度的可行区间。
                if result>=right-left+1:
                    result=right-left+1
                    is_none=False
                # 移除左端元素后继续检查，直到窗口和低于目标。
                Sum-=nums[left]
                left+=1
        # 未出现过满足条件的窗口时按题意返回 0。
        return 0 if is_none else result