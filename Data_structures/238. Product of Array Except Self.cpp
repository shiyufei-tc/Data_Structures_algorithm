#include<vector>
class Solution
{
public:
    /**
     * @brief 计算每个位置以外所有元素的乘积。
     *
     * 算法意图是使用前缀积和后缀积，而不是通过总乘积除以当前元素：
     * 前缀阶段计算每个位置左侧所有元素的乘积，后缀阶段从右向左累计
     * 右侧乘积并与对应的前缀结果相乘。这样即使输入包含 0，也无需特殊
     * 的除零处理。
     *
     * @param nums 输入整数数组。
     * @return 预期返回一个数组，其中每个位置保存除该位置元素外其余元素
     *         的乘积。
     *
     * @complexity 预期时间 O(n)；输出占用 O(n) 空间，除输出外额外空间 O(1)。
     * 空数组会直接返回空结果。
     */
    std::vector<int> productExceptSelf(std::vector<int> &nums)
    {
        // preproduct 和 surproduct 分别用于累计左侧与右侧的元素乘积。
        int preproduct = 1, surproduct = 1;
        // 先将每个输出位置初始化为乘法单位元 1。
        std::vector<int> product(nums.size(), 1);

        // 空输入没有需要计算的位置，提前返回以避免无符号长度减法下溢。
        if (nums.empty())
        {
            return product;
        }

        // 前缀积阶段：累计左侧元素，并将累计结果放入其右侧的位置。
        // 最后一轮读取倒数第二个元素，为结果数组的最后一位写入所需前缀积。
        for (int index = 0; index < nums.size() - 1;++index)
        {
            preproduct *= nums[index];
            product[index + 1] = preproduct;
        }

        // 后缀积阶段从右向左累计，并将右侧元素乘积并入其左侧相邻位置。
        for (int index =nums.size()-1 ; index >=1;--index)
        {
            surproduct *= nums[index];
            product[index - 1] *= surproduct;
        }

        // 返回保存前缀积与后缀积乘积的结果数组。
        return product;
    }
};