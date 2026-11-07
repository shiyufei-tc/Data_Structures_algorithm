#include <unordered_map>

/**
 * @brief 带有 next 和 random 指针的链表节点。
 *
 * next 指向链表中的下一个节点，random 可以指向链表中的任意节点，
 * 也可以为空。深拷贝时不能直接复用这些指针，否则新链表仍会引用原链表。
 */
class Node
{
public:
    int val;
    Node *next;
    Node *random;

    /**
     * @brief 创建一个仅包含值的新节点。
     *
     * 新节点初始化时尚未连接到其他节点，因此 next 和 random 都为空。
     *
     * @param _val 要复制到新节点中的值。
     */
    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution
{
public:
    /**
     * @brief 深拷贝带随机指针的链表。
     *
     * 深拷贝要求新链表中的每个节点都是独立创建的对象，且所有 next 和
     * random 关系与原链表完全对应，不能让新节点的指针指向原节点。
     *
     * 算法分两次遍历：
     * 1. 遍历原链表，为每个原节点创建一个只有值相同的拷贝节点，并用哈希表建立
     *    “原节点地址 -> 拷贝节点地址”的映射。此时只创建节点，不连接指针。
     * 2. 再次遍历原链表，在拷贝节点上进行操作，通过映射查找当前节点的 next 和 random 对应拷贝节点，
     *    将两个指针连接到拷贝链表。原指针为空时，副本指针也保持为空。
     *
     * 先完成全部节点创建，再连接指针，是因为 random 可能指向链表中的任意
     * 位置；只有所有原节点都已有对应副本后，才能稳定地完成任意方向的连接。
     *
     * @param head 原链表头节点，可以为 nullptr。
     * @return 新链表头节点；输入为空时返回 nullptr。
     *
     * @complexity 时间 O(n)，需要两次遍历；额外空间 O(n)，用于节点映射。
     */
    Node *copyRandomList(Node *head)
    {
        // 记录每个原节点对应的副本节点，供后续恢复 next/random 关系。
        std::unordered_map<Node *, Node *> hash_map;
        auto cur = head;
        // 第一遍只复制节点值，不连接指针，确保任意目标副本最终都能被找到。
        while (cur)
        {
            hash_map[cur] = new Node(cur->val);
            cur = cur->next;
        }

        cur = head;
        // 第二遍根据映射设置副本节点的两个指针。
        while (cur)
        {
            auto copy_node = hash_map[cur];
            // next 为空时保持为空，否则连接到 next 节点的副本。
            copy_node->next = cur->next ? hash_map[cur->next] : nullptr;
            // random 为空时保持为空，否则连接到 random 节点的副本。
            copy_node->random = cur->random ? hash_map[cur->random] : nullptr;
            cur = cur->next;
        }
        // 返回头节点的副本，而不是原链表头节点。
        return hash_map[head];
    }
};