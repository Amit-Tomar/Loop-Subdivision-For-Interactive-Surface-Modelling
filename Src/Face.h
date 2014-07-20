#ifndef FACE_H
#define FACE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Edge.h"

using namespace  std;

class Face
{
public:
    Face();

    bool hasEdge(Edge);
    unsigned int  vertexOppositeToEdge(Edge);

    std::vector<int>& getBoundingVerticesList()  { return boundingVertices ; }
    std::vector<int>& getNeighborFacesList()     { return neighboringFaces;  }
    bool operator==(Face);

private:

    std::vector<int> boundingVertices;
    std::vector<int> neighboringFaces;
};

#endif // FACE_H
