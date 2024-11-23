#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 8; // Number of cities in the network

// Structure to represent a road (edge) between two cities
struct Edge {
    int src, dest, weight;  // source city, destination city, travel time in hours
};

// Alias for pair<int, int> representing destination city and travel time
typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;  // Adjacency list to store the graph
    
    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);  // Resize adjList to hold SIZE number of cities
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
        cout << "Transportation Network Topology:\n=================================\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << "City " << i << " connects to:\n";
            for (Pair v : adjList[i]) {
                cout << "  → City " << v.first << " (Travel time: " << v.second << " hours)\n";
            }
            cout << endl;
        }
    }

    // Depth-First Search (DFS)
    void DFS(int start) {
        vector<bool> visited(SIZE, false);  // To track visited cities
        cout << "Network Trace (DFS) from City 0:\nPurpose: Tracing possible delivery routes\n======================================\n";
        DFSUtil(start, visited);  // Helper function for DFS
        cout << endl;
    }

    // Helper function for DFS (recursive)
    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;  // Mark the current city as visited
        cout << "Inspecting City " << v << "\n";

        // Recur for all the cities adjacent to this city
        for (Pair neighbor : adjList[v]) {
            if (!visited[neighbor.first]) {  // If the city is not visited
                cout << "  → Potential delivery route to City " << neighbor.first << " (Travel time: " << neighbor.second << " hours)\n";
                DFSUtil(neighbor.first, visited);
            }
        }
    }

    // Breadth-First Search (BFS)
    void BFS(int start) {
        vector<bool> visited(SIZE, false);  // To track visited cities
        queue<int> q;
        visited[start] = true;
        q.push(start);  // Start with the initial city
        
        cout << "Layer-by-Layer Network Inspection (BFS) from City 0:\nPurpose: Analyzing delivery routes by distance from source\n=================================================\n";
        
        while (!q.empty()) {
            int v = q.front();
            cout << "Checking City " << v << "\n";
            q.pop();
            
            // Traverse all the adjacent cities
            for (Pair neighbor : adjList[v]) {
                if (!visited[neighbor.first]) {  // If the city is not visited
                    visited[neighbor.first] = true;
                    cout << "  → Next delivery route to City " << neighbor.first << " (Travel time: " << neighbor.second << " hours)\n";
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // List of roads connecting cities with travel times (edges with weights)
    vector<Edge> edges = {
        {0, 1, 12},
        {0, 3, 21},
        {1, 2, 3},
        {2, 3, 26},
        {2, 6, 2},
        {5, 6, 6},
        {4, 5, 9},
        {2, 5, 5},
        {1, 1, 7}, // Loop at City 1
        {7, 4, 12},
        {3, 3, 3}, // Loop at City 3
        {1, 2, 3},
        {7, 7, 7}, // Loop at City 7
        {5, 2, 15}
    };

    // Create the graph object representing the cities and roads
    Graph graph(edges);
    
    // Print the adjacency list representation of the graph (network)
    graph.printGraph();

    // Perform DFS starting from City 0 (index 0)
    graph.DFS(0);

    // Perform BFS starting from City 0 (index 0)
    graph.BFS(0);

    return 0;
}
