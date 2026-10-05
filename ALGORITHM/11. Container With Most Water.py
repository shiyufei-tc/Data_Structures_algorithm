class Solution:
    def maxArea(self, height: list[int]) -> int:
        """返回数组中两条竖线围成的最大容器面积。

        这是典型的双指针问题：
        - left 指向左边界，right 指向右边界；
        - 容器面积 = min(height[left], height[right]) * (right - left)
        - 如果较短的那条边是 left 这一侧，则移动 left；
        - 否则移动 right。

        这样做的核心理由是：当较短边固定时，若移动较高的一侧，不可能得到更大面积，
        只有移动较短的一侧才有机会提升容积。

        Args:
            height: 每个位置表示竖条的高度。

        Returns:
            能装下的最大水量。

        Complexity:
            时间复杂度：O(n)
            空间复杂度：O(1)
        """
        # 当前最优面积初始化为 0。
        max_area = 0

        # 双指针分别从两端向中间靠拢。
        left, right = 0, len(height) - 1

        while left < right:
            # 计算当前左右指针围成的面积。
            # 容器高度受限于较短的那条边，宽度为两端距离。
            area = min(height[left], height[right]) * (right - left)

            # 更新最大面积。
            max_area = max(max_area, area)

            # 关键优化：如果左边较短，则向右移动 left，
            # 因为右边的边长更高，移动较长边不可能得到更大结果。
            # 反之则移动 right。
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1

        return max_area