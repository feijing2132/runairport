#pragma once

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

	explicit s_ptr(T* ptr):phandle(0)
	{
		if(ptr){ phandle = new shared_count_handle(ptr); }
	}

	T* get()const{ return (T*)( phandle?phandle->ptr:0); }

	inline bool isValid()const{ return phandle?phandle->ptr:false; }
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
	bool is_refed()const{ return phandle?phandle->nref!=0:false; }

	shared_count_handle* phandle;	

protected:
	s_ptr():phandle(0){}
	//inline bool is_trash()const{ return pref?(!pref->nown && !pref->nref):false; }
public:
	inline void own(){ if(phandle){ ++phandle->nown; } }
	inline void ref(){ if(phandle){ ++phandle->nref;} }


	inline void unown()
	{ 
		if(phandle){ 
			--phandle->nown;
			if(!phandle->nown) //no more ownership, destory it
			{				
				destoryObj();	
				if(!phandle->nref)
				{
					destory();
				}
			}
		}		
	}
	inline void unref(){ 
		if(phandle){
			--phandle->nref;
			if(!phandle->nref) //no more reference
			{
				if(!phandle->nown)
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
		std::swap( (T*&)phandle->ptr,ptmp);
		delete ptmp;		
	}
	void destory()
	{
		shared_count_handle* preftmp = 0;
		std::swap(phandle,preftmp);
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
		phandle = other.phandle;
		own();
		tmp.unown();		
	}
	void operator=(inst_ptr& other)
	{ 		
		s_ptr<T> tmp = *this;
		phandle = other.phandle;		
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
		phandle = other.phandle;
		ref();
		tmp.unref();
	}
	void operator=(s_ptr& other)
	{ 
		s_ptr<T> tmp = *this;
		phandle = other.phandle;		
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


