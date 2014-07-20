#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE
class GLRenderer;


class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    GLRenderer *glWidget;

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QSlider *createSlider();

    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
};

#endif
