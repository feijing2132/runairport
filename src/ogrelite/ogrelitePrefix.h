#pragma once
#include <OgrePrerequisites.h>
//#include <boost/shared_ptr.hpp>

#define BEGIN_NAMESPACE_OGRELITE namespace Ogre{ namespace OgreLite{
#define END_NAMESPACE_OGRELITE } }



BEGIN_NAMESPACE_OGRELITE
	class NameValueMap
	{
	public:
		void set(const String& sKey, const String& sValue);
		void set(const String& sKey, int iValue);
		void set(const String& sKey, const double& dValue);
		

		bool get(const String& sKey, String& sValue)const;
		bool get(const String& sKey, int& iValue)const;
		bool get(const String& sKey, double& dValue)const;

	protected:
		std::map<String,String> mMap;
	};	
END_NAMESPACE_OGRELITE