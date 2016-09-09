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
// file          : include/CGAL/PointHd.h
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
 

#ifndef CGAL_POINTHD_H
#define CGAL_POINTHD_H

#ifndef D_TUPLE_H
#include <CGAL/d_tuple.h>
#endif // D_TUPLE_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT>
class DAHd;

template < class FT, class RT >
class PointHd : public Handle
{
    friend class DAHd<FT,RT>;

    public:
    PointHd ();
    PointHd (int dim, const Origin&);
    PointHd (const PointHd<FT,RT> &p);

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES

    template <class InputIterator>
    PointHd (int dim, InputIterator first, InputIterator last);
#else
    PointHd (int dim, const RT* first, const RT* last);

#endif // CGAL_CFG_NO_MEMBER_TEMPLATES

    ~PointHd();

    PointHd<FT,RT>& operator=(const PointHd<FT,RT> &p);

      bool operator==(const PointHd<FT,RT> &p) const;
      bool operator!=(const PointHd<FT,RT> &p) const;

    int id() const;

    RT homogeneous (int i) const;
    FT cartesian (int i) const;
    FT operator[] (int i) const;
    const RT* begin() const;
    const RT* end() const;

    int dimension () const;

    private:
    const _d_tuple<RT>* ptr() const;
};

template < class FT, class RT >
CGAL_KERNEL_INLINE
const _d_tuple<RT>* PointHd<FT,RT>::ptr() const
{
  return (_d_tuple<RT>*)PTR;
}
CGAL_END_NAMESPACE


#ifndef CGAL_ORIGIN_H
#include <CGAL/Origin.h>
#endif // CGAL_ORIGIN_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
PointHd<FT,RT>::PointHd()
{
  PTR = new _d_tuple<RT>();
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
PointHd<FT,RT>::PointHd(int dim, const Origin &)
{
  CGAL_kernel_precondition (dim>=0);
  PTR = new _d_tuple<RT>(dim,false);
  RT *e = ptr()->e, *i;
  for (i=e; i<e+dim; *(i++)=RT(0));
  *i = RT(1);
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
PointHd<FT,RT>::PointHd(const PointHd<FT,RT> &p)
  : Handle((Handle&)p)
{}

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
template <class InputIterator>
PointHd<FT,RT>::PointHd(int dim,
                      InputIterator first,
                  InputIterator last)
{
    CGAL_kernel_precondition (dim>=0);
    PTR = new _d_tuple<RT>(dim,false);
    RT *e = ptr()->e, *o;
    InputIterator i;
    for (i=first, o=e; (i<last) && (o<e+dim); *(o++) = *(i++));
    CGAL_kernel_precondition (o==e+dim);
    if (i<last) {
    RT h = *(i++);
    CGAL_kernel_precondition (!is_zero (h));
    CGAL_kernel_precondition (i==last);
    *o = h;
    } else
    *o = RT(1);
}

#else

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
PointHd<FT,RT>::PointHd(int dim,
                      const RT* first,
                  const RT* last)
{
    CGAL_kernel_precondition (dim>=0);
    PTR = new _d_tuple<RT>(dim,false);
    RT *e = ptr()->e, *o;
    const RT *i;
    for (i=first, o=e; (i<last) && (o<e+dim); *(o++) = *(i++));
    CGAL_kernel_precondition (o==e+dim);
    if (i<last) {
    RT h = *(i++);
    CGAL_kernel_precondition (!is_zero (h));
    CGAL_kernel_precondition (i==last);
    *o = h;
    } else
    *o = RT(1);
}



#endif // CGAL_CFG_NO_MEMBER_TEMPLATES

template < class FT, class RT >
inline
PointHd<FT,RT>::~PointHd()
{}

template < class FT, class RT >
inline
PointHd<FT,RT>&
PointHd<FT,RT>::operator=(const PointHd<FT,RT> &p)
{
  Handle::operator=(p);
  return *this;
}

template < class FT, class RT >
inline
bool PointHd<FT,RT>::operator==(const PointHd<FT,RT>& p) const
{
  int d = dimension();
  if (d != p.dimension()) return false;
  RT *e = ptr()->e, *ep = p.ptr()->e;
  RT h = e[d], hp = ep[d];
  for (RT *i=e, *j=ep; i<e+d; ++i, ++j)
      if ((*i)*hp != (*j)*h) return false;
  return true;
}

template < class FT, class RT >
inline
bool PointHd<FT,RT>::operator!=(const PointHd<FT,RT>& p) const
{
  return !(*this == p);
}

template < class FT, class RT >
inline
int PointHd<FT,RT>::id() const
{
  return (int)PTR;
}

template < class FT, class RT >
inline
RT  PointHd<FT,RT>::homogeneous(int i) const
{
    CGAL_kernel_precondition ( (i>=0) && (i<=dimension()) );
    return ptr()->e[i];
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT PointHd<FT,RT>::cartesian(int i) const
{
    CGAL_kernel_precondition ( (i>=0) && (i<dimension()) );
    return FT(ptr()->e[i])/FT(ptr()->e[dimension()]);
}

template < class FT, class RT >
inline
FT  PointHd<FT,RT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT, class RT >
inline
int PointHd<FT,RT>::dimension() const
{
  return ptr()->d;
}

template < class FT, class RT >
inline
const RT* PointHd<FT,RT>::begin() const
{
  return ptr()->e;
}

template < class FT, class RT >
inline
const RT* PointHd<FT,RT>::end() const
{
  return ptr()->e + dimension() + 1;
}


#ifndef NO_OSTREAM_INSERT_POINTHD
template < class FT, class RT >
ostream &operator<<(ostream &os, const PointHd<FT,RT> &p)
{
    int d = p.dimension();
    switch(os.iword(IO::mode)) {
    case IO::ASCII : {
    os << d << ' ';
        for (int i=0; i<d; ++i)
        os << p.homogeneous(i) << ' ';
    return os << p.homogeneous(d);
    }
    case IO::BINARY : {
    for (int i=0; i<d+1; ++i)
           write(os, p.homogeneous(i));
        return os;
    }
    default:
        os << "PointHd(";
    os << d << ", (";
    for (int i=0; i<d; ++i)
        os << p.homogeneous(i) << ", ";
    return os << p.homogeneous(d) << "))";
    }
}
#endif // NO_OSTREAM_INSERT_POINTHD

#ifndef NO_ISTREAM_EXTRACT_POINTHD
template < class FT, class RT >
istream &operator>>(istream &is, PointHd<FT,RT> &p)
{
    int d=0, i;
    RT* e=0;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
    is >> d;
    e = new RT[d+1];
    for (i=0; i<d+1; ++i)
            is >> e[i];
    break;
    case IO::BINARY :
    read(is, d);
    e = new RT[d+1];
    for (i=0; i<d+1; ++i)
            read(is, e[i]);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        return is;
    }
    p = PointHd<FT,RT>(d,e,e+d+1);
    delete[] e;
    return is;
}
#endif // NO_ISTREAM_EXTRACT_POINTHD
CGAL_END_NAMESPACE


#endif // POINTH_H
