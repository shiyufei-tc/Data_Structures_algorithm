#include<vector>
#include<unordered_map>
#include<iostream>
#include<algorithm>


class Graph
{
public:
    std::vector<std::vector<int>> adj_matrix;
    std::vector<int> vertices;
    std::unordered_map<int,std::vector<int>> adj_list;

    Graph(const std::vector<int> &vertices, const std::vector<std::vector<int>> &edge_relations= {}, const std::vector<std::vector<int>> &adj_matrix = {})
    {
        this->vertices=vertices;
        if (!adj_matrix.empty())
            this->adj_matrix=adj_matrix;
        else
        {
            size_t n=vertices.size();
            this->adj_matrix.assign(n, std::vector<int>(n, 0));
            for (const auto &edge_relation :edge_relations)
            {
                Add_Edge_relation_In_Matrix(edge_relation[0],edge_relation[1]);
            }
        }
        for (const auto &vertex:vertices)
            this->adj_list[vertex]={};
        for (const auto &edge_relation : edge_relations)
        {
            this->adj_list[edge_relation[0]].push_back(edge_relation[1]);
            this->adj_list[edge_relation[1]].push_back(edge_relation[0]);
        }
    }

    void Add_Edge_relation_In_Matrix(int u, int v)
    {
        this->adj_matrix[u][v] = 1;
        this->adj_matrix[v][u] = 1;
    }
    
    void Add_Edge_relation_In_List(int u, int v)
    {
        this->adj_list[u].push_back(v);
        this->adj_list[v].push_back(u);
    }

    void Add_New_Vertex(int vertex, const std::vector<std::vector<int>> &new_edge_relations= {})
    {
        this->vertices.push_back(vertex);
        size_t n=this->vertices.size();
        this->adj_matrix.resize(n, std::vector<int>(n, 0));
        for (auto &row : this->adj_matrix)
            row.resize(n, 0);
        for (const auto &edge_relation : new_edge_relations)
        {
            Add_Edge_relation_In_Matrix(edge_relation[0],edge_relation[1]);
        }
        this->adj_list[vertex]={};
        for (const auto &edge_relation : new_edge_relations)
        {
            this->adj_list[edge_relation[0]].push_back(edge_relation[1]);
            this->adj_list[edge_relation[1]].push_back(edge_relation[0]);
        }
    }

    void Remove_Vertex(int index)
    {
        this->vertices.erase(this->vertices.begin() + index);
        this->adj_matrix.erase(this->adj_matrix.begin() + index);
        for (auto &row : this->adj_matrix)
        row.erase(row.begin() + index);
        int vertex=this->vertices[index];
        this->adj_list.erase(vertex);
        for (auto &pair:this->adj_list)
        {
            auto &neighbors = pair.second;
            neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), vertex), neighbors.end());
        }
    }

    void Remove_Edge_relation_In_Matrix(int u, int v)
    {
        this->adj_matrix[u][v] = 0;
        this->adj_matrix[v][u] = 0;
    }

    void Remove_Edge_relation_In_List(int u,int v)
    {
        auto &neighbors_u =this->adj_list[u];
        neighbors_u.erase(std::remove(neighbors_u.begin(), neighbors_u.end(), v), neighbors_u.end());
        auto &neighbors_v =this->adj_list[v];
        neighbors_v.erase(std::remove(neighbors_v.begin(), neighbors_v.end(), u), neighbors_v.end());
    }
};
