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
// file          : include/CGAL/VectorC2.h
// package       : C2 (2.1.4)
// source        : web/VectorC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:33 $
// author(s)     : Andreas.Fabri
//                 Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_VECTORC2_H
#define CGAL_VECTORC2_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H
#ifndef CGAL_POINTC2_H
#include <CGAL/PointC2.h>
#endif // CGAL_POINTC2_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class VectorC2 : public Handle
{
friend VectorC2<FT> operator-CGAL_NULL_TMPL_ARGS(const PointC2<FT> &p,
                                   const Origin &o);
friend class DirectionC2<FT>;

public:
                  VectorC2();
                  VectorC2(const VectorC2<FT> &v);
                  VectorC2(const Null_vector &);
                  VectorC2(const FT &hx, const FT &hy, const FT &hw);
                  VectorC2(const FT &x, const FT &y);
                  ~VectorC2();


  VectorC2<FT>    &operator=(const VectorC2<FT> &v);

  bool            operator==(const VectorC2<FT> &v) const;
  bool            operator!=(const VectorC2<FT> &v) const;

  bool            operator==(const Null_vector &) const;
  bool            operator!=(const Null_vector &p) const;

  int             id() const;

  FT              hx() const;
  FT              hy() const;
  FT              hw() const;

  FT              x() const;
  FT              y() const;
  FT              cartesian(int i) const;
  FT              operator[](int i) const;

  FT              homogeneous(int i) const;

  int             dimension() const;

  VectorC2<FT>    operator+(const VectorC2<FT> &w) const;
  VectorC2<FT>    operator-(const VectorC2<FT> &w) const;
  VectorC2<FT>    operator-() const;
  FT              operator*(const VectorC2<FT> &w) const;
  VectorC2<FT>    operator/(const FT &c) const;
  DirectionC2<FT> direction() const;

  VectorC2<FT>    perpendicular(const Orientation &o) const;
  VectorC2<FT>    transform(const Aff_transformationC2<FT> &) const;

protected:
                  VectorC2(const PointC2<FT> &p);
                  VectorC2(const DirectionC2<FT> &d);
private:
  _Twotuple<FT>*   ptr() const;
};

template < class FT >
inline
_Twotuple<FT>*   VectorC2<FT>::ptr() const
{
  return (_Twotuple<FT>*)PTR;
}


CGAL_END_NAMESPACE

#ifndef CGAL_DIRECTIONC2_H
#include <CGAL/DirectionC2.h>
#endif // CGAL_DIRECTIONC2_H

CGAL_BEGIN_NAMESPACE

template < class FT >
VectorC2<FT>::VectorC2()
{
  PTR = new _Twotuple<FT>();
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
VectorC2<FT>::VectorC2(const VectorC2<FT>  &v) :
  Handle((Handle&)v)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
VectorC2<FT>::VectorC2(const Null_vector &)
{
  PTR = new _Twotuple<FT>(FT(0), FT(0));
}


template < class FT >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
VectorC2<FT>::VectorC2(const FT &hx, const FT &hy, const FT &hw)
{
  if ( hw == FT(1))
    PTR = new _Twotuple<FT>(hx, hy);
  else
    PTR = new _Twotuple<FT>(hx/hw, hy/hw);
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
VectorC2<FT>::VectorC2(const FT &x, const FT &y)
{
  PTR = new _Twotuple<FT>(x, y);
}

template < class FT >
inline
VectorC2<FT>::~VectorC2()
{}

template < class FT >
inline
VectorC2<FT> &VectorC2<FT>::operator=(const VectorC2<FT> &v)
{
  Handle::operator=(v);
  return *this;
}
template < class FT >
CGAL_KERNEL_CTOR_INLINE
VectorC2<FT>::VectorC2(const PointC2<FT> &p) :
  Handle((Handle&)p)
{
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
VectorC2<FT>::VectorC2(const DirectionC2<FT> &d) :
  Handle((Handle&)d)
{
}
template < class FT >
CGAL_KERNEL_INLINE
bool VectorC2<FT>::operator==(const VectorC2<FT> &v) const
{
  return (x() == v.x()) && (y() == v.y());
}

template < class FT >
inline
bool VectorC2<FT>::operator!=(const VectorC2<FT> &v) const
{
  return !(*this == v);
}

template < class FT >
inline
bool VectorC2<FT>::operator==(const Null_vector &) const
{
  return (x() == FT(0)) && (y() == FT(0));
}

template < class FT >
inline
bool VectorC2<FT>::operator!=(const Null_vector &v) const
{
  return !(*this == v);
}

template < class FT >
inline
int VectorC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
inline
FT VectorC2<FT>::x()  const
{
  return ptr()->e0;
}

template < class FT >
inline
FT VectorC2<FT>::y()  const
{
  return ptr()->e1;
}

template < class FT >
CGAL_KERNEL_INLINE
FT  VectorC2<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i == 0) || (i == 1) );
  return (i == 0) ? x() : y();
}

template < class FT >
inline
FT  VectorC2<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
inline
int VectorC2<FT>::dimension() const
{
  return 2;
}

template < class FT >
inline
FT VectorC2<FT>::hx()  const
{
  return ptr()->e0;
}

template < class FT >
inline
FT VectorC2<FT>::hy()  const
{
  return ptr()->e1;
}

template < class FT >
inline
FT VectorC2<FT>::hw()  const
{
  return FT(1);
}

template < class FT >
CGAL_KERNEL_INLINE
FT  VectorC2<FT>::homogeneous(int i) const
{
  return (i == 2) ? FT(1) : cartesian(i);
}
template < class FT >
CGAL_KERNEL_INLINE
VectorC2<FT> VectorC2<FT>::operator+(const VectorC2<FT> &w) const
{
  return VectorC2<FT>(x() + w.x(), y() + w.y()) ;
}

template < class FT >
CGAL_KERNEL_INLINE
VectorC2<FT> VectorC2<FT>::operator-(const VectorC2<FT> &w) const
{
  return VectorC2<FT>(x() - w.x(), y() - w.y()) ;
}

template < class FT >
CGAL_KERNEL_INLINE
VectorC2<FT> VectorC2<FT>::operator-() const
{
  return VectorC2<FT>(-x(), -y()) ;
}

template < class FT >
CGAL_KERNEL_INLINE
FT VectorC2<FT>::operator*(const VectorC2<FT> &w) const
{
  return x() * w.x() + y() * w.y() ;
}

template < class FT >
CGAL_KERNEL_INLINE
VectorC2<FT> operator*(const FT &c, const VectorC2<FT> &w)
{
   return VectorC2<FT>( c* w.x(), c * w.y()) ;
}


template < class FT >
CGAL_KERNEL_INLINE
VectorC2<FT> VectorC2<FT>::operator/(const FT &c) const
{
  return VectorC2<FT>( x()/c, y()/c) ;
}

template < class FT >
inline
DirectionC2<FT>   VectorC2<FT>::direction() const
{
  return DirectionC2<FT>(*this) ;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
VectorC2<FT> VectorC2<FT>::perpendicular(const Orientation &o) const
{
  CGAL_kernel_precondition( o != COLLINEAR );
  if (o == COUNTERCLOCKWISE)
    return VectorC2<FT>(-y(), x());
  else
    return VectorC2<FT>(y(), -x());
}

template < class FT >
inline
VectorC2<FT> VectorC2<FT>::transform(const Aff_transformationC2<FT> &t) const
{
  return t.transform(*this);
}



#ifndef CGAL_NO_OSTREAM_INSERT_VECTORC2
template < class FT >
ostream &operator<<(ostream &os, const VectorC2<FT> &v)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << v.x() << ' ' << v.y();
    case IO::BINARY :
        write(os, v.x());
        write(os, v.y());
        return os;
    default:
        return os << "VectorC2(" << v.x() << ", " << v.y() << ')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTORC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTORC2
template < class FT >
istream &operator>>(istream &is, VectorC2<FT> &p)
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
    p = VectorC2<FT>(x, y);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTORC2



CGAL_END_NAMESPACE

#endif
