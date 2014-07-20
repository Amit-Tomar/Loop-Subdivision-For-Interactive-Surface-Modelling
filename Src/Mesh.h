#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <Vertex.h>
#include <vector>
#include <math.h>
#include "Face.h"
#include "Edge.h"
#include "Window.h"

using namespace std;

class Mesh
{
public:

    Mesh();

    void printMeshInformation();
    bool areFacesNeighbors(Face,Face);
    void subdivideByLoop();
    int  findVertexPosition(std::vector<Vertex> &, Vertex);

    void setNumberOfVertices(unsigned int vertices){ numberOfVertices = vertices ; }
    void setNumberOfFaces(unsigned int faces){ numberOfFaces = faces ; }

    unsigned int totalVertices(){return numberOfVertices;}
    unsigned int totalFaces(){return numberOfFaces;}
    unsigned int getSelectedControlMeshIndex(){return selectedControlMeshVertex;}
    void setSelectedControlMeshIndex(unsigned int index){selectedControlMeshVertex = index;}
    unsigned int getSubdivisonLevel(){ return subdivisionLevel; }
    void setSubdivisonLevel(unsigned int level){ subdivisionLevel = level; }

    std::vector<Vertex> & getVertexList(){return vertexList;}
    std::vector<Vertex> & getControlMeshVertexList(){return controlMeshVertexList;}
    std::vector<Face> & getControlMeshFaceList(){return controlMeshFaceList;}
    std::vector<Face> & getFaceList(){return faceList;}
    void reset();
    void setParsingStatus(){ parsedOnce = true; }
    bool getParsingStatus(){ return parsedOnce; }

private:

    unsigned int numberOfVertices;
    unsigned int numberOfFaces;
    unsigned int subdivisionLevel;

    std::vector<Vertex> vertexList;
    std::vector<Face> faceList;

    std::vector<Vertex> controlMeshVertexList;
    std::vector<Face>   controlMeshFaceList;
    unsigned int selectedControlMeshVertex;

    bool parsedOnce;
};

#endif // MESH_H
