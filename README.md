# Bifrost

Bifrost is a C++ CLI-based weighted graph project focused on pathfinding and network analysis using Data Structures and Algorithms.

The project models a network of interconnected locations and explores graph algorithms through a practical, scalable implementation.

## Current Status

Bifrost currently can:

- [x] Load a network from a `.txt` dataset
- [x] Parse locations and their connection properties
- [x] Construct an undirected weighted graph in memory
- [x] Perform BFS traversal
- [x] Perform DFS traversal
- [x] Check reachability between two locations
- [x] Find connected components
- [x] Determine network connectivity
- [x] Find a minimum-weight path using Dijkstra's algorithm
- [x] Reconstruct the path found by Dijkstra

## Future Features

- [ ] Route analysis using distance, time and cost
- [ ] Advanced pathfinding using A*
- [ ] Algorithm benchmarking
- [ ] Improved CLI interface using FTXUI
- [ ] CMake-based build system

## Dataset

Bifrost currently parses its network data using the file system because the dataset is small and easy to manage during development.

As the network grows to 1,000+ nodes and a much larger number of connections, the project may transition to PostgreSQL for persistent and scalable data storage. *shhh* 🤫

The network is represented as an **undirected weighted graph**, allowing connections to be traversed in both directions.

### Example Dataset Format

Source,Destination,Distance,Time,Cost
Mumbai,Surat,280,4.5,500
Surat,Vadodara,150,2.5,300
Vadodara,Ahmedabad,110,2.0,250

## Tech Stack

- C++
- STL
- Data Structures & Algorithms
- File Handling
- PostgreSQL (planned)
- FTXUI (planned)
- CMake (planned)

## Why "Bifrost"? 🌈

The name is inspired by Marvel's Bifrost — the bridge that connects different realms and enables travel between them.

In a similar way, Bifrost works with connections between locations and finds meaningful paths through the network.

## Project Goal

The goal of Bifrost is to build a practical and scalable graph-based system while applying Data Structures and Algorithms to a real-world-inspired problem.

> Connect. Navigate. Analyze.