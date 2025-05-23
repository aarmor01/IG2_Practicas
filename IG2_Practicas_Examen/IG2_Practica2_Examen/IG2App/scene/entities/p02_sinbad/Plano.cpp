#include "Plano.h"

Plano::Plano(SceneNode* node, const String& name, const Plane& plane,
	Real width, Real height,
	int xsegments, int ysegments,
	bool normals, unsigned short numTexCoordSets,
	Real uTile, Real vTile, const Vector3& upVector,
	HardwareBuffer::Usage vertexBufferUsage,
	HardwareBuffer::Usage indexBufferUsage,
	bool vertexShadowBuffer, bool indexShadowBuffer) : EntityIG(node, ""), triggered(false), pName(name)
{
	MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		width, height, xsegments, ysegments, normals, numTexCoordSets, uTile, vTile, upVector,
		vertexBufferUsage, indexBufferUsage, vertexShadowBuffer, indexShadowBuffer);

	planeM = mSM->createEntity(name);
	setMaterialName("Practica1/White");
	mNode->attachObject(planeM);

	myTimer = new Timer();
}

Plano::~Plano()
{
	delete movablePlane;
	movablePlane = nullptr;
}

void Plano::frameRendered(const Ogre::FrameEvent& evt)
{
	if (triggered && myTimer->getMilliseconds() > 5000)
	{
		setMaterialName("Practica1/BeachStones");
		triggered = false;
	}
}

void Plano::setMaterialName(String materialName)
{
	planeM->setMaterialName(materialName);
}

void Plano::setReflejo(Camera* cam, int width, int height)
{
	// Configuramos el plano sobre el que se quiere el reflejo - espejo con la
	// misma orientacion que la malla de la entidad
	movablePlane = new MovablePlane(Vector3::UNIT_Y, 0);
	mNode->attachObject(movablePlane);

	// Configuramos la camara para el reflejo-espejo sobre el plano
	cam->enableReflection(movablePlane);
	cam->enableCustomNearClipPlane(movablePlane);

	//Anyadimos una textura, en el mismo grupo de recursos que la malla
	//del reflejo - espejo, para usarla de RenderTarget y de textura del
	//reflejo - espejo
	TexturePtr rttTex = TextureManager::getSingleton().createManual("textReflejo",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D,
		width, height, 0, PF_R8G8B8, TU_RENDERTARGET);

	// Anyadimos un puerto de vista al RenderTarget con la nueva camara
	RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
	Viewport* viewPort = renderTexture->addViewport(cam);
	viewPort->setClearEveryFrame(true);
	viewPort->setBackgroundColour(ColourValue::Black); //En las diapositivas pone Black pero con White se ve mejor      

	// Anyadimos la nueva unidad de textura al material del reflejo-espejo
	TextureUnitState* tu =
		planeM->getSubEntities()[0]->getMaterial()->getTechniques()[0]->getPasses()[0]->createTextureUnitState("textReflejo");
	tu->setColourOperation(LBO_ADD);
	tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
	tu->setProjectiveTexturing(true, cam);

	// Y anyadir al objeto de observador del RenderTarget
	renderTexture->addListener(this);
}

void Plano::setEspejo(Camera* cam, int width, int height)
{
	// Configuramos el plano sobre el que se quiere el reflejo - espejo con la
	// misma orientacion que la malla de la entidad
	movablePlane = new MovablePlane(Vector3::UNIT_Y, 0);
	mNode->attachObject(movablePlane);

	// Configuramos la camara para el reflejo-espejo sobre el plano
	cam->enableReflection(movablePlane);
	cam->enableCustomNearClipPlane(movablePlane);

	//Anyadimos una textura, en el mismo grupo de recursos que la malla
	//del reflejo - espejo, para usarla de RenderTarget y de textura del
	//reflejo - espejo
	TexturePtr rttTex = TextureManager::getSingleton().createManual("textEspejo",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D,
		width, height, 0, PF_R8G8B8, TU_RENDERTARGET);

	// Anyadimos un puerto de vista al RenderTarget con la nueva camara
	RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
	Viewport* viewPort = renderTexture->addViewport(cam);
	viewPort->setClearEveryFrame(true);
	viewPort->setBackgroundColour(ColourValue::Black); //En las diapositivas pone Black pero con White se ve mejor      

	// Anyadimos la nueva unidad de textura al material del reflejo-espejo
	TextureUnitState* tu =
		planeM->getSubEntities()[0]->getMaterial()->getTechniques()[0]->getPasses()[0]->createTextureUnitState("textEspejo");
	tu->setColourOperation(LBO_REPLACE);
	tu->setTextureAddressingMode(TextureUnitState::TAM_WRAP);
	tu->setProjectiveTexturing(true, cam);

	// Y anyadir al objeto de observador del RenderTarget
	renderTexture->addListener(this);
}

// nos avisa antes del renderizado
void Plano::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) {
	planeM->setVisible(false);
	movablePlane->setVisible(false);
	sendEvent({ PRE_REFLECTION }, this);
}

// nos avisa despues del renderizado
void Plano::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) {
	planeM->setVisible(true);
	movablePlane->setVisible(true);
	sendEvent({ POST_REFLECTION }, this);
}

void Plano::receiveEvent(Message message, EntityIG* entidad)
{
	if (message.id_ == BOMB && pName == "mPlaneWater")
	{
		triggered = true;
		myTimer->reset();
	}
}

inline bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return true;
}
