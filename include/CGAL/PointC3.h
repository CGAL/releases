//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: PointC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_POINTC3_H
#define CGAL_POINTC3_H

#include <CGAL/Threetuple.h>

template < class FT >
class CGAL_PointC3 : public CGAL_Handle
{
friend inline CGAL_PointC3<FT> operator+(const CGAL_Origin &o,
                                         const CGAL_VectorC3<FT> &v);
friend inline CGAL_PointC3<FT> operator-(const CGAL_Origin &o,
                                         const CGAL_VectorC3<FT> &v);
public:
                   CGAL_PointC3();
                   CGAL_PointC3(const CGAL_Origin &o);
                   CGAL_PointC3(const CGAL_PointC3<FT> &p);
                   CGAL_PointC3(const FT &x, const FT &y, const FT &z);
                   CGAL_PointC3(const FT &x, const FT &y, const FT &z,
                                const FT &hw);
                   ~CGAL_PointC3();

  CGAL_PointC3<FT> &operator=(const CGAL_PointC3<FT> &p);

  bool             operator==(const CGAL_PointC3<FT> &p) const;
  bool             operator!=(const CGAL_PointC3<FT> &p) const;
  int              id() const;

  FT               x() const;
  FT               y() const;
  FT               z() const;

  FT               hx() const;
  FT               hy() const;
  FT               hz() const;
  FT               hw() const;

  FT               cartesian(int i) const;
  FT               operator[](int i) const;

  FT               homogeneous(int i) const;

  int              dimension() const;
  CGAL_Bbox_3      bbox() const;

  CGAL_PointC3<FT> transform( const CGAL_Aff_transformationC3<FT> &) const;


protected:
                   CGAL_PointC3(const CGAL_VectorC3<FT> &v);
private:
  CGAL__Threetuple<FT>*   ptr() const;

};

template < class FT >
inline CGAL__Threetuple<FT>* CGAL_PointC3<FT>::ptr() const
{
  return (CGAL__Threetuple<FT>*)PTR;
}


#include <CGAL/Origin.h>
#include <CGAL/VectorC3.h>

#include <CGAL/Aff_transformationC3.h>

#include <CGAL/Bbox_3.h>
#include <CGAL/number_utils.h>

template < class FT >
CGAL_PointC3<FT>::CGAL_PointC3()
{
  PTR = new CGAL__Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class FT >
CGAL_PointC3<FT>::CGAL_PointC3(const CGAL_Origin &)
{
  PTR = new CGAL__Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class FT >
CGAL_PointC3<FT>::CGAL_PointC3(const CGAL_PointC3<FT> &p) :
  CGAL_Handle((CGAL_Handle&)p)
{

}

template < class FT >
CGAL_PointC3<FT>::CGAL_PointC3(const FT &x, const FT &y, const FT &z)
{
  PTR = new CGAL__Threetuple<FT>(x, y, z);
}

template < class FT >
CGAL_PointC3<FT>::CGAL_PointC3(const FT &x, const FT &y, const FT &z,
                               const FT &w)
{
  if( w != FT(1)) {
    PTR = new CGAL__Threetuple<FT>(x/w, y/w, z/w);
  } else {
    PTR = new CGAL__Threetuple<FT>(x, y, z);
  }
}

template < class FT >
CGAL_PointC3<FT>::~CGAL_PointC3()
{}



template < class FT >
CGAL_PointC3<FT> &CGAL_PointC3<FT>::operator=(const CGAL_PointC3<FT> &p)
{

  CGAL_Handle::operator=(p);
  return *this;
}
template < class FT >
CGAL_PointC3<FT>::CGAL_PointC3(const CGAL_VectorC3<FT> &v) :
  CGAL_Handle((CGAL_Handle&)v)
{}
template < class FT >
bool CGAL_PointC3<FT>::operator==(const CGAL_PointC3<FT>& p) const
{
  return  ((x() == p.x()) && (y() == p.y()) && (z() == p.z())) ;
}

template < class FT >
inline bool  CGAL_PointC3<FT>::operator!=(const CGAL_PointC3<FT>& p) const
{
  return !(*this == p);
}

template < class FT >
int CGAL_PointC3<FT>::id() const
{
  return (int) PTR ;
}

template < class FT >
FT CGAL_PointC3<FT>::x()  const
{

  return ptr()->e0;
}

template < class FT >
FT CGAL_PointC3<FT>::y()  const
{

  return  ptr()->e1 ;
}

template < class FT >
FT CGAL_PointC3<FT>::z()  const
{

  return  ptr()->e2 ;
}

template < class FT >
int CGAL_PointC3<FT>::dimension() const
{

  return 3;
}

template < class FT >
FT  CGAL_PointC3<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition( i == 0 || i == 1 || i == 2 );
  switch (i)
    {
    case 0: return x();
    case 1: return y();
    };
  return z();
}

template < class FT >
inline FT CGAL_PointC3<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
FT CGAL_PointC3<FT>::hx()  const
{

  return ptr()->e0;
}

template < class FT >
FT CGAL_PointC3<FT>::hy()  const
{

  return ptr()->e1;
}

template < class FT >
FT CGAL_PointC3<FT>::hz()  const
{

  return ptr()->e2;
}

template < class FT >
FT CGAL_PointC3<FT>::hw()  const
{

  return FT(1);
}

template < class FT >
FT  CGAL_PointC3<FT>::homogeneous(int i) const
{
 CGAL_kernel_precondition((i>=0) && (i<=3));
  if (i<3){
    return cartesian(i);
  }
  return FT(1);
}

template < class FT >
inline CGAL_PointC3<FT> operator+(const CGAL_PointC3<FT> &p,
                                  const CGAL_VectorC3<FT> &v)
{
  return CGAL_PointC3<FT>(p.x() + v.x(), p.y() + v.y(), p.z() + v.z()) ;
}

template < class FT >
inline CGAL_PointC3<FT> operator-(const CGAL_PointC3<FT> &p,
                                  const CGAL_VectorC3<FT> &v)
{
  return CGAL_PointC3<FT>(p.x() - v.x(), p.y() - v.y(), p.z() - v.z()) ;
}

template < class FT >
inline CGAL_PointC3<FT> operator+(const CGAL_Origin &,
                                  const CGAL_VectorC3<FT> &v)
{

  return CGAL_PointC3<FT>(v) ;
}

template < class FT >
inline CGAL_PointC3<FT> operator-(const CGAL_Origin &,
                                  const CGAL_VectorC3<FT> &v)
{

  return CGAL_PointC3<FT>(-v) ;
}

template < class FT >
inline CGAL_VectorC3<FT> operator-(const CGAL_PointC3<FT> &p,
                                   const CGAL_PointC3<FT> &q)
{
  return CGAL_VectorC3<FT>(p.x() - q.x(), p.y() - q.y(), p.z() - q.z()) ;
}

template < class FT >
inline CGAL_VectorC3<FT> operator-(const CGAL_PointC3<FT> &p,
                                   const CGAL_Origin &)
{

  return CGAL_VectorC3<FT>(p) ;
}

template < class FT >
inline CGAL_VectorC3<FT> operator-(const CGAL_Origin &,
                                   const CGAL_PointC3<FT> &p)
{

  return CGAL_VectorC3<FT>(-p.x(), -p.y(), -p.z()) ;
}


template < class FT >
CGAL_PointC3<FT> CGAL_PointC3<FT>::transform(
                                 const CGAL_Aff_transformationC3<FT> &t) const
{
  return t.transform(*this);
}


template < class FT >
CGAL_Bbox_3 CGAL_PointC3<FT>::bbox() const
{

  double bx = CGAL_to_double(x());
  double by = CGAL_to_double(y());
  double bz = CGAL_to_double(z());
  return CGAL_Bbox_3(bx, by, bz, bx, by, bz);
}


#endif // CGAL_POINTC3_H
