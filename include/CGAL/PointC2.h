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
// file          : include/CGAL/PointC2.h
// package       : C2 (2.1.4)
// source        : web/PointC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:32 $
// author(s)     : Andreas.Fabri
//                 Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_POINTC2_H
#define CGAL_POINTC2_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class PointC2 : public Handle
{
friend PointC2<FT> operator+CGAL_NULL_TMPL_ARGS(const Origin &,
                                  const VectorC2<FT> &v);
friend PointC2<FT> operator-CGAL_NULL_TMPL_ARGS(const Origin &,
                                  const VectorC2<FT> &v);
public:
              PointC2();
              PointC2(const Origin &);
              PointC2(const PointC2<FT> &p);
              PointC2(const FT &hx, const FT &hy,
                      const FT &hw);
              PointC2(const FT &x, const FT &y);
              ~PointC2();

  PointC2<FT> &operator=(const PointC2<FT> &p);

  bool        operator==(const PointC2<FT> &p) const;
  bool        operator!=(const PointC2<FT> &p) const;
  int         id() const;

  FT          hx() const;
  FT          hy() const;
  FT          hw() const;

  FT          x() const;
  FT          y() const;
  FT          cartesian(int i) const;
  FT          operator[](int i) const;

  FT          homogeneous(int i) const;

  int         dimension() const;
  Bbox_2      bbox() const;


  PointC2<FT> transform(const Aff_transformationC2<FT> &) const;

protected:
              PointC2(const VectorC2<FT> &v);

private:
  _Twotuple<FT>*  ptr() const;
};


template < class FT >
CGAL_KERNEL_INLINE
_Twotuple<FT>* PointC2<FT>::ptr() const
{
  return (_Twotuple<FT>*)PTR;
}


CGAL_END_NAMESPACE

#ifndef CGAL_ORIGIN_H
#include <CGAL/Origin.h>
#endif // CGAL_ORIGIN_H
#ifndef CGAL_VECTORC2_H
#include <CGAL/VectorC2.h>
#endif // CGAL_VECTORC2_H

#ifndef CGAL_AFF_TRANSFORMATIONC2_H
#include <CGAL/Aff_transformationC2.h>
#endif // CGAL_AFF_TRANSFORMATIONC2_H

#ifndef CGAL_BBOX_2_H
#include <CGAL/Bbox_2.h>
#endif // CGAL_BBOX_2_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

CGAL_BEGIN_NAMESPACE

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointC2<FT>::PointC2()
{
  PTR = new _Twotuple<FT>;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointC2<FT>::PointC2(const Origin &)
{
  PTR = new _Twotuple<FT>(FT(0), FT(0));
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointC2<FT>::PointC2(const PointC2<FT> &p) :
  Handle((Handle&)p)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointC2<FT>::PointC2(const FT &hx, const FT &hy, const FT &hw)
{
  if( hw != FT(1)){
    PTR = new _Twotuple<FT>(hx/hw, hy/hw);
  }else{
    PTR = new _Twotuple<FT>(hx, hy);
  }
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointC2<FT>::PointC2(const FT &x, const FT &y)
{
    PTR = new _Twotuple<FT>(x, y);
}

template < class FT >
inline
PointC2<FT>::~PointC2()
{}


template < class FT >
inline
PointC2<FT> &PointC2<FT>::operator=(const PointC2<FT> &p)
{
  Handle::operator=(p);
  return *this;
}
template < class FT >
CGAL_KERNEL_CTOR_INLINE
PointC2<FT>::PointC2(const VectorC2<FT> &v) :
  Handle((Handle&)v)
{}
template < class FT >
inline
bool PointC2<FT>::operator==(const PointC2<FT>& p) const
{
  return ((x() == p.x()) && (y() == p.y())) ;
}

template < class FT >
inline
bool PointC2<FT>::operator!=(const PointC2<FT>& p) const
{
  return !(*this == p);
}

template < class FT >
inline
int PointC2<FT>::id() const
{
  return (int)PTR;
}

template < class FT >
inline
FT PointC2<FT>::x()  const
{
  return ptr()->e0;
}

template < class FT >
inline
FT PointC2<FT>::y()  const
{
  return  ptr()->e1 ;
}

template < class FT >
CGAL_KERNEL_INLINE
FT  PointC2<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i == 0) || (i == 1) );
  return (i == 0) ? x() : y();
}

template < class FT >
inline
FT  PointC2<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
inline
int PointC2<FT>::dimension() const
{
  return 2;
}

template < class FT >
inline
FT PointC2<FT>::hx()  const
{
  return ptr()->e0;
}

template < class FT >
inline
FT PointC2<FT>::hy()  const
{
  return ptr()->e1;
}

template < class FT >
inline
FT PointC2<FT>::hw()  const
{
  return FT(1);
}

template < class FT >
inline
FT  PointC2<FT>::homogeneous(int i) const
{
  CGAL_kernel_precondition( (i>=0) && (i<=2) );
  if (i<2)
    return cartesian(i);
  return FT(1);
}

template < class FT >
inline
PointC2<FT> operator+(const PointC2<FT> &p, const VectorC2<FT> &v)
{
  return PointC2<FT>(p.x() + v.x(), p.y() + v.y()) ;
}

template < class FT >
inline
PointC2<FT> operator-(const PointC2<FT> &p, const VectorC2<FT> &v)
{
  return PointC2<FT>(p.x() - v.x(), p.y() - v.y()) ;
}

template < class FT >
inline
PointC2<FT> operator+(const Origin &, const VectorC2<FT> &v)
{
  return PointC2<FT>(v) ;
}

template < class FT >
inline
PointC2<FT> operator-(const Origin &, const VectorC2<FT> &v)
{
  return PointC2<FT>(-v) ;
}

template < class FT >
inline
VectorC2<FT> operator-(const PointC2<FT> &p, const PointC2<FT> &q)
{
  return VectorC2<FT>(p.x() - q.x(), p.y() - q.y()) ;
}

template < class FT >
inline
VectorC2<FT> operator-(const PointC2<FT> &p, const Origin &)
{
  return VectorC2<FT>(p) ;
}

template < class FT >
inline
VectorC2<FT> operator-(const Origin &, const PointC2<FT> &p)
{
  return VectorC2<FT>(-p.x(), -p.y()) ;
}


template < class FT >
CGAL_KERNEL_INLINE
PointC2<FT> PointC2<FT>::transform( const Aff_transformationC2<FT> &t) const
{
  return t.transform(*this);
}

template < class FT >
CGAL_KERNEL_INLINE
Bbox_2 PointC2<FT>::bbox() const
{
  double bx = CGAL::to_double(x());
  double by = CGAL::to_double(y());
  return Bbox_2(bx,by, bx,by);
}

#ifndef CGAL_NO_OSTREAM_INSERT_POINTC2
template < class FT >
ostream &operator<<(ostream &os, const PointC2<FT> &p)
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
template < class FT >
istream &operator>>(istream &is, PointC2<FT> &p)
{
    FT x, y;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> x >> y;
        break;
    case IO::BINARY :
        read(is, x);
        read(is, y);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = PointC2<FT>(x, y);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTC2



CGAL_END_NAMESPACE

#endif // CGAL_POINTC2_H
