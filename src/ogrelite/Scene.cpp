#include "Scene.h"

BEGIN_NAMESPACE_OGRELITE
Scene::Scene(void)
{
	pRoot = new SceneNode(this);
}




Scene::~Scene(void)
{
}

SceneNode* Scene::createSceneNode()
{
	SceneNode* sn = new SceneNode(this);
	assert(mSceneNodes.find(sn->getName()) == mSceneNodes.end());
	mSceneNodes[sn->getName()] = sn;
	return sn;
}

SceneNode* Scene::createSceneNode( const String& name )
{
	SceneNodeMapType::iterator itrFind = mSceneNodes.find(name);
	if ( itrFind != mSceneNodes.end())
	{		
		SceneNodeInstPtr& instPtr = itrFind->second;
		if( instPtr.is_refed() )
		{
			OGRE_EXCEPT(
			Exception::ERR_DUPLICATE_ITEM,
			"A scene node with the name " + name + " already exists",
			"SceneManager::createSceneNode" );
		}
	}

	SceneNode* sn = new SceneNode(this,name);
	mSceneNodes[sn->getName()] = sn;
	return sn;
}

END_NAMESPACE_OGRELITE
