// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : demo/Robustness/include/CGAL/further_point_generators_2.h
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/01/09 18:56:41 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_FURTHER_POINT_GENERATORS_2_H
#define CGAL_FURTHER_POINT_GENERATORS_2_H

#include <CGAL/Cartesian.h>
#include <iterator>
#include <CGAL/Random.h>

namespace CGAL {

class Point_on_horizontal_bar
{
  public:
    typedef Cartesian<double>::Point_2  Point_2;
    typedef std::output_iterator_tag    iterator_category;
    typedef Point_2                     value_type;
    typedef void                        difference_type;
    typedef void                        pointer;
    typedef void                        reference;

    Point_on_horizontal_bar( int lo_x, int hi_x, int Y)
     : a(lo_x), b(hi_x), y(Y)
    { generate_point(); }

    void
    generate_point()
    {
      int x = RS.get_int(a,b);
      p = Point_2( x, y);
    }

    Point_2
    operator*()
    { return p; }

    Point_on_horizontal_bar&
    operator++()
    {
        generate_point();
        return *this;
    }

    Point_on_horizontal_bar
    operator++(int)
    {
        Point_on_horizontal_bar tmp = *this;
        ++(*this);
        return tmp;
    }


  private:
    int a, b;
    Random  RS;
    int  y;
    Point_2 p;

};

class Point_on_vertical_bar
{
  public:
    typedef Cartesian<double>::Point_2  Point_2;
    typedef std::output_iterator_tag    iterator_category;
    typedef Point_2                     value_type;
    typedef void                        difference_type;
    typedef void                        pointer;
    typedef void                        reference;

    Point_on_vertical_bar( int lo_y, int hi_y, int X)
     : a(lo_y), b(hi_y), x(X)
    { generate_point(); }

    void
    generate_point()
    {
      int y = RS.get_int(a,b);
      p = Point_2( x, y);
    }

    Point_2
    operator*()
    { return p; }

    Point_on_vertical_bar&
    operator++()
    {
        generate_point();
        return *this;
    }

    Point_on_vertical_bar
    operator++(int)
    {
        Point_on_vertical_bar tmp = *this;
        ++(*this);
        return tmp;
    }


  private:
    int a, b;
    Random RS;
    int  x;
    Point_2 p;

};

} // namespace CGAL
#endif //  CGAL_FURTHER_POINT_GENERATORS_2_H
