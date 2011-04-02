#pragma once
#include <OgrePrerequisites.h>

#define BEGIN_NAMESPACE_OGRELITE namespace Ogre{ namespace OgreLite{
#define END_NAMESPACE_OGRELITE } }



BEGIN_NAMESPACE_OGRELITE
template<class T> 
class Share_Ptr
{

};


template<class T>
class ObjectPool
{
public:
	
protected:
	typedef Share_Ptr<T> pointer_type;
	HashMap<String, pointer_type> m_map;

	
};




END_NAMESPACE_OGRELITE