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
// file          : include/CGAL/Segment_less_yx_2.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/01/12 12:58:47 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Ordering of segments for visibility sweep.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SEGMENT_LESS_YX_2_H
#define CGAL_SEGMENT_LESS_YX_2_H

#include <utility>
#include <CGAL/Turn_reverser.h>

namespace CGAL {

//
// Compares two pairs of points representing two segments. The first is 
// "less than" the second if the second can see some point of the first 
// by looking straight down (i.e., in direction -pi/2). If the first can see
// the second in this way, it is greater than the second.  If neither sees
// the other when looking in the direction -pi/2, the one that is farther
// to the left is less than the one farther to the right.
//
template <class Traits>
class Segment_less_yx_2
{
   typedef typename Traits::Point_2             Point_2;
   typedef std::pair<Point_2, Point_2>          Point_pair;
   typedef typename Traits::Less_xy_2           Less_xy_2;
   typedef typename Traits::Compare_x_2         Compare_x_2;
   typedef typename Traits::Compare_y_2         Compare_y_2;
   typedef typename Traits::Leftturn_2          Leftturn_2;
   typedef Turn_reverser<Point_2, Leftturn_2>   Rightturn_2;

   public:
     Segment_less_yx_2() : 
       _less_xy_2(Traits().less_xy_2_object()),
       _compare_x_2(Traits().compare_x_2_object()),
       _compare_y_2(Traits().compare_y_2_object()),
       _leftturn_2(Traits().leftturn_2_object()),
       _rightturn_2(Rightturn_2(_leftturn_2))
     { }
     

     bool 
     operator()(const Point_pair& p, const Point_pair& q) const
     { 
        Point_2 p_smaller_xy, p_larger_xy;
        Point_2 q_smaller_xy, q_larger_xy;
        // order the point pairs by x value
        if (_less_xy_2(p.first, p.second))
        {
           p_smaller_xy = p.first;
           p_larger_xy = p.second;
        }
        else
        {
           p_smaller_xy = p.second;
           p_larger_xy = p.first;
        }
        if (_less_xy_2(q.first, q.second))
        {
           q_smaller_xy = q.first;
           q_larger_xy = q.second;
        }
        else
        {
           q_smaller_xy = q.second;
           q_larger_xy = q.first;
        }


        // x range of p comes before x range of q
        if (_compare_x_2(p_larger_xy, q_smaller_xy) == SMALLER)
           return true;
        else if (_compare_x_2(p_larger_xy, q_smaller_xy) == EQUAL)
        { 
           // x range of p ends where x range of q starts
           Comparison_result y_comp = _compare_y_2(p_larger_xy, q_smaller_xy);
           if (y_comp == SMALLER)
              return true;
           else if (y_comp == LARGER)
              return false;
           else // y_comp == EQUAL, so p's x range comes before q's
              return true;
        }
        // x range of q comes before x range of p
        else if (_compare_x_2(q_larger_xy, p_smaller_xy) == SMALLER)
           return false;
        else if (_compare_x_2(q_larger_xy, p_smaller_xy) == EQUAL)
        { 
           // x range of p starts where x range of q ends
           Comparison_result y_comp = _compare_y_2(p_smaller_xy, q_larger_xy);
           if (y_comp == SMALLER)
              return true;
           else if (y_comp == LARGER)
              return false;
           else // y_comp == EQUAL, so p's x range comes after q's
              return false;
        }
        // see if one of q's endpoints is contained in p's x range
        else if (_compare_x_2(p_smaller_xy,q_smaller_xy) == SMALLER && 
                 _compare_x_2(q_smaller_xy,p_larger_xy) == SMALLER)
           return _leftturn_2(p_smaller_xy,p_larger_xy,q_smaller_xy);
        else if (_compare_x_2(p_smaller_xy,q_larger_xy) == SMALLER &&
                 _compare_x_2(q_larger_xy,p_larger_xy) == SMALLER)
           return _leftturn_2(p_smaller_xy,p_larger_xy,q_larger_xy);
        //
        // neither of q's endpoints is in p's x-range so see if one of
        // p's endpoints is in q's x-range 
        //
        else if (_compare_x_2(q_smaller_xy,p_smaller_xy) == SMALLER && 
                 _compare_x_2(p_smaller_xy,q_larger_xy) == SMALLER)
           return _rightturn_2(q_smaller_xy,q_larger_xy,p_smaller_xy);
        else if (_compare_x_2(q_smaller_xy,p_larger_xy) == SMALLER &&
                 _compare_x_2(p_larger_xy,q_larger_xy) == SMALLER )
           return _rightturn_2(q_smaller_xy,q_larger_xy,p_larger_xy);
        else // the x ranges are exactly the same
        {
           Comparison_result y_comp = _compare_y_2(p_smaller_xy, q_smaller_xy);
           if (y_comp == SMALLER) 
              return true;
           else if (y_comp == LARGER)
              return false;
           else // look at the other endpoint
           {
              y_comp = _compare_y_2(p_larger_xy, q_larger_xy);
              if (y_comp == SMALLER) 
                 return true;
              else if (y_comp == LARGER)
                 return false;
              else  // point pairs are identical
                 return false;
           }
        }
     }

   private:
      Less_xy_2 _less_xy_2;
      Compare_x_2 _compare_x_2;
      Compare_y_2 _compare_y_2;
      Leftturn_2 _leftturn_2;
      Rightturn_2 _rightturn_2;
};

}

#endif // CGAL_SEGMENT_LESS_YX_2_H

