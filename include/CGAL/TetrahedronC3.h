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
// file          : include/CGAL/TetrahedronC3.h
// package       : C3 (2.1.5)
// source        : web/TetrahedronC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:38 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TETRAHEDRONC3_H
#define CGAL_TETRAHEDRONC3_H

#ifndef CGAL_FOURTUPLE_H
#include <CGAL/Fourtuple.h>
#endif // CGAL_FOURTUPLE_H
#ifndef CGAL_PLANEC3_H
#include <CGAL/PlaneC3.h>
#endif // CGAL_PLANEC3_H
#ifndef CGAL_SOLVEC3_H
#include <CGAL/solveC3.h>
#endif // CGAL_SOLVEC3_H

CGAL_BEGIN_NAMESPACE

template <class FT>
class TetrahedronC3 : public Handle
{
public:
                 TetrahedronC3();
                 TetrahedronC3(const TetrahedronC3<FT> &t);
                 TetrahedronC3(const PointC3<FT> &p,
                               const PointC3<FT> &q,
                               const PointC3<FT> &r,
                               const PointC3<FT> &s);
                 ~TetrahedronC3();

  TetrahedronC3<FT> &operator=(const TetrahedronC3<FT> &t);

  PointC3<FT>    vertex(int i) const;
  PointC3<FT>    operator[](int i) const;

  bool           operator==(const TetrahedronC3<FT> &t) const;
  bool           operator!=(const TetrahedronC3<FT> &t) const;
  long           id() const;

  Bbox_3         bbox() const;

  TetrahedronC3<FT> transform(const Aff_transformationC3<FT> &t) const;

  Orientation    orientation() const;
  Oriented_side  oriented_side(const PointC3<FT> &p) const;
  Bounded_side   bounded_side(const PointC3<FT> &p) const;

  bool           has_on_boundary(const PointC3<FT> &p) const;
  bool           has_on_positive_side(const PointC3<FT> &p) const;
  bool           has_on_negative_side(const PointC3<FT> &p) const;
  bool           has_on_bounded_side(const PointC3<FT> &p) const;
  bool           has_on_unbounded_side(const PointC3<FT> &p) const;

  bool           is_degenerate() const;

private:
  _Fourtuple< PointC3<FT> >*   ptr() const;
};

template < class FT >
_Fourtuple< PointC3<FT> >*  TetrahedronC3<FT>::ptr() const
{
  return (_Fourtuple< PointC3<FT> >*)PTR;
}

template < class FT >
TetrahedronC3<FT>::TetrahedronC3()
{
  PTR = new _Fourtuple< PointC3<FT> >;
}


template < class FT >
TetrahedronC3<FT>::TetrahedronC3(const TetrahedronC3<FT> &t) :
  Handle(t)
{}


template < class FT >
TetrahedronC3<FT>::TetrahedronC3(const PointC3<FT> &p,
                                 const PointC3<FT> &q,
                                 const PointC3<FT> &r,
                                 const PointC3<FT> &s)
{
  PTR = new _Fourtuple< PointC3<FT> >(p, q, r, s);
}


template < class FT >
inline TetrahedronC3<FT>::~TetrahedronC3()
{}


template < class FT >
TetrahedronC3<FT> &TetrahedronC3<FT>::operator=(const TetrahedronC3<FT> &t)
{
  Handle::operator=(t);
  return *this;
}
template < class FT >
bool
TetrahedronC3<FT>::operator==(const TetrahedronC3<FT> &t) const
{
  if ( id() == t.id() ) return true;
  if ( orientation() != t.orientation() ) return false;

  int i;
  for (i=0; i<4; i++)
    if ( vertex(0) == t.vertex(i) )
      break;

  // the following is a fix-up until the proper STL-algorithms can be
  // used as in H3
  if (i == 4) return false;
  return (vertex(1) == t.vertex(i+1))
            && (vertex(2) == t.vertex(i+2)) && (vertex(3) == t.vertex(i+3)) ||
    (vertex(1) == t.vertex(i+2))
            && (vertex(2) == t.vertex(i+3)) && (vertex(3) == t.vertex(i+1)) ||
    (vertex(1) == t.vertex(i+3))
            && (vertex(2) == t.vertex(i+1)) && (vertex(3) == t.vertex(i+2));
}


template < class FT >
inline
bool
TetrahedronC3<FT>::operator!=(const TetrahedronC3<FT> &t) const
{
  return !(*this == t);
}


template < class FT >
inline
long TetrahedronC3<FT>::id() const
{
  return (long) PTR;
}
template < class FT >
PointC3<FT>
TetrahedronC3<FT>::vertex(int i) const
{
  // modulo 4 is a logical operation, hence cheap
  if (i<0) i=(i%4)+4;
  else if (i>3) i=i%4;
  switch (i)
    {
    case 0: return ptr()->e0;
    case 1: return ptr()->e1;
    case 2: return ptr()->e2;
    default: return ptr()->e3;
    }
}


template < class FT >
inline
PointC3<FT>
TetrahedronC3<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
inline
bool
TetrahedronC3<FT>::has_on_boundary(const PointC3<FT> &p) const
{
  return oriented_side(p) == ON_ORIENTED_BOUNDARY;
}


template < class FT >
inline
bool
TetrahedronC3<FT>::has_on_positive_side(const PointC3<FT> &p) const
{
  return oriented_side(p) == ON_POSITIVE_SIDE;
}


template < class FT >
inline
bool
TetrahedronC3<FT>::has_on_negative_side(const PointC3<FT> &p) const
{
  return oriented_side(p) == ON_NEGATIVE_SIDE;
}


template < class FT >
inline
bool
TetrahedronC3<FT>::has_on_bounded_side(const PointC3<FT> &p) const
{
  return oriented_side(p) == ON_BOUNDED_SIDE;
}


template < class FT >
inline
bool
TetrahedronC3<FT>::has_on_unbounded_side(const PointC3<FT> &p) const
{
  return oriented_side(p) == ON_UNBOUNDED_SIDE;
}
template < class FT >
Orientation
TetrahedronC3<FT>::orientation() const
{
  return CGAL::orientation(vertex(0), vertex(1), vertex(2), vertex(3));
}
template < class FT >
Oriented_side
TetrahedronC3<FT>::oriented_side(const PointC3<FT> &p) const
{
  Orientation o = orientation();
  if (o != ZERO)
    return Oriented_side(o * bounded_side(p));

  CGAL_assertion (!is_degenerate());
  return ON_ORIENTED_BOUNDARY;
}
template < class FT >
Bounded_side
TetrahedronC3<FT>::bounded_side(const PointC3<FT> &p) const
{
  FT alpha, beta, gamma;

  solve(vertex(1)-vertex(0), vertex(2)-vertex(0), vertex(3)-vertex(0),
             p - vertex(0), alpha, beta, gamma);
  if (   (alpha < FT(0)) || (beta < FT(0)) || (gamma < FT(0))
      || (alpha + beta + gamma > FT(1)) )
      return ON_UNBOUNDED_SIDE;

  if (   (alpha == FT(0)) || (beta == FT(0)) || (gamma == FT(0))
      || (alpha+beta+gamma == FT(1)) )
    return ON_BOUNDARY;

  return ON_BOUNDED_SIDE;
}
template < class FT >
bool
TetrahedronC3<FT>::is_degenerate() const
{
  PlaneC3<FT> plane(vertex(0), vertex(1), vertex(2));
  return (plane.is_degenerate()) ? true
                                 : plane.has_on_boundary(vertex(3));
}


template < class FT >
inline
Bbox_3
TetrahedronC3<FT>::bbox() const
{
  return vertex(0).bbox() + vertex(1).bbox()
       + vertex(2).bbox() + vertex(3).bbox();
}


template < class FT >
inline
TetrahedronC3<FT>
TetrahedronC3<FT>::transform(const Aff_transformationC3<FT> &t) const
{
  return TetrahedronC3<FT>(t.transform(vertex(0)),
                           t.transform(vertex(1)),
                           t.transform(vertex(2)),
                           t.transform(vertex(3)));
}

#ifndef CGAL_NO_OSTREAM_INSERT_TETRAHEDRONC3
template < class FT >
ostream &operator<<(ostream &os, const TetrahedronC3<FT> &t)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2] << ' ' << t[3];
    case IO::BINARY :
        return os << t[0]  << t[1]  << t[2] << t[3];
    default:
        os << "TetrahedronC3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] ;
        os <<  ", " << t[3] << ")";
        return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_TETRAHEDRONC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRONC3
template < class FT >
istream &operator>>(istream &is, TetrahedronC3<FT> &t)
{
    PointC3<FT> p, q, r, s;

    is >> p >> q >> r >> s;

    t = TetrahedronC3<FT>(p, q, r, s);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRONC3


CGAL_END_NAMESPACE

#endif
