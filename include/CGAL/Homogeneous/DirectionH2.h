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
// file          : include/CGAL/Homogeneous/DirectionH2.h
// package       : H2 (2.67)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/02/06 12:34:06 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_HOMOGENEOUS_DIRECTION_2_H
#define CGAL_HOMOGENEOUS_DIRECTION_2_H

CGAL_BEGIN_NAMESPACE

template < class R_ >
class DirectionH2
  : public R_::Direction_handle_2
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::RT                   RT;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Vector_2             Vector_2;
  typedef typename R_::Line_2               Line_2;
  typedef typename R_::Ray_2                Ray_2;
  typedef typename R_::Segment_2            Segment_2;
  typedef typename R_::Aff_transformation_2 Aff_transformation_2;

  typedef typename R_::Direction_handle_2        Direction_handle_2_;
  typedef typename Direction_handle_2_::element_type  Direction_ref_2;

public:
  typedef R_                                    R;

   DirectionH2()
      : Direction_handle_2_ ( Direction_ref_2()) {}

   DirectionH2(const DirectionH2<R>& d )
      : Direction_handle_2_ ( d ) {}

   DirectionH2(const Point_2 & p )
      : Direction_handle_2_ ( p) {}

   DirectionH2(const Vector_2 & v )
      : Direction_handle_2_ ( v) {}

   DirectionH2(const Line_2 & l )
      : Direction_handle_2_ ( l.direction()) {}

   DirectionH2(const Ray_2 & r )
      : Direction_handle_2_ ( r.direction()) {}

   DirectionH2(const Segment_2 & s )
      : Direction_handle_2_ ( s.direction()) {}

   DirectionH2(const RT& x, const RT& y)
      : Direction_handle_2_ ( Direction_ref_2( x, y, RT(1) )) {}

   // TODO Not documented : should not exist , not used.
   // we should also change Threetuple<RT> -> Twotuple<RT>
   DirectionH2(const RT& x, const RT& y, const RT& w )
   {
     if (w > RT(0)   )
       initialize_with( Direction_ref_2( x, y, w));
     else
       initialize_with( Direction_ref_2(-x,-y,-w));
   }

    bool    operator==( const DirectionH2<R>& d) const;
    bool    operator!=( const DirectionH2<R>& d) const;
    bool    operator< ( const DirectionH2<R>& d) const;
    bool    operator<=( const DirectionH2<R>& d) const;
    bool    operator> ( const DirectionH2<R>& d) const;
    bool    operator>=( const DirectionH2<R>& d) const;
    bool    counterclockwise_in_between( const DirectionH2<R>& d1,
                                         const DirectionH2<R>& d2 ) const;

    DirectionH2<R> operator-() const;

    Vector_2       to_vector() const;
    Vector_2       vector() const { return to_vector(); }

    const RT & x() const { return Ptr()->e0; };
    const RT & y() const { return Ptr()->e1; };

    const RT & delta(int i) const;
    const RT & dx() const { return Ptr()->e0; };
    const RT & dy() const { return Ptr()->e1; };

    DirectionH2<R> perpendicular(const Orientation &o) const;
    DirectionH2<R> transform(const Aff_transformation_2 &) const;
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template <class R >
CGAL_KERNEL_INLINE
bool
DirectionH2<R>::operator==( const DirectionH2<R>& d) const
{
  return (  ( x() * d.y() == y() * d.x() )
          &&( CGAL_NTS sign( x() ) == CGAL_NTS sign( d.x() ) )
          &&( CGAL_NTS sign( y() ) == CGAL_NTS sign( d.y() ) ) );
}

template <class R >
inline
bool
DirectionH2<R>::operator!=( const DirectionH2<R>& d) const
{ return !(*this == d); }

template <class R >
inline
DirectionH2<R>
DirectionH2<R>::operator-() const
{ return DirectionH2<R>( - x(), - y() ); }

template <class R >
CGAL_KERNEL_INLINE
const typename DirectionH2<R>::RT &
DirectionH2<R>::delta(int i) const
{
  CGAL_kernel_precondition( ( i == 0 ) || ( i == 1 ) );
  if (i == 0)
      return dx();
  return dy();
}

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#include <CGAL/Homogeneous/predicates_on_directionsH2.h>

CGAL_BEGIN_NAMESPACE

template <class R >
inline
bool
DirectionH2<R>::operator< (const DirectionH2<R>& d) const
{ return (compare_angle_with_x_axis(*this,d) == SMALLER); }

template <class R >
inline
bool
DirectionH2<R>::operator> (const DirectionH2<R>& d) const
{ return (compare_angle_with_x_axis(*this,d) == LARGER); }

template <class R >
inline
bool
DirectionH2<R>::operator>= (const DirectionH2<R>& d) const
{ return !(compare_angle_with_x_axis(*this,d) == SMALLER); }

template <class R >
inline
bool
DirectionH2<R>::operator<= (const DirectionH2<R>& d) const
{ return !(compare_angle_with_x_axis(*this,d) == LARGER); }

template <class R >
CGAL_KERNEL_INLINE
bool
DirectionH2<R>::
counterclockwise_in_between( const DirectionH2<R>& d1,
                             const DirectionH2<R>& d2) const
{
  if ( d1 < *this)
  {
      return ( *this < d2 )||( d2 <= d1 );
  }
  else
  {
      return ( *this < d2 )&&( d2 <= d1 );
  }
}

template <class R >
CGAL_KERNEL_INLINE
DirectionH2<R>
DirectionH2<R>::perpendicular(const Orientation& o) const
{
  CGAL_kernel_precondition(o != COLLINEAR);
  if (o == COUNTERCLOCKWISE)
  {
      return DirectionH2<R>(-dy(), dx());
  }
  else
  {
      return DirectionH2<R>(dy(), -dx());
  }
}

template <class R >
inline
DirectionH2<R>
DirectionH2<R>::
transform(const typename DirectionH2<R>::Aff_transformation_2& t) const
{ return t.transform(*this); }

template <class R >
CGAL_KERNEL_INLINE
typename DirectionH2<R>::Vector_2
DirectionH2<R>::to_vector() const
{ return Vector_2(dx(), dy()); }


#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTIONH2
template < class R >
std::ostream &
operator<<(std::ostream &os, const DirectionH2<R> &p)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << p.dx() << ' ' << p.dy();
    case IO::BINARY :
        write(os, p.dx());
        write(os, p.dy());
        return os;
    default:
        return os << "DirectionH2(" << p.dx() << ", "
                                    << p.dy() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTIONH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTIONH2
template < class R >
std::istream &
operator>>(std::istream &is, DirectionH2<R> &p)
{
  typename R::RT x, y;
  switch(is.iword(IO::mode))
  {
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
  p = DirectionH2<R>(x, y);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTIONH2

CGAL_END_NAMESPACE

#endif // CGAL_HOMOGENEOUS_DIRECTION_2_H
