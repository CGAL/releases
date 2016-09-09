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
// file          : include/CGAL/Cartesian/Vector_3.C
// package       : C3 (5.2)
// revision      : $Revision: 1.23 $
// revision_date : $Date: 2000/08/23 14:34:44 $
// author        : Andreas Fabri
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_VECTOR_3_C
#define CGAL_CARTESIAN_VECTOR_3_C

#include <CGAL/Cartesian/Direction_3.h>

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_3_H
#define CGAL_CTAG
#endif

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
VectorC3<R CGAL_CTAG>::VectorC3()
{
  new ( static_cast< void*>(ptr)) Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class R >
VectorC3<R CGAL_CTAG>::
VectorC3(const VectorC3<R CGAL_CTAG>  &v)
  : Handle_for<Threetuple<typename R::FT> >(v)
{}

template < class R >
VectorC3<R CGAL_CTAG>::
VectorC3(const Null_vector  &)
{
  new  (static_cast< void*>(ptr)) Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class R >
VectorC3<R CGAL_CTAG>::
VectorC3(const typename VectorC3<R CGAL_CTAG>::FT &x,
         const typename VectorC3<R CGAL_CTAG>::FT &y,
         const typename VectorC3<R CGAL_CTAG>::FT &z)
{
  new (static_cast< void*>(ptr)) Threetuple<FT>(x, y, z);
}

template < class R >
VectorC3<R CGAL_CTAG>::
VectorC3(const typename VectorC3<R CGAL_CTAG>::FT &x,
         const typename VectorC3<R CGAL_CTAG>::FT &y,
         const typename VectorC3<R CGAL_CTAG>::FT &z,
         const typename VectorC3<R CGAL_CTAG>::FT &w)
{
  if (w != FT(1))
    new (static_cast< void*>(ptr)) Threetuple<FT>(x/w, y/w, z/w);
  else
    new (static_cast< void*>(ptr)) Threetuple<FT>(x, y, z);
}

template < class R >
VectorC3<R CGAL_CTAG>::~VectorC3()
{}

template < class R >
inline
VectorC3<R CGAL_CTAG>::
VectorC3(const typename VectorC3<R CGAL_CTAG>::Point_3 &p)
  : Handle_for<Threetuple<typename R::FT> >(p)
{}

template < class R >
inline VectorC3<R CGAL_CTAG>::
VectorC3(const typename VectorC3<R CGAL_CTAG>::Direction_3 &d)
  : Handle_for<Threetuple<typename R::FT> >(d)
{}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::x()  const
{
  return ptr->e0;
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::y()  const
{
  return ptr->e1;
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::z()  const
{
  return ptr->e2;
}

template < class R >
bool VectorC3<R CGAL_CTAG>::operator==(const VectorC3<R CGAL_CTAG> &v) const
{
  return x() == v.x() && y() == v.y() && z() == v.z();
}

template < class R >
inline
bool
VectorC3<R CGAL_CTAG>::operator!=(const VectorC3<R CGAL_CTAG> &v) const
{
  return !(*this == v);
}

template < class R >
bool
VectorC3<R CGAL_CTAG>::operator==(const Null_vector &) const
{
  return x() == FT(0) && y() == FT(0) && z() == FT(0);
}

template < class R >
inline
bool
VectorC3<R CGAL_CTAG>::operator!=(const Null_vector &v) const
{
  return !(*this == v);
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i>=0) && (i<3) );
  if (i==0) return x();
  if (i==1) return y();
  return z();
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::operator[](int i) const
{
  return cartesian(i);
}

template < class R >
inline
int
VectorC3<R CGAL_CTAG>::dimension() const
{
  return 3;
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::hx()  const
{
  return x();
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::hy()  const
{
  return y();
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::hz()  const
{
  return z();
}

template < class R >
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::hw()  const
{
  return FT(1);
}

template < class R >
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::homogeneous(int i) const
{
  if (i==3) return FT(1);
  return cartesian(i);
}

template < class R >
inline
VectorC3<R CGAL_CTAG>
VectorC3<R CGAL_CTAG>::
operator+(const VectorC3<R CGAL_CTAG> &w) const
{
  return VectorC3<R CGAL_CTAG>(x() + w.x(), y() + w.y(), z() + w.z());
}

template < class R >
inline
VectorC3<R CGAL_CTAG>
VectorC3<R CGAL_CTAG>::operator-(const VectorC3<R CGAL_CTAG> &w) const
{
  return VectorC3<R CGAL_CTAG>(x() - w.x(), y() - w.y(), z() - w.z());
}

template < class R >
inline
VectorC3<R CGAL_CTAG>
VectorC3<R CGAL_CTAG>::operator-() const
{
  return VectorC3<R CGAL_CTAG>(-x(), -y(), -z());
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::operator*(const VectorC3<R CGAL_CTAG> &w) const
{
  return x() * w.x() + y() * w.y() + z() * w.z();
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::FT
VectorC3<R CGAL_CTAG>::squared_length() const
{
  return CGAL_NTS square(x()) + CGAL_NTS square(y()) + CGAL_NTS square(z());
}

template < class R >
inline
VectorC3<R CGAL_CTAG>
VectorC3<R CGAL_CTAG>::
operator/(const typename VectorC3<R CGAL_CTAG>::FT &c) const
{
  return VectorC3<R CGAL_CTAG>( x()/c, y()/c, z()/c);
}

template < class R >
inline
typename VectorC3<R CGAL_CTAG>::Direction_3
VectorC3<R CGAL_CTAG>::direction() const
{
  return Direction_3(*this);
}

template < class R >
VectorC3<R CGAL_CTAG>
VectorC3<R CGAL_CTAG>::
transform(const typename VectorC3<R CGAL_CTAG>::Aff_transformation_3 &t) const
{
  return t.transform(*this);
}

#ifndef CGAL_CARTESIAN_NO_OSTREAM_INSERT_VECTORC3
template < class R >
std::ostream &
operator<<(std::ostream &os, const VectorC3<R CGAL_CTAG> &v)
{
  switch(os.iword(IO::mode)) {
    case IO::ASCII :
      return os << v.x() << ' ' << v.y()  << ' ' << v.z();
    case IO::BINARY :
      write(os, v.x());
      write(os, v.y());
      write(os, v.z());
      return os;
    default:
      os << "VectorC3(" << v.x() << ", " << v.y() <<  ", " << v.z() << ")";
      return os;
  }
}
#endif // CGAL_CARTESIAN_NO_OSTREAM_INSERT_VECTORC3

#ifndef CGAL_CARTESIAN_NO_ISTREAM_EXTRACT_VECTORC3
template < class R >
std::istream &
operator>>(std::istream &is, VectorC3<R CGAL_CTAG> &p)
{
  typename R::FT x, y, z;
  switch(is.iword(IO::mode)) {
    case IO::ASCII :
      is >> x >> y >> z;
      break;
    case IO::BINARY :
      read(is, x);
      read(is, y);
      read(is, z);
      break;
    default:
      std::cerr << "" << std::endl;
      std::cerr << "Stream must be in ascii or binary mode" << std::endl;
      break;
  }
  p = VectorC3<R CGAL_CTAG>(x, y, z);
  return is;
}
#endif // CGAL_CARTESIAN_NO_ISTREAM_EXTRACT_VECTORC3

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

#endif // CGAL_CARTESIAN_VECTOR_3_C
