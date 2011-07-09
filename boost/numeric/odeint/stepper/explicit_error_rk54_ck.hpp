/*
 boost header: NUMERIC_ODEINT_STEPPER/explicit_error_rk54_ck.hpp

 Copyright 2009 Karsten Ahnert
 Copyright 2009 Mario Mulansky
 Copyright 2009 Andre Bergner

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_RK54_CK_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_RK54_CK_HPP_INCLUDED

#include <boost/ref.hpp>
#include <boost/bind.hpp>

#include <boost/numeric/odeint/stepper/base/explicit_stepper_and_error_stepper_base.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/detail/macros.hpp>
#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

namespace boost {
namespace numeric {
namespace odeint {





/*
 * ToDo: Check orders rk_ckc
 */
template<
	class State ,
    class Value = double ,
    class Deriv = State ,
    class Time = double ,
	class Algebra = range_algebra ,
	class Operations = default_operations ,
	class Resizer = initially_resizer
	>
class explicit_error_rk54_ck
: public explicit_stepper_and_error_stepper_base<
	  explicit_error_rk54_ck< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
	  5 , 5 , 4 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
{


public :

	BOOST_ODEINT_EXPLICIT_STEPPERS_AND_ERROR_STEPPERS_TYPEDEFS( explicit_error_rk54_ck , 5 , 5 , 4);

	typedef explicit_error_rk54_ck< State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;


	template< class System , class StateIn , class DerivIn , class StateOut , class Err >
	void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , const time_type &t , StateOut &out , const time_type &dt , Err &xerr )
	{
		const value_type c1 = static_cast<value_type> ( 37.0 ) / static_cast<value_type>( 378.0 );
		const value_type c3 = static_cast<value_type> ( 250.0 ) / static_cast<value_type>( 621.0 );
		const value_type c4 = static_cast<value_type> ( 125.0 ) / static_cast<value_type>( 594.0 );
		const value_type c6 = static_cast<value_type> ( 512.0 ) / static_cast<value_type>( 1771.0 );

		const value_type dc1 = c1 - static_cast<value_type> ( 2825.0 ) / static_cast<value_type>( 27648 );
		const value_type dc3 = c3 - static_cast<value_type> ( 18575.0 ) / static_cast<value_type>( 48384.0 );
		const value_type dc4 = c4 - static_cast<value_type> ( 13525.0 ) / static_cast<value_type>( 55296.0 );
		const value_type dc5 = static_cast<value_type> ( -277.0 ) / static_cast<value_type>( 14336.0 );
		const value_type dc6 = c6 - static_cast<value_type> ( 0.25 );

		do_step_impl( system , in , dxdt , t , out , dt );

		//error estimate
		stepper_base_type::m_algebra.for_each6( xerr , dxdt , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v ,
				typename operations_type::template scale_sum5< time_type , time_type , time_type , time_type , time_type >( dt*dc1 , dt*dc3 , dt*dc4 , dt*dc5 , dt*dc6 ));

	}



	template< class System , class StateIn , class DerivIn , class StateOut >
	void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , const time_type &t , StateOut &out , const time_type &dt )
	{
		const value_type a2 = static_cast<value_type> ( 0.2 );
		const value_type a3 = static_cast<value_type> ( 0.3 );
		const value_type a4 = static_cast<value_type> ( 0.6 );
		const value_type a5 = static_cast<value_type> ( 1.0 );
		const value_type a6 = static_cast<value_type> ( 0.875 );

		const value_type b21 = static_cast<value_type> ( 0.2 );
		const value_type b31 = static_cast<value_type> ( 3.0 ) / static_cast<value_type>( 40.0 );
		const value_type b32 = static_cast<value_type> ( 9.0 ) / static_cast<value_type>( 40.0 );
		const value_type b41 = static_cast<value_type> ( 0.3 );
		const value_type b42 = static_cast<value_type> ( -0.9 );
		const value_type b43 = static_cast<value_type> ( 1.2 );
		const value_type b51 = static_cast<value_type> ( -11.0 ) / static_cast<value_type>( 54.0 );
		const value_type b52 = static_cast<value_type> ( 2.5 );
		const value_type b53 = static_cast<value_type> ( -70.0 ) / static_cast<value_type>( 27.0 );
		const value_type b54 = static_cast<value_type> ( 35.0 ) / static_cast<value_type>( 27.0 );
		const value_type b61 = static_cast<value_type> ( 1631.0 ) / static_cast<value_type>( 55296.0 );
		const value_type b62 = static_cast<value_type> ( 175.0 ) / static_cast<value_type>( 512.0 );
		const value_type b63 = static_cast<value_type> ( 575.0 ) / static_cast<value_type>( 13824.0 );
		const value_type b64 = static_cast<value_type> ( 44275.0 ) / static_cast<value_type>( 110592.0 );
		const value_type b65 = static_cast<value_type> ( 253.0 ) / static_cast<value_type>( 4096.0 );

		const value_type c1 = static_cast<value_type> ( 37.0 ) / static_cast<value_type>( 378.0 );
		const value_type c3 = static_cast<value_type> ( 250.0 ) / static_cast<value_type>( 621.0 );
		const value_type c4 = static_cast<value_type> ( 125.0 ) / static_cast<value_type>( 594.0 );
		const value_type c6 = static_cast<value_type> ( 512.0 ) / static_cast<value_type>( 1771.0 );

		typename boost::unwrap_reference< System >::type &sys = system;

		m_resizer.adjust_size( in , boost::bind( &stepper_type::resize<StateIn> , boost::ref( *this ) , _1 ) );

		//m_x1 = x + dt*b21*dxdt
		stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , dxdt ,
				typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt*b21 ) );

		sys( m_x_tmp.m_v , m_k2.m_v , t + dt*a2 );
		// m_x_tmp = x + dt*b31*dxdt + dt*b32*m_x2
		stepper_base_type::m_algebra.for_each4( m_x_tmp.m_v , in , dxdt , m_k2.m_v ,
				typename operations_type::template scale_sum3< value_type , time_type , time_type >( 1.0 , dt*b31 , dt*b32 ));

		sys( m_x_tmp.m_v , m_k3.m_v , t + dt*a3 );
		// m_x_tmp = x + dt * (b41*dxdt + b42*m_x2 + b43*m_x3)
		stepper_base_type::m_algebra.for_each5( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v ,
				typename operations_type::template scale_sum4< value_type , time_type , time_type , time_type >( 1.0 , dt*b41 , dt*b42 , dt*b43 ));

		sys( m_x_tmp.m_v, m_k4.m_v , t + dt*a4 );
		stepper_base_type::m_algebra.for_each6( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v , m_k4.m_v ,
				typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b51 , dt*b52 , dt*b53 , dt*b54 ));

		sys( m_x_tmp.m_v , m_k5.m_v , t + dt*a5 );
		stepper_base_type::m_algebra.for_each7( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v , m_k4.m_v , m_k5.m_v ,
				typename operations_type::template scale_sum6< value_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b61 , dt*b62 , dt*b63 , dt*b64 , dt*b65 ));

		sys( m_x_tmp.m_v , m_k6.m_v , t + dt*a6 );
		stepper_base_type::m_algebra.for_each6( out , in , dxdt , m_k3.m_v , m_k4.m_v , m_k6.m_v ,
				typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*c1 , dt*c3 , dt*c4 , dt*c6 ));

	}

	template< class StateIn >
	bool resize( const StateIn &x )
	{
	    bool resized = false;
	    resized |= adjust_size_by_resizeability( m_x_tmp , x , typename wrapped_state_type::is_resizeable() );
	    resized |= adjust_size_by_resizeability( m_k2 , x , typename wrapped_deriv_type::is_resizeable() );
	    resized |= adjust_size_by_resizeability( m_k3 , x , typename wrapped_deriv_type::is_resizeable() );
	    resized |= adjust_size_by_resizeability( m_k4 , x , typename wrapped_deriv_type::is_resizeable() );
	    resized |= adjust_size_by_resizeability( m_k5 , x , typename wrapped_deriv_type::is_resizeable() );
	    resized |= adjust_size_by_resizeability( m_k6 , x , typename wrapped_deriv_type::is_resizeable() );
	    return resized;
	}

	template< class StateIn >
	void adjust_size( const StateIn &x )
	{
	    resize( x );
	    stepper_base_type::adjust_size( x );
	}

private:

	wrapped_state_type m_x_tmp;
    wrapped_deriv_type m_k2, m_k3, m_k4, m_k5, m_k6;
    resizer_type m_resizer;

};







} // odeint
} // numeric
} // boost




#endif //BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_RK54_CK_HPP_INCLUDED
