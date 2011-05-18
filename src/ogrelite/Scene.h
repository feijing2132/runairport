#pragma once
#include "ogrelitePrefix.h"
#include "../core/s_ptr.h"


BEGIN_NAMESPACE_OGRELITE
typedef inst_ptr<SceneNode> SceneNodeInstPtr;
typedef inst_ptr<Camera> CameraInstPtr;


class Scene
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
	
};

END_NAMESPACE_OGRELITE