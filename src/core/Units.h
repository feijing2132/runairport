#pragma once


#include <boost/units/cmath.hpp>
#include <boost/units/io.hpp>
#include <boost/units/base_dimension.hpp>

namespace boost
{
	namespace units
	{
		struct meter_base_unit : base_unit<meter_base_unit, length_dimension, 1>
		{
			static std::string name()               { return "meter"; }
			static std::string symbol()             { return "m"; }
		};
typedef unit<dimensionless_type,mks_system>      dimensionless;
		struct kilogram_base_unit : base_unit<kilogram_base_unit, mass_dimension, 2> { };
		struct second_base_unit : base_unit<second_base_unit, time_dimension, 3> { };

		BOOST_UNITS_STATIC_CONSTANT()
	}
}

typedef boost::units::quantity<boost::units::meter_base_unit> meters;
typedef boost::units::quantity<boost::units::kilogram_base_unit> kilograms;
typedef boost::units:;quantity<boost::units::second_base_unit> seconds;