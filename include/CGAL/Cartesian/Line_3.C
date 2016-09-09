// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian/Line_3.C
// package       : C3 (5.2)
// revision      : $Revision: 1.21 $
// revision_date : $Date: 2000/07/09 10:39:14 $
// author(s)     : Andreas Fabri
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_LINE_3_C
#define CGAL_CARTESIAN_LINE_3_C

#include <CGAL/Cartesian/Segment_3.h>
#include <CGAL/Cartesian/Ray_3.h>
#include <CGAL/Cartesian/Plane_3.h>
#include <CGAL/Cartesian/constructions_on_lines_3.h>

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_3_H
#define CGAL_CTAG
#endif

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
inline
void
LineC3<R CGAL_CTAG>::
new_rep(const typename LineC3<R CGAL_CTAG>::Point_3 &p,
        const typename LineC3<R CGAL_CTAG>::Vector_3 &v)
{
  // CGAL_kernel_precondition(  v != NULL_VECTOR );
  new ( static_cast< void*>(ptr)) Twotuple< Point_3 > (p, ORIGIN+v);
}

template < class R >
LineC3<R CGAL_CTAG>::LineC3()
{
  new ( static_cast< void*>(ptr)) Twotuple<Point_3>();
}

template < class R >
LineC3<R CGAL_CTAG>::LineC3(const LineC3<R CGAL_CTAG>  &l)
  : Handle_for<Twotuple<typename R::Point_3 > >(l)
{}

template < class R >
LineC3<R CGAL_CTAG>::
LineC3(const typename LineC3<R CGAL_CTAG>::Point_3 &p,
       const typename LineC3<R CGAL_CTAG>::Point_3 &q)
{
  new_rep(p, q-p);
}

template < class R >
LineC3<R CGAL_CTAG>::
LineC3(const typename LineC3<R CGAL_CTAG>::Segment_3 &s)
{
  new_rep(s.start(), s.end() - s.start());
}

template < class R >
LineC3<R CGAL_CTAG>::
LineC3(const typename LineC3<R CGAL_CTAG>::Ray_3 &r)
{
  new_rep(r.start(), r.point(1) - r.start());
}

template < class R >
inline
LineC3<R CGAL_CTAG>::
LineC3(const typename LineC3<R CGAL_CTAG>::Point_3 &p,
       const typename LineC3<R CGAL_CTAG>::Direction_3 &d)
{
  new_rep(p, d.to_vector());
}

template < class R >
inline
LineC3<R CGAL_CTAG>::~LineC3()
{}

template < class R >
inline
bool
LineC3<R CGAL_CTAG>::operator==(const LineC3<R CGAL_CTAG> &l) const
{
  if (ptr == l.ptr) return true;
  return has_on(l.point()) && (direction() == l.direction());
}

template < class R >
inline
bool
LineC3<R CGAL_CTAG>::operator!=(const LineC3<R CGAL_CTAG> &l) const
{
  return !(*this == l);
}

template < class R >
inline
typename LineC3<R CGAL_CTAG>::Point_3
LineC3<R CGAL_CTAG>::point() const
{
  return ptr->e0;
}

template < class R >
inline
typename LineC3<R CGAL_CTAG>::Direction_3
LineC3<R CGAL_CTAG>::
direction() const
{
  return ((ptr->e1) - ORIGIN).direction();
}

template < class R >
inline
typename LineC3<R CGAL_CTAG>::Point_3
LineC3<R CGAL_CTAG>::
point(int i) const
{
  return point_on_line(i,*this);
}

template < class R >
inline
typename LineC3<R CGAL_CTAG>::Plane_3
LineC3<R CGAL_CTAG>::
perpendicular_plane(const typename LineC3<R CGAL_CTAG>::Point_3 &p) const
{
  return Plane_3(p, direction().to_vector());
}

template < class R >
inline
LineC3<R CGAL_CTAG>
LineC3<R CGAL_CTAG>::
opposite() const
{
  return LineC3<R CGAL_CTAG>(point(), -direction());
}

template < class R >
inline
typename LineC3<R CGAL_CTAG>::Point_3
LineC3<R CGAL_CTAG>::
projection(const typename LineC3<R CGAL_CTAG>::Point_3 &p) const
{
  return projection_line(p,*this);
}

template < class R >
inline
bool
LineC3<R CGAL_CTAG>::
has_on(const typename LineC3<R CGAL_CTAG>::Point_3 &p) const
{
  return collinear(point(), point()+direction().to_vector(), p);
}

template < class R >
inline
bool
LineC3<R CGAL_CTAG>::is_degenerate() const
{
  return direction() == Direction_3(0,0,0);
}

template < class R >
inline
LineC3<R CGAL_CTAG>
LineC3<R CGAL_CTAG>::
transform(const typename LineC3<R CGAL_CTAG>::Aff_transformation_3 &t) const
{
  return LineC3<R CGAL_CTAG>( t.transform(point()), t.transform(direction()));
}

#ifndef CGAL_CARTESIAN_NO_OSTREAM_INSERT_LINEC3
template < class R >
std::ostream &
operator<<(std::ostream &os, const LineC3<R CGAL_CTAG> &l)
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
operator>>(std::istream &is, LineC3<R CGAL_CTAG> &l)
{
    typename LineC3<R CGAL_CTAG>::Point_3 p, q;
    is >> p >> q;
    l = LineC3<R CGAL_CTAG>(p, q);
    return is;
}
#endif // CGAL_CARTESIAN_NO_ISTREAM_EXTRACT_LINEC3

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

#endif // CGAL_CARTESIAN_LINE_3_C
