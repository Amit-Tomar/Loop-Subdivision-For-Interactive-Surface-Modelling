#ifndef PLYPARSER_H
#define PLYPARSER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <iostream>
#include <QString>
#include <vector>
#include <stdio.h>
#include "Mesh.h"
#include "Face.h"

#define SIZE 1024

extern Mesh objMesh ;

class PLYParser
{
public:
    PLYParser();

    void startParsing(std::string);
    void updateMetaInformation();
    std::string getParsedFilePath(){ return fileImported; }
    void exportPly();

private:

    void importFile(std::string);
    int g_point_count = 0;
    std::string fileImported;
};

#endif // PLYPARSER_H
