// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Cartesian/Line_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.29 $
// revision_date : $Date: 2002/02/06 12:32:37 $
// author(s)     : Andreas Fabri
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_LINE_3_H
#define CGAL_CARTESIAN_LINE_3_H

CGAL_BEGIN_NAMESPACE

template < class R_ >
class LineC3
  : public R_::Line_handle_3
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::Point_3              Point_3;
  typedef typename R_::Vector_3             Vector_3;
  typedef typename R_::Direction_3          Direction_3;
  typedef typename R_::Plane_3              Plane_3;
  typedef typename R_::Ray_3                Ray_3;
  typedef typename R_::Line_3               Line_3;
  typedef typename R_::Segment_3            Segment_3;
  typedef typename R_::Aff_transformation_3 Aff_transformation_3;

  typedef typename R_::Line_handle_3             base;
  typedef typename base::element_type            rep;

public:
  typedef R_                                     R;

  LineC3()
    : base(rep()) {}

  LineC3(const Point_3 &p, const Point_3 &q)
    : base(rep(p, (q-p).direction())) {}

  LineC3(const Segment_3 &s)
    : base(rep(s.start(), (s.end() - s.start()).direction())) {}

  LineC3(const Ray_3 &r)
    : base(rep(r.start(), (r.point(1) - r.start()).direction())) {}

  LineC3(const Point_3 &p, const Direction_3 &d)
    : base(rep(p, d)) {}

  bool        operator==(const LineC3 &l) const;
  bool        operator!=(const LineC3 &l) const;

  Plane_3     perpendicular_plane(const Point_3 &p) const;
  Line_3      opposite() const;

  const Point_3 &     point() const
  {
      return Ptr()->first;
  }
  const Direction_3 & direction() const
  {
      return Ptr()->second;
  }

  Point_3     point(int i) const;

  Point_3     projection(const Point_3 &p) const;

  bool        has_on(const Point_3 &p) const;
  bool        is_degenerate() const;

  Line_3        transform(const Aff_transformation_3 &t) const
  {
    return LineC3<R>(t.transform(point()), t.transform(direction()));
  }
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template < class R >
inline
bool
LineC3<R>::operator==(const LineC3<R> &l) const
{
  if (identical(l))
      return true;
  return has_on(l.point()) && (direction() == l.direction());
}

template < class R >
inline
bool
LineC3<R>::operator!=(const LineC3<R> &l) const
{
  return !(*this == l);
}

template < class R >
inline
typename LineC3<R>::Point_3
LineC3<R>::point(int i) const
{
  return point_on_line(i, *this);
}

template < class R >
inline
typename LineC3<R>::Plane_3
LineC3<R>::
perpendicular_plane(const typename LineC3<R>::Point_3 &p) const
{
  return Plane_3(p, direction().to_vector());
}

template < class R >
inline
typename LineC3<R>::Line_3
LineC3<R>::opposite() const
{
  return LineC3<R>(point(), -direction());
}

template < class R >
inline
typename LineC3<R>::Point_3
LineC3<R>::
projection(const typename LineC3<R>::Point_3 &p) const
{
  return projection_line(p, *this);
}

template < class R >
inline
bool
LineC3<R>::
has_on(const typename LineC3<R>::Point_3 &p) const
{
  return collinear(point(), point()+direction().to_vector(), p);
}

template < class R >
inline
bool
LineC3<R>::is_degenerate() const
{ // FIXME : predicate
  return direction() == Direction_3(0,0,0);
}

#ifndef CGAL_CARTESIAN_NO_OSTREAM_INSERT_LINEC3
template < class R >
std::ostream &
operator<<(std::ostream &os, const LineC3<R> &l)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << l.point(0) << ' ' << l.point(1);
    case IO::BINARY :
        return os << l.point(0) <<  l.point(1);
    default:
        return  os << "LineC3(" << l.point(0) << ", " << l.point(1) << ")";
    }
}
#endif // CGAL_CARTESIAN_NO_OSTREAM_INSERT_LINEC3

#ifndef CGAL_CARTESIAN_NO_ISTREAM_EXTRACT_LINEC3
template < class R >
std::istream &
operator>>(std::istream &is, LineC3<R> &l)
{
    typename R::Point_3 p, q;
    is >> p >> q;
    if (is)
	l = LineC3<R>(p, q);
    return is;
}
#endif // CGAL_CARTESIAN_NO_ISTREAM_EXTRACT_LINEC3

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_LINE_3_H
