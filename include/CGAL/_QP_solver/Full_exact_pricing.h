// Copyright (c) 1997-2001  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/_QP_solver/include/CGAL/_QP_solver/Full_exact_pricing.h,v $
// $Revision: 1.4 $ $Date: 2003/09/18 10:26:43 $
// $Name: current_submission $
//
// Author(s)     : Sven Sch�nherr <sven@inf.ethz.ch>
                                                                               

#ifndef CGAL_FULL_EXACT_PRICING_H
#define CGAL_FULL_EXACT_PRICING_H

// includes
#include <CGAL/_QP_solver/Pricing_strategy_base.h>
#include <CGAL/_QP_solver/Join_random_access_iterator.h>
#include <CGAL/_QP_solver/Access_by_index.h>
#include <numeric>


CGAL_BEGIN_NAMESPACE
                    

// Class declaration
// =================
template < class Rep >
class Full_exact_pricing;
                         

// Class interface
// ===============
template < class _Rep >
class Full_exact_pricing
    : public CGAL::Pricing_strategy_base<_Rep> {
  public:
    // self
    typedef  _Rep                        Rep;
    typedef  Full_exact_pricing<Rep>     Self;
    typedef  Pricing_strategy_base<Rep>  Base;

    // types from the base class
    typedef  typename Base::NT          NT;
    typedef  typename Base::ET          ET;

    typedef  typename Base::A_iterator  A_iterator;
    typedef  typename Base::B_iterator  B_iterator;
    typedef  typename Base::C_iterator  C_iterator;
    typedef  typename Base::D_iterator  D_iterator;

    typedef  typename Base::A_artificial_iterator
                                        A_artificial_iterator;
    typedef  typename Base::C_auxiliary_iterator
                                        C_auxiliary_iterator;

    typedef  typename Base::Basic_variable_index_iterator
                                        Basic_variable_index_iterator;

    typedef  typename Base::Is_lp       Is_lp;

    typedef  typename Base::Solver      Solver;

    typedef  typename Base::Tag_true    Tag_true;
    typedef  typename Base::Tag_false   Tag_false;

  private:
      // some constants
      ET  et_0, et_2;
  public:
    
    // creation
    Full_exact_pricing( ) : et_0( 0), et_2( 2) { }
    
    // initialization
    void  set( )
    {
        CGAL_optimisation_debug {
            vout() << "full exact pricing" << std::endl;
        }
    }
    
    
    // operations
    int  pricing( )
    {
        typedef  CGAL::Access_by_index< typename
                     std::iterator_traits<D_iterator>::value_type,
                     false,false>       Access_D_Bj;
        typedef  CGAL::Join_random_access_iterator_1<
                     Basic_variable_index_iterator,
                     Access_D_Bj >      D_Bj_iterator;
    
        const Solver& s = solver();
        int  n = s.number_of_variables();
        int  m = s.number_of_constraints();
        ET   d = s.variables_common_denominator();
    
        int   j,  min_j  = -1;
        ET    mu, min_mu =  0;
        bool  is_phase_I = ( s.phase() == 1);
    
        // loop over all non-basic variables
        for ( j = 0; j < ( is_phase_I ? n+m : n); ++j) {
    
            // variable non-basic?
            if ( ! s.is_basic( j)) {
    
                // compute mu_j
                if ( is_phase_I) {      // phase I
                    if ( j < n) {          // original variable
                        mu = std::inner_product(
                            s.lambda_numerator_begin(),
                            s.lambda_numerator_end(),
                            s.a_begin()[ j],
                            d * s.c_auxiliary_begin()[ j]);
                    } else {               // artificial variable
                        mu = std::inner_product(
                            s.lambda_numerator_begin(),
                            s.lambda_numerator_end(),
                            s.a_artificial_begin()[ j-n],
                            d * s.c_auxiliary_begin()[ j]);
                    }
                } else {                // phase II
                    mu = std::inner_product(
                        s.lambda_numerator_begin(),
                        s.lambda_numerator_end(),
                        s.a_begin()[ j],
                        d * s.c_begin()[ j]);
                    // is QP?
                    if ( ! CGAL::check_tag( Is_lp())) {
                        mu += et_2 * std::inner_product(
                            s.basic_variables_numerator_begin(),
                            s.basic_variables_numerator_end(),
                            D_Bj_iterator( s.basic_variables_index_begin(),
                                           Access_D_Bj( s.d_begin()[ j])),
                            et_0);
                    }
                }
    
                CGAL_optimisation_debug {
                    vout() << "mu_" << j << ": " << mu << std::endl;
                }
    
                // new minimum?
                if ( mu < min_mu) { min_j = j; min_mu = mu; }
            }
        }
        vout() << std::endl;
    
        // return index of entering variable
        return min_j;
    }
    
    
};
  

CGAL_END_NAMESPACE
                  

#endif // CGAL_FULL_EXACT_PRICING_H

// ===== EOF ==================================================================
