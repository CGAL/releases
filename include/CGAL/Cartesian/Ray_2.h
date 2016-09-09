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
// file          : include/CGAL/Cartesian/Ray_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.23 $
// revision_date : $Date: 2002/02/06 12:32:38 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_RAY_2_H
#define CGAL_CARTESIAN_RAY_2_H

CGAL_BEGIN_NAMESPACE

template < class R_ >
class RayC2
  : public R_::Ray_handle_2
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Direction_2          Direction_2;
  typedef typename R_::Line_2               Line_2;
  typedef typename R_::Ray_2                Ray_2;
  typedef typename R_::Aff_transformation_2 Aff_transformation_2;

  typedef typename R_::Ray_handle_2              base;
  typedef typename base::element_type            rep;

public:
  typedef R_                                     R;

  RayC2()
    : base(rep()) {}

  RayC2(const Point_2 &sp, const Point_2 &secondp)
    : base(rep(sp, secondp)) {}

  RayC2(const Point_2 &sp, const Direction_2 &d)
    : base(rep(sp, sp + d.to_vector())){}

  bool        operator==(const RayC2 &r) const;
  bool        operator!=(const RayC2 &r) const;

  const Point_2 &     start() const;
  const Point_2 &     source() const
  {
      return Ptr()->e0;
  }
  Point_2     point(int i) const;
  const Point_2 &     second_point() const
  {
      return Ptr()->e1;
  }

  Direction_2 direction() const;
  Line_2      supporting_line() const;
  Ray_2        opposite() const;

  Ray_2        transform(const Aff_transformation_2 &t) const
  {
    return RayC2<R>(t.transform(source()), t.transform(second_point()));
  }

  bool        is_horizontal() const;
  bool        is_vertical() const;
  bool        is_degenerate() const;
  bool        has_on(const Point_2 &p) const;
  bool        collinear_has_on(const Point_2 &p) const;
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template < class R >
CGAL_KERNEL_INLINE
bool
RayC2<R>::operator==(const RayC2<R> &r) const
{
  if (identical(r))
      return true;
  return source() == r.source() && direction() == r.direction();
}

template < class R >
inline
bool
RayC2<R>::operator!=(const RayC2<R> &r) const
{
  return !(*this == r);
}

template < class R >
inline
const typename RayC2<R>::Point_2 &
RayC2<R>::start() const
{
  return source();
}

template < class R >
CGAL_KERNEL_INLINE
typename RayC2<R>::Point_2
RayC2<R>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  if (i == 0) return source();
  if (i == 1) return second_point();
  return source() + (second_point() - source()) * FT(i);
}

template < class R >
inline
typename RayC2<R>::Direction_2
RayC2<R>::direction() const
{
  return Direction_2( second_point() - source() );
}

template < class R >
inline
typename RayC2<R>::Line_2
RayC2<R>::supporting_line() const
{
  return Line_2(*this);
}

template < class R >
inline
typename RayC2<R>::Ray_2
RayC2<R>::opposite() const
{
  return RayC2<R>( source(), - direction() );
}

template < class R >
CGAL_KERNEL_INLINE
bool RayC2<R>::is_horizontal() const
{
  return y_equal(source(), second_point());
}

template < class R >
CGAL_KERNEL_INLINE
bool RayC2<R>::is_vertical() const
{
  return x_equal(source(), second_point());
}

template < class R >
CGAL_KERNEL_INLINE
bool RayC2<R>::is_degenerate() const
{
  return source() == second_point();
}

template < class R >
CGAL_KERNEL_INLINE
bool
RayC2<R>::has_on(const typename RayC2<R>::Point_2 &p) const
{
  return p == source()
      || collinear(source(), p, second_point())
      && Direction_2(p - source()) == direction();
}

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
bool
RayC2<R>::
collinear_has_on(const typename RayC2<R>::Point_2 &p) const
{
    switch(compare_x(source(), second_point())){
    case SMALLER:
        return compare_x(source(), p) != LARGER;
    case LARGER:
        return compare_x(p, source()) != LARGER;
    default:
        switch(compare_y(source(), second_point())){
        case SMALLER:
            return compare_y(source(), p) != LARGER;
        case LARGER:
            return compare_y(p, source()) != LARGER;
        default:
            return true; // p == source()
        }
    }
}

#ifndef CGAL_NO_OSTREAM_INSERT_RAYC2
template < class R >
std::ostream &
operator<<(std::ostream &os, const RayC2<R> &r)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << r.source() << ' ' << r.direction();
    case IO::BINARY :
        return os << r.source() << r.direction();
    default:
        return os << "RayC2(" << r.source() <<  ", " << r.direction() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYC2
template < class R >
std::istream &
operator>>(std::istream &is, RayC2<R> &r)
{
    typename R::Point_2 p;
    typename R::Direction_2 d;

    is >> p >> d;

    if (is)
	r = RayC2<R>(p, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYC2

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_RAY_2_H
