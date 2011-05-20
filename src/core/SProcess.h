#pragma once
#include "STime.h"
#include "SMessage.h"
#include <list>
#include <vector>

class SMessage;
class STime;

class SProcess;
struct MessageMail
{
	std::vector<SProcess*> pToProcs; //to all or 
	STime tschTime;
	SMessage msendMsg;		
	SProcess* pFromProc;

	struct Timeless
	{
		bool operator()(const MessageMail& m1, const MessageMail& m2)
		{
			return m1.tschTime < m2.tschTime;
		}
	};
	struct ProcEqual
	{
		ProcEqual(SProcess* pProc):mpProc(pProc){}
		bool operator()(const MessageMail& m1)const
		{
			return m1.pFromProc == mpProc;
		}
		SProcess* mpProc;
	};
};

//simulation process
class SProcess
{
public:
	virtual void receive(const MessageMail& mail);
	void post(const MessageMail& mail);
};

//////////////////////////////////////////////////////////////////////////
class STickTimer : public SProcess
{
public:
	virtual void receive(const MessageMail& mail)
	{
		//only accept self mail
		if(mail.pFromProc==this)
		{
			MessageMail nextMail;
			nextMail.pFromProc = this;
			nextMail.pToProcs = mListeners;
			nextMail.tschTime = mail.tschTime + m_interval;
			post(nextMail);
		}
	}
	std::vector<SProcess*> mListeners;
	STime m_interval;
};

//////////////////////////////////////////////////////////////////////////
class SEngine
{
public:
	//dispatch all mail to the process
	void dispatchMail();
	void addMail(const MessageMail& mail);
	void discardProcMail(SProcess* pProc);
	
protected: 
	typedef std::list<MessageMail> MailList;
	MailList mMailPool;	
	STime mSystime;
	STickTimer mTickTimer;
};