#include <bits/stdc++.h>
using namespace std;

class Edge
{
    float distance;
    float time;
    int cost;
    public:
    Edge(vector<string> components){
        this->distance = stof(components[2]);
        this->time = stof(components[3]);
        this->cost = stoi(components[4]);
    }
};
unordered_map<string, vector<pair<string , Edge>>> network;

int main()
{
    network.clear();
    fstream networkFile;
    networkFile.open("../data/network-test.txt", ios::in);
    if (networkFile.is_open())
    {
        string line;
        while (getline(networkFile, line))
        {
            //Deviding String into Components [ Source , Destination , Distance , Time , Cost]
            vector<string> lineComponents(5, "");
            int i = 0;
            int componentCount = 0;
            while (i < line.size())
            {
                if (line[i] == ' ')
                {
                    while(i < line.size() && line[i] == ' ') i++;
                    componentCount++;
                    continue;
                }
                else
                lineComponents[componentCount].push_back(line[i]);
                i++;
            }
            //Creating Node for Current Line
            Edge edge(lineComponents);
            string &locA = lineComponents[0];
            string &locB = lineComponents[1];
            network[locA].push_back({locB , edge});
            network[locB].push_back({locA , edge});

        }
        networkFile.close();
    }
}