#include  "../../src/core/Units.h"
#include "../../src/core/SProcess.h"

class SAirflight : public SAgent
{
public:
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{

	}

};


class SPassenger : public SAgent
{
public:
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{

	}

};

class SServiceVehicle : public SAgent
{
public:
	virtual void OnMsg(SAgent* pFrom, const SMessage& msg)
	{

	}

};
//
class SServiceProcess
{
public:

};

class SAirTrafficController : public SAgent
{
public:


};

//runways
class SRunwaysInAirport
{
public:
	
};
//taxiways
class STaxiwaysInAirport
{

};

//stands
class SStandsInAirport
{

};

//Airport
class SAirport
{
public:
};


int main()
{
	STickTimer timer;
	timer.Start(STime());

	
	

	SEngine::GetInstance().Loop();
}