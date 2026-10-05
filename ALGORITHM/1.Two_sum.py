"""
两数之和问题模块。

说明:
    该模块用于解决两数之和问题，
    通过哈希表实现高效查找并返回索引组合。
"""

from typing import List


class Solution:
    """
    Solution 类用于封装两数之和问题的求解逻辑。

    说明:
        该类通过哈希表记录已访问元素及其索引，
        从而在一次遍历中找到符合目标和的两个数。
    """

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        """
        两数之和问题的哈希表解法。

        参数:
            nums: 整数数组，存放待查找的元素
            target: 目标和，表示两个数相加后需要等于的值

        返回:
            如果找到两个数之和等于目标值，返回包含两个索引的列表；否则返回空列表。

        说明:
            通过字典记录已经遍历过的数值及其索引，
            对每个元素检查 target - 当前值 是否已出现，
            时间复杂度为 O(n)，空间复杂度为 O(n)。
        """
        # 创建一个空字典，用来存储 {数值: 索引}
        hash_map = {}

        # 遍历数组，i 是当前下标，v 是当前数值
        for i, v in enumerate(nums):
            # 计算需要的另一个数，检查它是否已经出现过
            if target - v in hash_map:
                # 如果已经出现过，返回当前下标和之前存储的下标
                return [i, hash_map[target - v]]

            # 否则，把当前数值和下标存入字典，供后续查找
            hash_map[v] = i

        # 如果未找到匹配组合，则返回空列表
        return []