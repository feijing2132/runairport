#include  "../../src/core/Units.h"
#include "../../src/core/SProcess.h"




class SPassenger : public SAgent
{
public:
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{
		if( typeid(msg)== typeid(Msg_SvcEnd) )
		{
			Msg_PaxLeaveAirport msg_leave;
			msg_leave.m_tSendTime = msg.m_tSendTime;
			AddOutMsg(msg_leave);
		}
	}

};


//words between check in service and the client

class SCheckInServer : public SAgent
{
public:

	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{
		if(typeid(*pFrom) == typeid(SPassenger) ) //passenger 
		{
			SPassenger* pPax = (SPassenger*)pFrom;
			if( typeid(msg) == typeid(Msg_RequestSvc) )  //request service
			{
				if(!svcFull())
				{
					startSvcProc(pPax,msg.m_tSendTime);
				}
				else    //tell him to wait
				{
					Msg_WaitForSvc msg_wait;
					msg_wait.m_tSendTime = msg.m_tSendTime;
					msg_wait.m_dest.push_back(pPax);
					AddOutMsg(msg_wait);
				}
			}
			
		}

		if(typeid(*pFrom)==typeid(SCheckInSVCProcess))  //svc process end
		{
			//tell pax 
			SCheckInSVCProcess* pProc = (SCheckInSVCProcess*)pFrom;
			Msg_SvcEnd svc_end;
			svc_end.m_tSendTime = msg.m_tSendTime;
			svc_end.m_dest.push_back(pProc->m_pClient);
			AddOutMsg(svc_end);
			
			OnSvcEnd(pProc);
		}
	}
	//in going process 
	class SCheckInSVCProcess : public  SAgent
	{
	public:
		SCheckInSVCProcess(SCheckInServer* pSrv, SPassenger* p,const STime& st):m_pClient(p),m_pSrv(pSrv)
		{
			m_startT = st;
			Msg_SvcEnd svc_end;
			svc_end.m_dest.push_back(pSrv);			
			svc_end.m_tSendTime = m_startT + STime(10);
			AddOutMsg(svc_end);			
		}
		SPassenger* m_pClient;
		SCheckInServer* m_pSrv; 

		STime m_startT;
		
	};

	bool svcFull()const{ return (int)m_svcProcs.size()>=nMaxSvc; }
	int startSvcProc(SPassenger* pAgent, const STime& t)
	{
		SCheckInSVCProcess* pSvcProc = new SCheckInSVCProcess(this, pAgent,t);
		m_svcProcs.push_back(pSvcProc);
	}
	void OnSvcEnd(SCheckInSVCProcess* proc)
	{
		std::vector<SCheckInSVCProcess*>::iterator itr= std::find(m_svcProcs.begin(),m_svcProcs.end(),proc);
		m_svcProcs.erase(itr);
	}
	
	std::vector<SCheckInSVCProcess*> m_svcProcs;
	int nMaxSvc;
};


struct Msg_GenPax : public SMessage
{

};

class SAirport : public SAgent
{
public:
	void Init(const STime& t1, const STime& t2)
	{
		for(int i=0;i<100;i++)
		{
			m_GenSchedule.push_back( t1 + (t2-t1).random() );
		}
		std::sort(m_GenSchedule.begin(),m_GenSchedule.end());	
	}
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{
		if( pFrom == this && typeid(msg) == typeid(Msg_GenPax) )
		{
			GenPax();
		}
	}

	void LoopGenPax()
	{
		if( m_nGeneratedPax< m_GenSchedule.size() )
		{
			STime nextT = m_GenSchedule[m_nGeneratedPax];
			Msg_GenPax genPax;
			genPax.m_tSendTime = nextT;
			genPax.m_dest.push_back(this);
			AddOutMsg(genPax);
		}
	}
	void GenPax()
	{
		SPassenger * pPax = new SPassenger;
		pPax->
	}


	int m_nGeneratedPax;
	std::vector<STime> m_GenSchedule;
	
};




int main()
{

	
	

	SEngine::GetInstance().Loop();
}