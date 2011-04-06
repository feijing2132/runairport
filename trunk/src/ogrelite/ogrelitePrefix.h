#pragma once
#include <OgrePrerequisites.h>
//#include <boost/shared_ptr.hpp>

#define BEGIN_NAMESPACE_OGRELITE namespace Ogre{ namespace OgreLite{
#define END_NAMESPACE_OGRELITE } }



BEGIN_NAMESPACE_OGRELITE
template<class T>
class SharedPtr;

template <class T> 
class InstPtr
{
public:
	typedef SharedPtr<T> shareptr;
	InstPtr():m_ptr(0),nref(0){}
	InstPtr(T* ptr):m_ptr(ptr),nref(0){ }

	~InstPtr()
	{
		if(nref!=0)
		{
			//warning other are reft shi
		}
		delete m_ptr;
		m_ptr = 0;
	}	

	void operator=(T* ptr)
	{ 
		if(nrefcount) throw ; 
	
		delete m_ptr;
		nrefcount = 0;
		m_ptr = ptr;
	}
	void operator=(const InstPtr& other)
	{
		if(nrefcount) throw ; 
		delete m_ptr;
		nrefcount = other.nrefcount;
		m_ptr = other.m_ptr;
	}
	
	int* pn(){ return &nref;}
	T* get(){ return m_ptr; }
protected:
	T * m_ptr;
	int nref;
};










END_NAMESPACE_OGRELITE