#include "Vertex.h"

Vertex::Vertex(double x, double y, double z)
{
    this->x = x ;
    this->y = y ;
    this->z = z ;
    reset();
}

bool Vertex::operator==(Vertex rightVertx)
{
    if( x == rightVertx.X() && y == rightVertx.Y() && z == rightVertx.Z() )
        return true;
    else
        return false;
}

std::vector<int> & Vertex::getFacesVertexBelongToList()
{
    return neighborFaceList;
}

std::vector<int> & Vertex::getNeighboringVerticesList()
{
    return neighborVerticesList;
}
