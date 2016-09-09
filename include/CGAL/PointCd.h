// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : ddim_points.fw
// file          : include/CGAL/PointCd.h
// package       : _d (2.1)
// revision      : 2.1
// revision_date : 26 Feb 1999 
// author(s)     : Sven Schoenherr
//                 Bernd Gaertner
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_POINTCD_H
#define CGAL_POINTCD_H

#ifndef D_TUPLE_H
#include <CGAL/d_tuple.h>
#endif // D_TUPLE_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class DACd;

template < class FT >
class PointCd : public Handle
{
    friend class DACd<FT>;

    public:
    PointCd ();
    PointCd (int dim, const Origin&);
    PointCd (const PointCd<FT> &p);

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES

    template <class InputIterator>
    PointCd (int dim, InputIterator first, InputIterator last);
#else
    PointCd (int dim, const FT* first, const FT* last);

#endif // CGAL_CFG_NO_MEMBER_TEMPLATES

    ~PointCd();

    PointCd<FT> &operator=(const PointCd<FT> &p);

      bool operator==(const PointCd<FT> &p) const;
      bool operator!=(const PointCd<FT> &p) const;

    int id() const;

    FT homogeneous (int i) const;
    FT cartesian (int i) const;
    FT operator[] (int i) const;
    const FT* begin() const;
    const FT* end() const;

    int dimension () const;

    private:
     const _d_tuple<FT>* ptr() const;
};

template < class FT >
CGAL_KERNEL_INLINE
const _d_tuple<FT>* PointCd<FT>::ptr() const
{
  return (_d_tuple<FT>*)PTR;
}
CGAL_END_NAMESPACE


#ifndef CGAL_ORIGIN_H
#include <CGAL/Origin.h>
#endif // CGAL_ORIGIN_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

CGAL_BEGIN_NAMESPACE

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointCd<FT>::PointCd()
{
  PTR = new _d_tuple<FT>();
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointCd<FT>::PointCd(int dim, const Origin &)
{
  CGAL_kernel_precondition (dim>=0);
  PTR = new _d_tuple<FT>(dim);
  FT *e = ptr()->e, *i;
  for (i=e; i<e+dim; *(i++)=FT(0));  // XXX
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointCd<FT>::PointCd(const PointCd<FT> &p)
  : Handle((Handle&)p)
{}

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES

template < class FT >
CGAL_KERNEL_CTOR_INLINE
template <class InputIterator>
PointCd<FT>::
PointCd(int dim, InputIterator first, InputIterator last)
{
    CGAL_kernel_precondition (dim>=0);
    PTR = new _d_tuple<FT>(dim);
    FT *e = ptr()->e, *o;
    InputIterator i;
    for (i=first, o=e; (i<last) && (o<e+dim); *(o++) = *(i++));
    CGAL_kernel_precondition (o==e+dim);
    if (i<last) {
    FT h = *(i++);
    CGAL_kernel_precondition (!is_zero (h));
    CGAL_kernel_precondition (i==last);
    for (o=e; o<e+dim; *(o++)/=h);
    }
}

#else

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointCd<FT>::PointCd(int dim,
                  const FT* first,
                  const FT* last)
{
    CGAL_kernel_precondition (dim>=0);
    PTR = new _d_tuple<FT>(dim);
    FT *e = ptr()->e, *o;
    const FT *i;
    for (i=first, o=e; (i<last) && (o<e+dim); *(o++) = *(i++));
    CGAL_kernel_precondition (o==e+dim);
    if (i<last) {
    FT h = *(i++);
    CGAL_kernel_precondition (!is_zero (h));
    CGAL_kernel_precondition (i==last);
    for (o=e; o<e+dim; *(o++)/=h);
    }
}


#endif // CGAL_CFG_NO_MEMBER_TEMPLATES

template < class FT >
inline
PointCd<FT>::~PointCd()
{}

template < class FT >
inline
PointCd<FT> &PointCd<FT>::operator=(const PointCd<FT> &p)
{
  Handle::operator=(p);
  return *this;
}

template < class FT >
inline
bool PointCd<FT>::operator==(const PointCd<FT>& p) const
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
bool PointCd<FT>::operator!=(const PointCd<FT>& p) const
{
  return !(*this == p);
}

template < class FT >
inline
int PointCd<FT>::id() const
{
  return (int)PTR;
}

template < class FT >
inline
FT  PointCd<FT>::homogeneous(int i) const
{
    CGAL_kernel_precondition ( (i>=0) && (i<=dimension()) );
    if (i<dimension())
    return ptr()->e[i];
    else
    return FT(1);
}

template < class FT >
CGAL_KERNEL_INLINE
FT  PointCd<FT>::cartesian(int i) const
{
    CGAL_kernel_precondition ( (i>=0) && (i<dimension()) );
    return ptr()->e[i];
}

template < class FT >
inline
FT  PointCd<FT>::operator[](int i) const
{
  return cartesian(i);
}


template < class FT >
inline
int PointCd<FT>::dimension() const
{
  return ptr()->d;
}

template < class FT >
inline
const FT* PointCd<FT>::begin() const
{
  return ptr()->e;
}

template < class FT >
inline
const FT* PointCd<FT>::end() const
{
  return ptr()->e + dimension();
}

#ifndef NO_OSTREAM_INSERT_POINTCD
template < class FT >
ostream &operator<<(ostream &os, const PointCd<FT> &p)
{
    int d = p.dimension();
    switch(os.iword(IO::mode)) {
    case IO::ASCII : {
    os << d << ' ';
        for (int i=0; i<d-1; ++i)
        os << p.cartesian(i) << ' ';
    return os << p.cartesian(d-1);
    }
    case IO::BINARY : {
    write(os, d);
    for (int i=0; i<d; ++i)
           write(os, p.cartesian(i));
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
#endif // NO_OSTREAM_INSERT_POINTCD

#ifndef NO_ISTREAM_EXTRACT_POINTCD
template < class FT >
istream &operator>>(istream &is, PointCd<FT> &p)
{
    int d=0, i;
    FT* e=0;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
    is >> d;
    e = new FT[d];
    for (i=0; i<d; ++i)
            is >> e[i];
    break;
    case IO::BINARY :
    read(is, d);
    e = new FT[d];
    for (i=0; i<d; ++i)
            read(is, e[i]);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        return is;
    }
    p = PointCd<FT>(d,e,e+d);
    delete[] e;
    return is;
}
#endif // NO_ISTREAM_EXTRACT_POINTCD
CGAL_END_NAMESPACE


#endif // CGAL_POINTCD_H
