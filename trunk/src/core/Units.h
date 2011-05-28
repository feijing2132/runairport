#pragma once


#include <boost/units/systems/si.hpp>
#include <boost/units/base_units/us/foot.hpp>

namespace boost
{
	
	namespace units
	{
	
		typedef derived_dimension<length_base_dimension,2>::type  area_dimension;
	typedef derived_dimension<mass_base_dimension,1,
		length_base_dimension,2,
			time_base_dimension,-2>::type   energy_dimension;
	
		

		namespace si
		{
			typedef unit<area_dimension,system>     area;
			typedef unit<energy_dimension,system>   energy;

		}
	}
}

namespace ark
{

	class Units //units system base on si system
	{
	public:
		static const boost::units::si::length& meter;//= boost::units::si::meter;
		static const boost::units::si::mass& kilogram;// = boost::units::si::kilogram;

		//typedef make_scaled_unit<si::time, scale<10, static_rational<-9> > >::type nanosecond;

		typedef boost::units::quantity<boost::units::si::dimensionless> Value;
		typedef boost::units::quantity<boost::units::si::length> Length; //length in meter;
		typedef boost::units::quantity<boost::units::si::mass> Mass; //mass in kg
		typedef boost::units::quantity<boost::units::si::time> Time; //time in seconds;

		typedef boost::units::quantity<boost::units::si::area> Area;
		typedef boost::units::quantity<boost::units::si::energy> Energy;	


		static const Length centimeter;
		
		
		static void Test( void );

	};
}


namespace ark
{
	namespace U
	{
		template <long N>
		struct base_dim
		{

		};

		typedef base_dim<0> length_dim;
		typedef base_dim<1> mass_dim;

		template<class D, long N> 
		struct base_unit
		{
			
		};
		
		typedef base_unit<length_dim,0> meter;
		typedef base_unit<length_dim,1> feet;

		typedef base_unit<mass_dim,0> kg;
		typedef base_unit<mass_dim,1> g;




		typedef boost::units::make_system< meter, kg > system;
		
		template<class T, class S>
		struct convert_worker
		{
			
		};

	}
}


//#include <boost/mpl/vector_c.hpp>
//#include <boost/mpl/equal_to.hpp>
//#include <boost/mpl/comparison.hpp>
//
//namespace ark
//{
//
//	typedef boost::mpl::vector_c<int,1,0,0,0,0,0,0,0> mass;
//	typedef boost::mpl::vector_c<int,0,1,0,0,0,0,0,0> length; // ªÚ « position 
//	typedef boost::mpl::vector_c<int,0,0,1,0,0,0,0,0> time;
//	typedef boost::mpl::vector_c<int,0,0,0,1,0,0,0,0> charge;
//	typedef boost::mpl::vector_c<int,0,0,0,0,1,0,0,0> temperature;
//	typedef boost::mpl::vector_c<int,0,0,0,0,0,1,0,0> intensity;
//	typedef boost::mpl::vector_c<int,0,0,0,0,0,0,1,0> angle;
//	typedef boost::mpl::vector_c<int,0,0,0,0,0,0,0,1> currency;
//
//
//	template<class Dim, long N>
//	struct base_unit
//	{
//		typedef Dim dimension;
//	};
//	
//	typedef base_unit<length,0> meter;
//	typedef base_unit<length,1> feet;
//
//	template<long U1, long U2>
//	struct factor
//	{
//		static double f(){ return 1.0; }
//	};
//
//	template< class U1, long N>
//	struct scale_factor
//	{
//		
//	}
//	
//		
//	
//
//	struct plus_f
//	{
//		template <class T1, class T2>
//		struct apply
//		{
//			typedef typename boost::mpl::plus<T1,T2>::type type;
//		};
//	};
//
//	template<long Dim,long Type>
//	struct base_unit
//	{
//
//	};
//	
//	template<class BaseU, long N, 0>
//	struct unit
//	{
//		
//	};
//
//	template<class Unit>
//	struct unit
//	{
//
//	};
//
//}


