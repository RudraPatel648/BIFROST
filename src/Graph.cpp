#include "Graph.h"

void Graph::loadNetwork(string fileName)
{
    network.clear();
    networkElements.clear();

    string URL = "../data/" + fileName + ".txt";
    fstream networkFile;
    unordered_map<string, int> visited;

    networkFile.open(URL, ios::in);
    if (networkFile.is_open())
    {
        string line;
        while (getline(networkFile, line))
        {
            vector<string> lineComponents(5, "");
            int i = 0;
            int componentCount = 0;
            while (i < line.size())
            {
                if (line[i] == ' ')
                {
                    while (i < line.size() && line[i] == ' ')
                        i++;
                    componentCount++;
                    continue;
                }
                else
                    lineComponents[componentCount].push_back(line[i]);
                i++;
            }

            Edge edge(lineComponents);
            string &locA = lineComponents[0];
            string &locB = lineComponents[1];
            network[locA].push_back({locB, edge});
            network[locB].push_back({locA, edge});

            if (!visited[locA])
            {
                networkElements.push_back(locA);
                visited[locA]++;
            }
            if (!visited[locB])
            {
                networkElements.push_back(locB);
                visited[locB]++;
            }
        }
        networkFile.close();
    }
}

void Graph::checkConnectionDFS(string &current, int &component, unordered_map<int, vector<string>> &components, unordered_map<string, int> &visited)
{
    components[component].push_back(current);
    for (auto nei : network[current])
    {
        if (!visited[nei.first])
        {
            visited[nei.first]++;
            checkConnectionDFS(nei.first, component, components, visited);
        }
    }
}

void Graph::checkConnection()
{
    int component = 0;
    unordered_map<int, vector<string>> components;
    unordered_map<string, int> visited;
    for (auto element : networkElements)
    {
        if (!visited[element])
        {
            visited[element]++;
            checkConnectionDFS(element, component, components, visited);
            component++;
        }
    }

    // temp - Checking whether function is working fine or not
    cout << "Total Nodes : " << networkElements.size() << endl;
    if (components.size() <= 1)
        cout << "Components Status : Connected" << endl;
    else
        cout << "Components Status : Disconnected" << endl;
    cout << "Connected Components : " << components.size() << endl;

    for (int i = 0; i < components.size(); i++)
    {
        cout << "Component " << i + 1 << " : ";
        for (auto component : components[i])
        {
            cout << component << " ";
        }
        cout << endl;
    }
}

bool Graph::checkReachabilityDFS(string &current, string &target, unordered_map<string, int> &visited)
{
    if (current == target)
        return true;
    for (auto nei : network[current])
    {
        if (!visited[nei.first])
        {
            visited[nei.first]++;
            if (checkReachabilityDFS(nei.first, target, visited))
                return true;
        }
    }
    return false;
}

bool Graph::checkReachabilityBFS(string &current, string &target, unordered_map<string, int> &visited)
{
    queue<string> q;
    q.push(current);
    while (!q.empty())
    {
        string current = q.front();
        q.pop();
        if (current == target)
            return true;

        for (auto nei : network[current])
        {
            if (!visited[nei.first])
            {
                visited[nei.first]++;
                q.push(nei.first);
            }
        }
    }
    return false;
}

vector<string> Graph::getShortestPathDijkstra(string &source, string &destination)
{
    if (source == destination)
    {
        cout << "Already At Destination" << endl;
        return {"Already At Destination"};
    }

    unordered_map<string, int> distance;
    unordered_map<string, string> parent;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> minHeap;

    parent[source] = source;
    minHeap.push({0, source});
    distance[source] = 0;

    while (!minHeap.empty())
    {
        string node = minHeap.top().second;
        int dis = minHeap.top().first;
        minHeap.pop();
        if (dis > distance[node])
            continue;

        for (auto nei : network[node])
        {
            if (distance.find(nei.first) == distance.end() || dis + nei.second.cost < distance[nei.first])
            {
                distance[nei.first] = dis + nei.second.cost;
                parent[nei.first] = node;
                minHeap.push({distance[nei.first], nei.first});
            }
        }
    }

    //temp - Need modification when working on UI and Formatting
    if (parent.find(destination) == parent.end())
    {
        cout << "Can't Reach Destination" << endl;
        return {"Can't Reach Destination"};
    }

    vector<string> path;
    string node = destination;
    while (parent[node] != node)
    {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());

    cout<<"---Route Analysis---\n"<<endl;
    float reqDistance = 0;
    float reqTime = 0;
    int reqCost = 0;

    for(int i = 0; i < path.size() - 1 ; i++){
        string currentNode = path[i];
        string nextNode = path[i+1];
        Edge currentEdge;
        for(auto nei : network[currentNode])
        {
            if(nei.first == nextNode)
                currentEdge = nei.second;
        }

        cout<<currentNode<<" -> "<<nextNode<<endl;
        cout<<"Distance : "<<currentEdge.distance<<" Km"<<endl;
        cout<<"Time : "<<currentEdge.time<<" H"<<endl;
        cout<<"Cost : "<<currentEdge.cost<<" Rs."<<endl<<endl;

        reqDistance += currentEdge.distance;
        reqTime += currentEdge.time;
        reqCost += currentEdge.cost;
    }

    cout<<"Route : ";
    for(int i = 0 ; i < path.size()-1 ; i++)
    cout<<path[i]<<" -> ";
    cout<<path[path.size() - 1]<<endl;

    cout<<"Distance : "<<reqDistance<<" Km"<<endl;
        cout<<"Time : "<<reqTime<<" H"<<endl;
        cout<<"Cost : "<<reqCost<<" Rs."<<endl<<endl;

    return path;
}