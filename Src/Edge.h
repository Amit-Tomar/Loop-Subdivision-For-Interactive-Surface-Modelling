#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Edge
{
public:
    Edge(int,int);
    bool operator==(Edge);
    int V1(){ return v1; }
    int V2(){ return v2; }
    Vertex & getSubDividedVertex(){ return subdividedVertex ; }

private:

    Vertex subdividedVertex;
    int v1,v2;
};

#endif // EDGE_H
