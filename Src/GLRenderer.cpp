#include <QtWidgets>
#include <QtOpenGL>

#include <math.h>
#include "GLRenderer.h"

GLRenderer::GLRenderer(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    setFocusPolicy(Qt::ClickFocus);
    scale = .25 ;
    //translateX = 0.01 ;
    //translateY = -.115 ;
    //translateZ = -1 ;
    lightPositionX = 1.0 ;
    lightPositionY = 1.0 ;
    lightPositionZ = 1.0 ;
    lightMovementEnabled = false ;
}

GLRenderer::~GLRenderer()
{
}

QSize GLRenderer::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLRenderer::sizeHint() const
{
    return QSize(1500, 800);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLRenderer::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLRenderer::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLRenderer::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLRenderer::initializeGL()
{
    qglClearColor(qtPurple.dark());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLRenderer::paintGL()
{
    if(objMesh.getFaceList().size() == 0 )
        return;

    // Set light
    GLfloat light_position[] = { lightPositionX, lightPositionY, lightPositionZ, 0.0 };
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enabling texture
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    float Tscale = 20; // dragon4
    bindTexture(QImage("dragon4.bmp"));

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glEnable(GL_NORMALIZE);
    glLoadIdentity();

    if( !lightMovementEnabled )
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glTranslatef( 0.0, 0.0, -10.0);

    /* Rotation*/
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    glScalef(scale,scale,scale);
    glTranslatef(translateX,translateY,translateZ);

    if( lightMovementEnabled )
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

        for( int i = 0 ; i < objMesh.totalFaces() ; i++)
        {
            glColor3f(1.0f, 0.6f, 0.0f);
            glBegin(GL_LINE_LOOP);
            //glBegin(GL_TRIANGLES);
            int vertex1 = objMesh.getFaceList()[i].getBoundingVerticesList()[0];
            int vertex2 = objMesh.getFaceList()[i].getBoundingVerticesList()[1];
            int vertex3 = objMesh.getFaceList()[i].getBoundingVerticesList()[2];

            float vector1[3], vector2[3], vCross[3], normalizationValue;
            vector1[0] = objMesh.getVertexList()[vertex1].X() - objMesh.getVertexList()[vertex2].X();
            vector1[1] = objMesh.getVertexList()[vertex1].Y() - objMesh.getVertexList()[vertex2].Y();
            vector1[2] = objMesh.getVertexList()[vertex1].Z() - objMesh.getVertexList()[vertex2].Z();

            vector2[0] = objMesh.getVertexList()[vertex1].X() - objMesh.getVertexList()[vertex3].X();
            vector2[1] = objMesh.getVertexList()[vertex1].Y() - objMesh.getVertexList()[vertex3].Y();
            vector2[2] = objMesh.getVertexList()[vertex1].Z() - objMesh.getVertexList()[vertex3].Z();

            // Cross product
            vCross[0] = vector1[1] * vector2[2] - vector2[1] * vector1[2];
            vCross[1] = vector2[0] * vector1[2] - vector1[0] * vector2[2];
            vCross[2] = vector1[0] * vector2[1] - vector2[0] * vector1[1];

            // Value to do normalization with
            normalizationValue = sqrt( vCross[0]*vCross[0] + vCross[1]*vCross[1] + vCross[2]*vCross[2] );

            float normal[3];
            normal[0] = vCross[0]/normalizationValue;
            normal[1] = vCross[1]/normalizationValue;
            normal[2] = vCross[2]/normalizationValue;

            glNormal3f(normal[0],normal[1],normal[2]);

            for( int j = 0 ; j < objMesh.getFaceList()[i].getBoundingVerticesList().size(); ++ j )
            {
                int vertex = objMesh.getFaceList()[i].getBoundingVerticesList()[j];
                glTexCoord2f(objMesh.getVertexList()[vertex].X()*Tscale, (objMesh.getVertexList()[vertex].Y()+objMesh.getVertexList()[vertex].Z())*Tscale);
                glVertex3f( objMesh.getVertexList()[vertex].X(), objMesh.getVertexList()[vertex].Y(), objMesh.getVertexList()[vertex].Z() );
            }

            glEnd();
        }

        // Draw Control Mesh Polygon
        for( int i = 0 ; i < objMesh.getControlMeshFaceList().size() ; i++ )
        {
            unsigned int ver1 = objMesh.getControlMeshFaceList()[i].getBoundingVerticesList()[0];
            unsigned int ver2 = objMesh.getControlMeshFaceList()[i].getBoundingVerticesList()[1];
            unsigned int ver3 = objMesh.getControlMeshFaceList()[i].getBoundingVerticesList()[2];

            glColor3f(1.0f, 0.0f, 0.0f);
            glPointSize(5);
            bindTexture(QImage("dragon3.bmp"));

            glBegin(GL_LINE_LOOP);
            glVertex3f( objMesh.getControlMeshVertexList()[ver1].X(), objMesh.getControlMeshVertexList()[ver1].Y(), objMesh.getControlMeshVertexList()[ver1].Z()  );
            glVertex3f( objMesh.getControlMeshVertexList()[ver2].X(), objMesh.getControlMeshVertexList()[ver2].Y(), objMesh.getControlMeshVertexList()[ver2].Z()  );
            glVertex3f( objMesh.getControlMeshVertexList()[ver3].X(), objMesh.getControlMeshVertexList()[ver3].Y(), objMesh.getControlMeshVertexList()[ver3].Z()  );
            glEnd();

            bindTexture(QImage("dragon2.bmp"));
            glBegin(GL_POINTS);
            glVertex3f( objMesh.getControlMeshVertexList()[ver1].X(), objMesh.getControlMeshVertexList()[ver1].Y(), objMesh.getControlMeshVertexList()[ver1].Z()  );
            glVertex3f( objMesh.getControlMeshVertexList()[ver2].X(), objMesh.getControlMeshVertexList()[ver2].Y(), objMesh.getControlMeshVertexList()[ver2].Z()  );
            glVertex3f( objMesh.getControlMeshVertexList()[ver3].X(), objMesh.getControlMeshVertexList()[ver3].Y(), objMesh.getControlMeshVertexList()[ver3].Z()  );
            glEnd();
        }

        glPointSize(15);
            glBegin(GL_POINTS);
            glColor3f(0.0f, 1.0f, 0.0f);
                glEnable(GL_POINT_SMOOTH);
                glVertex3f( objMesh.getControlMeshVertexList()[objMesh.getSelectedControlMeshIndex()].X()  , objMesh.getControlMeshVertexList()[objMesh.getSelectedControlMeshIndex()].Y()  , objMesh.getControlMeshVertexList()[objMesh.getSelectedControlMeshIndex()].Z() );
            glEnd();

    glDisable(GL_TEXTURE_2D);
}

void GLRenderer::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void GLRenderer::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLRenderer::keyPressEvent(QKeyEvent *keyevent)
{
    // Scale
    if( keyevent->key() == Qt::Key_P )
    {
        scale += .05;
    }

    else if( keyevent->key() == Qt::Key_Semicolon )
    {
        scale -= .05;
    }

    // Translation of object
    else if( keyevent->key() == Qt::Key_W )
    {
        translateY += .05 ;
    }

    else if( keyevent->key() == Qt::Key_A )
    {
        translateX -= .05 ;
    }

    else if( keyevent->key() == Qt::Key_D )
    {
        translateX += .05 ;
    }

    else if( keyevent->key() == Qt::Key_S )
    {
        translateY -= .05 ;
    }

    // Rotation of object
    else if( keyevent->key() == Qt::Key_T )
    {
        xRot += 15 ;
    }

    else if( keyevent->key() == Qt::Key_F )
    {
        yRot -= 15 ;
    }

    else if( keyevent->key() == Qt::Key_G )
    {
        xRot -= 15 ;
    }

    else if( keyevent->key() == Qt::Key_H )
    {
        yRot += 15 ;
    }


    // Translation of Light
    else if( keyevent->key() == Qt::Key_I )
    {
        lightPositionX += 1 ;
    }

    else if( keyevent->key() == Qt::Key_K )
    {
        lightPositionX -= 1; ;
    }

    else if( keyevent->key() == Qt::Key_L )
    {
        lightPositionY += 1 ;
    }

    else if( keyevent->key() == Qt::Key_J )
    {
        lightPositionY -= 1; ;
    }

    // Light movement enable/disable

    else if( keyevent->key() == Qt::Key_Q )
    {
       lightMovementEnabled = !lightMovementEnabled;
    }

    else if( keyevent->key() == Qt::Key_N )
    {
       objMesh.subdivideByLoop();
       objPLYParser.updateMetaInformation();
       //objMesh.printMeshInformation();
    }

    else if( keyevent->key() == Qt::Key_E )
    {
       objPLYParser.exportPly();
    }

    else if( keyevent->key() == Qt::Key_M )
    {
        if( objMesh.getSelectedControlMeshIndex() < objMesh.getControlMeshVertexList().size()-1)
            objMesh.setSelectedControlMeshIndex(objMesh.getSelectedControlMeshIndex()+1);
        else
            objMesh.setSelectedControlMeshIndex(0);
    }

    else if( keyevent->key() == Qt::Key_Z )
    {
        objMesh.getControlMeshVertexList()[objMesh.getSelectedControlMeshIndex()].Y() -= 1;
        objMesh.getControlMeshVertexList()[objMesh.getSelectedControlMeshIndex()].modified();

        objMesh.reset();
        objPLYParser.startParsing(objPLYParser.getParsedFilePath());
        objPLYParser.updateMetaInformation();

        for( int i = 0 ; i < objMesh.getControlMeshVertexList().size() ; ++ i )
        {
            if( objMesh.getControlMeshVertexList()[i].isModified() )
                objMesh.getVertexList()[i].Y() = objMesh.getControlMeshVertexList()[i].Y() ;
        }

        unsigned int levelOfDivision = objMesh.getSubdivisonLevel() ;

        for( int i = 0 ; i < levelOfDivision ; ++i )
        {
           objMesh.subdivideByLoop();
           std::cout << "Subdivided the mesh " << i+1 << " time" << std::endl ;
        }

        objMesh.setSubdivisonLevel(levelOfDivision);
    }

    else if( keyevent->key() == Qt::Key_X )
    {
        objMesh.getControlMeshVertexList()[objMesh.getSelectedControlMeshIndex()].Y() += 1;
        objMesh.getControlMeshVertexList()[objMesh.getSelectedControlMeshIndex()].modified();

        objMesh.reset();
        objPLYParser.startParsing(objPLYParser.getParsedFilePath());
        objPLYParser.updateMetaInformation();

        for( int i = 0 ; i < objMesh.getControlMeshVertexList().size() ; ++ i )
        {
            if( objMesh.getControlMeshVertexList()[i].isModified() )
                objMesh.getVertexList()[i].Y() = objMesh.getControlMeshVertexList()[i].Y() ;
        }

        unsigned int levelOfDivision = objMesh.getSubdivisonLevel() ;

        for( int i = 0 ; i < levelOfDivision ; ++i )
        {
           objMesh.subdivideByLoop();
           std::cout << "Subdivided the mesh " << i+1 << " time" << std::endl ;
        }

        objMesh.setSubdivisonLevel(levelOfDivision);
    }



    glDraw();
    update();
}

void GLRenderer::initShaders()
{
    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QGLShader::Vertex, "./vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QGLShader::Fragment, "./fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");
}

void GLRenderer::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
