// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/CircleC2.h
// package       : C2 (1.3)
// source        : web/CircleC2.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1997/12/15 11:11:26 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CIRCLEC2_H
#define CGAL_CIRCLEC2_H

#include <CGAL/PointC2.h>
#include <CGAL/Circle_repC2.h>
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

                      CGAL_CircleC2(const CGAL_PointC2<FT> &p,
                                    const CGAL_PointC2<FT> &q,
                                    const CGAL_PointC2<FT> &r);

                      CGAL_CircleC2(const CGAL_PointC2<FT> &p,
                                    const CGAL_PointC2<FT> &q,
                                    const CGAL_Orientation &orientation);

                      ~CGAL_CircleC2();

  CGAL_CircleC2<FT>   &operator=(const CGAL_CircleC2<FT> &t);

  bool                operator==(const CGAL_CircleC2<FT> &s) const;
  bool                operator!=(const CGAL_CircleC2<FT> &s) const;
  int                 id() const;

  CGAL_PointC2<FT>    center() const;
  FT                  squared_radius() const;

  CGAL_CircleC2<FT>   opposite() const;

//  CGAL_EllipseC2<FT> transform(const CGAL_Aff_transformationC2<FT> &t) const;

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
inline
CGAL__CircleC2<FT> *CGAL_CircleC2<FT>::ptr() const
{
  return (CGAL__CircleC2<FT>*)PTR;
}


template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_CircleC2<FT>::CGAL_CircleC2()
{
  PTR = new CGAL__CircleC2<FT> ;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_CircleC2<FT> &t) :
  CGAL_Handle((CGAL_Handle&)t)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_PointC2<FT> &center,
                                 const FT &squared_radius,
                                 const CGAL_Orientation &orientation)
{
  CGAL_kernel_precondition( ( squared_radius >= FT( 0)        ) &&
                            ( orientation    != CGAL_COLLINEAR) );

  PTR = new CGAL__CircleC2<FT>(center, squared_radius, orientation);
}

template < class FT >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_PointC2<FT> &p,
                                 const CGAL_PointC2<FT> &q,
                                 const CGAL_Orientation &orientation)
{
  CGAL_kernel_precondition( orientation != CGAL_COLLINEAR);

  if ( p != q) {
    CGAL_PointC2<FT> center = p + (q-p)/FT( 2);

    FT x_diff = center.x() - p.x();
    FT y_diff = center.y() - p.y();

    PTR = new CGAL__CircleC2<FT>( center,
                                  x_diff * x_diff + y_diff * y_diff,
                                  orientation);
  } else
   PTR = new CGAL__CircleC2<FT>( p, FT( 0), orientation);

}


template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
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
  CGAL_assertion( n != FT(0.0));
  return CGAL_PointC2<FT>( (l1b*l2c - l2b*l1c)/n,
                          (l2a*l1c - l1a*l2c)/n );
}


template < class FT >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
CGAL_CircleC2<FT>::CGAL_CircleC2(const CGAL_PointC2<FT> &p,
                                 const CGAL_PointC2<FT> &q,
                                 const CGAL_PointC2<FT> &r)
{
  CGAL_Orientation orientation = CGAL_orientation(p,q,r);
  CGAL_kernel_precondition( orientation != CGAL_COLLINEAR);

  CGAL_VectorC2<FT> v1 = (q - p)/FT(2);
  CGAL_VectorC2<FT> v2 = (r - q)/FT(2);

  CGAL_PointC2<FT> p2 = p + v1 + v1.perpendicular(CGAL_CLOCKWISE);
  CGAL_PointC2<FT> q2 = q + v2 + v2.perpendicular(CGAL_CLOCKWISE);

  CGAL_PointC2<FT> center = CGAL_intersection( p + v1, p2,
       q + v2, q2);
  FT x_diff = center.x() - p.x();
  FT y_diff = center.y() - p.y();

  PTR = new CGAL__CircleC2<FT>(center,
                               x_diff * x_diff + y_diff * y_diff,
                               orientation);
}


template < class FT >
inline
CGAL_CircleC2<FT>::~CGAL_CircleC2()
{}


template < class FT >
inline
CGAL_CircleC2<FT> &CGAL_CircleC2<FT>::operator=(const CGAL_CircleC2<FT> &t)
{
  CGAL_Handle::operator=(t);
  return *this;
}
template < class FT >
CGAL_KERNEL_INLINE
bool CGAL_CircleC2<FT>::operator==(const CGAL_CircleC2<FT> &t) const
{
   return (center() == t.center()) &&
          (squared_radius() == t.squared_radius() &&
          orientation() == t.orientation());
}

template < class FT >
inline
bool CGAL_CircleC2<FT>::operator!=(const CGAL_CircleC2<FT> &t) const
{
  return !(*this == t);
}

template < class FT >
int CGAL_CircleC2<FT>::id() const
{
  return (int)PTR;
}
template < class FT >
inline
CGAL_PointC2<FT> CGAL_CircleC2<FT>::center() const
{
 return ptr()->center;
}

template < class FT >
inline
FT CGAL_CircleC2<FT>::squared_radius() const
{
 return ptr()->squared_radius;
}

template < class FT >
inline
CGAL_Orientation CGAL_CircleC2<FT>::orientation() const
{
 return ptr()->orientation;
}


template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
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
CGAL_KERNEL_INLINE
FT CGAL_squared_distance(
    const CGAL_PointC2<FT> & pt1,
    const CGAL_PointC2<FT> & pt2)
{
    CGAL_VectorC2<FT> vec(pt1-pt2);
    return  FT(vec*vec);
}


template < class FT >
CGAL_KERNEL_INLINE
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
inline
bool CGAL_CircleC2<FT>::has_on_boundary(const CGAL_PointC2<FT> &p) const
{
  return CGAL_squared_distance(center(),p) == squared_radius();
}

template < class FT >
CGAL_KERNEL_INLINE
bool CGAL_CircleC2<FT>::has_on_negative_side(const CGAL_PointC2<FT> &p) const
{
  if (orientation() == CGAL_COUNTERCLOCKWISE) {
    return has_on_unbounded_side(p);
  }
  return has_on_bounded_side(p);
}

template < class FT >
CGAL_KERNEL_INLINE
bool CGAL_CircleC2<FT>::has_on_positive_side(const CGAL_PointC2<FT> &p) const
{
  if (orientation() == CGAL_COUNTERCLOCKWISE) {
    return has_on_bounded_side(p);
  }
  return has_on_unbounded_side(p);
}

template < class FT >
inline
bool CGAL_CircleC2<FT>::has_on_bounded_side(const CGAL_PointC2<FT> &p) const
{
  return CGAL_squared_distance(center(),p) < squared_radius();
}

template < class FT >
inline
bool CGAL_CircleC2<FT>::has_on_unbounded_side(const CGAL_PointC2<FT> &p) const
{
  return CGAL_squared_distance(center(),p) > squared_radius();
}


template < class FT >
inline
bool CGAL_CircleC2<FT>::is_degenerate() const
{
  return squared_radius() == FT(0);
}
template < class FT >
inline
CGAL_CircleC2<FT> CGAL_CircleC2<FT>::opposite() const
{
  return CGAL_CircleC2<FT>(center(),
                           squared_radius(),
                           CGAL_opposite(orientation()) );
}


template < class FT >
CGAL_KERNEL_INLINE
CGAL_Bbox_2 CGAL_CircleC2<FT>::bbox() const
{
  double cx = CGAL_to_double(center().x());
  double cy = CGAL_to_double(center().y());
  double radius = sqrt(CGAL_to_double(squared_radius()));

  return CGAL_Bbox_2(cx - radius, cy - radius, cx + radius, cy + radius);
}


template < class FT >
CGAL_KERNEL_INLINE
CGAL_CircleC2<FT> CGAL_CircleC2<FT>::orthogonal_transform(
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
inline
CGAL_EllipseC2<FT> CGAL_CircleC2<FT>::transform(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_CircleC2<FT>(t.transform(center()),
                           squared_radius(),
                           orientation());
}
*/


#ifndef CGAL_NO_OSTREAM_INSERT_CIRCLEC2
template < class FT >
CGAL_KERNEL_INLINE
ostream &operator<<(ostream &os, const CGAL_CircleC2<FT> &c)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        os << c.center() << ' ' << c.squared_radius() << ' '
           << (int)c.orientation();
        break;
    case CGAL_IO::BINARY :
        os << c.center();
        CGAL_write(os, c.squared_radius());
        CGAL_write(os, (int)c.orientation());
        break;
    default:
        os << "CircleC2(" << c.center() <<  ", " << c.squared_radius() ;
        if (c.orientation() == CGAL_CLOCKWISE) {
            os << ", clockwise)";
        } else if (c.orientation() == CGAL_COUNTERCLOCKWISE) {
            os << ", counterclockwise)";
        } else {
            os << ", collinear)";
        }
        break;
    }
    return os;
}
#endif // CGAL_NO_OSTREAM_INSERT_CIRCLEC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_CIRCLEC2
template < class FT >
CGAL_KERNEL_INLINE
istream& operator>>(istream &is, CGAL_CircleC2<FT> &c)
{
    CGAL_PointC2<FT> center;
    FT squared_radius;
    int o;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> center >> squared_radius >> o;
        break;
    case CGAL_IO::BINARY :
        is >> center;
        CGAL_read(is, c.squared_radius());
        is >> o;
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    c = CGAL_CircleC2<FT>(center, squared_radius, (CGAL_Orientation)o);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_CIRCLEC2



#endif // CGAL_CIRCLEC2_H
