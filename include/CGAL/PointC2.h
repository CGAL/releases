/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: PointC2.h
// Author: Andreas Fabri

#ifndef CGAL_POINTC2_H
#define CGAL_POINTC2_H

#include <CGAL/Twotuple.h>

template < class FT >
class CGAL_PointC2 : public CGAL_Handle
{
#ifdef CGAL_WORKAROUND_001
friend  CGAL_PointC2<FT> operator+(const CGAL_Origin &,
                                         const CGAL_VectorC2<FT> &v);
friend  CGAL_PointC2<FT> operator-(const CGAL_Origin &,
                                         const CGAL_VectorC2<FT> &v);
#else
friend inline CGAL_PointC2<FT> operator+(const CGAL_Origin &,
                                         const CGAL_VectorC2<FT> &v);
friend inline CGAL_PointC2<FT> operator-(const CGAL_Origin &,
                                         const CGAL_VectorC2<FT> &v);
#endif // CGAL_WORKAROUND_001
public:
                   CGAL_PointC2();
                   CGAL_PointC2(const CGAL_Origin &);
                   CGAL_PointC2(const CGAL_PointC2<FT> &p);
                   CGAL_PointC2(const FT &hx, const FT &hy,
                                const FT &hw);
                   CGAL_PointC2(const FT &x, const FT &y);
                   ~CGAL_PointC2();

  CGAL_PointC2<FT> &operator=(const CGAL_PointC2<FT> &p);

  bool             operator==(const CGAL_PointC2<FT> &p) const;
  bool             operator!=(const CGAL_PointC2<FT> &p) const;
  int              id() const;

  FT               hx() const;
  FT               hy() const;
  FT               hw() const;

  FT               x() const;
  FT               y() const;
  FT               cartesian(int i) const;
  FT               operator[](int i) const;

  FT               homogeneous(int i) const;

  int              dimension() const;
  CGAL_Bbox_2      bbox() const;


  CGAL_PointC2<FT> transform(const CGAL_Aff_transformationC2<FT> &) const;

protected:
                   CGAL_PointC2(const CGAL_VectorC2<FT> &v);

public: // was private
  CGAL__Twotuple<FT>*  ptr() const;
};


template < class FT >
inline CGAL__Twotuple<FT>* CGAL_PointC2<FT>::ptr() const
{
  return (CGAL__Twotuple<FT>*)PTR;
}


#include <CGAL/Origin.h>
#include <CGAL/VectorC2.h>

#include <CGAL/Aff_transformationC2.h>

#include <CGAL/Bbox_2.h>
#include <CGAL/number_utils.h>


template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2()
{
  PTR = new CGAL__Twotuple<FT>;
}

template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const CGAL_Origin &)
{
  PTR = new CGAL__Twotuple<FT>(FT(0), FT(0));
}

template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const CGAL_PointC2<FT> &p) :
  CGAL_Handle((CGAL_Handle&)p)
{}

template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const FT &hx, const FT &hy, const FT &hw)
{
  if( hw != FT(1)){
    PTR = new CGAL__Twotuple<FT>(hx/hw, hy/hw);
  }else{
    PTR = new CGAL__Twotuple<FT>(hx, hy);
  }
}

template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const FT &x, const FT &y)
{
    PTR = new CGAL__Twotuple<FT>(x, y);
}

template < class FT >
CGAL_PointC2<FT>::~CGAL_PointC2()
{}


template < class FT >
CGAL_PointC2<FT> &CGAL_PointC2<FT>::operator=(const CGAL_PointC2<FT> &p)
{
  CGAL_Handle::operator=(p);
  return *this;
}
template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const CGAL_VectorC2<FT> &v) :
  CGAL_Handle((CGAL_Handle&)v)
{}
template < class FT >
bool CGAL_PointC2<FT>::operator==(const CGAL_PointC2<FT>& p) const
{
  return ((x() == p.x()) && (y() == p.y())) ;
}

template < class FT >
inline bool CGAL_PointC2<FT>::operator!=(const CGAL_PointC2<FT>& p) const
{
  return !(*this == p);
}

template < class FT >
int CGAL_PointC2<FT>::id() const
{
  return (int)PTR;
}

template < class FT >
inline FT CGAL_PointC2<FT>::x()  const
{
  return ptr()->e0;
}

template < class FT >
FT CGAL_PointC2<FT>::y()  const
{
  return  ptr()->e1 ;
}

template < class FT >
FT  CGAL_PointC2<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition((i == 0 || i == 1 ) );
  if(i == 0) {
    return x();
  }
  return y();
}

template < class FT >
inline FT  CGAL_PointC2<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
int CGAL_PointC2<FT>::dimension() const
{
  return 2;
}

template < class FT >
FT CGAL_PointC2<FT>::hx()  const
{
  return ptr()->e0;
}

template < class FT >
FT CGAL_PointC2<FT>::hy()  const
{
  return ptr()->e1;
}

template < class FT >
FT CGAL_PointC2<FT>::hw()  const
{
  return FT(1);
}

template < class FT >
FT  CGAL_PointC2<FT>::homogeneous(int i) const
{
  CGAL_kernel_precondition( (i>=0) && (i<=2));
  if (i<2){
    return cartesian(i);
  }
  return FT(1);
}

template < class FT >
inline CGAL_PointC2<FT> operator+(const CGAL_PointC2<FT> &p,
                                  const CGAL_VectorC2<FT> &v)
{
  return CGAL_PointC2<FT>(p.x() + v.x(), p.y() + v.y()) ;
}

template < class FT >
inline CGAL_PointC2<FT> operator-(const CGAL_PointC2<FT> &p,
                                  const CGAL_VectorC2<FT> &v)
{
  return CGAL_PointC2<FT>(p.x() - v.x(), p.y() - v.y()) ;
}

template < class FT >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_PointC2<FT> operator+(const CGAL_Origin &,
                           const CGAL_VectorC2<FT> &v)
{
  return CGAL_PointC2<FT>(v) ;
}

template < class FT >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_PointC2<FT> operator-(const CGAL_Origin &,
                           const CGAL_VectorC2<FT> &v)
{
  return CGAL_PointC2<FT>(-v) ;
}

template < class FT >
inline CGAL_VectorC2<FT> operator-(const CGAL_PointC2<FT> &p,
                                   const CGAL_PointC2<FT> &q)
{
  return CGAL_VectorC2<FT>(p.x() - q.x(), p.y() - q.y()) ;
}

template < class FT >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_VectorC2<FT> operator-(const CGAL_PointC2<FT> &p,
                            const CGAL_Origin &)
{
  return CGAL_VectorC2<FT>(p) ;
}

template < class FT >
inline CGAL_VectorC2<FT> operator-(const CGAL_Origin &,
                                   const CGAL_PointC2<FT> &p)
{
  return CGAL_VectorC2<FT>(-p.x(), -p.y()) ;
}


template < class FT >
CGAL_PointC2<FT> CGAL_PointC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  return t.transform(*this);
}

template < class FT >
CGAL_Bbox_2 CGAL_PointC2<FT>::bbox() const
{
  double bx = CGAL_to_double(x());
  double by = CGAL_to_double(y());
  return CGAL_Bbox_2(bx,by, bx,by);
}

#ifndef CGAL_NO_OSTREAM_INSERT_POINTC2
template < class FT >
ostream &operator<<(ostream &os, const CGAL_PointC2<FT> &p)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << p.x() << ' ' << p.y();
    case CGAL_IO::BINARY :
        CGAL_write(os, p.x());
        CGAL_write(os, p.y());
        return os;
    default:
        return os << "PointC2(" << p.x() << ", " << p.y() << ')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_POINTC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINTC2
template < class FT >
istream &operator>>(istream &is, CGAL_PointC2<FT> &p)
{
    FT x, y;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> x >> y;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, x);
        CGAL_read(is, y);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = CGAL_PointC2<FT>(x, y);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTC2




#endif // CGAL_POINTC2_H
