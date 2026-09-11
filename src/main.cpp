#include <bits/stdc++.h>
#include <conio.h>
#include "Graph.h"
using namespace std;

const string RESET = "\033[0m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RED = "\033[31m";
const string BOLD = "\033[1m";
const string GREY = "\033[90m";

void clearScreen()
{
    cout << "\033[2J\033[H";
}

void pressAnyKeyToContinue()
{
    cout<<"\n\n";
    cout << "    " << GREY << "[ Press any key to continue ]" << RESET;
    _getch();
    cout<<endl;
}

void loadNetworkMenu(Graph &bifrost)
{
    int choice;

    while (true)
    {
        clearScreen();

        cout << CYAN << BOLD;
        cout << "╔══════════════════════════════════════════════════╗\n";
        cout << "║                                                  ║\n";
        cout << "║                   B I F R O S T                  ║\n";
        cout << "║                                                  ║\n";
        cout << "║                   LOAD NETWORK                   ║\n";
        cout << "║                                                  ║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";
        cout << RESET;

        cout << "\n";
        cout << "  Select a network:\n\n";

        cout << YELLOW << "  [1]  Network 1 "<<CYAN<<"  Network Of 100 Connected Nodes \n"<<RESET;
        cout << YELLOW << "  [2]  Network 2 "<<CYAN<<"  Network Of 1000 Connected Nodes \n"<<RESET;
        cout << YELLOW << "  [3]  Network 3 "<<CYAN<<"  Network Of 100000 Connected Nodes\n"<<RESET;
        cout << YELLOW << "  [4]  Network 4 "<<CYAN<<"  Network Of Connected Components   \n"<<RESET;
        cout << RED << "  [0]  Exit\n"
             << RESET;
        cout << "\n";
        cout << "    " << CYAN << "➜ Select option: " << RESET;

        cin >> choice;

        if (choice >= 1 && choice <= 4)
        {
            string networkName = "network_0" + to_string(choice);
            string coordinateName = "coordinates_0" + to_string(choice);
            bifrost.loadNetwork(networkName, coordinateName);

            cout << GREEN << "\n  ✓ Network " << choice
                 << " loaded successfully!" << RESET << "\n";
            pressAnyKeyToContinue();
            break;
        }

        if (choice == 0)
        {
            exit(0);
        }

        cout << RED << "\n ✗ Invalid option!"
             << RESET << "\n";
        pressAnyKeyToContinue();
    }
}

void routeAnalysis(Graph &bifrost, vector<string> &path)
{
    clearScreen();

    cout << CYAN << BOLD;
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║                                                  ║\n";
    cout << "║                  B I F R O S T                   ║\n";
    cout << "║                                                  ║\n";
    cout << "║                 ROUTE ANALYSIS                   ║\n";
    cout << "║                                                  ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    cout << RESET;

    cout << "\n";
    cout << CYAN << BOLD << "  Route\n"
         << RESET;
    cout << "  ────────────────────────────────────────────────\n";

    cout << "  ";

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i != path.size() - 1)
            cout << " → ";
    }

    cout << "\n";

    cout << "\n";
    cout << CYAN << BOLD << "  Route Details\n"
         << RESET;
    cout << "  ────────────────────────────────────────────────\n\n";

    float totalDistance = 0;
    float totalTime = 0;
    float totalCost = 0;

    for (int i = 0; i < path.size() - 1; i++)
    {
        string currentNode = path[i];
        string nextNode = path[i + 1];

        float distance = 0;
        float time = 0;
        float cost = 0;

        for (auto nei : bifrost.network[currentNode])
        {
            if (nei.first == nextNode)
            {
                distance = nei.second.getWeight(OptimizeBy::DISTANCE);
                time = nei.second.getWeight(OptimizeBy::TIME);
                cost = nei.second.getWeight(OptimizeBy::COST);

                break;
            }
        }

        totalDistance += distance;
        totalTime += time;
        totalCost += cost;

        cout << "  " << currentNode
             << " → " << nextNode << "\n";

        cout << "    Distance : " << distance << " Km\n";
        cout << "    Time     : " << time << " H\n";
        cout << "    Cost     : " << cost << " Rs.\n";

        cout << "\n";
    }


    cout << "  ────────────────────────────────────────────────\n";

    cout << GREEN << BOLD << "  TOTAL\n"
         << RESET;

    cout << "\n";

    cout << "    Distance : " << totalDistance << " Km\n";
    cout << "    Time     : " << totalTime << " H\n";
    cout << "    Cost     : " << totalCost << " Rs.\n";

    pressAnyKeyToContinue();
}

void routeFinder(Graph &bifrost)
{
    clearScreen();

    string source;
    string destination;

    int optimizeChoice;
    int algorithmChoice;

    OptimizeBy criteria;
    PathResult result;

    cout << CYAN << BOLD;
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║                                                  ║\n";
    cout << "║                  B I F R O S T                   ║\n";
    cout << "║                                                  ║\n";
    cout << "║                  ROUTE FINDER                    ║\n";
    cout << "║                                                  ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    cout << RESET;

    cout << "\n";

    cout << CYAN << BOLD << "  Source\n"
         << RESET;
    cout << "  ────────────────────────────────────────────────\n";
    cout << "  ➜ Enter source: ";
    cin >> source;

    cout << "\n";
    cout << CYAN << BOLD << "  Destination\n"
         << RESET;
    cout << "  ────────────────────────────────────────────────\n";
    cout << "  ➜ Enter destination: ";
    cin >> destination;

    cout << "\n";
    cout << CYAN << BOLD << "  Optimize By\n"
         << RESET;
    cout << "  ────────────────────────────────────────────────\n";
    cout << "  [1] Distance\n";
    cout << "  [2] Time\n";
    cout << "  [3] Cost\n";
    cout << "\n";
    cout << "    " << CYAN << "➜ Select option: " << RESET;
    cin >> optimizeChoice;

    switch (optimizeChoice)
    {
    case 1:
        criteria = OptimizeBy::DISTANCE;
        break;

    case 2:
        criteria = OptimizeBy::TIME;
        break;

    case 3:
        criteria = OptimizeBy::COST;
        break;

    default:
        cout << RED << "\n  ✗ Invalid optimization option.\n"
             << RESET;
        pressAnyKeyToContinue();
        return;
    }

    cout << "\n";
    cout << CYAN << BOLD << "  Algorithm\n"
         << RESET;
    cout << "  ────────────────────────────────────────────────\n";
    cout << "  [1] Dijkstra\n";
    cout << "  [2] A*\n";
    cout << "\n";
    cout << "    " << CYAN << "➜ Select option: " << RESET;
    cin >> algorithmChoice;

    if (algorithmChoice == 1)
    {
        result = bifrost.getOptimalPathDijkstra(
            source,
            destination,
            criteria);
    }
    else if (algorithmChoice == 2)
    {
        result = bifrost.getOptimalPathAstar(
            source,
            destination,
            criteria);
    }
    else
    {
        cout << RED << "\n  ✗ Invalid algorithm option.\n"
             << RESET;
        pressAnyKeyToContinue();
        return;
    }

    clearScreen();

    cout << CYAN << BOLD;
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║                  ROUTE RESULT                    ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    cout << RESET;

    cout << "\n";

    if (result.path.empty())
    {
        cout << RED;
        cout << "  ✗ No path exists between "
             << source << " and " << destination << ".\n";
        cout << RESET;
        pressAnyKeyToContinue();
        return;
    }

    cout << GREEN;
    cout << "  ✓ Optimal route found!\n";
    cout << RESET;

    cout << "\n";
    cout << "  Route\n";
    cout << "  ────────────────────────────────────────────────\n";

    cout << "  ";

    for (int i = 0; i < result.path.size(); i++)
    {
        cout << result.path[i];

        if (i != result.path.size() - 1)
            cout << " → ";
    }

    cout << "\n\n";

    cout << YELLOW ;
    cout << "  [1] Analyze Route\n";
    cout << RED << "  [0] Back\n";
    cout << RESET;

    cout << "\n";
    cout << "    " << CYAN << "➜ Select option: " << RESET;

    int nextChoice;
    cin >> nextChoice;

    if (nextChoice == 1)
    {
        routeAnalysis(bifrost, result.path);
    }
    else
    {
        return;
    }
}

void bfsTraversal(Graph &bifrost)
{
    while (true)
    {
        clearScreen();

        cout << CYAN<<BOLD;
        cout << "╔══════════════════════════════════════════════════╗" << endl;
        cout << "║                                                  ║" << endl;
        cout << "║                  B I F R O S T                   ║" << endl;
        cout << "║                                                  ║" << endl;
        cout << "║                  BFS TRAVERSAL                   ║" << endl;
        cout << "║                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════╝"
             << RESET << endl;

        cout << endl;

        cout << CYAN << "  Starting Node" << RESET << endl;
        cout << "  ────────────────────────────────────────────────" << endl;
        cout << endl;

        string start;

        cout << "    " << CYAN << "➜ Select option: " << RESET;
        cin >> start;

        if (bifrost.network.find(start) == bifrost.network.end())
        {
            cout << endl;
            cout << RED << "    ✗ Node not found!" << RESET << endl;
            
            pressAnyKeyToContinue();
            continue;
        }

        vector<string> traversal = bifrost.getBFSTraversal(start);

        cout << endl;

        cout << CYAN << "  BFS Traversal" << RESET << endl;
        cout << "  ────────────────────────────────────────────────" << endl;
        cout << endl;

        for (int i = 0; i < traversal.size(); i++)
        {
            cout << traversal[i];

            if (i != traversal.size() - 1)
                cout << " → ";
        }

        cout << endl;
        cout << endl;

        cout << "    Nodes Visited : "
             << GREEN << traversal.size() << RESET << endl;

        cout << endl;
        cout << YELLOW << "    [1] Run Again" << RESET << endl;
        cout << RED << "    [0] Back" << RESET << endl;

        cout << endl;
        cout << "    " << CYAN << "➜ Select option: " << RESET;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            continue;
        }
        else if (choice == 0)
        {
            return;
        }
    }
}

void dfsTraversal(Graph &bifrost)
{
    while (true)
    {
        clearScreen();

        cout << CYAN<<BOLD;
        cout << "╔══════════════════════════════════════════════════╗" << endl;
        cout << "║                                                  ║" << endl;
        cout << "║                  B I F R O S T                   ║" << endl;
        cout << "║                                                  ║" << endl;
        cout << "║                  DFS TRAVERSAL                   ║" << endl;
        cout << "║                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════╝"
             << RESET << endl;

        cout << endl;

        cout << CYAN << "  Starting Node" << RESET << endl;
        cout << "  ────────────────────────────────────────────────" << endl;
        cout << endl;

        string start;

        cout << "    ➜ Enter starting node: "
             << RESET;
        cin >> start;

        if (bifrost.network.find(start) == bifrost.network.end())
        {
            cout << endl;
            cout << RED << "    ✗ Node not found!" << RESET << endl;
            cout << endl;
 
            pressAnyKeyToContinue();
            continue;
        }

        vector<string> traversal = bifrost.getDFSTraversal(start);

        cout << endl;

        cout << CYAN << "  DFS Traversal" << RESET << endl;
        cout << "  ────────────────────────────────────────────────" << endl;
        cout << endl;

        for (int i = 0; i < traversal.size(); i++)
        {
            cout << traversal[i];

            if (i != traversal.size() - 1)
                cout << " → ";
        }

        cout << endl;
        cout << endl;

        cout << "    Nodes Visited : "
             << GREEN << traversal.size() << RESET << endl;

        cout << endl;

        cout << YELLOW << "    [1] Run Again" << RESET << endl;
        cout << RED << "    [0] Back" << RESET << endl;

        cout << endl;
        cout << "    " << CYAN << "➜ Select option: " << RESET;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            continue;
        }
        else if (choice == 0)
        {
            return;
        }
    }
}

void networkAnalysis(Graph &bifrost)
{
    while (true)
    {
        clearScreen();

        cout << CYAN<<BOLD;
        cout << "╔══════════════════════════════════════════════════╗" << endl;
        cout << "║                                                  ║" << endl;
        cout << "║                  B I F R O S T                   ║" << endl;
        cout << "║                                                  ║" << endl;
        cout << "║                NETWORK ANALYSIS                  ║" << endl;
        cout << "║                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════╝" << RESET << endl;

        cout << endl;

        cout << CYAN << "  Network Overview" << RESET << endl;
        cout << "  ────────────────────────────────────────────────" << endl;
        cout << endl;

        cout << "    Total Nodes : " << bifrost.networkElements.size() << endl;
        cout << "    Total Edges : " << bifrost.getTotalEdges() << endl;

        cout << endl;
        cout << CYAN << "  Connectivity" << RESET << endl;
        cout << "  ────────────────────────────────────────────────" << endl;
        cout << endl;

        int components = bifrost.getConnectedComponents();

        cout << "    Connected Components : " << components << endl;

        if (components == 1)
        {
            cout << "    Network Status       : "
                 << GREEN << "✓ Connected" << RESET << endl;
        }
        else
        {
            cout << "    Network Status       : "
                 << RED << "✗ Disconnected" << RESET << endl;
        }

        cout << endl;
        cout << CYAN << "  Traversal" << RESET << endl;
        cout << "  ────────────────────────────────────────────────" << endl;
        cout << endl;

        cout << YELLOW << "    [1] Run BFS" << RESET << endl;
        cout << YELLOW << "    [2] Run DFS" << RESET << endl;
        cout << RED << "    [0] Back" << RESET << endl;

        cout << endl;
        cout << "    " << CYAN << "➜ Select option: " << RESET;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            bfsTraversal(bifrost);
        }
        else if (choice == 2)
        {
            dfsTraversal(bifrost);
        }
        else if (choice == 0)
        {
            return;
        }
    }
}

void benchmarkMenu(Graph &bifrost)
{
    while (true)
    {
        clearScreen();

        cout << CYAN<<BOLD;
        cout << "╔══════════════════════════════════════════════════╗" << endl;
        cout << "║                                                  ║" << endl;
        cout << "║                  B I F R O S T                   ║" << endl;
        cout << "║                                                  ║" << endl;
        cout << "║             ALGORITHM BENCHMARK                  ║" << endl;
        cout << "║                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════╝"
             << RESET << endl;

        cout << endl;

        cout << CYAN << "  Benchmark Configuration" << RESET << endl;
        cout << "  ────────────────────────────────────────────────" << endl;
        cout << endl;

        cout << "    Queries         : 20" << endl;
        cout << "    Runs per Query  : 5" << endl;
        cout << "    Optimize By     : Distance" << endl;

        cout << endl;

        cout << YELLOW << "    [1] Run Benchmark" << RESET << endl;
        cout << RED << "    [0] Back" << RESET << endl;

        cout << endl;
        cout << "    " << CYAN << "➜ Select option: " << RESET;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            clearScreen();

            cout << CYAN<<BOLD;
            cout << "╔══════════════════════════════════════════════════╗" << endl;
            cout << "║                                                  ║" << endl;
            cout << "║                  B I F R O S T                   ║" << endl;
            cout << "║                                                  ║" << endl;
            cout << "║             ALGORITHM BENCHMARK                  ║" << endl;
            cout << "║                                                  ║" << endl;
            cout << "╚══════════════════════════════════════════════════╝"
                 << RESET << endl;

            cout << endl;

            cout << YELLOW << "  Running benchmark..." << RESET << endl;
            cout << endl;

            BenchmarkResult result = bifrost.benchmark();

            cout << GREEN << "  ✓ Benchmark completed successfully!"
                 << RESET << endl;

            cout << endl;

            cout << CYAN << "  Benchmark Results" << RESET << endl;
            cout << "  ────────────────────────────────────────────────"
                 << endl;
            cout << endl;

            cout << "    Dijkstra" << endl;
            cout << "      Average Time   : "
                 << result.dijkstraTime << " μs" << endl;

            cout << "      Nodes Explored : "
                 << result.dijkstraNodes << endl;

            cout << endl;

            cout << "    A*" << endl;
            cout << "      Average Time   : "
                 << result.astarTime << " μs" << endl;

            cout << "      Nodes Explored : "
                 << result.astarNodes << endl;

            cout << endl;

            cout << CYAN << "  Performance" << RESET << endl;
            cout << "  ────────────────────────────────────────────────"
                 << endl;
            cout << endl;

            cout << "    A* Speedup : "
                 << GREEN << result.speedup << "x"
                 << RESET << endl;

            cout << endl;

            cout << "    Queries         : "
                 << result.queries << endl;

            cout << "    Runs per Query  : "
                 << result.runsPerQuery << endl;

            pressAnyKeyToContinue();

        }
        else if (choice == 0)
        {
            return;
        }
    }
}

void aboutPage()
{
    clearScreen();

    cout << CYAN;
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║                                                  ║" << endl;
    cout << "║                  B I F R O S T                   ║" << endl;
    cout << "║                                                  ║" << endl;
    cout << "║                     ABOUT                        ║" << endl;
    cout << "║                                                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝"
         << RESET << endl;

    cout << endl;

    cout << CYAN << "  About Bifrost" << RESET << endl;
    cout << "  ────────────────────────────────────────────────" << endl;
    cout << endl;

    cout << "    Bifrost is a C++ based network analysis" << endl;
    cout << "    and route optimization tool." << endl;
    cout << endl;

    cout << "    It provides algorithms for exploring networks," << endl;
    cout << "    finding optimal routes, and comparing algorithm" << endl;
    cout << "    performance." << endl;

    cout << endl;

    cout << CYAN << "  Features" << RESET << endl;
    cout << "  ────────────────────────────────────────────────" << endl;
    cout << endl;

    cout << "    • Network Connectivity Analysis" << endl;
    cout << "    • BFS & DFS Traversal" << endl;
    cout << "    • Dijkstra's Shortest Path" << endl;
    cout << "    • A* Pathfinding" << endl;
    cout << "    • Multi-Criteria Routing" << endl;
    cout << "    • Route Analysis" << endl;
    cout << "    • Algorithm Benchmarking" << endl;

    cout << endl;

    cout << CYAN << "  Optimization Criteria" << RESET << endl;
    cout << "  ────────────────────────────────────────────────" << endl;
    cout << endl;

    cout << "    Distance  •  Time  •  Cost" << endl;

    cout << endl;

    cout << CYAN << "  Technology" << RESET << endl;
    cout << "  ────────────────────────────────────────────────" << endl;
    cout << endl;

    cout << "    Language  : C++" << endl;
    cout << "    Interface : Command Line" << endl;

    cout << endl;
    cout << "  ────────────────────────────────────────────────" << endl;
    cout << endl;

    cout << "                    B I F R O S T" << endl;
    cout << endl;

    cout << GREY << "             Built for learning & exploration"
         << RESET << endl<<endl;

    _getch();
}

void mainMenu(Graph &bifrost)
{
    int choice;

    while (true)
    {
        clearScreen();

        cout << CYAN << BOLD;
        cout << "╔══════════════════════════════════════════════════╗\n";
        cout << "║                                                  ║\n";
        cout << "║                  B I F R O S T                   ║\n";
        cout << "║                                                  ║\n";
        cout << "║                  MAIN MENU                       ║\n";
        cout << "║                                                  ║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";
        cout << RESET;

        cout << "\n";

        cout << GREEN << "  ✓ Network Loaded\n"
             << RESET;

        cout << "\n";

        cout << YELLOW << "  [1]  Find Optimal Route\n";
        cout << "  [2]  Network Analysis\n";
        cout << "  [3]  Benchmark Algorithms\n";
        cout << "  [4]  Load Another Network\n";
        cout << "  [5]  About\n";
        cout << RED << "  [0]  Back\n"
             << RESET;

        cout << "\n";
        cout << "    " << CYAN << "➜ Select option: " << RESET;

        cin >> choice;

        switch (choice)
        {
        case 1:
            clearScreen();
            routeFinder(bifrost);
            break;

        case 2:
            networkAnalysis(bifrost);
            break;

        case 3:
            benchmarkMenu(bifrost);
            break;

        case 4:
            loadNetworkMenu(bifrost);
            break;
        case 5:
            aboutPage();
            break;
        case 0:
            return;
        default:
            cout << RED << "\n  ✗ Invalid option!\n"
                 << RESET;

            pressAnyKeyToContinue();
            break;
        }
    }
}

int main()
{
    Graph bifrost;
    int choice;
    while (true)
    {
        loadNetworkMenu(bifrost);
        mainMenu(bifrost);
    }
}