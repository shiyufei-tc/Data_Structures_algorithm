#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <queue>
#include <span>

struct EdgeNode
{
    int to;
    int weight;
    EdgeNode(int to, int weight) : to(to), weight(weight) {}
};

class GraphAdj_List
{
public:
    std::vector<std::vector<EdgeNode>> adj_list;
    std::vector<bool> is_visited;

    GraphAdj_List(const std::vector<std::vector<EdgeNode>> &adj_list) : adj_list(adj_list)
    {
        this->is_visited.assign(adj_list.size(), false);
    }
    GraphAdj_List(const std::vector<std::vector<int>> &matrix, const std::vector<int> &vertices)
    {
        size_t n = vertices.size();
        this->adj_list.resize(n);
        this->is_visited.assign(n, false);
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                if (matrix[i][j] != 0)
                {
                    this->adj_list[i].emplace_back(j, matrix[i][j]);
                }
            }
        }
    }

    void Add_Edge_relation_In_List(int u, int v, int weight = 1)
    {
        this->adj_list[u].emplace_back(v, weight);
        this->adj_list[v].emplace_back(u, weight);
    }

    void Add_Vertex()
    {
        this->adj_list.emplace_back();
    }

    void Remove_Vertex(int Vertex_index)
    {
        this->adj_list.erase(this->adj_list.begin() + Vertex_index);
        for (auto &EdgeNodes : this->adj_list)
        {
            EdgeNodes.erase(std::remove_if(EdgeNodes.begin(), EdgeNodes.end(), [Vertex_index](const EdgeNode &EdgeNode)
                                           { return Vertex_index == EdgeNode.to; }),
                            EdgeNodes.end());
        }
    }

    void Remove_Edge_relation_In_List(int u, int v)
    {
        this->adj_list[u].erase(std::remove_if(this->adj_list[u].begin(), this->adj_list[u].end(), [v](const EdgeNode &EdgeNode)
                                               { return EdgeNode.to == v; }),
                                this->adj_list[u].end());
        this->adj_list[v].erase(std::remove_if(this->adj_list[v].begin(), this->adj_list[v].end(), [u](const EdgeNode &EdgeNode)
                                               { return EdgeNode.to == u; }),
                                this->adj_list[v].end());
    }

    void Travel_Display(std::span<const EdgeNode> EdgeNodes)
    {
        for (const auto &EdgeNode : EdgeNodes)
        {
            std::cout << "Visited edge: " << EdgeNode.to << "Distance: " << EdgeNode.weight << std::endl;
        }
    }

    void DFS(int Vertex)
    {
        this->is_visited[Vertex] = true;
        this->Travel_Display(this->adj_list[Vertex]);
        for (auto &EdgeNode : this->adj_list[Vertex])
        {
            if (!is_visited[EdgeNode.to])
            {
                DFS(EdgeNode.to);
            }
        }
    }

    void BFS(int start)
    {
        this->is_visited.assign(is_visited.size(), false);
        std::queue<int> pending;
        pending.push(start);
        while (!pending.empty())
        {
            int Vertex = pending.front();
            pending.pop();
            this->is_visited[Vertex] = true;
            
            this->Travel_Display(this->adj_list[Vertex]);

            for (auto &EdgeNode : this->adj_list[Vertex])
            {
                if (!is_visited[EdgeNode.to])
                {
                    pending.push(EdgeNode.to);
                }
            }
        }
    }
};
