// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Distance_2.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Distance_2.h,v $
// revision      : $Revision: 1.1.1.5 $
// revision_date : $Date: 1999/03/11 16:48:13 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_DISTANCE_2_H
#define CGAL_DISTANCE_2_H

#include<CGAL/number_utils.h>

CGAL_BEGIN_NAMESPACE


template <class I>
class Distance_2{
public:
    typedef typename I::Point Point;
    Distance_2(const I* traits = NULL)
    {}

    Distance_2(const Point& p0,
                    const I* traits = NULL)
        : _p0(p0)
    {}


    Distance_2(const Point& p0,
                    const Point& p1,
                    const I* traits = NULL)
        : _p0(p0), _p1(p1)
    {}


    Distance_2(const Point& p0,
                    const Point& p1,
                    const Point& p2,
                    const I* traits = NULL)
        : _p0(p0), _p1(p1), _p2(p2)
    {}

    void
    set_point(int i, const Point& p)
    {
        CGAL_triangulation_precondition(i == 0 || i == 1 || i == 2);
        switch(i){
        case 0:
            _p0 = p;
            break;
        case 1:
            _p1 = p;
            break;
        default:
            _p2 = p;
        }
    }

    Point
    get_point(int i) const
    {
      CGAL_triangulation_precondition(i == 0 || i == 1 || i == 2);
      switch(i){
      case 0:
        return _p0;
      case 1:
        return _p1;
      }
      return _p2;
    }

    Comparison_result
    compare() const
    {
        return CGAL::compare(
          (typename Point::R::FT)squared_distance(_p0, _p1),
          (typename Point::R::FT)squared_distance(_p0, _p2));

    }

private:
    Point _p0, _p1, _p2;
};

CGAL_END_NAMESPACE

#endif // CGAL_DISTANCE_2_H
