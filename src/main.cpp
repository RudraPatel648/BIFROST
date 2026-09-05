#include <bits/stdc++.h>
#include "Graph.h"
using namespace std;

int main()
{
    //temp - testing features
    Graph bifrost;
    bifrost.loadNetwork("network-test02");
    string source, destination ;
    cin>>source>>destination;
    bifrost.getOptimalPathDijkstra(source , destination , OptimizeBy::DISTANCE);
    bifrost.getOptimalPathDijkstra(source , destination , OptimizeBy::TIME);
    bifrost.getOptimalPathDijkstra(source , destination , OptimizeBy::COST);
}