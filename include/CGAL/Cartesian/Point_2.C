// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian/Point_2.C
// package       : C2 (4.4)
// revision      : $Revision: 1.18 $
// revision_date : $Date: 2000/08/23 13:45:35 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_POINT_2_C
#define CGAL_CARTESIAN_POINT_2_C

#include <CGAL/Origin.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/number_utils.h>

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_2_H
#define CGAL_CTAG
#endif

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
CGAL_KERNEL_CTOR_INLINE
PointC2<R CGAL_CTAG>::PointC2()
{
  new ( static_cast< void*>(ptr)) Twotuple<FT>(); 
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
PointC2<R CGAL_CTAG>::PointC2(const Origin &)
{
   new ( static_cast< void*>(ptr)) Twotuple<FT>(FT(0), FT(0));
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
PointC2<R CGAL_CTAG>::PointC2(const PointC2<R CGAL_CTAG> &p)
  : Handle_for<Twotuple<typename R::FT> >(p)
{}

template < class R >
CGAL_KERNEL_CTOR_INLINE
PointC2<R CGAL_CTAG>::PointC2(const typename PointC2<R CGAL_CTAG>::Vector_2 &v)
  : Handle_for<Twotuple<typename R::FT> > (v)
{}

template < class R >
CGAL_KERNEL_CTOR_INLINE
PointC2<R CGAL_CTAG>::PointC2(const typename PointC2<R CGAL_CTAG>::FT &hx,
			      const typename PointC2<R CGAL_CTAG>::FT &hy,
                              const typename PointC2<R CGAL_CTAG>::FT &hw)
{
  if( hw != FT(1))
    new ( static_cast< void*>(ptr)) Twotuple<FT>(hx/hw, hy/hw);
  else
    new ( static_cast< void*>(ptr)) Twotuple<FT>(hx, hy);
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
PointC2<R CGAL_CTAG>::PointC2(const typename PointC2<R CGAL_CTAG>::FT &x,
                              const typename PointC2<R CGAL_CTAG>::FT &y)
{
  new ( static_cast< void*>(ptr)) Twotuple<FT>(x, y);
}

template < class R >
inline
PointC2<R CGAL_CTAG>::~PointC2()
{}

template < class R >
inline
bool
PointC2<R CGAL_CTAG>::operator==(const PointC2<R CGAL_CTAG>& p) const
{
  return equal_xy(*this, p);
}

template < class R >
inline
bool
PointC2<R CGAL_CTAG>::operator!=(const PointC2<R CGAL_CTAG>& p) const
{
  return !(*this == p);
}

template < class R >
inline
typename PointC2<R CGAL_CTAG>::FT
PointC2<R CGAL_CTAG>::x() const
{
  return ptr->e0;
}

template < class R >
inline
typename PointC2<R CGAL_CTAG>::FT
PointC2<R CGAL_CTAG>::y() const
{
  return ptr->e1;
}

template < class R >
CGAL_KERNEL_INLINE
typename PointC2<R CGAL_CTAG>::FT
PointC2<R CGAL_CTAG>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i == 0) || (i == 1) );
  return (i == 0) ? x() : y();
}

template < class R >
inline
typename PointC2<R CGAL_CTAG>::FT
PointC2<R CGAL_CTAG>::operator[](int i) const
{
  return cartesian(i);
}

template < class R >
inline
int
PointC2<R CGAL_CTAG>::dimension() const
{
  return 2;
}

template < class R >
inline
typename PointC2<R CGAL_CTAG>::FT
PointC2<R CGAL_CTAG>::hx() const
{
  return x();
}

template < class R >
inline
typename PointC2<R CGAL_CTAG>::FT
PointC2<R CGAL_CTAG>::hy() const
{
  return y();
}

template < class R >
inline
typename PointC2<R CGAL_CTAG>::FT
PointC2<R CGAL_CTAG>::hw() const
{
  return FT(1);
}

template < class R >
inline
typename PointC2<R CGAL_CTAG>::FT
PointC2<R CGAL_CTAG>::homogeneous(int i) const
{
  CGAL_kernel_precondition( (i>=0) && (i<=2) );
  if (i<2)
    return cartesian(i);
  return FT(1);
}

template < class R >
CGAL_KERNEL_INLINE
PointC2<R CGAL_CTAG>
PointC2<R CGAL_CTAG>::
transform( const typename PointC2<R CGAL_CTAG>::Aff_transformation_2 &t) const
{
  return t.transform(*this);
}

template < class R >
CGAL_KERNEL_INLINE
Bbox_2
PointC2<R CGAL_CTAG>::bbox() const
{
  double bx = CGAL::to_double(x());
  double by = CGAL::to_double(y());
  return Bbox_2(bx,by, bx,by);
}

#ifndef CGAL_NO_OSTREAM_INSERT_POINTC2
template < class R >
std::ostream &
operator<<(std::ostream &os, const PointC2<R CGAL_CTAG> &p)
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
operator>>(std::istream &is, PointC2<R CGAL_CTAG> &p)
{
    typename PointC2<R CGAL_CTAG>::FT x, y;
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
    p = PointC2<R CGAL_CTAG>(x, y);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTC2

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

#endif // CGAL_CARTESIAN_POINT_2_C
