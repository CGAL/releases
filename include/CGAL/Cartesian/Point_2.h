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
// file          : include/CGAL/Cartesian/Point_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.22 $
// revision_date : $Date: 2002/02/06 12:32:37 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_POINT_2_H
#define CGAL_CARTESIAN_POINT_2_H

#include <CGAL/Origin.h>
#include <CGAL/Bbox_2.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class PointC2
  : public R_::Point_handle_2
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::Vector_2             Vector_2;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Aff_transformation_2 Aff_transformation_2;

  typedef typename R_::Point_handle_2		 base;
  typedef typename base::element_type	         rep;

public:
  typedef R_                                     R;

  PointC2()
    : base(rep()) {}

  PointC2(const Origin &)
    : base(rep(FT(0), FT(0))) {}

  PointC2(const FT &x, const FT &y)
    : base(rep(x, y)) {}

  PointC2(const FT &hx, const FT &hy, const FT &hw)
  {
    if (hw != FT(1))
      initialize_with( rep(hx/hw, hy/hw) );
    else
      initialize_with( rep(hx, hy) );
  }

  PointC2(const Vector_2 &v)
    : base(v) {}

  const FT& x() const
  {
      return Ptr()->e0;
  }
  const FT& y() const
  {
      return Ptr()->e1;
  }

  const FT& hx() const
  {
      return x();
  }
  const FT& hy() const
  {
      return y();
  }
  FT hw() const
  {
      return FT(1);
  }

  const FT& cartesian(int i) const;
  FT homogeneous(int i) const;
  const FT& operator[](int i) const
  {
      return cartesian(i);
  }

  int dimension() const
  {
      return 2;
  }

  bool operator==(const PointC2 &p) const
  {
      if (identical(p))
	  return true;
      return equal_xy(*this, p);
  }
  bool operator!=(const PointC2 &p) const
  {
      return !(*this == p);
  }

  Bbox_2 bbox() const;

  Point_2 transform(const Aff_transformation_2 &t) const
  {
    return t.transform(*this);
  }
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template < class R >
CGAL_KERNEL_INLINE
const typename PointC2<R>::FT &
PointC2<R>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i == 0) || (i == 1) );
  return (i == 0) ? x() : y();
}

template < class R >
CGAL_KERNEL_INLINE
typename PointC2<R>::FT
PointC2<R>::homogeneous(int i) const
{
  CGAL_kernel_precondition( (i>=0) && (i<=2) );
  if (i<2)
    return cartesian(i);
  return FT(1);
}

template < class R >
CGAL_KERNEL_INLINE
Bbox_2
PointC2<R>::bbox() const
{
  double bx = CGAL::to_double(x());
  double by = CGAL::to_double(y());
  return Bbox_2(bx,by, bx,by);
}

#ifndef CGAL_NO_OSTREAM_INSERT_POINTC2
template < class R >
std::ostream &
operator<<(std::ostream &os, const PointC2<R> &p)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << p.x() << ' ' << p.y();
    case IO::BINARY :
        write(os, p.x());
        write(os, p.y());
        return os;
    default:
        return os << "PointC2(" << p.x() << ", " << p.y() << ')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_POINTC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINTC2
template < class R >
std::istream &
operator>>(std::istream &is, PointC2<R> &p)
{
    typename R::FT x, y;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> x >> y;
        break;
    case IO::BINARY :
        read(is, x);
        read(is, y);
        break;
    default:
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;
    }
    if (is)
	p = PointC2<R>(x, y);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTC2

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_POINT_2_H
