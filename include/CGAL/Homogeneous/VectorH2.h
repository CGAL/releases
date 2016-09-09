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
// $Source: /CVSROOT/CGAL/Packages/H2/include/CGAL/Homogeneous/VectorH2.h,v $
// $Revision: 1.14 $ $Date: 2003/10/21 12:16:12 $
// $Name: current_submission $
//
// Author(s)     : Stefan Schirra
 

#ifndef CGAL_HOMOGENEOUS_VECTOR_2_h
#define CGAL_HOMOGENEOUS_VECTOR_2_h

#include <CGAL/Origin.h>
#include <CGAL/Threetuple.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class VectorH2
  : public R_::template Handle<Threetuple<typename R_::RT> >::type
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::RT                   RT;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Segment_2            Segment_2;
  typedef typename R_::Ray_2                Ray_2;
  typedef typename R_::Line_2               Line_2;
  typedef typename R_::Direction_2          Direction_2;
  typedef typename R_::Vector_2             Vector_2;
  typedef typename R_::Aff_transformation_2 Aff_transformation_2;

  typedef Threetuple<RT>                           rep;
  typedef typename R_::template Handle<rep>::type  base;

public:
  typedef R_                                    R;

   VectorH2() {}

   VectorH2(const Point_2& a, const Point_2& b)
      : base (b-a) {}

   VectorH2(const Segment_2& s)
      : base (s.to_vector()) {}

   VectorH2(const Ray_2& r)
      : base (r.to_vector()) {}

   VectorH2(const Line_2& l)
      : base (l.to_vector()) {}

   VectorH2(const Null_vector &)
      : base ( rep(RT(0), RT(0), RT(1) )) {}

   VectorH2(const RT& x, const RT& y)
      : base ( rep( x,  y,  RT(1) )) {}

   VectorH2(const RT& x, const RT& y, const RT& w )
   {
     if ( w >= RT(0)   )
     { initialize_with( rep( x,  y,  w)); }
     else
     { initialize_with( rep(-x, -y, -w)); }
   }

   bool    operator==( const VectorH2<R>& v) const;
   bool    operator!=( const VectorH2<R>& v) const;
   bool    operator==( const Null_vector&) const;
   bool    operator!=( const Null_vector& v) const;

   const RT & hx() const { return Ptr()->e0; };
   const RT & hy() const { return Ptr()->e1; };
   const RT & hw() const { return Ptr()->e2; };

   FT      x()  const { return FT(hx()) / FT(hw()); };
   FT      y()  const { return FT(hy()) / FT(hw()); };

   FT      cartesian(int i)   const;
   const RT & homogeneous(int i) const;
   FT      operator[](int i)  const;

   int     dimension() const;
   Direction_2 direction() const;
   Vector_2 transform(const Aff_transformation_2& t ) const;
   Vector_2 perpendicular(const Orientation& o ) const;

   Vector_2 operator+(const VectorH2 &v) const;
   Vector_2 operator-(const VectorH2 &v) const;
   FT       operator*(const VectorH2 &v) const;
   Vector_2 operator-() const;
   Vector_2 opposite() const;
   Vector_2 operator*(const RT &f) const;
   Vector_2 operator*(const FT &f) const;
   FT squared_length() const;
   Vector_2 operator/(const RT &f) const;
   Vector_2 operator/(const FT &f) const;

// undocumented:
   VectorH2(const Direction_2 & dir)
      : base ( dir) {}

  VectorH2(const Point_2 & p)
     : base ( p) {}
};

template < class R >
inline
bool
VectorH2<R>::operator==( const Null_vector&) const
{ return (hx() == RT(0)) && (hy() == RT(0)); }

template < class R >
inline
bool
VectorH2<R>::operator!=( const Null_vector& v) const
{ return !(*this == v); }

template < class R >
CGAL_KERNEL_INLINE
bool
VectorH2<R>::operator==( const VectorH2<R>& v) const
{
  return (  (hx() * v.hw() == v.hx() * hw() )
          &&(hy() * v.hw() == v.hy() * hw() ) );
}

template < class R >
inline
bool
VectorH2<R>::operator!=( const VectorH2<R>& v) const
{ return !(*this == v); }  /* XXX */

template < class R >
CGAL_KERNEL_INLINE
typename VectorH2<R>::FT
VectorH2<R>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i==0 || i==1) );
  if (i==0)
      return x();
  return y();
}

template < class R >
CGAL_KERNEL_INLINE
const typename VectorH2<R>::RT &
VectorH2<R>::homogeneous(int i) const
{
  CGAL_kernel_precondition( (i>=0) && (i<=2) );
  if (i==0)
      return hx();
  if (i==1)
      return hy();
  return hw();
}

template < class R >
inline
typename VectorH2<R>::FT
VectorH2<R>::operator[](int i) const
{ return cartesian(i); }

template < class R >
inline
int
VectorH2<R>::dimension() const
{ return 2; }

template < class R >
CGAL_KERNEL_INLINE
typename VectorH2<R>::Direction_2
VectorH2<R>::direction() const
{ return Direction_2(*this); }

template < class R >
inline
typename VectorH2<R>::Vector_2
VectorH2<R>::operator-() const
{ return VectorH2<R>(- hx(), - hy(), hw() ); }

template < class R >
inline
typename VectorH2<R>::Vector_2
VectorH2<R>::opposite() const
{ return VectorH2<R>(- hx(), - hy(), hw() ); }

template <class R>
CGAL_KERNEL_INLINE
typename VectorH2<R>::Vector_2
VectorH2<R>::operator+(const VectorH2<R>& v) const
{
  return VectorH2<R>( hx()*v.hw() + v.hx()*hw(),
                      hy()*v.hw() + v.hy()*hw(),
                      hw()*v.hw() );
}

template <class R>
CGAL_KERNEL_INLINE
typename VectorH2<R>::Vector_2
VectorH2<R>::operator-(const VectorH2<R>& v) const
{
  return VectorH2<R>( hx()*v.hw() - v.hx()*hw(),
                      hy()*v.hw() - v.hy()*hw(),
                      hw()*v.hw() );
}

template <class R>
CGAL_KERNEL_INLINE
typename VectorH2<R>::FT
VectorH2<R>::operator*(const VectorH2<R>& v) const
{
  typedef typename R::RT RT;
  typedef typename R::FT FT;
  return FT( RT(hx()*v.hx() + hy()*v.hy()) ) / FT( RT(hw()*v.hw() ) );
}

template <class R>
CGAL_KERNEL_INLINE
typename VectorH2<R>::FT
VectorH2<R>::squared_length() const
{
  typedef typename R::FT FT;
  return 
    FT( CGAL_NTS square(hx()) + CGAL_NTS square(hy()) ) / 
    FT( CGAL_NTS square(hw()) );
}

template <class R>
CGAL_KERNEL_INLINE
typename VectorH2<R>::Vector_2
VectorH2<R>::operator/(const typename VectorH2<R>::RT& f) const
{ return VectorH2<R>( hx(), hy(), hw()*f ); }

template <class R>
CGAL_KERNEL_INLINE
typename VectorH2<R>::Vector_2
VectorH2<R>::operator/(const typename VectorH2<R>::FT& f) const
{ return VectorH2<R>( hx()*f.denominator(), hy()*f.denominator(),
	              hw()*f.numerator() ); }

template <class R>
CGAL_KERNEL_INLINE
typename VectorH2<R>::Vector_2
VectorH2<R>::operator*(const typename VectorH2<R>::RT& f) const
{ return VectorH2<R>( hx()*f, hy()*f, hw() ); }

template <class R>
CGAL_KERNEL_INLINE
typename VectorH2<R>::Vector_2
VectorH2<R>::operator*(const typename VectorH2<R>::FT& f) const
{ return VectorH2<R>( hx()*f.numerator(), hy()*f.numerator(),
	              hw()*f.denominator() ); }

template <class R>
CGAL_KERNEL_INLINE
typename R::Vector_2
operator*(const typename R::RT& f, const VectorH2<R>& v)
{ return VectorH2<R>( v.hx()*f, v.hy()*f, v.hw() ); }

template <class R>
inline
PointH2<R>
origin_plus_vector(const VectorH2<R>& v)
{ return PointH2<R>( v ); }

template <class R>
inline
typename R::Point_2
operator+(const Origin&, const VectorH2<R>& v)
{ return origin_plus_vector( v ); }

template <class R>
inline
typename R::Point_2
origin_minus_vector(const VectorH2<R>& v)
{ return PointH2<R>( v.opposite() ); }

template <class R>
inline
typename R::Point_2
operator-(const Origin&, const VectorH2<R>& v)
{ return origin_minus_vector( v ); }

template <class R>
inline
typename R::Vector_2
point_minus_origin(const PointH2<R>& p)
{ return VectorH2<R>( p ); }

template <class R>
inline
typename R::Vector_2
operator-(const PointH2<R>& p, const Origin&)
{ return point_minus_origin( p ); }

template <class R>
inline
typename R::Vector_2
origin_minus_point(const PointH2<R>& p)
{ return  VectorH2<R>( p ).opposite(); }

template <class R>
inline
typename R::Vector_2
operator-(const Origin&, const PointH2<R>& p)
{ return  origin_minus_point( p ); }

template <class R>
CGAL_KERNEL_INLINE
typename R::Point_2
operator+(const PointH2<R>& p, const VectorH2<R>& v)
{
  return PointH2<R>( p.hx()*v.hw() + v.hx()*p.hw(),
                     p.hy()*v.hw() + v.hy()*p.hw(),
                     p.hw()*v.hw() );
}

template <class R>
CGAL_KERNEL_INLINE
typename R::Point_2
operator-(const PointH2<R>& p, const VectorH2<R>& v)
{
  return PointH2<R>( p.hx()*v.hw() - v.hx()*p.hw(),
                     p.hy()*v.hw() - v.hy()*p.hw(),
                     p.hw()*v.hw() );
}

template <class R>
CGAL_KERNEL_INLINE
typename R::Vector_2
operator-(const PointH2<R>& p, const PointH2<R>& q)
{
  return VectorH2<R>( p.hx()*q.hw() - q.hx()*p.hw(),
                      p.hy()*q.hw() - q.hy()*p.hw(),
                      p.hw()*q.hw() );
}

template < class R >
CGAL_KERNEL_INLINE
typename VectorH2<R>::Vector_2
VectorH2<R>::perpendicular(const Orientation& o) const
{
  CGAL_kernel_precondition(o != COLLINEAR);
  if (o == COUNTERCLOCKWISE)
  {
      return VectorH2<R>(-hy(), hx(), hw());
  }
  else
  {
      return VectorH2<R>(hy(), -hx(), hw());
  }
}

template < class R >
inline
typename VectorH2<R>::Vector_2
VectorH2<R>::
transform(const typename VectorH2<R>::Aff_transformation_2& t) const
{ return t.transform(*this); }


#ifndef CGAL_NO_OSTREAM_INSERT_VECTORH2
template < class R >
std::ostream &
operator<<(std::ostream &os, const VectorH2<R> &p)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << p.hx() << ' ' << p.hy() << ' ' << p.hw();
    case IO::BINARY :
        write(os, p.hx());
        write(os, p.hy());
        write(os, p.hw());
        return os;
    default:
        return os << "VectorH2(" << p.hx() << ", "
                                 << p.hy() << ", "
                                 << p.hw() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTORH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTORH2
template < class R >
std::istream &
operator>>(std::istream &is, VectorH2<R> &p)
{
  typename R::RT hx, hy, hw;
  switch(is.iword(IO::mode))
  {
    case IO::ASCII :
        is >> hx >> hy >> hw;
        break;
    case IO::BINARY :
        read(is, hx);
        read(is, hy);
        read(is, hw);
        break;
    default:
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;
  }
  p = VectorH2<R>(hx, hy, hw);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTORH2

CGAL_END_NAMESPACE

#endif // CGAL_HOMOGENEOUS_VECTOR_2_h
