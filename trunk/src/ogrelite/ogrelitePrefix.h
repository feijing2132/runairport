#pragma once
#include <OgrePrerequisites.h>
//#include <boost/shared_ptr.hpp>
#include <OgreCommon.h>
#include <OgreStringConverter.h>
#define BEGIN_NAMESPACE_OGRELITE namespace Ogre{ namespace OgreLite{
#define END_NAMESPACE_OGRELITE } }



BEGIN_NAMESPACE_OGRELITE
	class RenderProcess;
	class NameValueMap 
	{
	public:
		NameValueMap(){}
		NameValueMap(const NameValuePairList& other){  mMap = other; }
		void set(const String& sKey, const String& sValue){  mMap[sKey] = sValue; }
		
		template<class T>
		void set(const String& sKey, const T& tValue){ mMap[sKey] = StringConverter::toString(tValue); }
	
		

		bool get(const String& sKey, String& sValue)const
		{
			NameValuePairList::const_iterator itrFind = mMap.find(sKey);				
			if( itrFind !=mMap.end())
			{
				sValue = itrFind->second;
				return true;
			}
			return false;
		}
		bool get(const String& sKey, int& iValue)const
		{
			String sValue;
			if(get(sKey,sValue))
			{
				iValue = StringConverter::parseInt(sValue);
				return true;
			}
			return false;
		}
		

	public:
		NameValuePairList mMap;
	};	


	class IRenderCanvas;
	class IRenderEngine;
END_NAMESPACE_OGRELITE