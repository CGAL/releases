// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Partition_opt_cvx_edge.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2002/03/19 20:34:37 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Edge used in optimal convex partitioning algorithm.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_PARTITION_OPT_CVX_EDGE_H
#define CGAL_PARTITION_OPT_CVX_EDGE_H

#include <iostream>
#include <CGAL/Partition_opt_cvx_diagonal_list.h>

namespace CGAL {

enum Partition_opt_cvx_edge_validity {PARTITION_OPT_CVX_NOT_VALID, 
                                      PARTITION_OPT_CVX_START_VALID,
                                      PARTITION_OPT_CVX_END_VALID, 
                                      PARTITION_OPT_CVX_BOTH_VALID};

class Partition_opt_cvx_edge 
{
public:
   Partition_opt_cvx_edge(): _is_done(false), 
                             _validity(PARTITION_OPT_CVX_NOT_VALID), 
                             _is_visible(false), _value(0) {}

   bool is_done( ) const { return _is_done; }

   bool is_valid( ) const { return _validity != PARTITION_OPT_CVX_NOT_VALID; }

   Partition_opt_cvx_edge_validity validity( ) const { return _validity; }

   bool is_visible( ) const { return _is_visible; }

   int  value( ) const { return _value; }

   Partition_opt_cvx_diagonal_list  solution( ) const { return _solution; }

   void set_done(bool val)  { _is_done = val; }

   void set_valid(Partition_opt_cvx_edge_validity val) { _validity = val; }
   
   template <class Point_2_, class Traits>
   void set_valid(const Point_2_& p1, const Point_2_& p2, const Point_2_& p3,
                  const Point_2_& p4, const Point_2_& p5, const Point_2_& p6,
                  const Traits& traits)
   { 
      typedef typename Traits::Leftturn_2     Leftturn_2;
      Leftturn_2 leftturn = traits.leftturn_2_object();

      _validity = PARTITION_OPT_CVX_NOT_VALID;

      Turn_reverser<Point_2_, Leftturn_2>  rightturn(leftturn);
      if (rightturn(p1, p2, p3))
         _validity = PARTITION_OPT_CVX_START_VALID;
      if (rightturn(p4, p5, p6))
         if (_validity == PARTITION_OPT_CVX_START_VALID) 
            _validity = PARTITION_OPT_CVX_BOTH_VALID;
         else _validity = PARTITION_OPT_CVX_END_VALID;
   }

   void set_visible(bool vis) { _is_visible = vis; }

   void set_value(int val) { _value = val; }

   void set_solution(const Partition_opt_cvx_diagonal_list& diag_list) 
   { _solution = diag_list; }


private:
   bool                            _is_done;
   Partition_opt_cvx_edge_validity _validity;
   bool                            _is_visible;
   int                             _value;
   Partition_opt_cvx_diagonal_list _solution;
};

std::ostream& operator<<(std::ostream& os, const Partition_opt_cvx_edge& g)
{
   if (g.is_done()) os << "1";
   else os << "0";
   if (g.validity() == PARTITION_OPT_CVX_NOT_VALID) os << "0";
   else if (g.validity() == PARTITION_OPT_CVX_START_VALID) os << "1";
   else if (g.validity() == PARTITION_OPT_CVX_END_VALID) os << "2";
   else os << "3";
   if (g.is_visible()) os << "1";
   else os << "0";
   os << g.value();
   return os;
}

}

#endif // CGAL_PARTITION_OPT_CVX_EDGE_H
