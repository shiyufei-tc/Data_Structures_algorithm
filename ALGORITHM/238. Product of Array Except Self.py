class Solution:
    def productExceptSelf(self, nums: list[int]) -> list[int]:
        """计算每个位置以外所有元素的乘积。

        算法思路是分别利用前缀积和后缀积，避免使用除法：

        1. 前缀阶段让 ``product[i]`` 保存 ``nums[i]`` 左侧所有元素的乘积。
        2. 后缀阶段从右向左累计右侧元素的乘积，并乘入对应的 ``product[i]``。
        3. 两阶段完成后，每个位置的结果即为该位置左侧积与右侧积的乘积。

        该方法可自然处理包含 0 的输入，因为不会进行除法。

        Args:
            nums: 输入整数列表。

        Returns:
            按输入位置排列的乘积列表；每个结果不包含对应位置的输入元素。

        Complexity:
            时间复杂度为 O(n)。输出列表占用 O(n) 空间；反向切片
            ``nums[::-1]`` 也会创建 O(n) 大小的临时列表。
        """
        # preproduct 用于累计当前元素左侧的乘积；surproduct 用于累计右侧乘积。
        preproduct,surproduct=1,1
        # 初始化输出槽位为 1，后续分别乘入对应位置的左侧积和右侧积。
        product=[1]*len(nums)

        # 前缀积阶段：累计遍历到的元素，并将累计积写入下一个结果位置。
        for index,num in enumerate(nums):
            # 最后一个元素没有右侧位置需要写入，因此在读取它之前结束前缀遍历。
            if index==len(nums)-1:
                break
            preproduct*=num
            # 将已累计的前缀积写入下一个位置，作为该位置左侧元素的乘积。
            product[index+1]=preproduct

        # 后缀积阶段从右向左遍历；index 是反转序列下标。
        for index,num in enumerate(nums[::-1]):
            surproduct*=num
            # 当前后缀积包含 nums[len(nums)-index-1]，因此写入它左侧的位置。
            # 最左侧元素没有需要更新的左邻位置，避免计算出负下标。
            if index < len(nums)-1:
                product[len(nums)-index-2]*=surproduct

        # 返回组合前缀积与后缀积后的结果列表。
        return product