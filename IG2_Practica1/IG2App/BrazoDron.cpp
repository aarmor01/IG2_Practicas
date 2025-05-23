#include "BrazoDron.h"

BrazoDron::BrazoDron(SceneNode* node, int nAspas, double rotation) : EntityIG(node)
{
	//Creacion
	mSphereNode = mNode->createChildSceneNode();
	mBrazosNode = mNode->createChildSceneNode();

	mSphereNode->attachObject(mSM->createEntity("Barrel.mesh"));
	mAspas = new RotorDron(mBrazosNode, nAspas, rotation);

	//Escalas
	float cilindroScale = 16.5f;
	float yScaleMultiplier = 3.0f;
	float dronScale = 0.55f;
	mSphereNode->setScale(cilindroScale, cilindroScale * yScaleMultiplier, cilindroScale);
	mBrazosNode->setScale(dronScale, dronScale, dronScale);

	//Posiciones
	mSphereNode->pitch(Degree(-90));
	mSphereNode->setPosition(0, 0, 250);

	numAspas = nAspas;
}

BrazoDron::~BrazoDron()
{
	delete mAspas;
}

bool BrazoDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mAspas->keyPressed(evt);
	return true;
}