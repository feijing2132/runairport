#include "SProcess.h"
#include <algorithm>



void SEngine::addMail( const MessageMail& mail )
{
	MailList::iterator itrPos = std::upper_bound(mMailPool.begin(),mMailPool.end(),mail, MessageMail::Timeless() );
	mMailPool.insert(itrPos, mail);
}

void SEngine::dispatchMail()
{
	while(!mMailPool.empty())
	{
		MessageMail curMail = mMailPool.front();
		mMailPool.pop_front();
		for(size_t i=0;i<curMail.pToProcs.size();i++)
		{
			SProcess* pToProc = curMail.pToProcs[i];
			pToProc->receive(curMail);
		}
		mSystime = curMail.tschTime;
	}
}

void SEngine::discardProcMail( SProcess* pProc )
{
	mMailPool.remove_if( MessageMail::ProcEqual(pProc) );
}