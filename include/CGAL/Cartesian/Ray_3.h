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
// file          : include/CGAL/Cartesian/Ray_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.24 $
// revision_date : $Date: 2002/02/06 12:32:38 $
// author(s)     : Andreas Fabri
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_RAY_3_H
#define CGAL_CARTESIAN_RAY_3_H

CGAL_BEGIN_NAMESPACE

template < class R_ >
class RayC3
  : public R_::Ray_handle_3
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::Point_3              Point_3;
  typedef typename R_::Direction_3          Direction_3;
  typedef typename R_::Line_3               Line_3;
  typedef typename R_::Ray_3                Ray_3;
  typedef typename R_::Aff_transformation_3 Aff_transformation_3;

  typedef typename R_::Ray_handle_3              base;
  typedef typename base::element_type            rep;

public:
  typedef R_                                     R;

  RayC3()
    : base(rep()) {}

  RayC3(const Point_3 &sp, const Point_3 &secondp)
    : base(rep(sp, secondp)) {}

  RayC3(const Point_3 &sp, const Direction_3 &d)
    : base(rep(sp, sp + d.to_vector())) {}

  bool        operator==(const RayC3 &r) const;
  bool        operator!=(const RayC3 &r) const;

  const Point_3 &   start() const;
  const Point_3 &   source() const
  {
      return Ptr()->e0;
  }
  const Point_3 &   second_point() const
  {
      return Ptr()->e1;
  }
  Point_3     point(int i) const;

  Direction_3 direction() const;
  Line_3      supporting_line() const;
  Ray_3       opposite() const;

  Ray_3       transform(const Aff_transformation_3 &t) const
  {
    return RayC3<R>(t.transform(source()), t.transform(second_point()));
  }

  bool        is_degenerate() const;
  bool        has_on(const Point_3 &p) const;
  bool        collinear_has_on(const Point_3 &p) const;
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template < class R >
inline
bool
RayC3<R>::operator==(const RayC3<R> &r) const
{
    if (identical(r))
	return true;
    return source() == r.source() && direction() == r.direction();
}

template < class R >
inline
bool
RayC3<R>::operator!=(const RayC3<R> &r) const
{
  return !(*this == r);
}

template < class R >
inline
const typename RayC3<R>::Point_3 &
RayC3<R>::start() const
{
  return source();
}

template < class R >
CGAL_KERNEL_INLINE
typename RayC3<R>::Point_3
RayC3<R>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  if (i == 0) return source();
  if (i == 1) return second_point();
  return source() + FT(i) * (second_point() - source());
}

template < class R >
inline
typename RayC3<R>::Direction_3
RayC3<R>::direction() const
{
  return Direction_3( second_point() - source() );
}

template < class R >
inline
typename RayC3<R>::Line_3
RayC3<R>::supporting_line() const
{
  return Line_3(*this);
}

template < class R >
inline
typename RayC3<R>::Ray_3
RayC3<R>::opposite() const
{
  return RayC3<R>( source(), - direction() );
}

template < class R >
bool
RayC3<R>::
has_on(const typename RayC3<R>::Point_3 &p) const
{
  return (p == source()) ||
         ( collinear(source(), p, second_point())
           && ( Direction_3(p - source()) == direction() ));
}

template < class R >
inline
bool
RayC3<R>::is_degenerate() const
{
  return source() == second_point();
}

template < class R >
inline
bool
RayC3<R>::
collinear_has_on(const typename RayC3<R>::Point_3 &p) const
{
  CGAL_kernel_exactness_precondition( collinear(source(), p, second_point()) );

  Comparison_result cx = compare_x(source(), second_point());
  if (cx != EQUAL)
    return cx != compare_x(p, source());

  Comparison_result cy = compare_y(source(), second_point());
  if (cy != EQUAL)
    return cy != compare_y(p, source());

  Comparison_result cz = compare_z(source(), second_point());
  if (cz != EQUAL)
    return cz != compare_z(p, source());

  return true; // p == source()
}

#ifndef CGAL_NO_OSTREAM_INSERT_RAYC3
template < class R >
std::ostream &
operator<<(std::ostream &os, const RayC3<R> &r)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << r.start() << ' ' << r.direction();
    case IO::BINARY :
        return os<< r.start() << r.direction();
    default:
        return os << "RayC3(" << r.start() <<  ", " << r.direction() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYC3
template < class R >
std::istream &
operator>>(std::istream &is, RayC3<R> &r)
{
    typename R::Point_3 p;
    typename R::Direction_3 d;

    is >> p >> d;

    if (is)
	r = RayC3<R>(p, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYC3

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_RAY_3_H
