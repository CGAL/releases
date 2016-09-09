// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/width_assertions.h
// package       : Width_3 (1.13)
// chapter       : Geometric Optimisation
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/07/12 05:59:08 $
//
// author(s)     : Thomas Herrmann
// coordinator   : ETH Zuerich (Bernd Gaertner)
//
// implementation: 3D Width of a Point Set
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_WIDTH_ASSERTIONS_H
#define CGAL_WIDTH_ASSERTIONS_H 1

#ifdef SIMPLIFY
#define GCD_COMPUTATION 1
#endif

#ifdef DEBUG

//Turn assertion output on/off 
#define ASSERTION_OUTPUT 0
#define EXPENSIVE_CHECKS_OUTPUT 0

//Turn on/off output in preparation_check
#define PREPARATION_CHECK 0

//Turn on/off output in neighbors_of
#define NEIGHBORS_OF 0

//Turn on/off output of setminus, setunion and setcut
#define SETMINUS 0
#define SETUNION 0
#define SETCUT 0

//Turn on/off output of compute_plane_equation
#define COMPUTE_PLANE_EQUATION 0

//Turn on/off output of solve_3x3
#define SOLVE_3X3 0

//Turn on/off output of solve_4x4
#define SOLVE_4X4 0

//Turn on/off output in check_feasibility
#define CHECK_FEASIBILITY 0

//Turn on/off compilation and output of gcd computation
#define GCD_OUTPUT 0

//Turn on/off output of simplify_solution
#define SIMPLIFY_SOLUTION 0

//Turn on/off output in initial_VF_pair
#define INITIAL_VF_PAIR 0

//Turn on/off output in check_about_VF-pairs
#define CHECK_ABOUT_VF_PAIRS 0
#define VF_PAIR_OUTPUT 0

//Turn on/off output of update_width
#define UPDATE_WIDTH 0

//Turn on/off output of EE_computation and EE_pairs
#define EE_COMPUTATION 0
#define EE_PAIRS 0

//Turn on/off output in origin_inside_CH
#define ORIGIN_INSIDE_CH 0

//Turn on/off output of width_3_convex
#define WIDTH_3_CONVEX 0
#define EDGE_INITIALIZING 0

//Turn on/off output of stack go_on
#define GO_ON_OUTPUT 0

//Turn infos on/off
#define INFO 0

//Turn on/off output of verifications on edges
#define VISITED_CHECK 0
#define IMPASSABLE_CHECK 0

 #include<stream.h>

 #define DEBUGENDL(doit,msg,var)\
 if(doit!=0) std::cout << msg << " " << var << endl;

 #define DEBUGPRINT(doit,msg,var)\
 if(doit!=0) std::cout << msg << " " << var;

 #define DEBUGMSG(doit,msg)\
 if(doit!=0) std::cout << msg << endl;

 #define INFOMSG(doit,msg)\
 if(doit!=0) std::cerr<<msg<<endl;

#else
 #define DEBUGENDL(doit,msg,var)
 #define DEBUGPRINT(doit,msg,var)
 #define DEBUGMSG(doit,msg)
 #define INFOMSG(doit,msg)
// #define NDEBUG // discard assertions. Changed since it violates std: L.K.
#endif

#include <assert.h>

#endif //#WIDTH_DEBUG_H




