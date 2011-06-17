#include  "../../src/core/Units.h"
#include "../../src/core/SProcess.h"



class SPassenger : public SAgent
{
public:
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{

	}

};


struct Msg_RequestSvc : public SMessage
{

};
struct Msg_WaitForSvc : public SMessage
{

};
struct  Msg_SvcEnd : public SMessage
{

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
			OnSvcEnd((SCheckInSVCProcess*)pFrom);
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


class SAirport 
{
public:
	
	
};




int main()
{

	
	

	SEngine::GetInstance().Loop();
}