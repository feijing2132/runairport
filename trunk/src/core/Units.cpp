#include ".\units.h"
using namespace ark;



const boost::units::si::length& Units::meter = boost::units::si::meter;

const boost::units::si::mass& Units::kilogram =  boost::units::si::kilogram;



const Units::Length Units::centimeter = 0.01*meter;

void ark::Units::Test( void )
{
	Value n = 1.0;
	Length l = 1.0*centimeter;
	Mass m = 1*kilogram;
	l*m;
	Area a;
	a  = l*l;

	std::cout<<l/m<<std::endl;
}