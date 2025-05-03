#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

int adj_mat[50][50] = {0};      // Adjacency matrix
int visited[50] = {0};          // Visited array for DFS
unordered_map<int, vector<int>> adj_list; // Adjacency list for BFS

// Depth First Search (Recursive)
void dfs(int s, int n, string arr[]) {
    visited[s] = 1;
    cout << arr[s] << " ";
    for (int i = 0; i < n; i++) {
        if (adj_mat[s][i] && !visited[i]) {
            dfs(i, n, arr);
        }
    }
}

// Breadth First Search (Queue)
void bfs(int s, int n, string arr[]) {
    vector<bool> visited(n, false);
    queue<int> bfsq;
    visited[s] = true;
    bfsq.push(s);

    while (!bfsq.empty()) {
        int v = bfsq.front();
        bfsq.pop();
        cout << arr[v] << " ";

        for (int neighbor : adj_list[v]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                bfsq.push(neighbor);
            }
        }
    }
}

int main() {
    int n, u;

    cout << "Enter number of locations (nodes): ";
    cin >> n;
    cin.ignore(); // Clear input buffer

    string locations[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter location #" << i << " (Landmark Name): ";
        getline(cin, locations[i]);
    }

    cout << "\nYour locations are:\n";
    for (int i = 0; i < n; i++) {
        cout << "Location #" << i << ": " << locations[i] << endl;
    }

    cout << "\nEnter distances between connected locations (Enter 0 if not connected):\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Enter distance between " << locations[i] << " and " << locations[j] << ": ";
            cin >> adj_mat[i][j];
            adj_mat[j][i] = adj_mat[i][j];

            if (adj_mat[i][j] > 0) {
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }
    }

    // Print adjacency matrix
    cout << "\nAdjacency Matrix:\n\t";
    for (int i = 0; i < n; i++)
        cout << locations[i] << "\t";
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << locations[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << adj_mat[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nEnter Starting Vertex (index 0 to " << n - 1 << "): ";
    cin >> u;

    if (u < 0 || u >= n) {
        cout << "Invalid starting index!" << endl;
        return 1;
    }

    cout << "\nDFS Traversal: ";
    fill_n(visited, 50, 0); // Reset visited
    dfs(u, n, locations);

    cout << "\nBFS Traversal: ";
    bfs(u, n, locations);

    return 0;
}
