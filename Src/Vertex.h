#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

class Vertex
{
public:
    Vertex(double,double,double);
    double & X(){return x;}
    double & Y(){return y;}
    double & Z(){return z;}
    bool operator==(Vertex);

    std::vector<int>& getFacesVertexBelongToList();
    std::vector<int>& getNeighboringVerticesList();

    bool isModified(){ return modifiedInControlMesh; }
    void reset(){ modifiedInControlMesh = false; }
    void modified(){ modifiedInControlMesh = true ; }

private:

    double x;
    double y;
    double z;

    bool modifiedInControlMesh;

    std::vector<int> neighborVerticesList;
    std::vector<int> neighborFaceList;
};

#endif // VERTEX_H
