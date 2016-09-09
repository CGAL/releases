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
// file          : include/CGAL/VectorC3.h
// package       : C3 (2.1.5)
// source        : web/VectorC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:38 $
// author        : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_VECTORC3_H
#define CGAL_VECTORC3_H

#ifndef CGAL_THREETUPLE_H
#include <CGAL/Threetuple.h>
#endif // CGAL_THREETUPLE_H
#ifndef CGAL_POINTC3_H
#include <CGAL/PointC3.h>
#endif // CGAL_POINTC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
inline VectorC3<FT>
operator-(const PointC3<FT> &p, const Origin &o);

template < class FT >
class VectorC3 : public Handle
{
friend inline VectorC3<FT> operator- CGAL_NULL_TMPL_ARGS (
                                          const PointC3<FT> &p,
                                          const Origin &o);

friend class DirectionC3<FT>;

public:
                  VectorC3();
                  VectorC3(const VectorC3<FT> &v);
                  VectorC3(const Null_vector &);
                  VectorC3(const FT &x, const FT &y, const FT &z);
                  VectorC3(const FT &x, const FT &y, const FT &z, const FT &w);
                  ~VectorC3();

  VectorC3<FT>    &operator=(const VectorC3<FT> &v);

  bool            operator==(const VectorC3<FT> &p) const;
  bool            operator!=(const VectorC3<FT> &p) const;

  bool            operator==(const Null_vector &) const;
  bool            operator!=(const Null_vector &) const;

  long            id() const;

  FT              x() const;
  FT              y() const;
  FT              z() const;
  FT              cartesian(int i) const;
  FT              operator[](int i) const;

  FT              hx() const;
  FT              hy() const;
  FT              hz() const;
  FT              hw() const;
  FT              homogeneous(int i) const;

  int             dimension() const;

  VectorC3<FT>    operator+(const VectorC3<FT> &w) const;
  VectorC3<FT>    operator-(const VectorC3<FT> &w) const;
  VectorC3<FT>    operator-() const;
  FT              operator*(const VectorC3<FT> &w) const;
  VectorC3<FT>    operator/(const FT &c) const;
  DirectionC3<FT> direction() const;
  VectorC3<FT> transform(const Aff_transformationC3<FT> &) const;

protected:
                  VectorC3(const PointC3<FT> &p);
                  VectorC3(const DirectionC3<FT> &p);

private:
  _Threetuple<FT>*   ptr() const;
};

template < class FT >
inline _Threetuple<FT>*   VectorC3<FT>::ptr() const
{
  return (_Threetuple<FT>*)PTR;
}


CGAL_END_NAMESPACE

#ifndef CGAL_DIRECTIONC3_H
#include <CGAL/DirectionC3.h>
#endif // CGAL_DIRECTIONC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
VectorC3<FT>::VectorC3()
{
  PTR = new _Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class FT >
VectorC3<FT>::VectorC3(const VectorC3<FT>  &v) :
  Handle(v)
{}

template < class FT >
VectorC3<FT>::VectorC3(const Null_vector  &)
{
  PTR = new _Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class FT >
VectorC3<FT>::VectorC3(const FT &x, const FT &y, const FT &z)
{
  PTR = new _Threetuple<FT>(x, y, z);
}

template < class FT >
VectorC3<FT>::VectorC3(const FT &x, const FT &y, const FT &z, const FT &w)
{
  if (w != FT(1))
    PTR = new _Threetuple<FT>(x/w, y/w, z/w);
  else
    PTR = new _Threetuple<FT>(x, y, z);
}

template < class FT >
VectorC3<FT>::~VectorC3()
{}


template < class FT >
VectorC3<FT> &VectorC3<FT>::operator=(const VectorC3<FT> &v)
{
  Handle::operator=(v);
  return *this;
}
template < class FT >
inline VectorC3<FT>::VectorC3(const PointC3<FT> &p) :
  Handle((Handle&)p)
{
}

template < class FT >
inline VectorC3<FT>::VectorC3(const DirectionC3<FT> &d) :
  Handle((Handle&)d)
{
}
template < class FT >
bool VectorC3<FT>::operator==(const VectorC3<FT> &v) const
{
  return (x() == v.x()) && (y() == v.y()) && (z() == v.z()) ;
}

template < class FT >
inline bool VectorC3<FT>::operator!=(const VectorC3<FT> &v) const
{
  return !(*this == v);
}


template < class FT >
bool VectorC3<FT>::operator==(const Null_vector &) const
{
  return (x() == FT(0)) && (y() == FT(0)) && (z() == FT(0)) ;
}

template < class FT >
inline bool VectorC3<FT>::operator!=(const Null_vector &v) const
{
  return !(*this == v);
}


template < class FT >
inline
long VectorC3<FT>::id() const
{
  return (long) PTR;
}
template < class FT >
inline
FT
VectorC3<FT>::x()  const
{
  return ptr()->e0;
}

template < class FT >
inline
FT
VectorC3<FT>::y()  const
{
  return  ptr()->e1;
}

template < class FT >
inline
FT
VectorC3<FT>::z()  const
{
  return  ptr()->e2;
}

template < class FT >
inline
FT
VectorC3<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i>=0) && (i<3) );
  return (i==0) ? x() :
         (i==1) ? y() : z();
}

template < class FT >
inline
FT
VectorC3<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
inline
int
VectorC3<FT>::dimension() const
{
  return 3;
}

template < class FT >
inline
FT
VectorC3<FT>::hx()  const
{
  return ptr()->e0;
}

template < class FT >
inline
FT
VectorC3<FT>::hy()  const
{
  return ptr()->e1;
}

template < class FT >
inline
FT
VectorC3<FT>::hz()  const
{
  return ptr()->e2;
}

template < class FT >
FT
VectorC3<FT>::hw()  const
{
  return FT(1);
}

template < class FT >
FT
VectorC3<FT>::homogeneous(int i) const
{
  return (i==3) ? FT(1) : cartesian(i);
}
template < class FT >
inline VectorC3<FT> VectorC3<FT>::operator+(const VectorC3<FT> &w) const
{
  return VectorC3<FT>(x() + w.x(), y() + w.y(), z() + w.z()) ;
}

template < class FT >
inline VectorC3<FT> VectorC3<FT>::operator-(const VectorC3<FT> &w) const
{
  return VectorC3<FT>(x() - w.x(), y() - w.y(), z() - w.z()) ;
}

template < class FT >
inline VectorC3<FT> VectorC3<FT>::operator-() const
{

  return VectorC3<FT>(-x(), -y(), -z()) ;
}

template < class FT >
inline FT VectorC3<FT>::operator*(const VectorC3<FT> &w) const
{
  return x() * w.x() + y() * w.y() + z() * w.z() ;
}

template < class FT >
inline VectorC3<FT> operator*(const FT &c, const VectorC3<FT> &w)
{
  return VectorC3<FT>( c* w.x(), c * w.y(), c * w.z()) ;
}

template < class FT >
inline VectorC3<FT> VectorC3<FT>::operator/(const FT &c) const
{
  return VectorC3<FT>( x()/c, y()/c, z()/c) ;
}

template < class FT >
VectorC3<FT> cross_product(const VectorC3<FT>& v, const VectorC3<FT>& w)
{
    return VectorC3<FT>( v.y() * w.z() - v.z() * w.y() ,
                         v.z() * w.x() - v.x() * w.z() ,
                         v.x() * w.y() - v.y() * w.x() );
}
template < class FT >
inline
DirectionC3<FT>
VectorC3<FT>::direction() const
{
  return DirectionC3<FT>(*this);
}


template < class FT >
VectorC3<FT>
VectorC3<FT>::transform(const Aff_transformationC3<FT> &t) const
{
  return t.transform(*this);
}


#ifndef CGAL_NO_OSTREAM_INSERT_VECTORC3
template < class FT >
ostream &operator<<(ostream &os, const VectorC3<FT> &v)
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
#endif // CGAL_NO_OSTREAM_INSERT_VECTORC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTORC3
template < class FT >
istream &operator>>(istream &is, VectorC3<FT> &p)
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
    p = VectorC3<FT>(x, y, z);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTORC3


CGAL_END_NAMESPACE

#endif
