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
};

//simulation process
class SProcess
{
public:
	virtual void receive(const MessageMail& mail);
	void post(const MessageMail& mail);
};

class STickTimer : public SProcess
{
public:
	virtual void receive(const MessageMail& mail)
	{
		MessageMail next
		post(mail.tschTime+m_interval);
	}
	std::vector<SProcess*> 
	STime m_interval;
};


class SEngine
{
public:
	//dispatch all mail to the process
	void dispatchMail();
	void addMail(const MessageMail& mail);
	
protected: 
	typedef std::list<MessageMail> MailList;
	MailList mMailPool;	
	STime mSystime;
};