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
// file          : include/CGAL/PointC3.h
// package       : C3 (2.1.5)
// source        : web/PointC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:37 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_POINTC3_H
#define CGAL_POINTC3_H

#ifndef CGAL_THREETUPLE_H
#include <CGAL/Threetuple.h>
#endif // CGAL_THREETUPLE_H

CGAL_BEGIN_NAMESPACE

template < class FT >
inline
PointC3<FT>
operator+(const Origin &o, const VectorC3<FT> &v);

template < class FT >
inline
PointC3<FT>
operator-(const Origin &o, const VectorC3<FT> &v);

template < class FT >
class PointC3 : public Handle
{
friend inline PointC3<FT> operator+ CGAL_NULL_TMPL_ARGS(
                                    const Origin &o,
                                    const VectorC3<FT> &v);
friend inline PointC3<FT> operator- CGAL_NULL_TMPL_ARGS(
                                    const Origin &o,
                                    const VectorC3<FT> &v);
public:
              PointC3();
              PointC3(const Origin &o);
              PointC3(const PointC3<FT> &p);
              PointC3(const FT &x, const FT &y, const FT &z);
              PointC3(const FT &x, const FT &y, const FT &z,
                      const FT &hw);
              ~PointC3();

  PointC3<FT> &operator=(const PointC3<FT> &p);

  bool        operator==(const PointC3<FT> &p) const;
  bool        operator!=(const PointC3<FT> &p) const;
  long        id() const;

  FT          x() const;
  FT          y() const;
  FT          z() const;

  FT          hx() const;
  FT          hy() const;
  FT          hz() const;
  FT          hw() const;

  FT          cartesian(int i) const;
  FT          operator[](int i) const;

  FT          homogeneous(int i) const;

  int         dimension() const;
  Bbox_3      bbox() const;

  PointC3<FT> transform( const Aff_transformationC3<FT> &) const;


protected:
              PointC3(const VectorC3<FT> &v);
private:
  _Threetuple<FT>*   ptr() const;

};

template < class FT >
inline _Threetuple<FT>* PointC3<FT>::ptr() const
{
  return (_Threetuple<FT>*)PTR;
}


CGAL_END_NAMESPACE

#ifndef CGAL_ORIGIN_H
#include <CGAL/Origin.h>
#endif // CGAL_ORIGIN_H
#ifndef CGAL_VECTORC3_H
#include <CGAL/VectorC3.h>
#endif // CGAL_VECTORC3_H
#ifndef CGAL_AFF_TRANSFORMATIONC3_H
#include <CGAL/Aff_transformationC3.h>
#endif // CGAL_AFF_TRANSFORMATIONC3_H
#ifndef CGAL_BBOX_3_H
#include <CGAL/Bbox_3.h>
#endif // CGAL_BBOX_3_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

CGAL_BEGIN_NAMESPACE

template < class FT >
PointC3<FT>::PointC3()
{
  PTR = new _Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class FT >
PointC3<FT>::PointC3(const Origin &)
{
  PTR = new _Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class FT >
PointC3<FT>::PointC3(const PointC3<FT> &p) :
  Handle((Handle&)p)
{
}

template < class FT >
PointC3<FT>::PointC3(const FT &x, const FT &y, const FT &z)
{
  PTR = new _Threetuple<FT>(x, y, z);
}

template < class FT >
PointC3<FT>::PointC3(const FT &x, const FT &y, const FT &z, const FT &w)
{
  if (w != FT(1))
    PTR = new _Threetuple<FT>(x/w, y/w, z/w);
  else
    PTR = new _Threetuple<FT>(x, y, z);
}

template < class FT >
PointC3<FT>::~PointC3()
{}

template < class FT >
PointC3<FT> &PointC3<FT>::operator=(const PointC3<FT> &p)
{
  Handle::operator=(p);
  return *this;
}
template < class FT >
PointC3<FT>::PointC3(const VectorC3<FT> &v) :
  Handle((Handle&)v)
{}
template < class FT >
inline
bool
PointC3<FT>::operator==(const PointC3<FT>& p) const
{
  return (x() == p.x()) && (y() == p.y()) && (z() == p.z());
}

template < class FT >
inline
bool
PointC3<FT>::operator!=(const PointC3<FT>& p) const
{
  return !(*this == p);
}

template < class FT >
inline
long
PointC3<FT>::id() const
{
  return (long) PTR;
}

template < class FT >
inline
FT
PointC3<FT>::x()  const
{
  return ptr()->e0;
}


template < class FT >
inline
FT
PointC3<FT>::y()  const
{
  return  ptr()->e1;
}


template < class FT >
inline
FT
PointC3<FT>::z()  const
{
  return  ptr()->e2;
}


template < class FT >
inline
int
PointC3<FT>::dimension() const
{
  return 3;
}


template < class FT >
inline
FT
PointC3<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i>=0) && (i<=2) );
  return (i==0) ? x() :
         (i==1) ? y() : z();
}


template < class FT >
inline
FT
PointC3<FT>::operator[](int i) const
{
  return cartesian(i);
}


template < class FT >
inline
FT
PointC3<FT>::hx()  const
{
  return ptr()->e0;
}


template < class FT >
inline
FT
PointC3<FT>::hy()  const
{
  return ptr()->e1;
}


template < class FT >
inline
FT
PointC3<FT>::hz()  const
{
  return ptr()->e2;
}


template < class FT >
inline
FT
PointC3<FT>::hw()  const
{
  return FT(1);
}

template < class FT >
FT
PointC3<FT>::homogeneous(int i) const
{
  CGAL_kernel_precondition((i>=0) && (i<=3));
  return (i<3) ? cartesian(i) : FT(1);
}

template < class FT >
inline
PointC3<FT>
operator+(const PointC3<FT> &p, const VectorC3<FT> &v)
{
  return PointC3<FT>(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}

template < class FT >
inline
PointC3<FT>
operator-(const PointC3<FT> &p, const VectorC3<FT> &v)
{
  return PointC3<FT>(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
}

template < class FT >
inline
PointC3<FT>
operator+(const Origin &, const VectorC3<FT> &v)
{
  return PointC3<FT>(v);
}

template < class FT >
inline
PointC3<FT>
operator-(const Origin &, const VectorC3<FT> &v)
{
  return PointC3<FT>(-v);
}

template < class FT >
inline
VectorC3<FT>
operator-(const PointC3<FT> &p, const PointC3<FT> &q)
{
  return VectorC3<FT>(p.x() - q.x(), p.y() - q.y(), p.z() - q.z());
}


template < class FT >
inline
VectorC3<FT>
operator-(const PointC3<FT> &p, const Origin &)
{
  return VectorC3<FT>(p);
}


template < class FT >
inline
VectorC3<FT>
operator-(const Origin &, const PointC3<FT> &p)
{
  return VectorC3<FT>(-p.x(), -p.y(), -p.z());
}


template < class FT >
inline
PointC3<FT>
PointC3<FT>::transform(const Aff_transformationC3<FT> &t) const
{
  return t.transform(*this);
}


template < class FT >
Bbox_3 PointC3<FT>::bbox() const
{
  // Not robust...
  double bx = CGAL::to_double(x());
  double by = CGAL::to_double(y());
  double bz = CGAL::to_double(z());
  return Bbox_3(bx, by, bz, bx, by, bz);
}


#ifndef CGAL_NO_OSTREAM_INSERT_POINTC3
template < class FT >
ostream &operator<<(ostream &os, const PointC3<FT> &p)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << p.x() << ' ' << p.y()  << ' ' << p.z();
    case IO::BINARY :
        write(os, p.x());
        write(os, p.y());
        write(os, p.z());
        return os;
    default:
        os << "PointC3(" << p.x() << ", " << p.y()  << ", " << p.z() << ")";
        return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_POINTC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINTC3
template < class FT >
istream &operator>>(istream &is, PointC3<FT> &p)
{
    FT x, y, z;
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
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = PointC3<FT>(x, y, z);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTC3


CGAL_END_NAMESPACE

#endif // CGAL_POINTC3_H
