#include <bits/stdc++.h>
using namespace std;

class Edge
{
    float distance;
    float time;
    int cost;

public:
    Edge(vector<string> components)
    {
        this->distance = stof(components[2]);
        this->time = stof(components[3]);
        this->cost = stoi(components[4]);
    }
};

unordered_map<string, vector<pair<string, Edge>>> network;
vector<string> networkElements;
void loadNetwork(string fileName)
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
            // Deviding String into Components [ Source , Destination , Distance , Time , Cost]
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
            // Creating Node for Current Line

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

bool checkReachabilityDFS(string &current, string &target, unordered_map<string, int> &visited)
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

bool checkReachabilityBFS(string &current, string &target, unordered_map<string, int> &visited)
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

void checkConnectionDFS(string &current ,int &component , unordered_map<int , vector<string>> &components,unordered_map<string , int> &visited)
{
    components[component].push_back(current);
    for(auto nei : network[current])
    {
        if(!visited[nei.first])
        {
            visited[nei.first]++;
            checkConnectionDFS(nei.first , component , components , visited);
        }
    }
}

void checkConnection()
{
    int component = 0;
    unordered_map<int,vector<string>> components;
    unordered_map<string , int> visited;
    for(auto element : networkElements)
    {
        if(!visited[element])
        {
            visited[element]++;
            checkConnectionDFS(element , component , components , visited);
            component++;
        }
    }

    //temp
    cout<<"Total Nodes : "<<networkElements.size()<<endl;
    if(components.size()<=1)
    cout<<"Components Status : Connected"<<endl;
    else 
    cout<<"Components Status : Disconnected"<<endl;
    cout<<"Connected Components : "<<components.size()<<endl;

    for(int i = 0 ; i < components.size() ; i++)
    {
        cout<<"Component "<<i + 1<<" : ";
        for(auto component : components[i])
        {
            cout<<component<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    loadNetwork("network-test");
    checkConnection();
    cout<<endl;
    loadNetwork("network-india");
    checkConnection();
}