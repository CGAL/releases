// Copyright (c) 1999,2001  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/H2/include/CGAL/Homogeneous/TriangleH2.h,v $
// $Revision: 1.13 $ $Date: 2003/10/21 12:16:11 $
// $Name: current_submission $
//
// Author(s)     : Stefan Schirra

#ifndef CGAL_TRIANGLEH2_H
#define CGAL_TRIANGLEH2_H

#include <CGAL/Threetuple.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class TriangleH2
  : public R_::template Handle<Threetuple<typename R_::Point_2> >::type
{
CGAL_VC7_BUG_PROTECTED
    typedef typename R_::FT                   FT;
    typedef typename R_::RT                   RT;
    typedef typename R_::Point_2              Point_2;
    typedef typename R_::Vector_2             Vector_2;
    typedef typename R_::Aff_transformation_2 Aff_transformation_2;

    typedef Threetuple<Point_2>                      rep;
    typedef typename R_::template Handle<rep>::type  base;

public:
    typedef R_                                    R;

    TriangleH2() {}

    TriangleH2(const Point_2& p, const Point_2& q, const Point_2& r)
      : base(rep(p, q, r)) {}

    Bbox_2             bbox() const;

    TriangleH2<R>  opposite() const;
    TriangleH2<R>  transform(const Aff_transformation_2&) const;

    Orientation        orientation() const;

    Oriented_side      oriented_side(const Point_2& ) const;
    Bounded_side       bounded_side(const Point_2& ) const;
    bool               has_on_positive_side( const Point_2& ) const;
    bool               has_on_negative_side( const Point_2& ) const;
    bool               has_on_boundary( const Point_2& ) const;
    bool               has_on_bounded_side( const Point_2& ) const;
    bool               has_on_unbounded_side(const Point_2& )const;
    bool               is_degenerate() const;

    bool               operator==( const TriangleH2<R>& ) const;
    bool               operator!=( const TriangleH2<R>& ) const;

    // bool               oriented_equal( const TriangleH2<R>& ) const;
    // bool               unoriented_equal( const TriangleH2<R>& ) const;

    const Point_2 & vertex(int i) const;
    const Point_2 & operator[](int i) const;

    FT                 area() const;
};

template <class R>
CGAL_KERNEL_INLINE
const typename TriangleH2<R>::Point_2 &
TriangleH2<R>::vertex(int i) const
{
  switch (i%3)
  {
     case 0:  return Ptr()->e0;
     case 1:  return Ptr()->e1;
     default: /*case 2:*/  return Ptr()->e2;
  }
}

template <class R>
inline
const typename TriangleH2<R>::Point_2 &
TriangleH2<R>::operator[](int i) const
{ return vertex(i); }

template <class R>
inline
typename TriangleH2<R>::FT
TriangleH2<R>::area() const
{ 
   Vector_2 v1 = vertex(1) - vertex(0);
   Vector_2 v2 = vertex(2) - vertex(0);

   typename R::RT num = v1.hx()*v2.hy() - v2.hx()*v1.hy();
   typename R::RT den = RT(2) * v1.hw() * v2.hw();
   return FT(num)/FT(den);
}

template <class R>
inline
Orientation
TriangleH2<R>::orientation() const
{ return CGAL::orientation(vertex(0), vertex(1), vertex(2)); }

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
Oriented_side
TriangleH2<R>::oriented_side( const typename TriangleH2<R>::Point_2& p) const
{
  Orientation o12 = CGAL::orientation( vertex(1), vertex(2), p);
  Orientation o23 = CGAL::orientation( vertex(2), vertex(3), p);
  Orientation o31 = CGAL::orientation( vertex(3), vertex(1), p);

  if (orientation() == CLOCKWISE)
  {
      if (  (o12 == COUNTERCLOCKWISE)
          ||(o23 == COUNTERCLOCKWISE)
          ||(o31 == COUNTERCLOCKWISE) )
      {
          return ON_POSITIVE_SIDE;
      }
      if (  (o12 == COLLINEAR)
          ||(o23 == COLLINEAR)
          ||(o31 == COLLINEAR) )
      {
          return ON_ORIENTED_BOUNDARY;
      }
      else
      {
          return ON_NEGATIVE_SIDE;
      }
  }
  else       // COUNTERCLOCKWISE
  {
      if (  (o12 == CLOCKWISE)
          ||(o23 == CLOCKWISE)
          ||(o31 == CLOCKWISE) )
      {
          return ON_NEGATIVE_SIDE;
      }
      if (  (o12 == COLLINEAR)
          ||(o23 == COLLINEAR)
          ||(o31 == COLLINEAR) )
      {
          return ON_ORIENTED_BOUNDARY;
      }
      else
      {
          return ON_POSITIVE_SIDE;
      }
  }
}

template <class R>
inline
bool
TriangleH2<R>::
has_on_positive_side( const typename TriangleH2<R>::Point_2& p) const
{ return ( oriented_side(p) == ON_POSITIVE_SIDE ); }

template <class R>
inline
bool
TriangleH2<R>::has_on_boundary(const typename TriangleH2<R>::Point_2& p) const
{ return oriented_side(p) == ON_ORIENTED_BOUNDARY; }

template <class R>
inline
bool
TriangleH2<R>::
has_on_negative_side( const typename TriangleH2<R>::Point_2& p) const
{ return  oriented_side(p) == ON_NEGATIVE_SIDE; }

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
Bounded_side
TriangleH2<R>::bounded_side(const typename TriangleH2<R>::Point_2& p) const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  Orientation o12 = CGAL::orientation( vertex(1), vertex(2), p);
  Orientation o23 = CGAL::orientation( vertex(2), vertex(3), p);
  Orientation o31 = CGAL::orientation( vertex(3), vertex(1), p);
  Orientation ori = orientation();
  Orientation opp = CGAL::opposite( ori);

  if ( (o12 == opp) || (o23 == opp) || (o31 == opp) )
  {
      return ON_UNBOUNDED_SIDE;
  }
  if ( (o12 == ori) && (o23 == ori) && (o31 == ori) )
  {
      return ON_BOUNDED_SIDE;
  }
  return ON_BOUNDARY;
}

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
bool
TriangleH2<R>::
has_on_bounded_side(const typename TriangleH2<R>::Point_2& p) const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  Orientation o12 = CGAL::orientation( vertex(1), vertex(2), p);
  Orientation o23 = CGAL::orientation( vertex(2), vertex(3), p);
  Orientation o31 = CGAL::orientation( vertex(3), vertex(1), p);
  Orientation ori = orientation();

  return  ( (o12 == ori) && (o23 == ori) && (o31 == ori) );
}

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
bool
TriangleH2<R>::
has_on_unbounded_side(const typename TriangleH2<R>::Point_2& p) const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  Orientation o12 = CGAL::orientation( vertex(1), vertex(2), p);
  Orientation o23 = CGAL::orientation( vertex(2), vertex(3), p);
  Orientation o31 = CGAL::orientation( vertex(3), vertex(1), p);
  Orientation opp = CGAL::opposite( orientation() );

  return  ( (o12 == opp) || (o23 == opp) || (o31 == opp) );
}

template <class R>
inline
bool
TriangleH2<R>::is_degenerate() const
{ return orientation() == COLLINEAR; }

template <class R>
inline
Bbox_2
TriangleH2<R>::bbox() const
{ return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox(); }

template <class R>
CGAL_KERNEL_INLINE
TriangleH2<R>
TriangleH2<R>::
transform( const typename TriangleH2<R>::Aff_transformation_2& t) const
{
  return TriangleH2<R>(t.transform(vertex(0)),
                       t.transform(vertex(1)),
                       t.transform(vertex(2)) );
}

template <class R>
CGAL_KERNEL_INLINE
TriangleH2<R>
TriangleH2<R>::opposite() const
{ return TriangleH2<R>(vertex(0), vertex(2), vertex(1)); }

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
bool
TriangleH2<R>::operator==(const TriangleH2<R>& t) const
{
  int j = 0;
  while ( (t.vertex(0) != vertex(j)) && (j < 3) ) j++;
  if ( j == 3)
  {
      return false;
  }
  if ( (t.vertex(1) == vertex(j+1)) && (t.vertex(2) == vertex(j+2)) )
  {
      return true;
  }
  return false;
}

template <class R>
inline
bool
TriangleH2<R>::operator!=(const TriangleH2<R>& t) const
{ return !(*this == t); }

#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLEH2
template < class R >
std::ostream &
operator<<(std::ostream &os, const TriangleH2<R> &t)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2];
    case IO::BINARY :
        return os << t[0] << t[1]  << t[2];
    default:
       return os<< "TriangleH2(" << t[0] << ", " << t[1] << ", " << t[2] <<")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLEH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLEH2
template < class R >
std::istream &
operator>>(std::istream &is, TriangleH2<R> &t)
{
  typename R::Point_2 p, q, r;
  is >> p >> q >> r;
  t = TriangleH2<R>(p, q, r);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLEH2

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGLEH2_H
