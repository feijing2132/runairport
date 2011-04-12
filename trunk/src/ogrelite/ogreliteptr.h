#pragma once
#include "ogrelitePrefix.h"

BEGIN_NAMESPACE_OGRELITE
//////////////////////////////////////////////////////////////////////////

typedef long count_type;
template <class T> 
class inst_ptr
{
public:	
	inst_ptr():m_ptr(0),nref(0){}
	//inst_ptr(T* ptr):m_ptr(ptr),nref(0){ }

	~inst_ptr()
	{
		if(nref!=0)
		{
			//warning other  ref this object
			//assert(false);
		}
		destory();
	}	

	void operator=(T* ptr)
	{ 
		if(nref!=0)
			throw  ; 
		
		destory();
		nref = 0;
		m_ptr = ptr;
	}	

	T & operator*() const  // never throws
	{
		//BOOST_ASSERT(px != 0);
		return *m_ptr;
	}

	T * operator->() const  // never throws
	{
		//BOOST_ASSERT(px != 0);
		return m_ptr;
	}

	bool isValid()const{ return m_ptr!=0; }
	bool isInRef()const{ return nref!=0; }
	count_type* pn(){ return &nref;}
	T* get()const{ return m_ptr; }

	inline void destory()
	{
		T* ptmp= m_ptr;
		m_ptr = 0;
		delete ptmp;
	}
protected:
	T * m_ptr;
	count_type nref;

private:
	void operator=(const inst_ptr& other){ assert(false);}
	
};




//////////////////////////////////////////////////////////////////////////

//class sharedcount
//{
//public:
//	sharedcount():pn(0){}
//	explicit sharedcount(count_type* _pn):pn(_pn){ ++(*pn); }
//	explicit sharedcount(const sharedcount& other):pn(other.pn){  ++(*pn); }
//	void operator=(const sharedcount& r)
//	{
//		count_type * tmp = r.pn;
//		if( tmp != pn )
//		{
//			if( tmp != 0 ) ++(*tmp);
//			if( pn != 0 ) --(*pn);
//			pn = tmp;
//		}
//
//	}
//	~sharedcount(){ --(*pn); }
//
//protected:
//	count_type* pn;
//};

template<class T> class nodelete_shared_ptr
{	
public:
	typedef T element_type;
	typedef T value_type;

	nodelete_shared_ptr(inst_ptr<T> & r):px(r.get()),pn(r.pn())
	{ 
		++*pn;
	} 

	nodelete_shared_ptr(nodelete_shared_ptr const & r): px(r.px),pn(r.pn)  // never throws
	{		
		++*pn;
	}
	~nodelete_shared_ptr(){
		--*pn;
		px = 0;
	}
	nodelete_shared_ptr & operator=(nodelete_shared_ptr const & r)
	{
		nodelete_shared_ptr(r).swap(*this);
		return *this;
	}

	void reset(T * p = 0)
	{
		//BOOST_ASSERT(p == 0 || p != px);
		nodelete_shared_ptr(p).swap(*this);
	}

	T & operator*() const  // never throws
	{
		//BOOST_ASSERT(px != 0);
		return *px;
	}

	T * operator->() const  // never throws
	{
		//BOOST_ASSERT(px != 0);
		return px;
	}

	T * get() const  // never throws
	{
		return px;
	}

	long use_count() const  // never throws
	{
		return *pn;
	}

	bool unique() const  // never throws
	{
		return *pn == 1;
	}

	void swap(nodelete_shared_ptr<T> & other)  // never throws
	{
		std::swap(px, other.px);
		std::swap(pn, other.pn);
	}

private:

	T * px;            // contained pointer
	count_type* pn;   // ptr to reference counter
};

template<class T, class U> inline bool operator==(nodelete_shared_ptr<T> const & a, nodelete_shared_ptr<U> const & b)
{
	return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(nodelete_shared_ptr<T> const & a, nodelete_shared_ptr<U> const & b)
{
	return a.get() != b.get();
}

template<class T> inline bool operator<(nodelete_shared_ptr<T> const & a, nodelete_shared_ptr<T> const & b)
{
	return std::less<T*>()(a.get(), b.get());
}

template<class T> void swap(nodelete_shared_ptr<T> & a, nodelete_shared_ptr<T> & b)
{
	a.swap(b);
}

// get_pointer() enables boost::mem_fn to recognize shared_ptr

template<class T> inline T * get_pointer(nodelete_shared_ptr<T> const & p)
{
	return p.get();
}

END_NAMESPACE_OGRELITE
