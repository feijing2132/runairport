#pragma once
#include <stdlib.h>

class STime
{
public:
	STime():m_nanosecond(0){  }
	STime(double sec):m_nanosecond(  static_cast<long>(sec*1000) ){}

	bool operator==(const STime& tother)const
	{
		return m_nanosecond == tother.m_nanosecond;
	}
	bool operator<(const STime& tother)const
	{
		return m_nanosecond<tother.m_nanosecond;
	}
	STime operator+(const STime& t)const{
		STime tret = *this;
		return tret+=t;
	}
	STime operator-(const STime& t)const
	{
		STime tret = *this;
		return tret-=t;
	}
	STime& operator+=(const STime& t)
	{
		m_nanosecond+=t.m_nanosecond;
		return *this;
	}

	STime& operator-=(const STime& t)
	{
		m_nanosecond-=t.m_nanosecond;
		return *this;
	}

	long m_nanosecond;

	STime random()const
	{
		if(m_nanosecond>0)
		{
			return STime(rand()%m_nanosecond);
		}
		return STime(0);
	}
};

