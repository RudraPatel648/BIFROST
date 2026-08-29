#include <bits/stdc++.h>
#include "Graph.h"
using namespace std;



int main()
{
    Graph bifrost;
    bifrost.loadNetwork("network-test");
    bifrost.checkConnection();
    cout<<endl;
    bifrost.loadNetwork("network-india");
    bifrost.checkConnection();
}