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

// Source: RayC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_RAYC3_H
#define CGAL_RAYC3_H

#include <CGAL/LineC3.h>

template < class FT >
class CGAL_RayC3 : public CGAL_Handle
{
public:
                       CGAL_RayC3();
                       CGAL_RayC3(const CGAL_RayC3<FT> &r);
                       CGAL_RayC3(const CGAL_PointC3<FT> &sp,
                                const CGAL_PointC3<FT> &secondp);
                       CGAL_RayC3(const CGAL_PointC3<FT> &sp,
                                const CGAL_DirectionC3<FT> &d);
                       ~CGAL_RayC3();

  CGAL_RayC3<FT>       &operator=(const CGAL_RayC3<FT> &r);

  bool                 operator==(const CGAL_RayC3<FT> &r) const;
  bool                 operator!=(const CGAL_RayC3<FT> &r) const;
  int                  id() const;

  CGAL_PointC3<FT>     start() const;
  CGAL_PointC3<FT>     source() const;
  CGAL_PointC3<FT>     second_point() const;
  CGAL_PointC3<FT>     point(int i) const;

  CGAL_DirectionC3<FT> direction() const;
  CGAL_LineC3<FT>      supporting_line() const;
  CGAL_RayC3           opposite() const;

  CGAL_RayC3           transform(const CGAL_Aff_transformationC3<FT> &t) const;

  bool                 is_degenerate() const;
  bool                 has_on(const CGAL_PointC3<FT> &p) const;
  bool                 collinear_has_on(const CGAL_PointC3<FT> &p) const;

private:
CGAL__Twotuple< CGAL_PointC3<FT> > *ptr() const;
};


template < class FT >
CGAL__Twotuple< CGAL_PointC3<FT> > *CGAL_RayC3<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC3<FT> >*)PTR;
}


template < class FT >
CGAL_RayC3<FT>::CGAL_RayC3()
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >;
}

template < class FT >
CGAL_RayC3<FT>::CGAL_RayC3(const CGAL_RayC3<FT>  &r) :
  CGAL_Handle((CGAL_Handle&)r)
{}

template < class FT >
CGAL_RayC3<FT>::CGAL_RayC3(const CGAL_PointC3<FT> &sp,
                           const CGAL_PointC3<FT> &secondp)
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >(sp,secondp);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_RayC3<FT>::CGAL_RayC3(const CGAL_PointC3<FT> &sp,
                           const CGAL_DirectionC3<FT> &d)
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >(sp, sp + d.vector());
    CGAL_nondegeneracy_assertion;
}

template < class FT >
inline CGAL_RayC3<FT>::~CGAL_RayC3()
{}


template < class FT >
CGAL_RayC3<FT> &CGAL_RayC3<FT>::operator=(const CGAL_RayC3<FT> &r)
{

  CGAL_Handle::operator=(r);
  return *this;
}
template < class FT >
inline bool CGAL_RayC3<FT>::operator==(const CGAL_RayC3<FT> &r) const
{
  return ((source() == r.source()) && (direction() == r.direction()) );
}

template < class FT >
inline bool CGAL_RayC3<FT>::operator!=(const CGAL_RayC3<FT> &r) const
{
  return !(*this == r);
}

template < class FT >
int CGAL_RayC3<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_PointC3<FT>  CGAL_RayC3<FT>::start() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC3<FT>  CGAL_RayC3<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC3<FT>  CGAL_RayC3<FT>::second_point() const
{

  return ptr()->e1;
}


template < class FT >
CGAL_PointC3<FT>  CGAL_RayC3<FT>::point(int i) const
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
inline CGAL_DirectionC3<FT> CGAL_RayC3<FT>::direction() const
{

  return CGAL_DirectionC3<FT>(  second_point() - source() );
}

template < class FT >
inline CGAL_LineC3<FT> CGAL_RayC3<FT>::supporting_line() const
{

  return CGAL_LineC3<FT>(*this);
}

template < class FT >
inline CGAL_RayC3<FT> CGAL_RayC3<FT>::opposite() const
{

  return CGAL_RayC3<FT>( source(), - direction() );
}


template < class FT >
inline CGAL_RayC3<FT> CGAL_RayC3<FT>::transform(
                           const CGAL_Aff_transformationC3<FT> &t) const
{
  return CGAL_RayC3<FT>(t.transform(source()),
                        t.transform(second_point()));
}


template < class FT >
bool CGAL_RayC3<FT>::has_on(const CGAL_PointC3<FT> &p) const
{
  return ( p == source()
           || ( CGAL_collinear(source(), p, second_point())
                && ( CGAL_DirectionC3<FT>(p - source()) == direction() )));

}

template < class FT >
bool CGAL_RayC3<FT>::is_degenerate() const
{
  return (source() == second_point());
}

template < class FT >
inline bool CGAL_RayC3<FT>::collinear_has_on(const CGAL_PointC3<FT> &p) const
{
  CGAL_exactness_precondition( CGAL_collinear(source(), p, second_point()) );
  return ( p == source()
           || ( CGAL_DirectionC3<FT>(p - source()) == direction()) );

}



#endif
