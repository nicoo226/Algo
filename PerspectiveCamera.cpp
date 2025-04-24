#include "PerspectiveCamera.h"
#include "RenderCamera.h"
#include "Hexahedron.h"

using namespace std;


PerspectiveCamera::PerspectiveCamera(const QVector4D& pos,const QVector4D& viewDir,const QVector4D& up,float focal): position(pos), viewDirection(viewDir.normalized()), upVector(up.normalized()), focalLength(focal)
{
    type = SceneObjectType::ST_PERSPECTIVE_CAMERA;
}

void PerspectiveCamera::draw(const RenderCamera& renderer, const QColor& color, float lineWidth) const
{
    // Kameraachsen
    QVector3D z = viewDirection.toVector3D();
    QVector3D x = QVector3D::crossProduct(z, upVector.toVector3D());
    QVector3D y = upVector.toVector3D();

    // Wichtige Punkte
    QVector3D origin = position.toVector3D();
    QVector3D imageCenter = origin + z * focalLength;

    // Image plane Ecken berechnen
    float planeSize = 5.0;
    QVector3D seite = x * (planeSize / 2);
    QVector3D oben = y * (planeSize / 2);

    QVector3D obenlinks     = imageCenter + oben - seite;
    QVector3D obenrechts    = imageCenter + oben + seite;
    QVector3D untenlinks  = imageCenter - oben - seite;
    QVector3D untenrechts = imageCenter - oben + seite;

    // Achsen zeichnen
    renderer.renderLine(origin, origin - x * 1.0, Qt::red, lineWidth);
    renderer.renderLine(origin, origin + y * 1.0, Qt::green, lineWidth);
    renderer.renderLine(origin, origin + z * 1.0, Qt::blue, lineWidth);

    // Bildfläche zeichnen
    renderer.renderPlane(obenlinks,obenrechts,untenrechts,untenlinks,Qt::red,0.3);
    renderer.renderLine(origin, untenrechts,Qt::red,lineWidth);
    renderer.renderLine(origin, obenrechts,Qt::red,lineWidth);
    renderer.renderLine(origin, obenlinks,Qt::red,lineWidth);
    renderer.renderLine(origin, untenlinks,Qt::red,lineWidth);

    // Center of projection als Punkt
    renderer.renderPoint(origin, color, 15.0);

    // Mitte der Bildebene
    renderer.renderPoint(imageCenter, color, 15.0);


    int count;

    for (const SceneObject* obj : sceneObjects) {

        vector<QVector3D> projectedPoints;

        const Hexahedron* hex = dynamic_cast<const Hexahedron*>(obj);
        count=0;
        if (!hex) continue;

        for (const QVector3D& P : *hex) {
            renderer.renderLine(origin, P, Qt::gray, 1);

            QVector3D RichtungsvektorZuP = P - origin;
            float t = QVector3D::dotProduct(imageCenter - origin, z) / QVector3D::dotProduct(RichtungsvektorZuP, z);
            QVector3D Schnittpunkt = origin + t * RichtungsvektorZuP;

            renderer.renderPoint(Schnittpunkt, Qt::green, 10);
            projectedPoints.push_back(Schnittpunkt);
            count++;


        }
        if(count==8){
            renderer.renderLine(projectedPoints[0], projectedPoints[1], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[1], projectedPoints[2], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[2], projectedPoints[3], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[3], projectedPoints[0], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[3], projectedPoints[7], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[6], projectedPoints[2], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[4], projectedPoints[5], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[5], projectedPoints[6], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[6], projectedPoints[7], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[7], projectedPoints[4], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[0], projectedPoints[4], Qt::yellow, 2.0f);
            renderer.renderLine(projectedPoints[5], projectedPoints[1], Qt::yellow, 2.0f);


        }
    }

}
void PerspectiveCamera::affineMap(const QMatrix4x4& matrix)
{
    position = matrix * position;
    viewDirection = matrix * viewDirection;
    upVector = matrix * upVector;
}

void PerspectiveCamera::setSceneObjects(const vector<SceneObject*>& objects)
{
    sceneObjects = objects;
}
