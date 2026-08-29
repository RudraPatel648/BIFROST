#include <bits/stdc++.h>
using namespace std;

class Edge
{
    string destination;
    float distance;
    float time;
    int cost;
public:
    Edge(vector<string> components){
        this->destination = components[1];
        this->distance = stof(components[2]);
        this->time = stof(components[3]);
        this->cost = stoi(components[4]);
    }
};

int main()
{
    unordered_map<string, vector<Edge>> network;

    fstream networkFile;
    networkFile.open("network.txt", ios::in);
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
            string &source = lineComponents[0];
            network[source].push_back(edge);

        }
        networkFile.close();
    }


}