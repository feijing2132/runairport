#pragma once
#include <vector>
#include <string>
#include "STime.h"
#include <typeinfo>

class SAgent;
class SMessage
{
public:
	STime m_tSendTime;
	std::vector<SAgent*> m_dest; //if m_dest is empty send to followers;	

	struct TimeLess
	{
		bool operator()(const SMessage& msg1, const SMessage& msg2)const
		{
			return msg1.m_tSendTime < msg2.m_tSendTime;
		}
	};
protected:
	SMessage(){}
};



