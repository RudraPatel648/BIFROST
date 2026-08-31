#include <bits/stdc++.h>
#include "Graph.h"
using namespace std;

int main()
{
    //temp - testing functions
    Graph bifrost;
    bifrost.loadNetwork("network-test02");
    string source, destination ;
    cin>>source>>destination;
    bifrost.getShortestPathDijkstra(source , destination);
}