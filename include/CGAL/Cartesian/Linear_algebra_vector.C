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
// file          : include/CGAL/Cartesian/Linear_algebra_vector.C
// package       : Cd (1.5)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2000/06/27 14:32:24 $
// author        : Herve Brönnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_LINEAR_ALGEBRA_VECTOR_D_C
#define CGAL_CARTESIAN_LINEAR_ALGEBRA_VECTOR_D_C

#include <CGAL/Cartesian/d_utils.h>
#include <iterator>
#include <algorithm>
#include <numeric>

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
LA_vectorCd<R CGAL_CTAG>::
LA_vectorCd(int d)
{
  new_rep(d);
}

template < class R >
LA_vectorCd<R CGAL_CTAG>::
LA_vectorCd(const Handle &v)
  : Handle(v)
{}

template < class R >
LA_vectorCd<R CGAL_CTAG>::
LA_vectorCd(const LA_vectorCd<R CGAL_CTAG> &v)
  : Handle(v)
{}

template < class R >
LA_vectorCd<R CGAL_CTAG>::~LA_vectorCd()
{}

template < class R >
LA_vectorCd<R CGAL_CTAG> &
LA_vectorCd<R CGAL_CTAG>::operator=(const LA_vectorCd<R CGAL_CTAG> &v)
{
  Handle::operator=((const Handle &)v);
  return *this;
}

template < class R >
bool
LA_vectorCd<R CGAL_CTAG>::operator==(const LA_vectorCd<R CGAL_CTAG> &v) const
{
  if (dimension() != v.dimension()) return false;
  if (ptr() == v.ptr()) return true; // identical
  return std::equal(begin(),end(),v.begin());
}

template < class R >
inline
bool
LA_vectorCd<R CGAL_CTAG>::operator!=(const LA_vectorCd<R CGAL_CTAG> &v) const
{
  return !(*this == v);
}

template < class R >
inline
LA_vectorCd<R CGAL_CTAG>
LA_vectorCd<R CGAL_CTAG>::operator+(const LA_vectorCd<R CGAL_CTAG> &v) const
{
  CGAL_kernel_precondition( dimension() == v.dimension() );
  Self w(dimension());
  std::transform(begin(),end(),v.begin(),w.begin(),std::plus<FT>());
  return w;
}

template < class R >
inline
LA_vectorCd<R CGAL_CTAG>
LA_vectorCd<R CGAL_CTAG>::operator-(const LA_vectorCd<R CGAL_CTAG> &v) const
{
  CGAL_kernel_precondition( dimension() == v.dimension() );
  Self w(dimension());
  std::transform(begin(),end(),v.begin(),w.begin(),std::minus<FT>());
  return w;
}

template < class R >
inline
LA_vectorCd<R CGAL_CTAG>
LA_vectorCd<R CGAL_CTAG>::operator-() const
{
  Self v(dimension());
  std::transform(begin(),end(),v.begin(),std::negate<FT>());
  return v;
}

template < class R >
inline
typename LA_vectorCd<R CGAL_CTAG>::FT
LA_vectorCd<R CGAL_CTAG>::operator*(const LA_vectorCd<R CGAL_CTAG> &v) const
{
  CGAL_kernel_precondition( dimension() == v.dimension() );
  return std::inner_product(begin(),end(),v.begin(),FT(0));
}

template < class R >
inline
LA_vectorCd<R CGAL_CTAG>
LA_vectorCd<R CGAL_CTAG>::
operator*(const typename LA_vectorCd<R CGAL_CTAG>::FT &c) const
{
  Self v(dimension());
  std::transform(begin(),end(),v.begin(),std::bind2nd(std::multiplies<FT>(),c));
  return v;
}

template < class R >
inline
LA_vectorCd<R CGAL_CTAG>
LA_vectorCd<R CGAL_CTAG>::
operator/(const typename LA_vectorCd<R CGAL_CTAG>::FT &c) const
{
  Self v(dimension());
  std::transform(begin(),end(),v.begin(),std::bind2nd(std::divides<FT>(),c));
  return v;
}

#ifndef CGAL_CARTESIAN_NO_OSTREAM_INSERT_LA_VECTORCD
template < class R >
std::ostream &
operator<<(std::ostream &os, const LA_vectorCd<R CGAL_CTAG> &v)
{
  typedef typename LA_vectorCd<R CGAL_CTAG>::FT FT;
  print_d<FT> prt(&os);
  if (os.iword(IO::mode)==IO::PRETTY) os << "LA_Vector(";
  prt(v.dimension());
  if (os.iword(IO::mode)==IO::PRETTY) { os << ", ("; prt.reset(); }
  std::for_each(v.begin(),v.end(),prt);
  if (os.iword(IO::mode)==IO::PRETTY) os << "))";
  return os;
}
#endif // CGAL_CARTESIAN_NO_OSTREAM_INSERT_LA_VECTORCD

#ifndef CGAL_CARTESIAN_NO_ISTREAM_EXTRACT_LA_VECTORCD
template < class R >
std::istream &
operator>>(std::istream &is, LA_vectorCd<R CGAL_CTAG> &v)
{
  typedef typename LA_vectorCd<R CGAL_CTAG>::FT FT;
  int dim;
  FT* w;
  switch(is.iword(IO::mode)) {
    case IO::ASCII :
    case IO::BINARY :
      is >> dim;
      v = LA_vectorCd<R CGAL_CTAG>(dim);
      std::copy_n(std::istream_iterator<FT>(is),dim, v.begin());
      break;
    default:
      std::cerr << "" << std::endl;
      std::cerr << "Stream must be in ascii or binary mode" << std::endl;
      break;
  }
  return is;
}
#endif // CGAL_CARTESIAN_NO_ISTREAM_EXTRACT_LA_VECTORCD

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

#endif // CGAL_CARTESIAN_VECTOR_D_C
