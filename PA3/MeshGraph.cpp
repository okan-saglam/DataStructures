#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    // TODO:
    int i, j, sizeOfPositions, sizeOfEdges, sizeOfVertices;
    sizeOfPositions = vertexPositions.size();
    sizeOfEdges = edges.size();

    for(i=0 ; i < sizeOfPositions ; i++)
    {
        struct Vertex point;
        point.id = i; point.position3D = vertexPositions[i];
        vertices.push_back(point); 
    }

    sizeOfVertices = vertices.size();

    for(i=0 ; i < sizeOfVertices ; i++)
    {
        std::list<Vertex*> vertices_i;
        for(j=0 ; j < sizeOfEdges ; j++)
        {
            struct Vertex *pushed;
            if(edges[j].vertexId0 == vertices[i].id)
            { 
                pushed = &vertices[edges[j].vertexId1];
                vertices_i.push_back(pushed);
            }
            else if(edges[j].vertexId1 == vertices[i].id)
            { 
                pushed = &vertices[edges[j].vertexId0];
                vertices_i.push_back(pushed);
            }
        }
        adjList.push_back(vertices_i);
    }
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    double sum=0.0;
    int i, sizeOfAdjlist, edge_count;
    edge_count = TotalEdgeCount();
    sizeOfAdjlist = adjList.size();
    if(edge_count == 0)
        return 0.0;
    for(i = 0 ; i < sizeOfAdjlist ; i++)
    {
        std::list<struct Vertex *>::const_iterator i1;
        for(i1 = adjList[i].begin() ; i1 != adjList[i].end() ; i1++)
        {
            sum += Double3::Distance(vertices[i].position3D, (**i1).position3D);
        }
    }
    sum /= 2;
    return sum/edge_count;
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    double edges;
    edges = TotalEdgeCount();
    return edges/TotalVertexCount();
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    int i, sizeOfAdjlist, count=0;
    sizeOfAdjlist = adjList.size();
    for(i = 0 ; i < sizeOfAdjlist ; i++)
    {
        std::list<struct Vertex *>::const_iterator i1;
        for(i1 = adjList[i].begin() ; i1 != adjList[i].end() ; i1++)
        {
            count++;
        }
    }
    return count/2;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    int i, sizeOfAdjlist;
    sizeOfAdjlist = adjList.size();
    if(vertexId >= sizeOfAdjlist || vertexId < 0)
        return -1;
    else
    {
        return adjList[vertexId].size();
    }
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    // TODO:
    outVertexIds.clear();
    int sizeOfAdjlist;
    sizeOfAdjlist = vertices.size();
    if(vertexId >= sizeOfAdjlist || vertexId < 0)
        return;
    else
    {
        std::list<struct Vertex *>::const_iterator i1;
        for(i1 = adjList[vertexId].begin() ; i1 != adjList[vertexId].end() ; i1++)
        {
            outVertexIds.push_back((*i1)->id);
        }
    }
}

void MeshGraph::Dijsktra(std::vector<int>&path, int vertexfrom, int vertexto) const
{
    int sizeOfVertices;
    BinaryHeap unvisited;
    std::vector<double> distances;
    std::vector<int> previous; 
    std::vector<int> temp_path;
    sizeOfVertices = vertices.size();
    for(int i=0 ; i < sizeOfVertices ; i++)
    {
        distances.push_back(INFINITY);
        previous.push_back(-1);
    }
    distances[vertexfrom] = 0;
    for(int i=0 ; i<sizeOfVertices ; i++)
    {
        unvisited.Add(vertices[i].id, distances[i]);
    }
    while(unvisited.HeapSize() > 0)
    {
        int sizeOfAdjecent;
        HeapElement v;
        std::vector<int> adjecents;
        unvisited.PopHeap(v.uniqueId, v.weight); // vertexIdFrom
        ImmediateNeighbours(adjecents, v.uniqueId); // E(v,adjecents[i])
        sizeOfAdjecent = adjecents.size();
        for(int i=0 ; i < sizeOfAdjecent ; i++)
        {
            bool flag = false;
            double new_dist;
            new_dist = distances[v.uniqueId] + Double3::Distance(vertices[v.uniqueId].position3D, vertices[adjecents[i]].position3D);
            for(int j=0 ; j < adjecents.size() ; j++)
            {
                if(new_dist == distances[j])
                    {flag = true; break;}
            }
            if(flag)
                continue;
            if(new_dist < distances[adjecents[i]])
            {
                distances[adjecents[i]] = new_dist;
                previous[adjecents[i]] = v.uniqueId;
                unvisited.ChangePriority(adjecents[i], new_dist);
            }
        }
    }
    int last = vertexto;
    temp_path.push_back(last);
    while(previous[last] != -1)
    {
        temp_path.push_back(previous[last]);
        last = previous[last];
    }
    for(int i=temp_path.size()-1 ; i>=0 ; i--)
    {
        path.push_back(temp_path[i]);
    }
}

void MeshGraph::BFS(std::vector<int>& toBeColored, std::vector<int>& previous, int vertexId, int maxDepth) const
{
    int order=2;
    int sizeOfVertices = TotalVertexCount();
    BinaryHeap nextToVisit;
    std::vector<int> visited; 
    std::vector<int> depths;
    for(int i=0 ; i < sizeOfVertices ; i++)
    {
        visited.push_back(0);
        previous.push_back(-1);
        depths.push_back(-1);
    }
    toBeColored.push_back(vertexId);
    visited[vertexId] = 1;
    depths[vertexId] = 0;
    nextToVisit.Add(vertexId, 1);
    while(nextToVisit.HeapSize() > 0)
    {
        bool flag = false;
        int sizeOfAdjecents, sizeOfDepths;
        HeapElement u;
        nextToVisit.PopHeap(u.uniqueId, u.weight);
        std::vector<int> adjecents;
        if(depths[u.uniqueId] < maxDepth)
        {
            ImmediateNeighbours(adjecents, u.uniqueId);
        }
        sizeOfAdjecents = adjecents.size();
        for(int j=0 ; j < sizeOfAdjecents ; j++, order++)
        {
            int temp_depth=0;
            if(visited[adjecents[j]] == 0)
            {
                toBeColored.push_back(adjecents[j]);
                visited[adjecents[j]] = 1;
                previous[adjecents[j]] = u.uniqueId;
                nextToVisit.Add(adjecents[j], order);
            }
            int kendisi = adjecents[j];
            while(previous[kendisi] > -1)
            {
                temp_depth++;
                kendisi = previous[kendisi];
            }
            depths[adjecents[j]] = temp_depth;
        }
    }
}

double MeshGraph::Gaussian(double x, double alpha) const
{
    double filter_value, nom_power, denom_power;
    nom_power = std::pow(x, 2);
    denom_power = std::pow(alpha, 2);
    filter_value = std::exp(-(nom_power/denom_power));
    return filter_value;
}

int MeshGraph::Box(double x, double alpha) const
{
    int filter_value;
    if(-alpha <= x && x <= alpha)
        return 1;
    else
        return 0;
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    // TODO:
    outputColorAllVertex.clear();
    std::vector<int> path;
    int sizeOfVertices;
    sizeOfVertices = vertices.size();
    if((vertexIdFrom > sizeOfVertices || vertexIdFrom < 0) || (vertexIdTo > sizeOfVertices || vertexIdTo <0))
        return;
    else
    {
        Dijsktra(path, vertexIdFrom, vertexIdTo);
    }
    outputColorAllVertex.resize(sizeOfVertices);
    for(int i=0 ; i < sizeOfVertices ; i++)
    {
        Color black;
        black.r = 0; black.g = 0; black.b = 0;
        outputColorAllVertex[i] = black;
    }
    for(int i=0 ; i < path.size() ; i++)
    {
        for(int j=0 ; j < sizeOfVertices ; j++)
        {
            if(path[i] == j)
                outputColorAllVertex[j] = color;
        }
    }
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    // TODO:
    outputColorAllVertex.clear();
    int sizeOfVertices = TotalVertexCount();
    outputColorAllVertex.resize(sizeOfVertices);
    if(sizeOfVertices <= vertexId || vertexId < 0)
        return ;
    else
    {
        int sizeOfShouldcolored, sizeOfPreviousids;
        std::vector<double> filter_value;
        std::vector<double> distances;
        std::vector<int> shouldcolored;
        std::vector<int> previousids;
        Color black;
        black.r = 0; black.g = 0; black.b = 0;
        for(int i=0 ; i < sizeOfVertices ; i++)
        {
            outputColorAllVertex[i] = black;
        }
        BFS(shouldcolored, previousids, vertexId, maxDepth);
        sizeOfShouldcolored = shouldcolored.size(); sizeOfPreviousids = previousids.size();
        for(int i=0 ; i < sizeOfVertices ; i++)
        {
            distances.push_back(-1);
            filter_value.push_back(0);
        }
        distances[vertexId] = 0;
        for(int i=0 ; i < sizeOfShouldcolored ; i++)
        {
            double new_dist = 0;
            int kendisi = shouldcolored[i];
            while(previousids[kendisi] > -1)
            {
                double temp_dist;
                temp_dist = Double3::Distance(vertices[kendisi].position3D, vertices[previousids[kendisi]].position3D);
                new_dist += temp_dist;
                kendisi = previousids[kendisi];
            }
            distances[shouldcolored[i]] = new_dist;
        }
        for(int i=0 ; i < sizeOfShouldcolored ; i++)
        {
            double new_filterValue;
            if(type == FILTER_GAUSSIAN)
            {
                new_filterValue = Gaussian(distances[shouldcolored[i]], alpha);
                filter_value[shouldcolored[i]] = new_filterValue;
            }
            else
            {
                new_filterValue = Box(distances[shouldcolored[i]], alpha);
                filter_value[shouldcolored[i]] = new_filterValue;
            }
        }
        for(int i=0 ; i < sizeOfShouldcolored ; i++)
        {
            Color newColor;
            newColor.r = color.r * filter_value[shouldcolored[i]];
            newColor.g = color.g * filter_value[shouldcolored[i]];
            newColor.b = color.b * filter_value[shouldcolored[i]];
            outputColorAllVertex[shouldcolored[i]] = newColor;
        }
    }
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    // TODO:
    outputColorAllVertex.clear();
    int sizeOfVertices = TotalVertexCount();
    outputColorAllVertex.resize(sizeOfVertices);
    if(sizeOfVertices <= vertexId || vertexId < 0)
        return ;
    else
    {
        int sizeOfShouldcolored, sizeOfPreviousids;
        std::vector<double> filter_value;
        std::vector<int> shouldcolored;
        std::vector<int> previousids;
        Color black;
        black.r = 0; black.g = 0; black.b = 0;
        for(int i=0 ; i < sizeOfVertices ; i++)
        {
            outputColorAllVertex[i] = black;
        }
        BFS(shouldcolored, previousids, vertexId, maxDepth);
        sizeOfShouldcolored = shouldcolored.size(); sizeOfPreviousids = previousids.size();
        for(int i=0 ; i < sizeOfVertices ; i++)
        {
            filter_value.push_back(0);
        }
        for(int i=0 ; i < sizeOfShouldcolored ; i++)
        {
            double distance;
            double new_filterValue;
            distance = Double3::Distance(vertices[vertexId].position3D, vertices[shouldcolored[i]].position3D);
            if(type == FILTER_GAUSSIAN)
            {
                new_filterValue = Gaussian(distance, alpha);
                filter_value[shouldcolored[i]] = new_filterValue;
            }
            else
            {
                new_filterValue = Box(distance, alpha);
                filter_value[shouldcolored[i]] = new_filterValue;
            }
        }
        for(int i=0 ; i < sizeOfShouldcolored ; i++)
        {
            Color newColor;
            newColor.r = color.r * filter_value[shouldcolored[i]];
            newColor.g = color.g * filter_value[shouldcolored[i]];
            newColor.b = color.b * filter_value[shouldcolored[i]];
            outputColorAllVertex[shouldcolored[i]] = newColor;
        }
    }
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}