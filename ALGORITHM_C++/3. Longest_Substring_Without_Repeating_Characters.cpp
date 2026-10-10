#include <string>
#include <unordered_map>
#include <algorithm>
class Solution
{
public:
    /**
     * @brief 求字符串中不含重复字符的最长连续子串长度。
     *
     * 使用滑动窗口 [left + 1, right] 从左向右扫描字符串。hash_map 保存
     * 每个字符最近一次出现的位置。当当前字符此前出现过时，将 left 移至
     * 当前窗口中该字符上一次出现位置的右侧；使用 max 可避免 left 向左退，
     * 确保窗口始终只向右移动且不包含重复字符。
     *
     * 每轮计算当前窗口长度并更新最大值，然后记录当前字符的新位置并继续
     * 扫描。这里按 std::string 的 char 单位处理字符；对于 UTF-8 字符串，
     * char 表示字节而非完整 Unicode 字符。
     *
     * @param s 待搜索的字符串。
     * @return 最长无重复字符连续子串的长度；空字符串返回 0。
     *
     * @complexity 平均时间 O(n)，额外空间 O(min(n, 字符集大小))，
     *             其中 n 为字符串长度。
     */
    int lengthOfLongestSubstring(std::string s)
    {
        // 记录每个字符最近一次出现的位置，用于快速收缩窗口左边界。
        std::unordered_map<char, int> hash_map;
        // 窗口范围为 [left + 1, right]；left=-1 表示窗口从字符串开头开始。
        // count 保存已经发现的最长无重复子串长度。
        int left = -1, right = 0, count = 0;
        while (right < s.length())
        {
            // 若当前字符曾出现，窗口左边界至少要越过它上次出现的位置。
            // max 确保左边界不会因窗口外的旧记录而向左回退。
            if (hash_map.find(s[right]) != hash_map.end())
            {
                left = std::max(left, hash_map[s[right]]);
            }

            // 当前有效窗口是 [left + 1, right]，长度为 right - left。
            // 若比已知答案更长，或覆盖整个输入，就更新最长长度。
            if ((right - left > count) || (right - left == s.length()))
            {
                count = right - left;
            }

            // 当前字符处理完后，保存其最新位置，并将窗口右端向右扩展一位。
            hash_map[s[right]] = right;
            right++;
        }
        return count;
    }
};