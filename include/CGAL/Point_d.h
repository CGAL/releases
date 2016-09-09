// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : ddim_points.fw
// file          : include/CGAL/Point_d.h
// package       : _d (0.9.2)
// revision      : 0.9.2
// revision_date : 01 Jul 1998 
// author(s)     : Sven Schoenherr
//                 Bernd Gaertner
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
#endif // CGAL_POINTCD_H
#endif // CGAL_CARTESIAN_H


template < class _R >
class CGAL_Point_d : public _R::Point_d
{
public:
    typedef  _R   R;
    typedef typename R::RT              RT;
    typedef typename R::FT              FT;
    typedef typename R::Point_d         Point;

    CGAL_Point_d()
    {}

    CGAL_Point_d(int dim, const CGAL_Origin &o)
        : Point(dim, o)
    {}

    CGAL_Point_d(const CGAL_Point_d<R> &p)
        : Point((Point&)p)
    {}

    CGAL_Point_d(const Point &p)
        : Point(p)
    {}

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES

    template <class InputIterator>
    CGAL_Point_d (int dim, InputIterator first, InputIterator last)
        : Point (dim, first, last)
    {}

#else

    CGAL_Point_d (int dim, RT* first, RT* last)
        : Point (dim, first, last)
    {}

#endif // CGAL_CFG_NO_MEMBER_TEMPLATES

    CGAL_Point_d<R>& operator=(const CGAL_Point_d<R>& p)
    {
          Point::operator=(p);
          return *this;
    }

    bool operator==(const CGAL_Point_d<R>& p) const
    {
    return Point::operator==(p);
    }

    bool operator!=(const CGAL_Point_d<R>& p) const
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

    int dimension() const
    {
    return Point::dimension();
    }
};

#ifndef CGAL_NO_OSTREAM_INSERT_POINT_D
    template < class R >
    ostream &
    operator<<(ostream &os, const CGAL_Point_d<R>& p)
    {
      typedef typename  R::Point_d    Point;
      return os << (const Point&)p;
    }
#endif // CGAL_NO_OSTREAM_INSERT_POINT_D

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINT_D
    template < class R >
    istream &
    operator>>(istream &is, CGAL_Point_d<R> &p)
    {
      typedef typename  R::Point_d    Point;
      return is >> (Point&)p;
    }
#endif // CGAL_NO_ISTREAM_EXTRACT_POINT_D

#endif // CGAL_POINT_D_H

