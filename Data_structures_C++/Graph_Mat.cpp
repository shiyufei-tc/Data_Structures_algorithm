#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <queue>

struct EdgeNode
{
    int to;
    int weight;
    EdgeNode(int to, int weight) : to(to), weight(weight) {}
};

class GraphAdj_Mat
{
public:
    std::vector<std::vector<int>> adj_matrix;
    std::vector<int> vertices;
    std::vector<bool> is_visited;

    GraphAdj_Mat(const std::vector<std::vector<int>> &adj_matrix, const std::vector<int> &vertices)
    {
        this->adj_matrix = adj_matrix;
        this->vertices = vertices;
        this->is_visited.assign(vertices.size(), false);
    }
    GraphAdj_Mat(const std::vector<std::vector<EdgeNode>> &adj_list, const std::vector<int> &vertices)
    {
        size_t n = vertices.size();
        this->adj_matrix.assign(n, std::vector<int>(n, 0));
        for (size_t i = 0; i < n; ++i)
        {
            for (const auto &Edgenode : adj_list[i])
            {
                this->adj_matrix[i][Edgenode.to] = Edgenode.weight;
            }
        }
        this->is_visited.assign(vertices.size(), false);
    }

    void Add_Edge_relation_In_Matrix(int u, int v, int weight = 1)
    {
        this->adj_matrix[u][v] = weight;
        this->adj_matrix[v][u] = weight;
    }

    void Add_Vertex(int vertex)
    {
        this->vertices.push_back(vertex);
        size_t new_size = this->vertices.size();
        for (auto &row : this->adj_matrix)
        {
            row.push_back(0);
        }
        this->adj_matrix.emplace_back(new_size, 0);
    }

    void Remove_Vertex(int vertex_index)
    {
        this->vertices.erase(std::remove(this->vertices.begin(), this->vertices.end(), vertex_index), this->vertices.end());
        this->adj_matrix.erase(this->adj_matrix.begin() + vertex_index);
        for (auto &row : this->adj_matrix)
            row.erase(row.begin() + vertex_index);
    }

    void Remove_Edge_relation_In_Matrix(int u, int v)
    {
        this->adj_matrix[u][v] = 0;
        this->adj_matrix[v][u] = 0;
    }

    void DFS(int Vertex)
    {
        this->is_visited[Vertex] = true;
        for (size_t i = 0; i < this->adj_matrix[Vertex].size();++i)
        {
            if(this->adj_matrix[Vertex][i]==0)
                continue;
            std::cout << "Visited edge: " << i << " Distance: " << this->adj_matrix[Vertex][i] << std::endl;
        }
        for (size_t i = 0; i < this->adj_matrix[Vertex].size();++i)
        {
            if(this->adj_matrix[Vertex][i]!=0 && !is_visited[i])
            {
                DFS(i);
            }
        }
    }

    void BFS(int start)
    {
        this->is_visited.assign(is_visited.size(), false);
        std::queue<int> pending;
        pending.push(start);
        while(!pending.empty())
        {
            int Vertex = pending.front();
            pending.pop();
            this->is_visited[Vertex] = true;
            for (size_t i = 0; i < this->adj_matrix[Vertex].size();++i)
            {
                if(this->adj_matrix[Vertex][i]!=0)
                    std::cout << "Visited edge: " << i << " Distance: " << this->adj_matrix[Vertex][i] << std::endl;
            }
            for (size_t i = 0; i < this->adj_matrix[Vertex].size();++i)
            {
                if(this->adj_matrix[Vertex][i]!=0 && !is_visited[i])
                {
                    pending.push(i);
                }
            }
        }
    }
};
