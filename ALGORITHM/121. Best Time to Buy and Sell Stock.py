class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        """计算只允许完成一笔交易时能够获得的最大利润。

        算法思路：
            从左到右遍历价格。对每个卖出日，历史最低价就是此前最有利的
            买入价格；用当前价格减去该最低价，得到以当天卖出的最大利润。
            遍历过程中记录所有这些利润中的最大值。最低价只在计算当天利润
            之后更新，因此买入日始终早于卖出日。

        Args:
            prices: 按时间顺序排列的每日股票价格；题目保证至少包含一天。

        Returns:
            只进行一次买入和一次卖出（也可以不交易）时的最大利润。

        复杂度:
            时间 O(n)，其中 n 为价格数量；额外空间 O(1)。
        """
        # 先将第一天价格作为最低买入价；尚未完成交易时利润为 0。
        min_price = prices[0]
        max_profit = 0

        # 从第二天起，逐日尝试以当天价格卖出。
        for price in prices[1:]:
            # 以此前的最低价格买入、当天卖出，得到当天可实现的最大利润。
            profit = price - min_price
            # 保留截至当天为止的最优交易结果；若亏损或无利可图则仍为 0。
            max_profit = max(max_profit, profit)
            # 更新后续交易可用的最低买入价，确保买入发生在卖出之前。
            min_price = min(min_price, price)

        return max_profit