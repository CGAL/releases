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
// $Source: /CVSROOT/CGAL/Packages/H2/include/CGAL/Homogeneous/PointH2.h,v $
// $Revision: 1.13 $ $Date: 2003/10/21 12:16:10 $
// $Name: current_submission $
//
// Author(s)     : Stefan Schirra

#ifndef CGAL_HOMOGENEOUS_POINT_2_H
#define CGAL_HOMOGENEOUS_POINT_2_H

#include <CGAL/Origin.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Threetuple.h>
#include <CGAL/Kernel/Cartesian_coordinate_iterator_2.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class PointH2
  : public R_::template Handle<Threetuple<typename R_::RT> >::type
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::RT                   RT;
  typedef typename R_::Vector_2             Vector_2;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Direction_2          Direction_2;
  typedef typename R_::Aff_transformation_2 Aff_transformation_2;

  typedef Threetuple<RT>                           rep;
  typedef typename R_::template Handle<rep>::type  base;

public:
  typedef Cartesian_coordinate_iterator_2<R_> Cartesian_const_iterator;
  typedef R_                                    R;

    PointH2() {}

    PointH2(const Origin &)  
       : base ( rep( RT(0), RT(0), RT(1))) { }

    PointH2(const PointH2<R> & p) 
       : base (p) { }

    PointH2(const Vector_2& v) 
       : base (v) { }

    PointH2(const RT& hx, const RT& hy )
      : base ( rep( hx, hy, RT(1) )) { }

    PointH2(const RT& hx, const RT& hy, const RT& hw)
    {
      if ( hw >= RT(0)   )
        initialize_with( rep( hx, hy, hw)); 
      else
        initialize_with( rep(-hx,-hy,-hw)); 
    }

    bool    operator==( const PointH2<R>& p) const;
    bool    operator!=( const PointH2<R>& p) const;

    const RT & hx() const { return Ptr()->e0; };
    const RT & hy() const { return Ptr()->e1; };
    const RT & hw() const { return Ptr()->e2; };

    FT      x()  const { return FT(hx()) / FT(hw()); };
    FT      y()  const { return FT(hy()) / FT(hw()); };

    FT      cartesian(int i)   const;
    FT      operator[](int i)  const;
    const RT & homogeneous(int i) const;

  Cartesian_const_iterator cartesian_begin() const 
  {
    return Cartesian_const_iterator(static_cast<const Point_2*>(this), 0);
  }

  Cartesian_const_iterator cartesian_end() const 
  {
    return Cartesian_const_iterator(static_cast<const Point_2*>(this), 2);
  }
    int     dimension() const;
    Bbox_2  bbox() const;

    PointH2<R> transform( const Aff_transformation_2 & t) const;
    Direction_2 direction() const;
};

template < class R >
CGAL_KERNEL_INLINE
bool
PointH2<R>::operator==( const PointH2<R>& p) const
{
  return (  (hx() * p.hw() == p.hx() * hw() )
          &&(hy() * p.hw() == p.hy() * hw() ) );
}

template < class R >
inline
bool
PointH2<R>::operator!=( const PointH2<R>& p) const
{ return !(*this == p); }   /* XXX */

template < class R >
CGAL_KERNEL_INLINE
typename PointH2<R>::FT
PointH2<R>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i==0 || i==1) );
  if (i==0)
      return x();
  return y();
}

template < class R >
CGAL_KERNEL_INLINE
const typename PointH2<R>::RT &
PointH2<R>::homogeneous(int i) const
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
typename PointH2<R>::FT
PointH2<R>::operator[](int i) const
{ return cartesian(i); }


template < class R >
inline
int
PointH2<R>::dimension() const
{ return 2; }

template < class R >
CGAL_KERNEL_INLINE
typename PointH2<R>::Direction_2
PointH2<R>::direction() const
{ return typename PointH2<R>::Direction_2(*this); }


template < class R >
CGAL_KERNEL_MEDIUM_INLINE
Bbox_2
PointH2<R>::bbox() const
{
   Interval_nt<> ihx = CGAL::to_interval(hx());
   Interval_nt<> ihy = CGAL::to_interval(hy());
   Interval_nt<> ihw = CGAL::to_interval(hw());

   Interval_nt<> ix = ihx/ihw;
   Interval_nt<> iy = ihy/ihw;

   return Bbox_2(ix.inf(), iy.inf(), ix.sup(), iy.sup());
}


template < class R >
inline
PointH2<R>
PointH2<R>::transform(const typename PointH2<R>::Aff_transformation_2& t) const
{ return t.transform(*this); }

#ifndef CGAL_NO_OSTREAM_INSERT_POINTH2
template < class R >
std::ostream &
operator<<(std::ostream &os, const PointH2<R> &p)
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
        return os << "PointH2(" << p.hx() << ", "
                                << p.hy() << ", "
                                << p.hw() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_POINTH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINTH2
template < class R >
std::istream &
operator>>(std::istream &is, PointH2<R> &p)
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
  p = PointH2<R>(hx, hy, hw);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTH2

CGAL_END_NAMESPACE

#endif // CGAL_HOMOGENEOUS_POINT_2_H
