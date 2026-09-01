#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
using namespace std;

class Edge
{
public: //temp public , need to change afterwards
    float distance;
    float time;
    int cost;

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
    vector<string> getShortestPathDijkstra(string &src , string &dest);
};

#endif