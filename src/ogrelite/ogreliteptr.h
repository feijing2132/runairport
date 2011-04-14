#pragma once
#include "ogrelitePrefix.h"

BEGIN_NAMESPACE_OGRELITE
//////////////////////////////////////////////////////////////////////////



typedef long count_type;

template<class T>
class s_ptr
{
public:
	struct shared_count_handle
	{				
		shared_count_handle(void* p):ptr(p),nref(0),nown(0){}	
		count_type nref;
		void* ptr;
		count_type nown;		 
	};

	/*s_ptr(int ptr):pref(new shared_count_handle(ptr)){}*/
	explicit s_ptr(T* ptr):pref(0)
	{
		if(ptr){ pref = new shared_count_handle(ptr); }
	}
	
	T* get()const{ return (T*)( pref?pref->ptr:0); }

	inline bool isValid()const{ return pref?pref->ptr:false; }
	inline bool isNull() const {	return !isValid();	}
	inline bool operator!() const {	return isNull();	}
	inline operator bool() const{	return isValid();	}
	T & operator*() const  // never throws
	{	
		return *get();
	}
	T * operator->() const  // never throws
	{		
		return get();
	}
	bool is_refed()const{ return pref?pref->nref!=0:false; }

	shared_count_handle* pref;	

protected:
	s_ptr():pref(0){}
	//inline bool is_trash()const{ return pref?(!pref->nown && !pref->nref):false; }
public:
	inline void own(){ if(pref){ ++pref->nown; } }
	inline void ref(){ if(pref){ ++pref->nref;} }
	
	
	inline void unown()
	{ 
		if(pref){ 
			--pref->nown;
			if(!pref->nown) //no more ownership, destory it
			{				
				destoryObj();	
				if(!pref->nref)
				{
					destory();
				}
			}
		}		
	}
	inline void unref(){ 
		if(pref){
			--pref->nref;
			if(!pref->nref) //no more reference
			{
				if(!pref->nown)
				{
					destoryObj();
					destory();
				}				
			}
		} 
	}
protected:
	void destoryObj()
	{		
		T* ptmp= 0;		
		std::swap( (T*&)pref->ptr,ptmp);
		delete ptmp;		
	}
	void destory()
	{
		shared_count_handle* preftmp = 0;
		std::swap(pref,preftmp);
		delete preftmp;
	}
};



template <class T> 
class inst_ptr : public s_ptr<T>
{
public:	
	inst_ptr(){}
	explicit inst_ptr(s_ptr& other):s_ptr(other)
	{ 
		own();
	}
	explicit inst_ptr(inst_ptr& other):s_ptr(other)
	{
		own();
	}

	~inst_ptr()
	{
		unown();	
	}	
	
	void operator=(s_ptr& other)
	{ 
		s_ptr<T> tmp = *this;
		pref = other.pref;
		own();
		tmp.unown();		
	}
	void operator=(inst_ptr& other)
	{ 		
		s_ptr<T> tmp = *this;
		pref = other.pref;		
		own();
		tmp.unown();
	}	
	void operator = (T* pt)
	{
		if(pt!=get())
		{			
			s_ptr<T> other(pt);
			*this = other;		
		}
	}
private:	
	

};




//////////////////////////////////////////////////////////////////////////


template<class T> 
class ref_ptr : public s_ptr<T>
{	
public:
	ref_ptr(){}
	ref_ptr(s_ptr& other):s_ptr(other){
		ref();
	}
	ref_ptr(ref_ptr& other):s_ptr(other){
		ref();
	}
	void operator=(ref_ptr& other)
	{ 		
		s_ptr<T> tmp = *this;
		pref = other.pref;
		ref();
		tmp.unref();
	}
	void operator=(s_ptr& other)
	{ 
		s_ptr<T> tmp = *this;
		pref = other.pref;		
		ref();
		tmp.unref();
	}

	void operator = (T* pt)
	{
		if(pt!=get())
		{			
			s_ptr<T> other(pt);
			*this = other;		
		}
	}
	~ref_ptr(){ unref(); }
private:	

};

////template<class T, class U> inline bool operator==(nodelete_shared_ptr<T> const & a, nodelete_shared_ptr<U> const & b)
////{
////	return a.get() == b.get();
////}
////
////template<class T, class U> inline bool operator!=(nodelete_shared_ptr<T> const & a, nodelete_shared_ptr<U> const & b)
////{
////	return a.get() != b.get();
////}
////
////template<class T> inline bool operator<(nodelete_shared_ptr<T> const & a, nodelete_shared_ptr<T> const & b)
////{
////	return std::less<T*>()(a.get(), b.get());
////}
////
////template<class T> void swap(nodelete_shared_ptr<T> & a, nodelete_shared_ptr<T> & b)
////{
////	a.swap(b);
////}
////
////// get_pointer() enables boost::mem_fn to recognize shared_ptr
////
////template<class T> inline T * get_pointer(nodelete_shared_ptr<T> const & p)
////{
////	return p.get();
////}

END_NAMESPACE_OGRELITE
