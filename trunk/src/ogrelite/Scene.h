#pragma once
#include "ogrelitePrefix.h"
#include "ogreliteptr.h"

#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>

BEGIN_NAMESPACE_OGRELITE
typedef inst_ptr<SceneNode> SceneNodeInstPtr;
typedef inst_ptr<Camera> CameraInstPtr;


class Scene : public SceneManager
{
public:
	Scene(void);
	~Scene(void);

	SceneNode* getRoot(){ return pRoot.get(); }
	virtual SceneNode* createSceneNode();
	virtual SceneNode* createSceneNode(const String& name);
	virtual void destroySceneNode(const String& name){ mSceneNodes[name] = NULL; }

protected:
	//memory manager
	SceneNodeInstPtr pRoot;
	typedef HashMap<String, SceneNodeInstPtr> SceneNodeMapType;
	SceneNodeMapType mSceneNodes;	
	//typedef HashMap<String, CameraInstPtr> CameraMapType;
	//CameraMapType mCameraMap;

	std::map<String, inst_ptr<MovableObjectFactory> > mMovableObjCollectionMap;
};

END_NAMESPACE_OGRELITE