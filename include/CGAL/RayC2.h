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

// Source:RayC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_RAYC2_H
#define CGAL_RAYC2_H

#include<CGAL/PointC2.h>

#include <CGAL/LineC2.h>

template < class FT >
class CGAL_RayC2 : public CGAL_Handle
{
public:
                       CGAL_RayC2();
                       CGAL_RayC2(const CGAL_RayC2<FT> &r);
                       CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                                  const CGAL_PointC2<FT> &secondp);
                       CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                                  const CGAL_DirectionC2<FT> &d);
                       ~CGAL_RayC2();



  CGAL_RayC2<FT>       &operator=(const CGAL_RayC2<FT> &r);

  bool                 operator==(const CGAL_RayC2<FT> &r) const;
  bool                 operator!=(const CGAL_RayC2<FT> &r) const;
  int                  id() const;

  CGAL_PointC2<FT>     start() const;
  CGAL_PointC2<FT>     source() const;
  CGAL_PointC2<FT>     point(int i) const;

  CGAL_DirectionC2<FT> direction() const;
  CGAL_LineC2<FT>      supporting_line() const;
  CGAL_RayC2<FT>       opposite() const;

  CGAL_RayC2<FT>       transform(const CGAL_Aff_transformationC2<FT> &t) const;

  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 is_degenerate() const;
  bool                 has_on(const CGAL_PointC2<FT> &p) const;
  bool                 collinear_has_on(const CGAL_PointC2<FT> &p) const;

  CGAL_PointC2<FT>     second_point() const;
private:

CGAL__Twotuple< CGAL_PointC2<FT> > *ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}
};


/*
template < class FT >
inline CGAL__Twotuple< CGAL_PointC2<FT> > *CGAL_RayC2<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}
*/


template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2()
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_RayC2<FT>  &r) :
  CGAL_Handle((CGAL_Handle&)r)
{}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                           const CGAL_PointC2<FT> &secondp)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, secondp);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                           const CGAL_DirectionC2<FT> &d)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, sp + d.vector());
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_RayC2<FT>::~CGAL_RayC2()
{}


template < class FT >
CGAL_RayC2<FT> &CGAL_RayC2<FT>::operator=(const CGAL_RayC2<FT> &r)
{

  CGAL_Handle::operator=(r);
  return *this;
}
template < class FT >
bool CGAL_RayC2<FT>::operator==(const CGAL_RayC2<FT> &r) const
{
  return ((source() == r.source()) && (direction() == r.direction()) );
}

template < class FT >
bool CGAL_RayC2<FT>::operator!=(const CGAL_RayC2<FT> &r) const
{
  return !(*this == r);
}

template < class FT >
int CGAL_RayC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::start() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::second_point() const
{

  return ptr()->e1;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  if (i == 0){
    return ptr()->e0;
  }
  if (i == 1){
    return ptr()->e1;
  }
  return source() + FT(i) * (second_point() - source());
}

template < class FT >
CGAL_DirectionC2<FT> CGAL_RayC2<FT>::direction() const
{

  return CGAL_DirectionC2<FT>(  second_point() - source() );
}

template < class FT >
CGAL_LineC2<FT> CGAL_RayC2<FT>::supporting_line() const
{

  return CGAL_LineC2<FT>(*this);
}

template < class FT >
CGAL_RayC2<FT> CGAL_RayC2<FT>::opposite() const
{

  return CGAL_RayC2<FT>( source(), - direction() );
}


template < class FT >
CGAL_RayC2<FT> CGAL_RayC2<FT>::transform(const
                                     CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_RayC2<FT>(t.transform(source()),
                        t.transform(second_point()));
}


template < class FT >
bool CGAL_RayC2<FT>::is_horizontal() const
{

  return (source().y() ==  second_point().y());
}

template < class FT >
bool CGAL_RayC2<FT>::is_vertical() const
{

  return  (source().x() == second_point().x());
}

template < class FT >
bool CGAL_RayC2<FT>::is_degenerate() const
{

  return (source() == second_point());
}

template < class FT >
bool CGAL_RayC2<FT>::has_on(const CGAL_PointC2<FT> &p) const
{
  return ( p == source()
           || ( CGAL_collinear(source(), p, second_point())
                && ( CGAL_DirectionC2<FT>(p - source()) == direction() )));

}

template < class FT >
bool CGAL_RayC2<FT>::collinear_has_on(const CGAL_PointC2<FT> &p) const
{
  return ( p == source()
           || ( CGAL_DirectionC2<FT>(p - source()) == direction()) );

}



#endif
