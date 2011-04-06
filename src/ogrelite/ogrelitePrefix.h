#pragma once
#include <OgrePrerequisites.h>
//#include <boost/shared_ptr.hpp>

#define BEGIN_NAMESPACE_OGRELITE namespace Ogre{ namespace OgreLite{
#define END_NAMESPACE_OGRELITE } }



BEGIN_NAMESPACE_OGRELITE
	class Properties
	{
	public:
		void set(const String& sKey, const String& sValue);
		bool get(const String& sKey, String& sValue)const;
	protected:
		std::map<String,String> mMap;
	};

	class TextureProperties
	{
	public:

	};
END_NAMESPACE_OGRELITE