// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : ddim_points.fw
// file          : include/CGAL/Point_d.h
// package       : _d (2.2.7)
// revision      : 2.2.7
// revision_date : 08 Oct 1999 
// author(s)     : Sven Schoenherr
//                 Bernd Gaertner
// maintained by   Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_POINT_D_H
#define CGAL_POINT_D_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_POINTHD_H
#include <CGAL/PointHd.h>
#endif // CGAL_POINTHD_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_POINTCD_H
#include <CGAL/PointCd.h>
// #include <CGAL/Cartesian/Point_d.h>
#endif // CGAL_POINTCD_H
#endif // CGAL_CARTESIAN_H

CGAL_BEGIN_NAMESPACE

template < class _R >
class Point_d : public _R::Point_d_base
{
public:
    typedef  _R   R;
    typedef typename R::RT              RT;
    typedef typename R::FT              FT;
    typedef typename R::Point_d_base    Point;

    Point_d()
    {}

    Point_d(int dim, const Origin &o)
        : Point(dim, o)
    {}

    Point_d(const Point_d<R> &p)
        : Point((Point&)p)
    {}

    Point_d(const Point &p)
        : Point(p)
    {}

    template <class InputIterator>
    Point_d (int dim, InputIterator first, InputIterator last)
        : Point (dim, first, last)
    {}

    Point_d<R>& operator=(const Point_d<R>& p)
    {
          Point::operator=(p);
          return *this;
    }

    bool operator==(const Point_d<R>& p) const
    {
    return Point::operator==(p);
    }

    bool operator!=(const Point_d<R>& p) const
    {
        return !(*this == p);
    }

    int id() const
    {
        return (int) PTR;
    }

    RT homogeneous(int i) const
    {
        return Point::homogeneous(i);
    }

    FT cartesian(int i) const
    {
        return Point::cartesian(i);
    }

    FT operator[](int i) const
    {
        return Point::operator[](i);
    }

    typedef const RT* const_iterator;

    const_iterator begin() const
    {
        return Point::begin();
    }

    const_iterator end() const
    {
        return Point::end();
    }   

    int dimension() const
    {
    return Point::dimension();
    }
};

#ifndef NO_OSTREAM_INSERT_POINT_D
template < class R >
std::ostream& 
operator<<(std::ostream& os, const Point_d<R>& p)
{
  typedef typename  R::Point_d_base    Point;
  return os << (const Point&)p;
}
#endif // NO_OSTREAM_INSERT_POINT_D

#ifndef NO_ISTREAM_EXTRACT_POINT_D
template < class R >
std::istream& 
operator>>(std::istream& is, Point_d<R> &p)
{
  typedef typename  R::Point_d_base    Point;
  return is >> (Point&)p;
}
#endif // NO_ISTREAM_EXTRACT_POINT_D
CGAL_END_NAMESPACE


#endif // CGAL_POINT_D_H

