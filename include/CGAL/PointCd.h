// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : ddim_points.fw
// file          : include/CGAL/PointCd.h
// package       : _d (0.9.2)
// revision      : 0.9.2
// revision_date : 01 Jul 1998 
// author(s)     : Sven Schoenherr
//                 Bernd Gaertner
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_POINTCD_H
#define CGAL_POINTCD_H

#ifndef CGAL_D_TUPLE_H
#include <CGAL/d_tuple.h>
#endif // CGAL_D_TUPLE_H

template < class FT >
class CGAL_DACd;

template < class FT >
class CGAL_PointCd : public CGAL_Handle
{
    friend class CGAL_DACd<FT>;

    public:
    CGAL_PointCd ();
    CGAL_PointCd (int dim, const CGAL_Origin&);
    CGAL_PointCd (const CGAL_PointCd<FT> &p);

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES

    template <class InputIterator>
    CGAL_PointCd (int dim, InputIterator first, InputIterator last);
#else
    CGAL_PointCd (int dim, const FT* first, const FT* last);

#endif // CGAL_CFG_NO_MEMBER_TEMPLATES

    ~CGAL_PointCd();

    CGAL_PointCd<FT> &operator=(const CGAL_PointCd<FT> &p);

      bool operator==(const CGAL_PointCd<FT> &p) const;
      bool operator!=(const CGAL_PointCd<FT> &p) const;

    int id() const;

    FT homogeneous (int i) const;
    FT cartesian (int i) const;
    FT operator[] (int i) const;

    int dimension () const;

    private:
     const CGAL__d_tuple<FT>* ptr() const;
};

template < class FT >
CGAL_KERNEL_INLINE
const CGAL__d_tuple<FT>* CGAL_PointCd<FT>::ptr() const
{
  return (CGAL__d_tuple<FT>*)PTR;
}

#ifndef CGAL_ORIGIN_H
#include <CGAL/Origin.h>
#endif // CGAL_ORIGIN_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointCd<FT>::CGAL_PointCd()
{
  PTR = new CGAL__d_tuple<FT>();
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointCd<FT>::CGAL_PointCd(int dim, const CGAL_Origin &)
{
  CGAL_kernel_precondition (dim>=0);
  PTR = new CGAL__d_tuple<FT>(dim);
  FT *e = ptr()->e, *i;
  for (i=e; i<e+dim; *(i++)=FT(0));  // XXX
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointCd<FT>::CGAL_PointCd(const CGAL_PointCd<FT> &p)
  : CGAL_Handle((CGAL_Handle&)p)
{}

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES

template < class FT >
CGAL_KERNEL_CTOR_INLINE
template <class InputIterator>
CGAL_PointCd<FT>::
CGAL_PointCd(int dim, InputIterator first, InputIterator last)
{
    CGAL_kernel_precondition (dim>=0);
    PTR = new CGAL__d_tuple<FT>(dim);
    FT *e = ptr()->e, *o;
    InputIterator i;
    for (i=first, o=e; (i<last) && (o<e+dim); *(o++) = *(i++));
    CGAL_kernel_precondition (o==e+dim);
    if (i<last) {
    FT h = *(i++);
    CGAL_kernel_precondition (!CGAL_is_zero (h));
    CGAL_kernel_precondition (i==last);
    for (o=e; o<e+dim; *(o++)/=h);
    }
}

#else

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointCd<FT>::CGAL_PointCd(int dim,
                  const FT* first,
                  const FT* last)
{
    CGAL_kernel_precondition (dim>=0);
    PTR = new CGAL__d_tuple<FT>(dim);
    FT *e = ptr()->e, *o;
    const FT *i;
    for (i=first, o=e; (i<last) && (o<e+dim); *(o++) = *(i++));
    CGAL_kernel_precondition (o==e+dim);
    if (i<last) {
    FT h = *(i++);
    CGAL_kernel_precondition (!CGAL_is_zero (h));
    CGAL_kernel_precondition (i==last);
    for (o=e; o<e+dim; *(o++)/=h);
    }
}


#endif // CGAL_CFG_NO_MEMBER_TEMPLATES

template < class FT >
inline
CGAL_PointCd<FT>::~CGAL_PointCd()
{}

template < class FT >
inline
CGAL_PointCd<FT> &CGAL_PointCd<FT>::operator=(const CGAL_PointCd<FT> &p)
{
  CGAL_Handle::operator=(p);
  return *this;
}

template < class FT >
inline
bool CGAL_PointCd<FT>::operator==(const CGAL_PointCd<FT>& p) const
{
  int d = dimension();
  if (d != p.dimension()) return false;
  FT *e = ptr()->e, *ep = p.ptr()->e;
  for (FT *i=e, *j=ep; i<e+d; ++i, ++j)
      if (*i != *j) return false;
  return true;
}

template < class FT >
inline
bool CGAL_PointCd<FT>::operator!=(const CGAL_PointCd<FT>& p) const
{
  return !(*this == p);
}

template < class FT >
inline
int CGAL_PointCd<FT>::id() const
{
  return (int)PTR;
}

template < class FT >
inline
FT  CGAL_PointCd<FT>::homogeneous(int i) const
{
    CGAL_kernel_precondition ( (i>=0) && (i<=dimension()) );
    if (i<dimension())
    return ptr()->e[i];
    else
    return FT(1);
}

template < class FT >
CGAL_KERNEL_INLINE
FT  CGAL_PointCd<FT>::cartesian(int i) const
{
    CGAL_kernel_precondition ( (i>=0) && (i<dimension()) );
    return ptr()->e[i];
}

template < class FT >
inline
FT  CGAL_PointCd<FT>::operator[](int i) const
{
  return cartesian(i);
}


template < class FT >
inline
int CGAL_PointCd<FT>::dimension() const
{
  return ptr()->d;
}

#ifndef CGAL_NO_OSTREAM_INSERT_POINTCD
template < class FT >
ostream &operator<<(ostream &os, const CGAL_PointCd<FT> &p)
{
    int d = p.dimension();
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII : {
    os << d << ' ';
        for (int i=0; i<d-1; ++i)
        os << p.cartesian(i) << ' ';
    return os << p.cartesian(d-1);
    }
    case CGAL_IO::BINARY : {
    CGAL_write(os, d);
    for (int i=0; i<d; ++i)
           CGAL_write(os, p.cartesian(i));
        return os;
    }
    default:
        os << "PointCd(";
    os << d << ", (";
    for (int i=0; i<d-1; ++i)
        os << p.cartesian(i) << ", ";
    return os << p.cartesian(d-1) << "))";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_POINTCD

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINTCD
template < class FT >
istream &operator>>(istream &is, CGAL_PointCd<FT> &p)
{
    int d=0, i;
    FT* e=0;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
    is >> d;
    e = new FT[d];
    for (i=0; i<d; ++i)
            is >> e[i];
    break;
    case CGAL_IO::BINARY :
    CGAL_read(is, d);
    e = new FT[d];
    for (i=0; i<d; ++i)
            CGAL_read(is, e[i]);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        return is;
    }
    p = CGAL_PointCd<FT>(d,e,e+d);
    delete[] e;
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTCD

#endif // CGAL_POINTCD_H
