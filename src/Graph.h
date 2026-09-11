#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

enum class OptimizeBy
{
    DISTANCE,
    TIME,
    COST
};

struct PathResult
{
public:
    vector<string> path = {};
    int nodeExplored = 0;
};

struct BenchmarkResult
{
    int queries = 0;
    int runsPerQuery = 0;

    float dijkstraTime = 0.0f;
    float astarTime = 0.0f;

    float dijkstraNodes = 0.0f;
    float astarNodes = 0.0f;

    float speedup = 0.0f;
};

class Edge
{
private:
    float distance = 0.0f;
    float time = 0.0f;
    float cost = 0.0f;

public:
    Edge()
    {
        distance = time = cost = 0;
    }
    Edge(vector<string> components)
    {
        distance = stof(components[2]);
        time = stof(components[3]);
        cost = stoi(components[4]);
    }
    float getWeight(OptimizeBy criteria)
    {
        switch (criteria)
        {
        case OptimizeBy::DISTANCE:
            return distance;
        case OptimizeBy::TIME:
            return time;
        case OptimizeBy::COST:
            return cost;
        default:
            return distance;
        }
    }
};

class Graph
{
public: //
    unordered_map<string, vector<pair<string, Edge>>> network;
    vector<string> networkElements;
    unordered_map<string, pair<float, float>> coordinates;
    unordered_map<string, int> hash;

public:
    void loadNetwork(string networkName, string coordinateFile);
    BenchmarkResult benchmark();

    void checkConnectionDFS(string &current, int &component, unordered_map<int, vector<string>> &components, unordered_map<string, int> &visited);
    bool checkReachability(string &current, string &target, unordered_map<string, int> &visited);

    PathResult getOptimalPathDijkstra(string &src, string &dest, OptimizeBy criteria);
    PathResult getOptimalPathAstar(string &src, string &dest, OptimizeBy criteria);

    void dfsTraversal(string &current, unordered_map<string, int> &visited, vector<string> &traversal);
    
    void traversalDFS(string &current,vector<string> &traversal,unordered_map<string, int> &visited);
    vector<string> getDFSTraversal(string &start);
    vector<string> getBFSTraversal(string &start);
    int getConnectedComponents();
    int getTotalEdges();
};

#endif