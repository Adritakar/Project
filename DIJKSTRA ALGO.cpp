#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm> // Include this header for the reverse function

using namespace std;

// Structure to represent a node in the priority queue
struct Node {
    int vertex;
    int distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// Function to add an edge to the graph
void addEdge(vector<pair<int, int>> adj[], int u, int v, int weight) {
    adj[u].emplace_back(v, weight);
    adj[v].emplace_back(u, weight);
}

// Dijkstra's algorithm to find the shortest path from source to destination
vector<int> dijkstra(vector<pair<int, int>> adj[], int V, int src, int dest) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);

    pq.push({src, 0});
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({v, dist[v]});
                parent[v] = u;
            }
        }
    }

    // To store the shortest path
    vector<int> path;
    if (dist[dest] != INT_MAX) {
        for (int v = dest; v != -1; v = parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
    }
    return path;
}

int main() {
    int V = 6;  // Number of vertices
    vector<pair<int, int>> adj[V];

    // Adding edges to the graph (bus routes and metro routes)
    addEdge(adj, 0, 1, 10); // Bus route
    addEdge(adj, 0, 2, 15); // metro route 
    addEdge(adj, 1, 3, 12); // Bus route
    addEdge(adj, 2, 4, 10); // metro route 
    addEdge(adj, 3, 4, 1);  // Bus route
    addEdge(adj, 3, 5, 1);  // metro route 
    addEdge(adj, 4, 5, 5);  // Bus route

    int src = 0; // Starting point
    int dest = 5; // Destination

    vector<int> path = dijkstra(adj, V, src, dest);

    if (path.empty()) {
        cout << "No path found from " << src << " to " << dest << endl;
    } else {
        cout << "Shortest path from " << src << " to " << dest << ": ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}