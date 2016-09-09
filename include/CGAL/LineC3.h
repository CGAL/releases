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

//Source: LineC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_LINEC3_H
#define CGAL_LINEC3_H

#include <CGAL/Twotuple.h>
#include <CGAL/predicates_on_pointsC3.h>

template < class FT >
class CGAL_LineC3 : public CGAL_Handle
{
public:
                       CGAL_LineC3();
                       CGAL_LineC3(const CGAL_LineC3<FT>  &l);
                       CGAL_LineC3(const CGAL_PointC3<FT> &p,
                                   const CGAL_PointC3<FT> &q);
                       CGAL_LineC3(const CGAL_SegmentC3<FT> &s);
                       CGAL_LineC3(const CGAL_RayC3<FT> &r);
                       CGAL_LineC3(const CGAL_PointC3<FT> &p,
                                   const CGAL_DirectionC3<FT> &d);
                       ~CGAL_LineC3();

  CGAL_LineC3<FT>      &operator=(const CGAL_LineC3<FT> &l);

  bool                 operator==(const CGAL_LineC3<FT> &l) const;
  bool                 operator!=(const CGAL_LineC3<FT> &l) const;
  int                  id() const;

  CGAL_PlaneC3<FT>     perpendicular_plane(const CGAL_PointC3<FT> &p) const;
  CGAL_LineC3          opposite() const;

  CGAL_PointC3<FT>     point() const;
  CGAL_PointC3<FT>     point(int i) const;

  CGAL_PointC3<FT>     projection(const CGAL_PointC3<FT> &p) const;

  CGAL_DirectionC3<FT> direction() const;

  bool                 has_on(const CGAL_PointC3<FT> &p) const;
  bool                 is_degenerate() const;

  CGAL_LineC3          transform(const CGAL_Aff_transformationC3<FT> &t) const;


private:
  CGAL__Twotuple< CGAL_PointC3<FT> >* ptr() const;
  void                 new_rep(const CGAL_PointC3<FT> &p,
                               const CGAL_VectorC3<FT> &v);
};


template < class FT >
inline CGAL__Twotuple< CGAL_PointC3<FT> >* CGAL_LineC3<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC3<FT> >*)PTR;
}


template < class FT >
inline void CGAL_LineC3<FT>::new_rep(const CGAL_PointC3<FT> &p,
                                     const CGAL_VectorC3<FT> &v)
{
  // CGAL_kernel_precondition(  v != CGAL_NULL_VECTOR );
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> > (p, CGAL_ORIGIN+v);
  CGAL_nondegeneracy_assertion;
}

#include <CGAL/SegmentC3.h>
#include <CGAL/RayC3.h>

#include <CGAL/PlaneC3.h>

template < class FT >
CGAL_LineC3<FT>::CGAL_LineC3()
{
  PTR = new CGAL__Twotuple<FT>();
}

template < class FT >
CGAL_LineC3<FT>::CGAL_LineC3(const CGAL_LineC3<FT>  &l) :
  CGAL_Handle((CGAL_Handle&)l)
{}

template < class FT >
CGAL_LineC3<FT>::CGAL_LineC3(const CGAL_PointC3<FT> &p,
                             const CGAL_PointC3<FT> &q)
{
  new_rep(p, q-p);
}

template < class FT >
CGAL_LineC3<FT>::CGAL_LineC3(const CGAL_SegmentC3<FT> &s)
{
  new_rep(s.start(), s.end() - s.start());
}

template < class FT >
CGAL_LineC3<FT>::CGAL_LineC3(const CGAL_RayC3<FT> &r)
{
  new_rep(r.start(), r.second_point() - r.start());
}

template < class FT >
CGAL_LineC3<FT>::CGAL_LineC3(const CGAL_PointC3<FT> &p,
                             const CGAL_DirectionC3<FT> &d)
{
  new_rep(p, d.vector());
}

template < class FT >
CGAL_LineC3<FT>::~CGAL_LineC3()
{}


template < class FT >
CGAL_LineC3<FT> &CGAL_LineC3<FT>::operator=(const CGAL_LineC3<FT> &l)
{
  CGAL_Handle::operator=(l);
  return *this;
}
template < class FT >
bool CGAL_LineC3<FT>::operator==(const CGAL_LineC3<FT> &l) const
{
  return ( has_on(l.point()) && (direction() == l.direction()) );
}

template < class FT >
inline bool CGAL_LineC3<FT>::operator!=(const CGAL_LineC3<FT> &l) const
{
  return !(*this == l);
}

template < class FT >
int CGAL_LineC3<FT>::id() const
{
  return (int) PTR ;
}

template < class FT >
CGAL_PointC3<FT> CGAL_LineC3<FT>::point() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_DirectionC3<FT> CGAL_LineC3<FT>::direction() const
{
  return ((ptr()->e1) - CGAL_ORIGIN).direction();
}


template < class FT >
CGAL_PointC3<FT> CGAL_LineC3<FT>::point(int i) const
{
  return CGAL_PointC3<FT>(point() + FT(i) * ((ptr()->e1) - CGAL_ORIGIN));
}

template < class FT >
CGAL_PlaneC3<FT> CGAL_LineC3<FT>::perpendicular_plane(
                                             const CGAL_PointC3<FT> &p) const
{
  return CGAL_PlaneC3<FT>(p, direction().vector());
}

template < class FT >
CGAL_LineC3<FT> CGAL_LineC3<FT>::opposite() const
{
  return CGAL_LineC3<FT>(point(), -direction());
}

template < class FT >
CGAL_PointC3<FT> CGAL_LineC3<FT>::projection(const CGAL_PointC3<FT> &p) const
{
  return point() + ( ((direction().vector() * (p - point())) /
                      (direction().vector() * direction().vector()))
                     * direction().vector() );
}


template < class FT >
bool CGAL_LineC3<FT>::has_on(const CGAL_PointC3<FT> &p) const
{
  return CGAL_collinear(point(), point()+direction().vector(), p);
  }


template < class FT >
bool CGAL_LineC3<FT>::is_degenerate() const
{
  return (CGAL_DirectionC3<FT>(0.0, 0.0, 0.0) == direction() );
}


template < class FT >
inline CGAL_LineC3<FT> CGAL_LineC3<FT>::transform(
                               const CGAL_Aff_transformationC3<FT> &t) const
{
  return CGAL_LineC3<FT>( t.transform(point() ),
                          t.transform(direction() ));
}


#endif // CGAL_LINEC3_H
