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
// file          : include/CGAL/TriangleC2.h
// package       : C2 (2.1.4)
// source        : web/TriangleC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:33 $
// author(s)     : Andreas.Fabri
//                 Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGLEC2_H
#define CGAL_TRIANGLEC2_H

#ifndef CGAL_THREETUPLE_H
#include <CGAL/Threetuple.h>
#endif // CGAL_THREETUPLE_H
#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#include <CGAL/predicates_on_pointsC2.h>
#endif // CGAL_PREDICATES_ON_POINTSC2_H

CGAL_BEGIN_NAMESPACE



template <class FT>
class TriangleC2 : public Handle
{
public:
                 TriangleC2();
                 TriangleC2(const TriangleC2<FT> &);
                 TriangleC2(const PointC2<FT> &p,
                            const PointC2<FT> &q,
                            const PointC2<FT> &r);
                 ~TriangleC2();

  TriangleC2<FT> &operator=(const TriangleC2<FT> &t);

  bool           operator==(const TriangleC2<FT> &s) const;
  bool           operator!=(const TriangleC2<FT> &s) const;
  int            id() const;

  PointC2<FT>    vertex(int i) const;
  PointC2<FT>    operator[](int i) const;


  TriangleC2<FT> transform(const Aff_transformationC2<FT> &t) const;

  Orientation    orientation() const;
  Oriented_side  oriented_side(const PointC2<FT> &p) const;
  Bounded_side   bounded_side(const PointC2<FT> &p) const;

  bool           has_on_boundary(const PointC2<FT> &p) const;

  bool           has_on_bounded_side(const PointC2<FT> &p) const;
  bool           has_on_unbounded_side(const PointC2<FT> &p) const;

  bool           has_on_positive_side(const PointC2<FT> &p) const;
  bool           has_on_negative_side(const PointC2<FT> &p) const;

  bool           is_degenerate() const;

  Bbox_2         bbox() const;

private:
  _Threetuple< PointC2<FT> >*   ptr() const;
};

template < class FT >
inline
_Threetuple< PointC2<FT> > *TriangleC2<FT>::ptr() const
{
  return (_Threetuple< PointC2<FT> >*)PTR;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
TriangleC2<FT>::TriangleC2()
{
  PTR = new _Threetuple< PointC2<FT> >;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
TriangleC2<FT>::TriangleC2(const TriangleC2<FT> &t) :
  Handle((Handle&)t)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
TriangleC2<FT>::TriangleC2(const PointC2<FT> &p,
                           const PointC2<FT> &q,
                           const PointC2<FT> &r)
{
  PTR = new _Threetuple< PointC2<FT> >(p, q, r);
}

template < class FT >
inline
TriangleC2<FT>::~TriangleC2()
{}


template < class FT >
inline
TriangleC2<FT> &TriangleC2<FT>::operator=(const TriangleC2<FT> &t)
{
  Handle::operator=(t);
  return *this;
}
template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool TriangleC2<FT>::operator==(const TriangleC2<FT> &t) const
{
  int i;
  for(i=0; i<3; i++)
    if ( vertex(0) == t.vertex(i) )
      break;

  return (i<3) && vertex(1) == t.vertex(i+1) && vertex(2) == t.vertex(i+2);
}

template < class FT >
inline
bool TriangleC2<FT>::operator!=(const TriangleC2<FT> &t) const
{
  return !(*this == t);
}

template < class FT >
inline
int TriangleC2<FT>::id() const
{
  return (int)PTR ;
}
template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
PointC2<FT> TriangleC2<FT>::vertex(int i) const
{
  if (i>2) i = i%3;
  else if (i<0) i = (i%3) + 3;
  return (i==0) ? ptr()->e0 :
         (i==1) ? ptr()->e1 :
                  ptr()->e2 ;
}

template < class FT >
inline
PointC2<FT> TriangleC2<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
inline
Orientation
TriangleC2<FT>::orientation() const
{
  return CGAL::orientation(vertex(0), vertex(1), vertex(2));
}
template < class FT >
CGAL_KERNEL_LARGE_INLINE
Bounded_side
TriangleC2<FT>::bounded_side(const PointC2<FT> &p) const
{
  Orientation o1 = CGAL::orientation(vertex(0), vertex(1), p),
              o2 = CGAL::orientation(vertex(1), vertex(2), p),
              o3 = CGAL::orientation(vertex(2), vertex(3), p);

  if (o2 == o1 && o3 == o1)
    return ON_BOUNDED_SIDE;
  return
     (o1 == COLLINEAR
       && collinear_are_ordered_along_line(vertex(0), p, vertex(1))) ||
     (o2 == COLLINEAR
       && collinear_are_ordered_along_line(vertex(1), p, vertex(2))) ||
     (o3 == COLLINEAR
       && collinear_are_ordered_along_line(vertex(2), p, vertex(3)))
     ? ON_BOUNDARY
     : ON_UNBOUNDED_SIDE;
}


template < class FT >
CGAL_KERNEL_LARGE_INLINE
Oriented_side
TriangleC2<FT>::oriented_side(const PointC2<FT> &p) const
{
  // depends on the orientation of the vertices
  Orientation o1 = CGAL::orientation(vertex(0), vertex(1), p),
              o2 = CGAL::orientation(vertex(1), vertex(2), p),
              o3 = CGAL::orientation(vertex(2), vertex(3), p),
              ot = CGAL::orientation(vertex(0), vertex(1), vertex(2));

  if (o1 == ot && o2 == ot && o3 == ot) // ot cannot be COLLINEAR
    return Oriented_side(ot);
  return
     (o1 == COLLINEAR
       && collinear_are_ordered_along_line(vertex(0), p, vertex(1))) ||
     (o2 == COLLINEAR
       && collinear_are_ordered_along_line(vertex(1), p, vertex(2))) ||
     (o3 == COLLINEAR
       && collinear_are_ordered_along_line(vertex(2), p, vertex(3)))
     ? ON_ORIENTED_BOUNDARY
     : Oriented_side(opposite(ot));
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
TriangleC2<FT>::has_on_bounded_side(const PointC2<FT> &p) const
{
  return bounded_side(p) == ON_BOUNDED_SIDE;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
TriangleC2<FT>::has_on_unbounded_side(const PointC2<FT> &p) const
{
  return bounded_side(p) == ON_UNBOUNDED_SIDE;
}

template < class FT >
inline
bool TriangleC2<FT>::has_on_boundary(const PointC2<FT> &p) const
{
  return bounded_side(p) == ON_BOUNDARY;
}

template < class FT >
inline
bool TriangleC2<FT>::has_on_negative_side(const PointC2<FT> &p) const
{
  return oriented_side(p) == ON_NEGATIVE_SIDE;
}

template < class FT >
inline
bool TriangleC2<FT>::has_on_positive_side(const PointC2<FT> &p) const
{
  return oriented_side(p) == ON_POSITIVE_SIDE;
}

template < class FT >
inline
bool TriangleC2<FT>::is_degenerate() const
{
  return collinear(vertex(0), vertex(1), vertex(2));
}
template < class FT >
inline
Bbox_2 TriangleC2<FT>::bbox() const
{
  return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}


template < class FT >
inline
TriangleC2<FT>
TriangleC2<FT>::transform(const Aff_transformationC2<FT> &t) const
{
  return TriangleC2<FT>(t.transform(vertex(0)),
                        t.transform(vertex(1)),
                        t.transform(vertex(2)));
}


#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLEC2
template < class FT >
ostream &operator<<(ostream &os, const TriangleC2<FT> &t)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2];
    case IO::BINARY :
        return os << t[0] << t[1]  << t[2];
    default:
        return os<< "TriangleC2(" << t[0] << ", " << t[1] << ", " << t[2] <<")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLEC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLEC2
template < class FT >
istream &operator>>(istream &is, TriangleC2<FT> &t)
{
    PointC2<FT> p, q, r;

    is >> p >> q >> r;

    t = TriangleC2<FT>(p, q, r);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLEC2



CGAL_END_NAMESPACE

#endif
