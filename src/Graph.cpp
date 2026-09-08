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

    // Loading Coordinates
    networkFile.open("../data/coordinates.txt", ios::in);
    if (networkFile.is_open())
    {
        string line;
        while (getline(networkFile, line))
        {
            vector<string> lineComponents(3, "");
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

            float lati = stof(lineComponents[1]);
            float longi = stof(lineComponents[2]);
            coordinates[lineComponents[0]] = {lati, longi};
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

vector<string> Graph::getOptimalPathDijkstra(string &source, string &destination, OptimizeBy criteria)
{
    if (source == destination)
    {
        cout << "Already At Destination" << endl;
        return {"Already At Destination"};
    }

    unordered_map<string, float> optimized;
    unordered_map<string, string> parent;
    priority_queue<pair<float, string>, vector<pair<float, string>>, greater<pair<float, string>>> minHeap;

    parent[source] = source;
    minHeap.push({0, source});
    optimized[source] = 0;

    while (!minHeap.empty())
    {
        string node = minHeap.top().second;
        float dis = minHeap.top().first;
        minHeap.pop();
        if (dis > optimized[node])
            continue;

        for (auto nei : network[node])
        {
            float weight = nei.second.getWeight(criteria);
            if (optimized.find(nei.first) == optimized.end() || dis + weight < optimized[nei.first])
            {
                optimized[nei.first] = dis + weight;
                parent[nei.first] = node;
                minHeap.push({optimized[nei.first], nei.first});
            }
        }
    }

    // temp - Need modification when working on UI and Formatting
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

    cout << "---Route Analysis---\n"
         << endl;
    float reqDistance = 0;
    float reqTime = 0;
    float reqCost = 0;

    for (int i = 0; i < path.size() - 1; i++)
    {
        string currentNode = path[i];
        string nextNode = path[i + 1];
        float currentDistance;
        float currentTime;
        float currentCost;
        for (auto nei : network[currentNode])
        {
            if (nei.first == nextNode)
            {
                currentDistance = nei.second.getWeight(OptimizeBy::DISTANCE);
                currentTime = nei.second.getWeight(OptimizeBy::TIME);
                currentCost = nei.second.getWeight(OptimizeBy::COST);
            }
        }

        cout << currentNode << " -> " << nextNode << endl;
        cout << "Distance : " << currentDistance << " Km" << endl;
        cout << "Time : " << currentTime << " H" << endl;
        cout << "Cost : " << currentCost << " Rs." << endl
             << endl;

        reqDistance += currentDistance;
        reqTime += currentTime;
        reqCost += currentCost;
    }

    cout << "Route : ";
    for (int i = 0; i < path.size() - 1; i++)
        cout << path[i] << " -> ";
    cout << path[path.size() - 1] << endl;

    cout << "Distance : " << reqDistance << " Km" << endl;
    cout << "Time : " << reqTime << " H" << endl;
    cout << "Cost : " << reqCost << " Rs." << endl
         << endl;

    return path;
}

vector<string> Graph::getOptimalPathAstar(string &source, string &destination, OptimizeBy criteria)
{
    if (source == destination)
    {
        cout << "Already At Destination" << endl;
        return {"Already At Destination"};
    }

    unordered_map<string, float> optimized;
    unordered_map<string, float> gScore;
    unordered_map<string, string> parent;
    priority_queue<pair<float, string>, vector<pair<float, string>>, greater<pair<float, string>>> minHeap;

    auto getDistanceHeuristic = [&](string current, string destination)
    {
        // Calculating Haversine Distance

        const float R = 6371.0; // Earth radius in km

        float lat1 = coordinates[current].first * M_PI / 180.0;
        float lon1 = coordinates[current].second * M_PI / 180.0;
        float lat2 = coordinates[destination].first * M_PI / 180.0;
        float lon2 = coordinates[destination].second * M_PI / 180.0;

        float dLat = lat2 - lat1;
        float dLon = lon2 - lon1;

        float a = sin(dLat / 2) * sin(dLat / 2) +
                   cos(lat1) * cos(lat2) *
                       sin(dLon / 2) * sin(dLon / 2);

        float c = 2 * atan2(sqrt(a), sqrt(1 - a));

        return R * c;
    };

    auto getTimeHeuristic = [&](string current, string destination)
    {
        float straightDistance = getDistanceHeuristic(current, destination);
        return straightDistance / 200.0f;
    };

    auto getCostHeuristic = [&](string current, string destination)
    {
        float straightDistance = getDistanceHeuristic(current, destination);
        return straightDistance * 2.0f;
    };

    auto getHeuristic = [&](string current , string destination){
        switch (criteria)
        {
        case OptimizeBy::DISTANCE:
            return getDistanceHeuristic(current , destination);
        case OptimizeBy::TIME:
            return getTimeHeuristic(current , destination);
        case OptimizeBy::COST:
            return getCostHeuristic(current , destination);
        default:
            return getDistanceHeuristic(current , destination);

        }
    };

    parent[source] = source;
    minHeap.push({getHeuristic(source, destination), source});
    optimized[source] = getHeuristic(source, destination);
    gScore[source] = 0;

    while (!minHeap.empty())
    {
        string node = minHeap.top().second;
        float fNode = minHeap.top().first;
        float dis = gScore[node];
        minHeap.pop();
        if (fNode > optimized[node])
            continue;

        for (auto nei : network[node])
        {
            string neiNode = nei.first;
            float weight = nei.second.getWeight(OptimizeBy::DISTANCE);
            float g = dis + weight;
            float h = getHeuristic(neiNode, destination);
            if (optimized.find(neiNode) == optimized.end() || g + h < optimized[neiNode])
            {
                optimized[neiNode] = g + h;
                gScore[neiNode] = g;
                parent[neiNode] = node;
                minHeap.push({optimized[neiNode], neiNode});
            }
        }
    }

    // temp - Need modification when working on UI and Formatting
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

    cout << "---Route Analysis---\n"
         << endl;
    float reqDistance = 0;
    float reqTime = 0;
    float reqCost = 0;

    for (int i = 0; i < path.size() - 1; i++)
    {
        string currentNode = path[i];
        string nextNode = path[i + 1];
        float currentDistance;
        float currentTime;
        float currentCost;
        for (auto nei : network[currentNode])
        {
            if (nei.first == nextNode)
            {
                currentDistance = nei.second.getWeight(OptimizeBy::DISTANCE);
                currentTime = nei.second.getWeight(OptimizeBy::TIME);
                currentCost = nei.second.getWeight(OptimizeBy::COST);
            }
        }

        cout << currentNode << " -> " << nextNode << endl;
        cout << "Distance : " << currentDistance << " Km" << endl;
        cout << "Time : " << currentTime << " H" << endl;
        cout << "Cost : " << currentCost << " Rs." << endl
             << endl;

        reqDistance += currentDistance;
        reqTime += currentTime;
        reqCost += currentCost;
    }

    cout << "Route : ";
    for (int i = 0; i < path.size() - 1; i++)
        cout << path[i] << " -> ";
    cout << path[path.size() - 1] << endl;

    cout << "Distance : " << reqDistance << " Km" << endl;
    cout << "Time : " << reqTime << " H" << endl;
    cout << "Cost : " << reqCost << " Rs." << endl
         << endl;

    return path;
}