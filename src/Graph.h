#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
using namespace std;

enum class OptimizeBy{
    DISTANCE,
    TIME,
    COST
};

class Edge
{
private:
    float distance;
    float time;
    float cost;

public:
    Edge(){
        distance = time = cost = 0;
    }
    Edge(vector<string> components)
    {
        distance = stof(components[2]);
        time = stof(components[3]);
        cost = stoi(components[4]);
    }
    float getWeight(OptimizeBy criteria){
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
    unordered_map<string, vector<pair<string, Edge>>> network;
    vector<string> networkElements;

public:
    void loadNetwork(string filename);
    void checkConnection();
    void checkConnectionDFS(string &current ,int &component , unordered_map<int , vector<string>> &components,unordered_map<string , int> &visited);
    bool checkReachabilityBFS(string &current, string &target, unordered_map<string, int> &visited);
    bool checkReachabilityDFS(string &current, string &target, unordered_map<string, int> &visited);
    vector<string> getOptimalPathDijkstra(string &src , string &dest , OptimizeBy criteria);
};

#endif