// ======================================================================
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
// file          : include/CGAL/Homogeneous/RayH2.h
// package       : H2 (2.67)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/02/06 12:34:07 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_RAYH2_H
#define CGAL_RAYH2_H

CGAL_BEGIN_NAMESPACE

template < class R_ >
class RayH2
  : public R_::Ray_handle_2
{
CGAL_VC7_BUG_PROTECTED
    typedef typename R_::FT                   FT;
    typedef typename R_::RT                   RT;
    typedef typename R_::Point_2              Point_2;
    typedef typename R_::Direction_2          Direction_2;
    typedef typename R_::Line_2               Line_2;
    typedef typename R_::Vector_2             Vector_2;
    typedef typename R_::Aff_transformation_2 Aff_transformation_2;

    typedef typename R_::Ray_handle_2                      Ray_handle_2_;
    typedef typename Ray_handle_2_::element_type           Ray_ref_2;

public:
    typedef R_                                             R;

    RayH2()
      : Ray_handle_2_(Ray_ref_2()) {}
    RayH2( const Point_2& sp, const Point_2& secondp)
      : Ray_handle_2_(Ray_ref_2(sp, secondp)) {}
    RayH2( const Point_2& sp, const Direction_2& d)
      : Ray_handle_2_(Ray_ref_2(sp, sp + d.to_vector())) {}

    bool    operator==(const RayH2<R>& r) const;
    bool    operator!=(const RayH2<R>& r) const;

    const Point_2 & start() const;
    const Point_2 & source() const;
    const Point_2 & second_point() const;
    Point_2     point(int i) const;
    Direction_2    direction() const;
    Line_2         supporting_line() const;
    RayH2<R>       opposite() const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    has_on(const Point_2& p) const;
    bool    collinear_has_on(const Point_2& p) const;
    bool    is_degenerate() const;

    RayH2<R> transform( const Aff_transformation_2 & t) const;
};


template < class R >
inline
const typename RayH2<R>::Point_2 &
RayH2<R>::source() const
{ return Ptr()->e0; }

template < class R >
inline
const typename RayH2<R>::Point_2 &
RayH2<R>::start() const
{ return source(); }

template < class R >
CGAL_KERNEL_INLINE
typename RayH2<R>::Direction_2
RayH2<R>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return Direction_2( second_point() - start() );
}
template < class R >
inline
const typename RayH2<R>::Point_2 &
RayH2<R>::second_point() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return Ptr()->e1;
}

template < class R >
CGAL_KERNEL_INLINE
typename RayH2<R>::Point_2
RayH2<R>::point(int i) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  CGAL_kernel_precondition( i>= 0 );
  Vector_2 v = direction().to_vector();
  return start() + RT(i) * v;
}

template < class R >
inline
typename RayH2<R>::Line_2
RayH2<R>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return Line_2(*this);
}

template < class R >
inline
RayH2<R>
RayH2<R>::opposite() const
{ return RayH2<R>( start(), - direction() ); }

template < class R >
CGAL_KERNEL_INLINE
RayH2<R>
RayH2<R>::
transform(const typename RayH2<R>::Aff_transformation_2 & t) const
{
  return RayH2<R>(t.transform(start()), t.transform(second_point()) );
}

#ifndef CGAL_NO_OSTREAM_INSERT_RAYH2
template < class R >
std::ostream &
operator<<(std::ostream &os, const RayH2<R> &r)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << r.source() << ' ' << r.second_point();
    case IO::BINARY :
        return os << r.source() << r.second_point();
    default:
       return os << "RayC2(" << r.source() <<  ", " << r.second_point() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYH2
template < class R >
std::istream &
operator>>(std::istream &is, RayH2<R> &r)
{
  typename R::Point_2 p, q;
  is >> p >> q;
  r = RayH2<R>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYH2

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::is_horizontal() const
{
  return start().hy()*second_point().hw() == second_point().hy()*start().hw();
}

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::is_vertical() const
{
  return start().hx()*second_point().hw() == second_point().hx()*start().hw();
}

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::has_on(const typename RayH2<R>::Point_2& p) const
{
  return p == start() || Direction_2(p - start()) == direction();
}

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::is_degenerate() const
{ return start() == Ptr()->e1; }

template < class R >
inline
bool
RayH2<R>::collinear_has_on(const typename RayH2<R>::Point_2& p) const
{ return has_on(p); }

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::operator==(const RayH2<R>& r) const
{ return ( (start() == r.start() )&&( direction() == r.direction() ) ); }

template < class R >
inline
bool
RayH2<R>::operator!=( const RayH2<R>& r) const
{ return !(*this == r); }

CGAL_END_NAMESPACE

#endif // CGAL_RAYH2_H
