#pragma once
#include "STime.h"
#include "SMessage.h"
#include <list>
#include <vector>

class SMessage;
class STime;

class SAgent;
class SProcess;

//simulation process
class SAgent
{
public:	
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)=0;
public:
	void ClearOutBox(){ m_outBox.clear(); }
	void AddOutMsg(const SMessage& s);
	
	void AddListener(SAgent* pF);
	void RemoveListener(SAgent* pF);

	void _LoopSendoutMsg(const STime& t);
protected:
	void _sendmsgout(const SMessage& s);
	void _loopEvent();
	//message out box;
	std::list<SMessage> m_outBox;
	std::vector<SAgent*> m_listeners;
};


class SProcess
{
public:
	SProcess(SAgent* pParent):mpParent(pParent){}
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{
			
	}


	SAgent* mpParent;
};

class STickTimer : public SAgent
{
public:
	void Start(const STime& t)
	{
		SMessage startMsg;
		startMsg.m_tSendTime = t;
		startMsg.m_dest.push_back(this);
		AddOutMsg(startMsg);
	}
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{
		if(pFrom!=this)
			return;
		SMessage newMsg = msg;
		newMsg.m_dest.push_back(this);
		newMsg.m_tSendTime += STime(12.0);
		AddOutMsg(newMsg);
	}
};


//////////////////////////////////////////////////////////////////////////
class SEngine
{
public:	
	void Loop();	

	static SEngine& GetInstance();
	const STime& getCurrentTime()const{ return mSystime; }
	void AddAgentEvent(SAgent* pAgent, const STime& t);

protected: 
	struct SEvent
	{
		STime m_time;
		SAgent* m_pAgent;				
	};
	struct SameAgentEvent
	{
		SameAgentEvent(SAgent* pAgent):mpAgent(pAgent){}
		bool operator()(const SEvent& evt)
		{
			return mpAgent == evt.m_pAgent;
		}
		SAgent* mpAgent;
	};
	struct EventTimeLess
	{
		bool operator()(const SEvent& evt1, const SEvent& evt2)const
		{
			return evt1.m_time < evt2.m_time;
		}
	};

	typedef std::list<SEvent> EventList;
	EventList mEventsPool;	
	STime mSystime;
};