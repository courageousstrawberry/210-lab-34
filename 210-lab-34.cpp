#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 7; // Number of vertices in the graph

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair; // Alias for pair<int, int> data type 

class Graph {
public:
    vector<vector<Pair>> adjList;  // Adjacency list to store the graph
    
    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);  // Resize adjList to hold SIZE number of vertices
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));  // Directed graph edge
            adjList[dest].push_back(make_pair(src, weight));  // For undirected graph, add reverse edge
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i]) {
                cout << "(" << v.first << ", " << v.second << ") ";
            }
            cout << endl;
        }
    }

    // Depth-First Search (DFS)
    void DFS(int start) {
        vector<bool> visited(SIZE, false);  // To track visited nodes
        cout << "DFS traversal starting from vertex " << start << ": ";
        DFSUtil(start, visited);  // Helper function for DFS
        cout << endl;
    }

    // Helper function for DFS (recursive)
    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;  // Mark the current node as visited
        cout << v << " ";  // Print the node
        
        // Recur for all the vertices adjacent to this vertex
        for (Pair neighbor : adjList[v]) {
            if (!visited[neighbor.first]) {  // If the vertex is not visited
                DFSUtil(neighbor.first, visited);
            }
        }
    }

    // Breadth-First Search (BFS)
    void BFS(int start) {
        vector<bool> visited(SIZE, false);  // To track visited nodes
        queue<int> q;
        visited[start] = true;
        q.push(start);  // Start with the initial node
        
        cout << "BFS traversal starting from vertex " << start << ": ";
        
        while (!q.empty()) {
            int v = q.front();
            cout << v << " ";  // Print the node
            q.pop();
            
            // Traverse all the adjacent vertices
            for (Pair neighbor : adjList[v]) {
                if (!visited[neighbor.first]) {  // If the vertex is not visited
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        {0, 1, 12},
        {0, 3, 21},
        {2, 3, 26},
        {2, 6, 2},
        {5, 6, 6},
        {4, 5, 9},
        {2, 5, 5},
        {1, 1, 7},
        {7, 4, 12},
        {3, 3, 3},
        {1, 2, 3},
        {7, 7, 7},
        {5, 2, 15}
    };

    // Create graph object
    Graph graph(edges);
    
    // Print the adjacency list representation of the graph
    graph.printGraph();

    // Perform DFS starting from vertex 0
    graph.DFS(0);

    // Perform BFS starting from vertex 0
    graph.BFS(0);

    return 0;
}
