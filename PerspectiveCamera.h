#pragma once

#include "SceneObject.h"
#include <QVector4D>
#include <QColor>

using namespace std;

class PerspectiveCamera : public SceneObject
{
private:

    QVector4D position;
    QVector4D viewDirection;
    QVector4D upVector;
    float focalLength;

    vector<SceneObject*> sceneObjects;

public:
    void draw(const RenderCamera& renderer, const QColor& color = Qt::red, float lineWidth = 1.0f) const override ;
    void affineMap(const QMatrix4x4& matrix) override;

    void setSceneObjects(const vector<SceneObject*> & objects);

    PerspectiveCamera(const QVector4D& position,const QVector4D& viewDir,const QVector4D& up,float focalLength);
    ~PerspectiveCamera() {};
};
