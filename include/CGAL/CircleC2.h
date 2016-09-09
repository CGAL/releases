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
// file          : include/CGAL/CircleC2.h
// package       : C2 (2.1.4)
// source        : web/CircleC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:30 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CIRCLEC2_H
#define CGAL_CIRCLEC2_H

#ifndef CGAL_POINTC2_H
#include <CGAL/PointC2.h>
#endif // CGAL_POINTC2_H
#ifndef CGAL_CIRCLE_REPC2_H
#include <CGAL/Circle_repC2.h>
#endif // CGAL_CIRCLE_REPC2_H
#ifndef CGAL_BASIC_CONSTRUCTIONSC2_H
#include <CGAL/basic_constructionsC2.h>
#endif // CGAL_BASIC_CONSTRUCTIONSC2_H
#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#include <CGAL/predicates_on_pointsC2.h>
#endif // CGAL_PREDICATES_ON_POINTSC2_H

CGAL_BEGIN_NAMESPACE

template <class FT>
class CircleC2 : public Handle
{
public:
                 CircleC2();
                 CircleC2(const CircleC2<FT> &);

                 CircleC2(const PointC2<FT> &center,
                          const FT &squared_radius,
                          const Orientation &orient);

                 CircleC2(const PointC2<FT> &p,
                          const PointC2<FT> &q,
                          const PointC2<FT> &r);

                 CircleC2(const PointC2<FT> &p,
                          const PointC2<FT> &q,
                          const Orientation &orient);

                 ~CircleC2();

  CircleC2<FT>   &operator=(const CircleC2<FT> &t);

  bool           operator==(const CircleC2<FT> &s) const;
  bool           operator!=(const CircleC2<FT> &s) const;
  int            id() const;

  PointC2<FT>    center() const;
  FT             squared_radius() const;

  CircleC2<FT>   opposite() const;

//  EllipseC2<FT> transform(const Aff_transformationC2<FT> &t) const;

  CircleC2<FT>   orthogonal_transform(
                       const Aff_transformationC2<FT> &t) const;

  Orientation    orientation() const;

  Oriented_side  oriented_side(const PointC2<FT> &p) const;
  Bounded_side   bounded_side(const PointC2<FT> &p) const;

  bool           has_on_boundary(const PointC2<FT> &p) const;
  bool           has_on_negative_side(const PointC2<FT> &p) const;
  bool           has_on_positive_side(const PointC2<FT> &p) const;

  bool           has_on_bounded_side(const PointC2<FT> &p) const;
  bool           has_on_unbounded_side(const PointC2<FT> &p) const;

  bool           is_degenerate() const;

  Bbox_2         bbox() const;

private:
  _CircleC2<FT> *ptr() const;
};

template < class FT >
inline
_CircleC2<FT> *CircleC2<FT>::ptr() const
{
  return (_CircleC2<FT>*)PTR;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CircleC2<FT>::CircleC2()
{
  PTR = new _CircleC2<FT> ;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CircleC2<FT>::CircleC2(const CircleC2<FT> &t) :
  Handle((Handle&)t)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CircleC2<FT>::CircleC2(const PointC2<FT> &center,
                       const FT &squared_radius,
                       const Orientation &orient)
{
  CGAL_kernel_precondition( ( squared_radius >= FT( 0)        ) &&
                            ( orient    != COLLINEAR) );

  PTR = new _CircleC2<FT>(center, squared_radius, orient);
}

template < class FT >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
CircleC2<FT>::CircleC2(const PointC2<FT> &p,
                       const PointC2<FT> &q,
                       const Orientation &orient)
{
  CGAL_kernel_precondition( orient != COLLINEAR);

  if ( p != q) {
    PointC2<FT> center = midpoint(p,q);
    FT          squared_radius = squared_distance(p,center);

    PTR = new _CircleC2<FT>( center, squared_radius, orient);
  } else
    PTR = new _CircleC2<FT>( p, FT( 0), orient);

}


template < class FT >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
CircleC2<FT>::CircleC2(const PointC2<FT> &p,
                       const PointC2<FT> &q,
                       const PointC2<FT> &r)
{
  Orientation orient = CGAL::orientation(p,q,r);
  CGAL_kernel_precondition( orient != COLLINEAR);

  PointC2<FT> center = circumcenter(p,q,r);
  FT          squared_radius = squared_distance(p,center);

  PTR = new _CircleC2<FT>(center, squared_radius, orient);
}


template < class FT >
inline
CircleC2<FT>::~CircleC2()
{}


template < class FT >
inline
CircleC2<FT> &CircleC2<FT>::operator=(const CircleC2<FT> &t)
{
  Handle::operator=(t);
  return *this;
}
template < class FT >
CGAL_KERNEL_INLINE
bool CircleC2<FT>::operator==(const CircleC2<FT> &t) const
{
   return (center() == t.center()) &&
          (squared_radius() == t.squared_radius() &&
          orientation() == t.orientation());
}

template < class FT >
inline
bool CircleC2<FT>::operator!=(const CircleC2<FT> &t) const
{
  return !(*this == t);
}

template < class FT >
int CircleC2<FT>::id() const
{
  return (int)PTR;
}
template < class FT >
inline
PointC2<FT> CircleC2<FT>::center() const
{
 return ptr()->center;
}

template < class FT >
inline
FT CircleC2<FT>::squared_radius() const
{
 return ptr()->squared_radius;
}

template < class FT >
inline
Orientation CircleC2<FT>::orientation() const
{
 return ptr()->orient;
}


template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Oriented_side CircleC2<FT>::oriented_side(const PointC2<FT> &p) const
{
  return Oriented_side(bounded_side(p) * orientation());
}

template < class FT >
CGAL_KERNEL_INLINE
Bounded_side CircleC2<FT>::bounded_side(const PointC2<FT> &p) const
{
  return Bounded_side(CGAL::compare(squared_radius(),
                                    squared_distance(center(),p)));
}

template < class FT >
inline
bool CircleC2<FT>::has_on_boundary(const PointC2<FT> &p) const
{
  return squared_distance(center(),p) == squared_radius();
}

template < class FT >
CGAL_KERNEL_INLINE
bool CircleC2<FT>::has_on_negative_side(const PointC2<FT> &p) const
{
  if (orientation() == COUNTERCLOCKWISE) {
    return has_on_unbounded_side(p);
  }
  return has_on_bounded_side(p);
}

template < class FT >
CGAL_KERNEL_INLINE
bool CircleC2<FT>::has_on_positive_side(const PointC2<FT> &p) const
{
  if (orientation() == COUNTERCLOCKWISE) {
    return has_on_bounded_side(p);
  }
  return has_on_unbounded_side(p);
}

template < class FT >
inline
bool CircleC2<FT>::has_on_bounded_side(const PointC2<FT> &p) const
{
  return squared_distance(center(),p) < squared_radius();
}

template < class FT >
inline
bool CircleC2<FT>::has_on_unbounded_side(const PointC2<FT> &p) const
{
  return squared_distance(center(),p) > squared_radius();
}


template < class FT >
inline
bool CircleC2<FT>::is_degenerate() const
{
  return is_zero(squared_radius());
}
template < class FT >
inline
CircleC2<FT> CircleC2<FT>::opposite() const
{
  return CircleC2<FT>(center(),
                      squared_radius(),
                      CGAL::opposite(orientation()) );
}


template < class FT >
CGAL_KERNEL_INLINE
Bbox_2 CircleC2<FT>::bbox() const
{
  double cx = CGAL::to_double(center().x());
  double cy = CGAL::to_double(center().y());
  double radius = sqrt(CGAL::to_double(squared_radius()));

  return Bbox_2(cx - radius, cy - radius, cx + radius, cy + radius);
}


template < class FT >
CGAL_KERNEL_INLINE
CircleC2<FT> CircleC2<FT>::orthogonal_transform(
                                 const Aff_transformationC2<FT> &t) const
{
  VectorC2<FT> vec( FT(1), FT(0) );   // unit vector
  vec = vec.transform(t);             // transformed
  FT  sq_scale = FT( vec*vec );       // squared scaling factor

  return CircleC2<FT>(t.transform(center()),
                      sq_scale * squared_radius(),
                      t.is_even() ? orientation()
                                  : CGAL::opposite(orientation()));
}


/*
template < class FT >
inline
EllipseC2<FT> CircleC2<FT>::transform(
                                 const Aff_transformationC2<FT> &t) const
{
  return CircleC2<FT>(t.transform(center()),
                      squared_radius(),
                      orientation());
}
*/


#ifndef CGAL_NO_OSTREAM_INSERT_CIRCLEC2
template < class FT >
CGAL_KERNEL_INLINE
ostream &operator<<(ostream &os, const CircleC2<FT> &c)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        os << c.center() << ' ' << c.squared_radius() << ' '
           << (int)c.orientation();
        break;
    case IO::BINARY :
        os << c.center();
        write(os, c.squared_radius());
        write(os, (int)c.orientation());
        break;
    default:
        os << "CircleC2(" << c.center() <<  ", " << c.squared_radius() ;
        switch (c.orientation()) {
        case CLOCKWISE:
            os << ", clockwise)";
            break;
        case COUNTERCLOCKWISE:
            os << ", counterclockwise)";
            break;
        default:
            os << ", collinear)";
            break;
        }
        break;
    }
    return os;
}
#endif // CGAL_NO_OSTREAM_INSERT_CIRCLEC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_CIRCLEC2
template < class FT >
CGAL_KERNEL_INLINE
istream& operator>>(istream &is, CircleC2<FT> &c)
{
    PointC2<FT> center;
    FT squared_radius;
    int o;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> center >> squared_radius >> o;
        break;
    case IO::BINARY :
        is >> center;
        read(is, squared_radius);
        is >> o;
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    c = CircleC2<FT>(center, squared_radius, (Orientation)o);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_CIRCLEC2



CGAL_END_NAMESPACE

#endif // CGAL_CIRCLEC2_H
