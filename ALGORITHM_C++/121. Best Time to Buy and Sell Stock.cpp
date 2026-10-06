#include <algorithm>
#include <vector>
class Solution
{
public:
    /**
     * @brief 计算只进行一次买入和一次卖出时可以获得的最大利润。
     *
     * 从左到右遍历每日价格。遍历到某一天时，先用此前记录的最低价格
     * 作为买入价，计算当天卖出的利润，并更新目前的最大利润；再将当天
     * 价格纳入最低价记录，供之后的日期买入使用。由于先计算利润再更新
     * 最低价，买入日一定早于卖出日。若所有交易都无利可图，则返回 0，
     * 表示不进行交易。
     *
     * @param prices 按时间顺序排列的每日股票价格，要求至少有一个价格。
     * @return 一次交易（或不交易）所能获得的最大利润。
     *
     * @complexity 时间 O(n)，其中 n 为价格数量；额外空间 O(1)。
     */
    int maxProfit(std::vector<int> &prices)
    {
        // 初始时将第一天价格作为最低买入价，最大利润设为 0（不交易）。
        int min_price = prices[0];
        int max_profit = 0;

        // 逐日尝试在当天卖出；包含第一天时，当天利润为 0，不影响结果。
        for (auto price : prices)
        {
            // 以此前最低价买入、当天卖出的利润。
            int profit = price - min_price;
            // 更新目前为止的最大利润，亏损或持平时仍保留 0。
            max_profit = std::max(max_profit, profit);
            // 更新后续日期可使用的最低买入价，保证买入早于卖出。
            min_price = std::min(min_price, price);
        }

        return max_profit;
    }
};