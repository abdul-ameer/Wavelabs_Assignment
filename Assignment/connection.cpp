
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n); // adjacency list to store the graph
        vector<vector<int>> bridges; // to store the critical connections
        vector<int> disc(n, -1); // to store the discovery time of each node
        vector<int> low(n, -1); // to store the lowest discovery time of each node
        vector<bool> visited(n, false); // to mark the visited nodes
        int time = 0; // to keep track of the discovery time
        
        // build the graph from the given connections
        for (const auto& conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }
        
        // DFS traversal using Tarjan's algorithm to find the critical connections
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, i, disc, low, visited, time, graph, bridges);
            }
        }
        
        return bridges;
    }
    
private:
    void dfs(int u, int parent, vector<int>& disc, vector<int>& low, vector<bool>& visited, int& time, vector<vector<int>>& graph, vector<vector<int>>& bridges) {
        visited[u] = true;
        disc[u] = low[u] = time++;
        
        for (const auto& v : graph[u]) {
            if (v == parent) continue; // skip the parent node
            
            if (!visited[v]) {
                dfs(v, u, disc, low, visited, time, graph, bridges);
                low[u] = min(low[u], low[v]);
                
                if (disc[u] < low[v]) {
                    // this is a critical connection
                    bridges.push_back({u, v});
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
};

int main(){

    int  n = 4;
    vector<vector<int>> connection = {{0,1},{0,2}, {2,3}, {2,1}};
    Solution obj;
    vector<vector<int>> network = obj.criticalConnections(n, connection);
    for (auto i : network){
        cout << i[0] << " "<< i[1];
    }
}