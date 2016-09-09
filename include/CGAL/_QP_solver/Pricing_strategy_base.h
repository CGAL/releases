// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/_QP_solver/Pricing_strategy_base.h
// package       : _QP_solver (0.9.3)
//
// revision      : 0.4
// revision_date : 2000/08/17
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: Base Class for Pricing Strategies for the QP Solver
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
                                                                               
#ifndef CGAL_PRICING_STRATEGY_BASE_H
#define CGAL_PRICING_STRATEGY_BASE_H

// includes
#include <CGAL/_QP_solver/QP_solver.h>
#include <CGAL/IO/Verbose_ostream.h>

CGAL_BEGIN_NAMESPACE
                    

// Class declaration
// =================
template < class _Rep >
class Pricing_strategy_base;

template < class _Rep >
class QP_solver;
                

// Class interface
// ===============
struct To_double {
    template < class NT >
    double  operator () ( const NT& x) { return CGAL::to_double( x); }
};

template < class _Rep >
class Pricing_strategy_base {
  public:
    // self
    typedef  _Rep                       Rep;
    typedef  Pricing_strategy_base<Rep> Self;

    // the ambient QP solver
    typedef  CGAL::QP_solver<Rep>       Solver;

    // types from the ambient QP solver
    typedef  typename Solver::NT        NT;
    typedef  typename Solver::ET        ET;

    typedef  typename Solver::A_iterator
                                        A_iterator;
    typedef  typename Solver::B_iterator
                                        B_iterator;
    typedef  typename Solver::C_iterator
                                        C_iterator;
    typedef  typename Solver::D_iterator
                                        D_iterator;

    typedef  typename Solver::A_artificial_iterator
                                        A_artificial_iterator;
    typedef  typename Solver::C_auxiliary_iterator
                                        C_auxiliary_iterator;

    typedef  typename Solver::Basic_variable_index_iterator
                                        Basic_variable_index_iterator;
    typedef  typename Solver::Basic_variable_value_iterator
                                        Basic_variable_value_iterator;
    typedef  typename Solver::Basic_variable_numerator_iterator
                                        Basic_variable_numerator_iterator;

    typedef  typename Solver::Lambda_value_iterator
                                        Lambda_value_iterator;
    typedef  typename Solver::Lambda_numerator_iterator
                                        Lambda_numerator_iterator;

    // types from the representation class
    typedef  typename Rep::Is_lp        Is_lp;

  protected:
    // protected types
    typedef  CGAL::Tag_true             Tag_true;
    typedef  CGAL::Tag_false            Tag_false;

  public:
    
    // creation
    Pricing_strategy_base( ) { }
    
    // destruction
    virtual ~Pricing_strategy_base( ) { }
    
    
    // initialization
    void  set( const Solver&           solver,
               CGAL::Verbose_ostream&  verbose_out)
        {
            solverP = &solver;
            voutP   = &verbose_out;
            set();
        }
    
    
    virtual  void  set( ) { }
    
    
    virtual  void  init( ) { }
    
    
    // access
    const Solver&        solver( ) const { return *solverP; }
    CGAL::Verbose_ostream&  vout  ( ) const { return *voutP; }
    
    
    // operations
    virtual  int   pricing( ) = 0;
    
    
    virtual  void  leaving_basis( int) { }
    
    virtual  void  transition( ) { }
    
    

  private:
    // data members
    const Solver*            solverP;   // the ambient QP solver
    CGAL::Verbose_ostream*   voutP;     // used for verbose output
};
  

CGAL_END_NAMESPACE
                  

#endif // CGAL_PRICING_STRATEGY_BASE_H

// ===== EOF ==================================================================
