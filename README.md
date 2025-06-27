# CENG213 - Data Structures Programming Assignments (Fall 2022)

This repository contains three advanced C++ programming assignments developed as part of the CENG213 Data Structures course at Middle East Technical University. Each project explores different core data structures and their practical applications, demonstrating foundational concepts in systems-level programming and algorithm design.

---

## Assignment 1: Browser Tab Mechanism Using Circular Doubly Linked List

### Description

This assignment implements a simplified tabbed web browser interface using a custom circular, doubly linked list. The system mimics modern browser behavior including managing tabs and windows, allowing operations such as switching, closing, and moving tabs. STL is strictly not used; all data structures are implemented from scratch using templates.

### Key Features

- Custom `Node<T>` and `LinkedList<T>` classes implementing a circular, doubly linked list
- Full support for insertions, deletions, traversals, and indexed access
- A `Tab` abstraction with URL management
- `Window` class encapsulating a list of tabs with an active tab index
- `Browser` class handling multiple windows and tab transfers
- Memory-safe design with deep copy, destructors, and assignment operators

### File Structure

- `Node.h`: Node class template
- `LinkedList.h`: Circular doubly linked list implementation
- `Tab.h`, `Window.h`, `Browser.h`: Browser abstractions

---

## Assignment 2: TreeMap Implementation via Scapegoat Trees

### Description

This assignment focuses on implementing a self-balancing binary search tree known as a **Scapegoat Tree**, and building a fully functional **TreeMap** on top of it. The structure maintains sorted key-value pairs and dynamically rebalances to ensure logarithmic access and update performance in practice.

### Key Features

- Template-based `ScapegoatTree<T>` with dynamic rebalancing logic
- Scapegoat detection and subtree reconstruction to ensure height bounds
- Full support for:
  - `insert`, `remove`, `get`, `balance`, and traversal (`inorder`, `preorder`, `postorder`)
  - `getMin`, `getMax`, `getNext`, `getFloor`, `getCeiling`
- Custom `TreeMap<K, V>` class using `ScapegoatTree<KeyValuePair<K, V>>`
- Key-value operations like `update`, `pop`, `subMap`, `firstEntry`, `lastEntry`
- Exception-safe logic with `NoSuchItemException`

### File Structure

- `Node.h`: Node template for BST
- `ScapegoatTree.h`: Self-balancing BST logic
- `TreeMap.h`: TreeMap API built on ScapegoatTree
- `KeyValuePair.h`: Lightweight struct for key-value mapping

---

## Assignment 3: 3D Mesh Graph Painter with Shortest Path Coloring

### Description

This assignment implements a graph-based 3D painter that colors vertices of a mesh based on shortest paths or proximity. It introduces graph representations and pathfinding algorithms, especially Dijkstra’s algorithm using a custom binary heap for priority queue management.

### Key Features

- Custom `BinaryHeap` class for min-heap operations with unique ID enforcement
- `ChangePriority()` support for efficient shortest path algorithms
- `MeshGraph` class representing a 3D object as a graph with adjacency lists
- Paint algorithms:
  - `PaintInBetweenVertex`: Colors vertices along the shortest path
  - `PaintInRangeGeodesic`: Colors based on shortest path range and filter
  - `PaintInRangeEuclidian`: Colors based on Euclidean distance and filter
- Support for Box and Gaussian filter types with adjustable α
- Distance-weighted color blending and output to file/console
- Internal use of `Double3`, `Color`, and `Vertex` structs for 3D representation

### File Structure

- `BinaryHeap.h`, `BinaryHeap.cpp`: Custom heap for shortest path
- `MeshGraph.h`, `MeshGraph.cpp`: Graph with painting algorithms

---

## Constraints & Notes

- **Language**: All projects use C++ (no STL except where explicitly allowed)
- **Memory Safety**: Deep copies, destructors, and assignment operators must be implemented
- **Restrictions**:
  - No `std::priority_queue` or `std::queue`
  - No modifications to provided `.h` interfaces unless specified

