#include <iostream>
#include <unordered_map>
#include <string>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
    string destination;  
    int distance;        
    Node* next;          

    Node(string dest, int dist) : destination(dest), distance(dist), next(nullptr) {}
};

class Graph {
    unordered_map<string, Node*> adjList; 

public:
    void addEdge(const string& from, const string& to, int distance) {
        Node* newNode = new Node(to, distance);
        newNode->next = adjList[from];
        adjList[from] = newNode;

    
        newNode = new Node(from, distance);
        newNode->next = adjList[to];
        adjList[to] = newNode;
    }

    
    void printGraph() {
        for (auto& city : adjList) {
            cout << city.first << " is connected to: ";
            Node* temp = city.second;
            while (temp) {
                cout << "(" << temp->destination << ", " << temp->distance << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    const unordered_map<string, Node*>& getAdjList() const {
        return adjList;
    }
};

void dijkstra(const Graph& graph, const string& source, const string& destination) {
    const auto& adjList = graph.getAdjList();

    unordered_map<string, int> distances;
    unordered_map<string, string> previous;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> minHeap;

    for (const auto& node : adjList) {
        distances[node.first] = INT_MAX;
    }

    distances[source] = 0;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int currentDistance = minHeap.top().first;
        string currentNode = minHeap.top().second;
        minHeap.pop();

        if (currentDistance > distances[currentNode]) continue;

        Node* neighbor = adjList.at(currentNode);
        while (neighbor) {
            int newDistance = currentDistance + neighbor->distance;
            if (newDistance < distances[neighbor->destination]) {
                distances[neighbor->destination] = newDistance;
                previous[neighbor->destination] = currentNode;
                minHeap.push({newDistance, neighbor->destination});
            }
            neighbor = neighbor->next;
        }
    }

    if (distances[destination] == INT_MAX) {
        cout << "No path from " << source << " to " << destination << endl;
    } else {
        cout << "Shortest path distance from " << source << " to " << destination << " is " << distances[destination] << " Kms " << endl;

        vector<string> path;
        string current = destination;
        while (current != source) {
            path.push_back(current);
            current = previous[current];
        }
        path.push_back(source);

        reverse(path.begin(), path.end());
        cout << "Path: ";
        for (const string& city : path) {
            cout << city << " ";
        }
        cout << endl;
    }
}

int main() {
    Graph g;
    g.addEdge("Kharar", "Shimla", 131 );
    g.addEdge("Kharar", "Manali", 249 );
    g.addEdge("Shimla", "Manali", 227 );
    g.addEdge("Shimla", "Chandrataal", 338 );
    g.addEdge("Manali", "Chandrataal", 111 );
    g.addEdge("Chandrataal", "Ladakh", 477);
    g.addEdge("Shimla", "Ladakh", 660 );

    g.printGraph();

    string source, destination;
    cout << "\nEnter the starting location: ";
    cin >> source;
    cout << "Enter the destination location: ";
    cin >> destination;

    dijkstra(g, source, destination);

    return 0;
}
