#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>  // For INT_MAX (infinity)
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

    // Function to find the shortest path using Dijkstra's algorithm
    void shortestPath(int start) {
        vector<int> dist(SIZE, INT_MAX);  // Distance from the start city
        vector<int> parent(SIZE, -1);     // Parent city for path reconstruction
        dist[start] = 0;  // Distance to the start city is 0

        // Min-heap priority queue to select the city with the smallest distance
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push(make_pair(0, start));  // Push start city into the queue with distance 0

        while (!pq.empty()) {
            int u = pq.top().second;  // Get the city with the smallest distance
            pq.pop();

            // Visit each neighboring city of u
            for (Pair neighbor : adjList[u]) {
                int v = neighbor.first;   // Neighbor city
                int weight = neighbor.second;  // Travel time to the neighbor city
                
                // If a shorter path to v is found
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;  // Update the shortest distance
                    parent[v] = u;  // Update the parent city
                    pq.push(make_pair(dist[v], v));  // Push the updated city into the queue
                }
            }
        }

        // Output the shortest path and delivery times from the start city
        cout << "Shortest path from City " << start << ":\n";
        for (int i = 0; i < SIZE; i++) {
            if (dist[i] == INT_MAX) {
                cout << start << " -> " << i << " : Unreachable\n";
            } else {
                cout << start << " -> " << i << " : " << dist[i] << " hours\n";
            }
        }
    }

    // Depth-First Search (DFS)
    void DFS(int start) {
        vector<bool> visited(SIZE, false);  // To track visited cities
        cout << "Network Trace (DFS) from City " << start << ":\nPurpose: Tracing possible delivery routes\n======================================\n";
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
        
        cout << "Layer-by-Layer Network Inspection (BFS) from City " << start << ":\nPurpose: Analyzing delivery routes by distance from source\n=================================================\n";
        
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

    // Function to compute the Minimum Spanning Tree (MST) using Prim's Algorithm
    void minimumSpanningTree() {
        vector<int> parent(SIZE, -1);   // To store the MST structure
        vector<int> key(SIZE, INT_MAX);  // To store the minimum weight edge
        vector<bool> inMST(SIZE, false); // To track which cities are in the MST

        key[0] = 0;  // Start from city 0
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push(make_pair(0, 0));  // Push city 0 into the priority queue with key 0

        while (!pq.empty()) {
            int u = pq.top().second;  // Get the city with the minimum key
            pq.pop();

            inMST[u] = true;  // Include city u in MST

            // Check all adjacent cities of u
            for (Pair neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // If v is not in MST and the edge u-v is smaller than the current key of v
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;  // Update the key of v
                    parent[v] = u;    // Update the parent of v
                    pq.push(make_pair(key[v], v));  // Push v with updated key into the priority queue
                }
            }
        }

        // Output the MST edges and their weights
        cout << "\nMinimum Spanning Tree (MST):\n===============================\n";
        int totalWeight = 0;
        for (int i = 1; i < SIZE; i++) {
            if (parent[i] != -1) {
                cout << "City " << parent[i] << " → City " << i << " (Weight: " << key[i] << " hours)\n";
                totalWeight += key[i];
            }
        }
        cout << "Total Weight of MST: " << totalWeight << " hours\n";
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

    // Find and print the shortest paths from City 0
    graph.shortestPath(0);

    // Find and print the Minimum Spanning Tree (MST)
    graph.minimumSpanningTree();

    return 0;
}
