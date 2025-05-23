#ifndef PLANO_H_
#define PLANO_H_

#include <OgreTimer.h>

#include "../EntityIG.h"

class Plano : public EntityIG
{
private:
    Entity* planeM;
    Ogre::Timer* myTimer;
    bool triggered;

public:
    Plano(SceneNode* node, const String& name, const Plane& plane,
        Real width, Real height,
        int xsegments = 1, int ysegments = 1,
        bool normals = true, unsigned short numTexCoordSets = 1,
        Real uTile = 1.0f, Real vTile = 1.0f, const Vector3& upVector = Vector3::UNIT_Y,
        HardwareBuffer::Usage vertexBufferUsage = HardwareBuffer::HBU_STATIC_WRITE_ONLY,
        HardwareBuffer::Usage indexBufferUsage = HardwareBuffer::HBU_STATIC_WRITE_ONLY,
        bool vertexShadowBuffer = false, bool indexShadowBuffer = false);

    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual void receiveEvent(Message message, EntityIG* entidad);

    void setMaterialName(String materialName);

protected:
    virtual inline bool keyPressed(const OgreBites::KeyboardEvent& evt);
};
#endif