#include  "../../src/core/Units.h"
#include "../../src/core/SProcess.h"



class SPassenger : public SAgent
{
public:
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{

	}

};

//words between check in service and the client
enum emCheckInMsgAtom
{
	//client
	_arrivalAtServer,
	
	//server
	_endService,
};
class SCheckInServer : public SAgent
{
public:

	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{
		
		{
			
		}

	}
	//in going process 
	class SCheckInSVCProcess : public  SAgent
	{
	public:
		SPassenger* pClient;

	};
	std::vector<SCheckInSVCProcess*> m_svcProcs;


	int nMaxSvc;
};


class SAirport : public SAgent
{
public:
	

	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{
		if(pFrom==this)
		{
			switch(msg.m_msgAtom)
			{
			case GenNextPax:
				{
						
				}
				break;
			default:
				NULL;
			}
		}
	}
	
};




int main()
{
	STickTimer timer;
	timer.Start(STime());

	
	

	SEngine::GetInstance().Loop();
}