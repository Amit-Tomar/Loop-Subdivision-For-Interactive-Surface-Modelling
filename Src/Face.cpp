#include "Face.h"

Face::Face()
{
}

bool Face::hasEdge(Edge edge)
{
    int count = 0 ;
    for( int i = 0 ; i < boundingVertices.size() ; ++ i  )
    {
        if( edge.V1() == boundingVertices[i] || edge.V2() == boundingVertices[i] )
            count ++ ;
    }

    if( count >= 2 )
        return true;
    else
        return false;
}

unsigned int Face::vertexOppositeToEdge(Edge edge)
{
    if( (edge.V1() == boundingVertices[0] && edge.V2() == boundingVertices[1]) || (edge.V1() == boundingVertices[1] && edge.V2() == boundingVertices[0]) )
        return boundingVertices[2];
    if( (edge.V1() == boundingVertices[1] && edge.V2() == boundingVertices[2]) || (edge.V1() == boundingVertices[2] && edge.V2() == boundingVertices[1]) )
        return boundingVertices[0];
    if( (edge.V1() == boundingVertices[2] && edge.V2() == boundingVertices[0]) || (edge.V1() == boundingVertices[0] && edge.V2() == boundingVertices[2]) )
        return boundingVertices[1];

    std::cout << "[Error: Not common vertex]" << std::endl ;
    return 100;
}

bool Face::operator==(Face rightHandSideFace)
{
    for( int i =0 ; i < getBoundingVerticesList().size() ; ++ i )
    {
        if(std::find(rightHandSideFace.getBoundingVerticesList().begin(), rightHandSideFace.getBoundingVerticesList().end(), getBoundingVerticesList()[i])!=rightHandSideFace.getBoundingVerticesList().end())
        {
            return false;
        }
    }

    return true;
}

