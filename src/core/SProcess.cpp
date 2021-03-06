#include "SProcess.h"
#include <algorithm>
#include <iostream>

void SEngine::Loop()
{
	while(!mEventsPool.empty())
	{
		SAgentEvent curEvt = mEventsPool.front();
		mEventsPool.pop_front();
		mSystime = curEvt.m_time;
		//
		curEvt.m_pAgent->_outMsgLoop(mSystime);
	}
}



SEngine& SEngine::GetInstance()
{
	static SEngine inst;
	return inst;
}

//only one agent events in pool

void SEngine::AddAgentEvent( SAgent* pAgent, const STime& t )
{
//EventList::iterator itr = std::remove_if(mEventsPool.begin(),mEventsPool.end(),SameAgentEvent(pAgent) );
//mEventsPool.erase(itr,mEventsPool.end());
	SAgentEvent newEvt;
	newEvt.m_pAgent = pAgent;
	newEvt.m_time = t;

	EventList::iterator itr = std::upper_bound(mEventsPool.begin(),mEventsPool.end(),newEvt,EventTimeLess() );
	mEventsPool.insert(itr,newEvt);

}

void SEngine::sendMsgcall( SAgent* pFrom, SAgent* pTo, const String& msg )
{
	pTo->OnMsg(pFrom,msg);
}



void SAgent::_outMsgLoop(const STime& t) /*loop send message out */
{
	if(!m_outBox.empty())
	{		
		if(t == m_outBox.front().m_tSendTime) //check if the time is match
		{
			SMessage fmsg = m_outBox.front();
			m_outBox.pop_front();
			if(fmsg.m_dest.empty())
			{
				fmsg.m_dest = m_listeners;
			}
			_sendMsgout(fmsg);
		}	
		
		_loop();
	}
}

void SAgent::AddOutMsg( const SMessage& s )
{
	std::list<SMessage>::iterator itr = std::upper_bound(m_outBox.begin(),m_outBox.end(), s, SMessage::TimeLess() );
	bool bLoopEvt = (itr==m_outBox.begin());	
	m_outBox.insert(itr,s);
	if(bLoopEvt)
		_loop();
	
}

//
void SAgent::_sendMsgout( const SMessage& s )
{
	//
	std::cout<<("Message Send Out")<<std::endl;
	for(size_t i=0;i<s.m_dest.size();++i)
	{
		SAgent* pDest = s.m_dest[i];
		SEngine::GetInstance().sendMsgcall(this,pDest,s.m_msg);
	}
}

void SAgent::RemoveListener( SAgent* pF )
{
	std::vector<SAgent*>::iterator itr = std::remove(m_listeners.begin(),m_listeners.end(),pF);
	m_listeners.erase(itr,m_listeners.end());
}

void SAgent::AddListener( SAgent* pF )
{
	std::vector<SAgent*>::iterator itr  = std::find(m_listeners.begin(),m_listeners.end(),pF);
	if(itr==m_listeners.end())
		m_listeners.push_back(pF);
}

void SAgent::_loop()
{
	
}