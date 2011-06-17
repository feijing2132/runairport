#pragma once
#include "STime.h"
#include "SMessage.h"
#include <list>
#include <vector>

class SMessage;
class STime;

class SAgent;
class SProcess;

//in simulation an agent  is the object that can  communicate with each other by  send time msg

class SAgent
{
public:	
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg){}
public:
	void ClearOutBox(){ m_outBox.clear(); }
	void AddOutMsg(const SMessage& s);
	
	void AddListener(SAgent* pF);
	void RemoveListener(SAgent* pF);

	void _outMsgLoop(const STime& t);
protected:
	void _sendMsgout(const SMessage& s);
	void _loop();
	//message out box;
	std::list<SMessage> m_outBox;
	std::vector<SAgent*> m_listeners;

	SAgent(){}
};




//////////////////////////////////////////////////////////////////////////
//two kinds events 
class SEngine
{
public:	
	void Loop();	

	static SEngine& GetInstance();
	const STime& getCurrentTime()const{ return mSystime; }
	void AddAgentEvent(SAgent* pAgent, const STime& t);

protected: 
	struct SAgentEvent
	{
		STime m_time;
		SAgent* m_pAgent;				
	};
	struct SameAgentEvent
	{
		SameAgentEvent(SAgent* pAgent):mpAgent(pAgent){}
		bool operator()(const SAgentEvent& evt)
		{
			return mpAgent == evt.m_pAgent;
		}
		SAgent* mpAgent;
	};
	struct EventTimeLess
	{
		bool operator()(const SAgentEvent& evt1, const SAgentEvent& evt2)const
		{
			return evt1.m_time < evt2.m_time;
		}
	};

	typedef std::list<SAgentEvent> EventList;
	EventList mEventsPool;	
	STime mSystime;
};