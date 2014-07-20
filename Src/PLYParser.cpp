#include "PLYParser.h"

PLYParser::PLYParser()
{

}

void PLYParser::importFile(std::string sFilePath)
{
    std::cout << "Parsing started" << std::endl ;

    fileImported = sFilePath ;

    char str1[SIZE], str2[SIZE] ;
    unsigned int iTemp = 0;
    char buffer[SIZE];

    FILE * fileReadPointer  = fopen ( sFilePath.c_str(), "r" );
    if( NULL == fileReadPointer )
    {
        puts("Error : File not opened for reading.");
        return;
    }

    while ( NULL != fgets( buffer , SIZE , fileReadPointer) )
    {
        if( EOF == buffer[0] )
        {
            break;
        }

        else
        {
            sscanf( buffer, "%s %s %d", &str1 , &str2, &iTemp );

            if( 0 == strcmp( "end_header", str1 ) )
                break;
            else if( 0 == strcmp( "element", str1 ) && 0 == strcmp( "vertex", str2 ) )
                objMesh.setNumberOfVertices(iTemp);
            else if( 0 == strcmp( "element", str1 ) && 0 == strcmp( "face", str2 ) )
                objMesh.setNumberOfFaces(iTemp);
        }
    }

    unsigned int count = 0;
    double x=0, y=0, z=0 ;
    for( ; count < objMesh.totalVertices() ; ++count )
    {
            fgets( buffer , SIZE , fileReadPointer);
            sscanf( buffer, "%lf %lf %lf", &x , &y, &z );

            Vertex tempVertex(x,y,z);
            objMesh.getVertexList().push_back(tempVertex);
    }

    count = 0;
    int  v1=0, v2=0, v3=0, v4=0, v5=0 ;


    for( count = 0 ; count < objMesh.totalFaces() ; ++count )
    {
        fgets( buffer , SIZE , fileReadPointer);
        sscanf( buffer, "%d %d %d %d %d %d", &iTemp, &v1 , &v2, &v3, &v4, &v5 );

        // Triangulate the quads

        if( 3 == iTemp )
        {
            Face objFace;
            objFace.getBoundingVerticesList().push_back( v1 );
            objFace.getBoundingVerticesList().push_back( v2 );
            objFace.getBoundingVerticesList().push_back( v3 );

            objMesh.getFaceList().push_back(objFace);

            if( !objMesh.getParsingStatus() )
            objMesh.getControlMeshFaceList().push_back(objFace);

            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v2);
            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v2].getNeighboringVerticesList().push_back(v1);
            objMesh.getVertexList()[v2].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v2);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v1);
        }

        else if( 4 == iTemp )
        {
            Face objFace1;
            objFace1.getBoundingVerticesList().push_back( v1 );
            objFace1.getBoundingVerticesList().push_back( v2 );
            objFace1.getBoundingVerticesList().push_back( v3 );

            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v2);
            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v2].getNeighboringVerticesList().push_back(v1);
            objMesh.getVertexList()[v2].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v2);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v1);

            Face objFace2;
            objFace2.getBoundingVerticesList().push_back( v3 );
            objFace2.getBoundingVerticesList().push_back( v4 );
            objFace2.getBoundingVerticesList().push_back( v1 );

            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v4);
            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v4].getNeighboringVerticesList().push_back(v1);
            objMesh.getVertexList()[v4].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v4);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v1);

            objMesh.getFaceList().push_back(objFace1);
            objMesh.getFaceList().push_back(objFace2);

            if( !objMesh.getParsingStatus() )
            {
                objMesh.getControlMeshFaceList().push_back(objFace1);
                objMesh.getControlMeshFaceList().push_back(objFace2);
            }
        }

        else if( 5 == iTemp )
        {
            Face objFace1;
            objFace1.getBoundingVerticesList().push_back( v1 );
            objFace1.getBoundingVerticesList().push_back( v2 );
            objFace1.getBoundingVerticesList().push_back( v3 );

            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v2);
            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v2].getNeighboringVerticesList().push_back(v1);
            objMesh.getVertexList()[v2].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v2);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v1);

            Face objFace2;
            objFace2.getBoundingVerticesList().push_back( v3 );
            objFace2.getBoundingVerticesList().push_back( v4 );
            objFace2.getBoundingVerticesList().push_back( v5 );

            objMesh.getVertexList()[v4].getNeighboringVerticesList().push_back(v5);
            objMesh.getVertexList()[v4].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v5].getNeighboringVerticesList().push_back(v4);
            objMesh.getVertexList()[v5].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v4);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v5);

            Face objFace3;
            objFace3.getBoundingVerticesList().push_back( v5 );
            objFace3.getBoundingVerticesList().push_back( v1 );
            objFace3.getBoundingVerticesList().push_back( v3 );

            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v5);
            objMesh.getVertexList()[v1].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v5].getNeighboringVerticesList().push_back(v1);
            objMesh.getVertexList()[v5].getNeighboringVerticesList().push_back(v3);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v5);
            objMesh.getVertexList()[v3].getNeighboringVerticesList().push_back(v1);

            objMesh.getFaceList().push_back(objFace1);
            objMesh.getFaceList().push_back(objFace2);
            objMesh.getFaceList().push_back(objFace3);

            if( !objMesh.getParsingStatus() )
            {
                objMesh.getControlMeshFaceList().push_back(objFace1);
                objMesh.getControlMeshFaceList().push_back(objFace2);
                objMesh.getControlMeshFaceList().push_back(objFace3);
            }
        }

        else
        {
            std::cerr << "Error: Found a face with for than 5 sides" << std::endl ;
        }
    }

    if( !objMesh.getParsingStatus() )
    for( unsigned int i =0 ; i < objMesh.getVertexList().size() ; ++ i )
        objMesh.getControlMeshVertexList().push_back(objMesh.getVertexList()[i]);

    updateMetaInformation();
}

void PLYParser::startParsing(std::string path)
{
    if(path.length() == 0)
        importFile( "../plyFiles/dodecahedron.ply" );
    else
        importFile( path );

    objMesh.setParsingStatus();
}

void PLYParser::updateMetaInformation()
{
    //Update total faces based on triangulation just done
    objMesh.setNumberOfFaces(objMesh.getFaceList().size());

    // Fill the neighbor faces information in face list
    for(unsigned int i = 0 ; i < objMesh.totalFaces() ; ++ i)
    {
        for( unsigned int j = 0 ; j < objMesh.totalFaces() ; ++ j )
        {
            if( i != j && objMesh.areFacesNeighbors( objMesh.getFaceList()[i],  objMesh.getFaceList()[j]))
            {
                objMesh.getFaceList()[i].getNeighborFacesList().push_back(j);
            }
        }
    }

    // Fill the face information in vertex list
    for(unsigned int i = 0 ; i < objMesh.totalFaces() ; ++ i)
    {
        for( unsigned int j = 0 ; j < objMesh.getFaceList()[i].getBoundingVerticesList().size() ; ++ j )
        {
            unsigned int vertexNumber = objMesh.getFaceList()[i].getBoundingVerticesList()[j] ;
            objMesh.getVertexList()[vertexNumber].getFacesVertexBelongToList().push_back(i);
        }
    }

    std::cout << "Parsing over" << std::endl ;
    //objMesh.printMeshInformation();
}

void PLYParser::exportPly()
{
    FILE * fileWritePointer = fopen ( "OutputMesh.ply", "w" );
    fprintf( fileWritePointer, "ply\nformat ascii 1.0\nelement vertex ");
    fprintf( fileWritePointer, "%d\n", objMesh.totalVertices());
    fprintf( fileWritePointer, "property float x\nproperty float y\nproperty float z\nelement face " );
    fprintf( fileWritePointer, "%d\n", objMesh.totalFaces());
    fprintf( fileWritePointer, "property list uchar int vertex_index\nend_header\n" );

    for( unsigned int i = 0 ; i < objMesh.totalVertices() ; ++i )
    {
        fprintf( fileWritePointer, "%lf %lf %lf \n", objMesh.getVertexList()[i].X(), objMesh.getVertexList()[i].Y(), objMesh.getVertexList()[i].Z());
    }

    for( unsigned int i = 0 ; i < objMesh.totalFaces() ; ++i )
    {
        fprintf( fileWritePointer, "3 %d %d %d \n", objMesh.getFaceList()[i].getBoundingVerticesList()[0], objMesh.getFaceList()[i].getBoundingVerticesList()[1], objMesh.getFaceList()[i].getBoundingVerticesList()[2]);
    }
}
