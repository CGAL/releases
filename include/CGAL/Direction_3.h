// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/Direction_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/27 14:49:51 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_DIRECTION_3_H
#define CGAL_DIRECTION_3_H

#include <CGAL/Vector_3.h>
#include <CGAL/Line_3.h>
#include <CGAL/Ray_3.h>
#include <CGAL/Segment_3.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Direction_3 : public R_::Direction_3_base
{
public:
  typedef          R_                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Direction_3_base  RDirection_3;
  typedef typename R::Vector_3_base  RVector_3;
  typedef typename R::Line_3_base           RLine_3;
  typedef typename R::Ray_3_base            RRay_3;
  typedef typename R::Segment_3_base        RSegment_3;

  Direction_3()
  {}

  Direction_3(const CGAL::Direction_3<R>& d)
    : RDirection_3( static_cast<const RDirection_3&>(d) )
  {}

  Direction_3(const RDirection_3&  d)
    : RDirection_3(d)
  {}

  Direction_3(const RVector_3&  v)
    : RDirection_3(v)
  {}

  Direction_3(const RLine_3& l)
    : RDirection_3(l)
  {}

  Direction_3(const RRay_3& r)
    : RDirection_3(r)
  {}

  Direction_3(const RSegment_3& s)
    : RDirection_3(s)
  {}

  Direction_3(const RT& hx, const RT& hy, const RT& hz)
    : RDirection_3(hx, hy, hz)
  {}

  CGAL::Vector_3<R> vector() const
  { return static_cast<CGAL::Vector_3<R> >(RDirection_3::to_vector()); }

  CGAL::Vector_3<R> to_vector() const
  { return static_cast<CGAL::Vector_3<R> >(RDirection_3::to_vector()); }

  CGAL::Direction_3<R> transform(const CGAL::Aff_transformation_3<R> & t) const
  { return RDirection_3::transform(t); }

  CGAL::Direction_3<R> operator-() const
  { return RDirection_3::operator-(); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTION_3
template < class R >
std::ostream& operator<<(std::ostream& os, const Direction_3<R>& d)
{
  typedef typename  R::Direction_3_base  RDirection_3;
  return os << static_cast<const RDirection_3&>(d); }
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTION_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTION_3
template < class R >
std::istream& operator>>(std::istream& is, Direction_3<R>& p)
{
  typedef typename  R::Direction_3_base  RDirection_3;
  return is >> static_cast<RDirection_3&>(p); }
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTION_3

CGAL_END_NAMESPACE

#endif // CGAL_DIRECTION_3_H
