#ifndef BRAZODRON_H_
#define BRAZODRON_H_

#include "EntidadIG.h"
#include "RotorDron.h"

using namespace Ogre;

class BrazoDron : public EntidadIG
{
public:
	BrazoDron(SceneNode* node, int numAspas, double rotation = 2);
	~BrazoDron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	SceneNode* mCilindroNode;
	SceneNode* mRotorNode;
	RotorDron* rotor;

	int numAspas;
};
#endif