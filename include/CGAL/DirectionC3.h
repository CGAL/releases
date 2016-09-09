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

// Source: DirectionC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_DIRECTIONC3_H
#define CGAL_DIRECTIONC3_H

#include <CGAL/Threetuple.h>
#include <CGAL/VectorC3.h>

template < class FT >
class CGAL_DirectionC3 : public CGAL_Handle
{
public:
                      CGAL_DirectionC3();
                      CGAL_DirectionC3(const CGAL_DirectionC3<FT> &d);
                      CGAL_DirectionC3(const CGAL_VectorC3<FT> &v);
                      CGAL_DirectionC3(const FT &x, const FT &y, const FT &z);
                      ~CGAL_DirectionC3();

  CGAL_DirectionC3<FT> &operator=(const CGAL_DirectionC3<FT> &d);

  bool                operator==(const CGAL_DirectionC3<FT> &d) const;
  bool                operator!=(const CGAL_DirectionC3<FT> &d) const;
  int                 id() const;

  CGAL_VectorC3<FT>   vector() const;


  CGAL_DirectionC3    transform(const CGAL_Aff_transformationC3<FT> &t) const;


  CGAL_DirectionC3    operator-() const;

  FT                  delta(int i) const;
  FT                  dx() const;
  FT                  dy() const;
  FT                  dz() const;

  FT                  hdx() const;
  FT                  hdy() const;
  FT                  hdz() const;
  FT                  hw() const;


private:
  CGAL__Threetuple<FT>*   ptr() const;
};


template < class FT >
inline CGAL__Threetuple<FT>*   CGAL_DirectionC3<FT>::ptr() const
{
  return (CGAL__Threetuple<FT>*)PTR;
}


template < class FT >
CGAL_DirectionC3<FT>::CGAL_DirectionC3()
{
  PTR = new CGAL__Threetuple<FT>();
}

template < class FT >
CGAL_DirectionC3<FT>::CGAL_DirectionC3(const CGAL_DirectionC3<FT> &d) :
  CGAL_Handle(d)
{

}

template < class FT >
CGAL_DirectionC3<FT>::CGAL_DirectionC3(const CGAL_VectorC3<FT> &v) :
  CGAL_Handle(v)
{

}

template < class FT >
CGAL_DirectionC3<FT>::CGAL_DirectionC3(const FT &x, const FT &y, const FT &z)
{
  PTR = new CGAL__Threetuple<FT>(x, y, z);
}


template < class FT >
CGAL_DirectionC3<FT>:: ~CGAL_DirectionC3()
{}

template < class FT >
CGAL_DirectionC3<FT> &CGAL_DirectionC3<FT>::operator=(
                                               const CGAL_DirectionC3<FT> &d)
{

  CGAL_Handle::operator=(d);
  return *this;
}
template < class FT >
bool CGAL_DirectionC3<FT>::operator==(const CGAL_DirectionC3<FT> &d) const
{
  return ( ( dx()*d.dy() == dy()*d.dx() )
        &&( dx()*d.dz() == dz()*d.dx() )
        &&( dy()*d.dz() == dz()*d.dy() )
        &&( CGAL_sign( dx() ) == CGAL_sign( d.dx() ) )
        &&( CGAL_sign( dy() ) == CGAL_sign( d.dy() ) )
        &&( CGAL_sign( dz() ) == CGAL_sign( d.dz() ) ) );
}

template < class FT >
inline bool  CGAL_DirectionC3<FT>::operator!=(
                                         const CGAL_DirectionC3<FT> &d) const
{
  return !(*this == d);
}

template < class FT >
int  CGAL_DirectionC3<FT>::id() const
{
  return (int) PTR;
}
template < class FT >
inline CGAL_VectorC3<FT> CGAL_DirectionC3<FT>::vector() const
{

  return CGAL_VectorC3<FT>(*this);
}


template < class FT >
inline CGAL_DirectionC3<FT> CGAL_DirectionC3<FT>::transform(
                               const CGAL_Aff_transformationC3<FT> &t) const
{
  return t.transform(*this);
}


template < class FT >
inline CGAL_DirectionC3<FT> CGAL_DirectionC3<FT>::operator-() const
{

  return CGAL_DirectionC3<FT>(-dx(), -dy(), -dz());
}



template < class FT >
FT CGAL_DirectionC3<FT>::delta(int i) const
{
  CGAL_kernel_precondition( i >= 0 && i <= 2 );
  if(i == 0) {
    return dx();
  }
  if(i == 1) {
    return dy();
  }
  return dz();
}


template < class FT >
inline FT CGAL_DirectionC3<FT>::dx() const
{

  return ptr()->e0;
}

template < class FT >
inline FT CGAL_DirectionC3<FT>::dy() const
{

  return ptr()->e1;
}

template < class FT >
inline FT CGAL_DirectionC3<FT>::dz() const
{

  return ptr()->e2;
}
template < class FT >
inline FT CGAL_DirectionC3<FT>::hdx() const
{

  return ptr()->e0;
}

template < class FT >
inline FT CGAL_DirectionC3<FT>::hdy() const
{

  return ptr()->e1;
}

template < class FT >
inline FT CGAL_DirectionC3<FT>::hdz() const
{

  return ptr()->e2;
}

template < class FT >
inline FT CGAL_DirectionC3<FT>::hw() const
{

  return FT(1);
}


#endif
