# Bifrost

Bifrost is a C++ CLI-based weighted graph project focused on pathfinding and network analysis using Data Structures and Algorithms.

The project models a network of interconnected locations and aims to explore different graph algorithms through a practical, scalable implementation.

## Current Status

Currently, Bifrost can:

- Load a network from a `.txt` dataset
- Parse locations and their connection properties
- Construct an undirected weighted graph in memory

## Future Features

- [ ] BFS & DFS based network analysis
- [ ] Shortest path using Dijkstra's algorithm
- [ ] Advanced pathfinding using A*
- [ ] Network and path analysis
- [ ] Algorithm benchmarking
- [ ] CMake-based build system
- [ ] Improved CLI interface using FTXUI

## Dataset

Bifrost currently parses its network data using the file system because the dataset is small and easy to manage during development.

As the network grows to 1,000+ nodes and a much larger number of connections, the project may transition to PostgreSQL for persistent and scalable data storage.

The network is represented as an **undirected weighted graph**, allowing connections to be traversed in both directions.

Example dataset format:

```text
Source,Destination,Distance,Time,Cost
Mumbai,Surat,280,4.5,500
Surat,Vadodara,150,2.5,300
Vadodara,Ahmedabad,110,2.0,250
```

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
