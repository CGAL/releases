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

// Source: CircleC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_CIRCLEC2_H
#define CGAL_CIRCLEC2_H

#include <CGAL/PointC2.h>
#include <CGAL/_CircleC2.h>
#include <CGAL/predicates_on_pointsC2.h>


template <class FT>
class CGAL_CircleC2 : public CGAL_Handle
{
public:
                      CGAL_CircleC2();
                      CGAL_CircleC2(const CGAL_CircleC2<FT> &);

                      CGAL_CircleC2(const CGAL_PointC2<FT> &center,
                                    const FT &squared_radius,
                                    const CGAL_Orientation &orientation);

                      CGAL_CircleC2(const CGAL_PointC2<FT> &center,
                                    const FT &squared_radius);

                      CGAL_CircleC2(const CGAL_PointC2<FT> &p,
                                    const CGAL_PointC2<FT> &q,
                                    const CGAL_PointC2<FT> &r);

                      CGAL_CircleC2(const CGAL_PointC2<FT> & center,
                                    const CGAL_PointC2<FT> & p);

                      CGAL_CircleC2(const CGAL_PointC2<FT> & center,
                                    const CGAL_PointC2<FT> & p,
                                    const CGAL_Orientation &orientation);

                      ~CGAL_CircleC2();

  CGAL_CircleC2<FT>   &operator=(const CGAL_CircleC2<FT> &t);

  bool                operator==(const CGAL_CircleC2<FT> &s) const;
  bool                operator!=(const CGAL_CircleC2<FT> &s) const;
  int                 id() const;

  CGAL_PointC2<FT>    center() const;
  FT                  squared_radius() const;

  CGAL_CircleC2<FT>   opposite() const;

//  CGAL_EllipseC2    transform(const CGAL_Aff_transformationC2<FT> &t) const;

  CGAL_CircleC2<FT>   orthogonal_transform(
                                 const CGAL_Aff_transformationC2<FT> &t) const;

  CGAL_Orientation    orientation() const;

  CGAL_Oriented_side  oriented_side(const CGAL_PointC2<FT> &p) const;
  CGAL_Bounded_side   bounded_side(const CGAL_PointC2<FT> &p) const;

  bool                has_on_boundary(const CGAL_PointC2<FT> &p) const;
  bool                has_on_negative_side(const CGAL_PointC2<FT> &p) const;
  bool                has_on_positive_side(const CGAL_PointC2<FT> &p) const;

  bool                has_on_bounded_side(const CGAL_PointC2<FT> &p) const;
  bool                has_on_unbounded_side(const CGAL_PointC2<FT> &p) const;

  bool                is_degenerate() const;

  CGAL_Bbox_2         bbox() const;

private:
  CGAL__CircleC2<FT> *ptr() const;
};


template < class FT >
inline CGAL__CircleC2<FT> *CGAL_CircleC2<FT>::ptr() const
{
  return (CGAL__CircleC2<FT>*)PTR;
}


template < class FT >
CGAL_CircleC2<FT>::CGAL_CircleC2()
{
  PTR = new CGAL__CircleC2<FT> ;
}

template < class FT >
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_CircleC2<FT> &t) :
  CGAL_Handle((CGAL_Handle&)t)
{}

template < class FT >
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_PointC2<FT> &center,
                                 const FT &squared_radius)
{
  PTR = new CGAL__CircleC2<FT>(center, squared_radius, CGAL_COUNTERCLOCKWISE);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_PointC2<FT> &center,
                                 const FT &squared_radius,
                                 const CGAL_Orientation &orientation)
{
  CGAL_kernel_assertion_msg(orientation != CGAL_COLLINEAR,
                         "Orientation must be clockwise or counterclockwise");

  PTR = new CGAL__CircleC2<FT>(center, squared_radius, orientation);
  CGAL_nondegeneracy_assertion;
}



template < class FT >
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_PointC2<FT> &center,
                                 const CGAL_PointC2<FT> &p)
{
  FT x_diff = center.x() - p.x();
  FT y_diff = center.y() - p.y();

  PTR = new CGAL__CircleC2<FT>(center,
                               x_diff * x_diff + y_diff * y_diff,
                               CGAL_COUNTERCLOCKWISE);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_PointC2<FT> &center,
                                 const CGAL_PointC2<FT> &p,
                                 const CGAL_Orientation &o)
{
  FT x_diff = center.x() - p.x();
  FT y_diff = center.y() - p.y();

  PTR = new CGAL__CircleC2<FT>(center,
                               x_diff * x_diff + y_diff * y_diff,
                               o);
  CGAL_nondegeneracy_assertion;
}


template < class FT >
CGAL_PointC2<FT> CGAL_intersection(const CGAL_PointC2<FT> &p1,
                                   const CGAL_PointC2<FT> &q1,
                                   const CGAL_PointC2<FT> &p2,
                                   const CGAL_PointC2<FT> &q2)
{

  FT l1a = p1.y() - q1.y(),
     l1b = q1.x() - p1.x(),
     l1c = p1.x()*q1.y() - p1.y()*q1.x(),
     l2a = p2.y() - q2.y(),
     l2b = q2.x() - p2.x(),
     l2c = p2.x()*q2.y() - p2.y()*q2.x();

  FT n = l1a*l2b - l2a*l1b;
  assert(n != FT(0.0));
  return CGAL_PointC2<FT>( (l1b*l2c - l2b*l1c)/n,
                          (l2a*l1c - l1a*l2c)/n );
}


template < class FT >
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_PointC2<FT> &p,
                                 const CGAL_PointC2<FT> &q,
                                 const CGAL_PointC2<FT> &r)
{
  CGAL_Orientation o = CGAL_orientation(p,q,r);

  if ( o == CGAL_COLLINEAR ) {
    PTR = new CGAL__CircleC2<FT>(CGAL_PointC2<FT>(FT(0),FT(0)),
                                 FT(0),
                                 CGAL_COLLINEAR);
  } else {
    CGAL_VectorC2<FT> v1 = (q - p)/FT(2);
    CGAL_VectorC2<FT> v2 = (r - q)/FT(2);

    CGAL_PointC2<FT> p2 = p + v1 + v1.perpendicular(CGAL_CLOCKWISE);
    CGAL_PointC2<FT> q2 = q + v2 + v2.perpendicular(CGAL_CLOCKWISE);


    CGAL_PointC2<FT> center = CGAL_intersection(p + v1, p2,
                                                q + v2, q2);
    FT x_diff = center.x() - p.x();
    FT y_diff = center.y() - p.y();

    PTR = new CGAL__CircleC2<FT>(center,
                                 x_diff * x_diff + y_diff * y_diff,
                                 o);
  }
  CGAL_nondegeneracy_assertion;
}


template < class FT >
inline CGAL_CircleC2<FT>::~CGAL_CircleC2()
{}


template < class FT >
CGAL_CircleC2<FT> &CGAL_CircleC2<FT>::operator=(const CGAL_CircleC2<FT> &t)
{
  CGAL_Handle::operator=(t);
  return *this;
}
template < class FT >
bool CGAL_CircleC2<FT>::operator==(const CGAL_CircleC2<FT> &t) const
{
   return (center() == t.center()) &&
          (squared_radius() == t.squared_radius() &&
          orientation() == t.orientation());
}

template < class FT >
inline bool CGAL_CircleC2<FT>::operator!=(const CGAL_CircleC2<FT> &t) const
{
  return !(*this == t);
}

template < class FT >
int CGAL_CircleC2<FT>::id() const
{
  return (int)PTR;
}
template < class FT >
CGAL_PointC2<FT> CGAL_CircleC2<FT>::center() const
{
 return ptr()->center;
}

template < class FT >
FT CGAL_CircleC2<FT>::squared_radius() const
{
 return ptr()->squared_radius;
}

template < class FT >
CGAL_Orientation CGAL_CircleC2<FT>::orientation() const
{
 return ptr()->orientation;
}


template < class FT >
CGAL_Oriented_side CGAL_CircleC2<FT>::oriented_side(
                                        const CGAL_PointC2<FT> &p) const
{
  CGAL_Bounded_side bs = bounded_side(p);
  if (bs == CGAL_ON_BOUNDARY) {
    return CGAL_ON_ORIENTED_BOUNDARY;
  }
  if(orientation() == CGAL_COUNTERCLOCKWISE) {
    if(bs == CGAL_ON_BOUNDED_SIDE){
      return CGAL_ON_POSITIVE_SIDE;
    }
    return CGAL_ON_NEGATIVE_SIDE;
  }
  if(bs == CGAL_ON_BOUNDED_SIDE){
    return CGAL_ON_NEGATIVE_SIDE;
  }
  return CGAL_ON_POSITIVE_SIDE;
}


template <class FT>
inline FT
CGAL_squared_distance(
    const CGAL_PointC2<FT> & pt1,
    const CGAL_PointC2<FT> & pt2)
{
    CGAL_VectorC2<FT> vec(pt1-pt2);
    return  FT(vec*vec);
}


template < class FT >
CGAL_Bounded_side CGAL_CircleC2<FT>::bounded_side(
                                       const CGAL_PointC2<FT> &p) const
{
  FT diff = CGAL_squared_distance(center(),p) - squared_radius();

  if (diff > FT(0)) {
    return CGAL_ON_UNBOUNDED_SIDE;
  }
  if (diff < FT(0)) {
    return CGAL_ON_BOUNDED_SIDE;
  }
  return CGAL_ON_BOUNDARY;
}

template < class FT >
bool CGAL_CircleC2<FT>::has_on_boundary(const CGAL_PointC2<FT> &p) const
{
  return CGAL_squared_distance(center(),p) == squared_radius();
}

template < class FT >
bool CGAL_CircleC2<FT>::has_on_negative_side(const CGAL_PointC2<FT> &p) const
{
  if (orientation() == CGAL_COUNTERCLOCKWISE) {
    return has_on_unbounded_side(p);
  }
  return has_on_bounded_side(p);
}

template < class FT >
bool CGAL_CircleC2<FT>::has_on_positive_side(const CGAL_PointC2<FT> &p) const
{
  if (orientation() == CGAL_COUNTERCLOCKWISE) {
    return has_on_bounded_side(p);
  }
  return has_on_unbounded_side(p);
}

template < class FT >
bool CGAL_CircleC2<FT>::has_on_bounded_side(const CGAL_PointC2<FT> &p) const
{
  return CGAL_squared_distance(center(),p) < squared_radius();
}

template < class FT >
bool CGAL_CircleC2<FT>::has_on_unbounded_side(const CGAL_PointC2<FT> &p) const
{
  return CGAL_squared_distance(center(),p) > squared_radius();
}


template < class FT >
bool CGAL_CircleC2<FT>::is_degenerate() const
{
  return squared_radius() == FT(0);
}
template < class FT >
CGAL_CircleC2<FT> CGAL_CircleC2<FT>::opposite() const
{
  return CGAL_CircleC2<FT>(center(),
                           squared_radius(),
                           CGAL_opposite(orientation()) );
}


template < class FT >
inline CGAL_Bbox_2 CGAL_CircleC2<FT>::bbox() const
{
  double cx = CGAL_to_double(center().x());
  double cy = CGAL_to_double(center().y());
  double radius = sqrt(CGAL_to_double(squared_radius()));

  return CGAL_Bbox_2(cx - radius, cy - radius, cx + radius, cy + radius);
}


template < class FT >
inline CGAL_CircleC2<FT> CGAL_CircleC2<FT>::orthogonal_transform(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_VectorC2<FT> vec( FT(1), FT(0) );   // unit vector
  vec = vec.transform(t);                     // transformed
  FT  sq_scale = FT( vec*vec );               // squared scaling factor

  if ( t.is_even() ) {
    return CGAL_CircleC2<FT>(t.transform(center()),
                             sq_scale * squared_radius(),
                             orientation());
  } else {
    return CGAL_CircleC2<FT>(t.transform(center()),
                             sq_scale * squared_radius(),
                             CGAL_opposite(orientation()));
  }
}


/*
template < class FT >
inline CGAL_EllipseC2<FT> CGAL_CircleC2<FT>::transform(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_CircleC2<FT>(t.transform(center()),
                           squared_radius(),
                           orientation());
}
*/


#endif // CGAL_CIRCLEC2_H
