#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPushButton>
#include "GLRenderer.h"
#include "Window.h"
#include <QFileDialog>
#include "Mesh.h"

QString fileName;
Mesh objMesh;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString fileName = QFileDialog::getOpenFileName(NULL, ("Open File"), "",("Files (*.*)"));
    Window window;
    window.resize(window.sizeHint());
    window.glWidget->objPLYParser.startParsing(fileName.toStdString());
    window.showFullScreen();
    window.glWidget->initShaders();
    return app.exec();
}
