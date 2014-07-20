#ifndef QUATERNIONS_H
#define QUATERNIONS_H

#include <Quaternions.h>
#include <QMatrix4x4>

class Quaternions
{
public:
    Quaternions();
    void rotateX(int);
    void rotateY(int);
    void rotateZ(int);

    QQuaternion getQuaternion();

private:

    QQuaternion rotation;
    QMatrix4x4 projection;
};

#endif // QUATERNIONS_H
