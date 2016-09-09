// Copyright (c) 1999  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/H2/include/CGAL/Homogeneous/DirectionH2.h,v $
// $Revision: 1.14 $ $Date: 2004/02/19 20:26:35 $
// $Name:  $
//
// Author(s)     : Stefan Schirra
 
#ifndef CGAL_HOMOGENEOUS_DIRECTION_2_H
#define CGAL_HOMOGENEOUS_DIRECTION_2_H

#include <CGAL/Threetuple.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class DirectionH2
{
  typedef typename R_::FT                   FT;
  typedef typename R_::RT                   RT;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Vector_2             Vector_2;
  typedef typename R_::Line_2               Line_2;
  typedef typename R_::Ray_2                Ray_2;
  typedef typename R_::Segment_2            Segment_2;
  typedef typename R_::Aff_transformation_2 Aff_transformation_2;

  typedef Threetuple<RT>                           Rep;
  typedef typename R_::template Handle<Rep>::type  Base;

  Base base;

public:
  typedef R_                                    R;

   DirectionH2() {}

   DirectionH2(const Vector_2 & v )
   { *this = v.direction(); }

   DirectionH2(const Line_2 & l )
   { *this = l.direction(); }

   DirectionH2(const Ray_2 & r )
   { *this = r.direction(); }

   DirectionH2(const Segment_2 & s )
   { *this = s.direction(); }

   DirectionH2(const RT& x, const RT& y)
      : base (x, y, RT(1)) {}

   // TODO Not documented : should not exist , not used.
   // we should also change Threetuple<RT> -> Twotuple<RT>
   DirectionH2(const RT& x, const RT& y, const RT& w )
   {
     if (w > RT(0)   )
       base = Rep(x, y, w);
     else
       base = Rep(-x, -y, -w);
   }

    bool    operator==( const DirectionH2<R>& d) const;
    bool    operator!=( const DirectionH2<R>& d) const;
    bool    counterclockwise_in_between( const DirectionH2<R>& d1,
                                         const DirectionH2<R>& d2 ) const;

    DirectionH2<R> operator-() const;

    Vector_2       to_vector() const;
    Vector_2       vector() const { return to_vector(); }

    const RT & x() const { return get(base).e0; };
    const RT & y() const { return get(base).e1; };

    const RT & delta(int i) const;
    const RT & dx() const { return get(base).e0; };
    const RT & dy() const { return get(base).e1; };

    DirectionH2<R> perpendicular(const Orientation &o) const;
    DirectionH2<R> transform(const Aff_transformation_2 &) const;
};

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

CGAL_END_NAMESPACE

#include <CGAL/Homogeneous/predicates_on_directionsH2.h>

CGAL_BEGIN_NAMESPACE

template <class R >
CGAL_KERNEL_INLINE
bool
DirectionH2<R>::
counterclockwise_in_between( const DirectionH2<R>& d1,
                             const DirectionH2<R>& d2) const
{
  return R().counterclockwise_in_between_2_object()(*this, d1, d2);
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
