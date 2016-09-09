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

// Source: Iso_rectangleC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_ISO_RECTANGLEC2_H
#define CGAL_ISO_RECTANGLEC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/PointC2.h>

template <class FT>
class CGAL_Iso_rectangleC2 : public CGAL_Handle
{
public:
                       CGAL_Iso_rectangleC2();
                       CGAL_Iso_rectangleC2(const CGAL_Iso_rectangleC2<FT> &);
                       CGAL_Iso_rectangleC2(const CGAL_PointC2<FT> &p,
                                            const CGAL_PointC2<FT> &q);
                       ~CGAL_Iso_rectangleC2();

  CGAL_Iso_rectangleC2<FT>  &operator=(const CGAL_Iso_rectangleC2<FT> &r);

  bool                 operator==(const CGAL_Iso_rectangleC2<FT> &s) const;
  bool                 operator!=(const CGAL_Iso_rectangleC2<FT> &s) const;
  int                  id() const;

  CGAL_PointC2<FT>     min() const;
  CGAL_PointC2<FT>     max() const;
  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  CGAL_Iso_rectangleC2<FT> transform(
                               const CGAL_Aff_transformationC2<FT> &t) const;

  CGAL_Bounded_side    bounded_side(const CGAL_PointC2<FT> &p) const;

  bool                 has_on_boundary(const CGAL_PointC2<FT> &p) const;

  bool                 has_on_bounded_side(const CGAL_PointC2<FT> &p) const;
  bool                 has_on_unbounded_side(const CGAL_PointC2<FT> &p) const;

  bool                 is_degenerate() const;

  CGAL_Bbox_2          bbox() const;

  FT                   xmin() const;
  FT                   ymin() const;
  FT                   xmax() const;
  FT                   ymax() const;

private:
  CGAL__Twotuple< CGAL_PointC2<FT> >*   ptr() const;
};


template < class FT >
inline CGAL__Twotuple< CGAL_PointC2<FT> > *CGAL_Iso_rectangleC2<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}


template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2()
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
}

template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2(
                                      const CGAL_Iso_rectangleC2<FT> &r) :
  CGAL_Handle((CGAL_Handle&)r)
{

}

template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2(const CGAL_PointC2<FT> &p,
                                               const CGAL_PointC2<FT> &q)
{
  FT vx0 = p.x();
  FT vy0 = p.y();
  FT vx1 = q.x();
  FT vy1 = q.y();

  bool b1 = false,
       b2 = false;
  if( (b1 = (vx0 > vx1)) || (b2 = (vy0 > vy1)) ) {
    if (b1 && b2) {
      PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(q,p);
    } else {
      if (vx0 > vx1){
        FT z = vx1;
        vx1 = vx0;
        vx0 = z;
      }
      if (vy0 > vy1){
        FT z = vy1;
        vy1 = vy0;
        vy0 = z;
      }

      PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(CGAL_PointC2<FT>(vx0,vy0),
                                                   CGAL_PointC2<FT>(vx1,vy1));
    }
  }else {
    PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(p,q);
  }
  CGAL_nondegeneracy_assertion;
}


template < class FT >
inline CGAL_Iso_rectangleC2<FT>::~CGAL_Iso_rectangleC2()
{}


template < class FT >
CGAL_Iso_rectangleC2<FT> &CGAL_Iso_rectangleC2<FT>::operator=(
                                            const CGAL_Iso_rectangleC2<FT> &r)
{

  CGAL_Handle::operator=(r);
  return *this;
}
template < class FT >
bool CGAL_Iso_rectangleC2<FT>::operator==(
                                  const CGAL_Iso_rectangleC2<FT> &r) const
{
  return  vertex(0) == r.vertex(0) && vertex(2) == r.vertex(2);
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::operator!=(
                                  const CGAL_Iso_rectangleC2<FT> &r) const
{
  return !(*this == r);
}

template < class FT >
int CGAL_Iso_rectangleC2<FT>::id() const
{
  return (int)PTR;
}
template < class FT >
CGAL_PointC2<FT>  CGAL_Iso_rectangleC2<FT>::min() const
{

  return  ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT> CGAL_Iso_rectangleC2<FT>::max() const
{

  return  ptr()->e1;
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::xmin() const
{

  return  min().x();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::ymin() const
{

  return  min().y();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::xmax() const
{

  return  max().x();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::ymax() const
{

  return  max().y();
}



template < class FT >
CGAL_PointC2<FT> CGAL_Iso_rectangleC2<FT>::vertex(int i) const
{

  switch (i%4) {
  case 0: return min();
  case 1: return CGAL_PointC2<FT>(xmax(), ymin());
  case 2: return max();
  default: return CGAL_PointC2<FT>(xmin(), ymax());
  }
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_Iso_rectangleC2<FT>::operator[](int i) const
{

  return vertex(i);
}
template < class FT >
CGAL_Bounded_side CGAL_Iso_rectangleC2<FT>::bounded_side(
                                               const CGAL_PointC2<FT> &p) const
{
  bool x_incr = (xmin() < p.x()) &&  (p.x() < xmax()),
       y_incr = (ymin() < p.y()) &&  (p.y() < ymax());
  if( x_incr )
    {
      if( y_incr )
        {
          return CGAL_ON_BOUNDED_SIDE;
        }
      if( (p.y() == ymin()) || (ymax() == p.y()) )
        {
          return CGAL_ON_BOUNDARY;
        }
    }
  if( (p.x() == xmin()) || (xmax() == p.x()) )
    {
      if( y_incr || (p.y() == ymin()) || (ymax() == p.y()) )
        {
          return CGAL_ON_BOUNDARY;
        }
    }

  return CGAL_ON_UNBOUNDED_SIDE;
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::has_on_boundary(
                                              const CGAL_PointC2<FT> &p) const
{
  return bounded_side(p) == CGAL_ON_BOUNDARY;
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::has_on_bounded_side(
                                             const CGAL_PointC2<FT> &p) const
{
  return bounded_side(p) == CGAL_ON_BOUNDED_SIDE;
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::has_on_unbounded_side(
                                             const CGAL_PointC2<FT> &p) const
{
  return bounded_side(p) == CGAL_ON_UNBOUNDED_SIDE;
}

template < class FT >
bool CGAL_Iso_rectangleC2<FT>::is_degenerate() const
{

  return (xmin() == xmax()) || (ymin() ==ymax());
}
template < class FT >
inline CGAL_Bbox_2 CGAL_Iso_rectangleC2<FT>::bbox() const
{

  return CGAL_Bbox_2(CGAL_to_double(xmin()), CGAL_to_double(ymin()),
                     CGAL_to_double(xmax()), CGAL_to_double(ymax()));
}

template < class FT >
inline CGAL_Iso_rectangleC2<FT> CGAL_Iso_rectangleC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_Iso_rectangleC2<FT>(t.transform(vertex(0)),
                                  t.transform(vertex(2)));
}


#endif
