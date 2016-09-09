// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// source        : webS3/S3.lw
// file          : include/CGAL/SimpleCartesian/Iso_cuboidS3.h
// package       : S3 (1.6)
// revision      : 1.6
// revision_date : 28 Jun 2000
// author(s)     : Stefan Schirra
//                 based on code by
//                 Andreas Fabri and
//                 Herve Brönnimann
//
// coordinator   : MPI, Saarbrücken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ISO_CUBOIDS3_H
#define CGAL_ISO_CUBOIDS3_H

#include <CGAL/Bbox_3.h>
#include <CGAL/predicates_on_points_3.h>

CGAL_BEGIN_NAMESPACE

template < class FT >
class Iso_cuboidS3
{
 public:
  Iso_cuboidS3() {}
  Iso_cuboidS3(const PointS3<FT>& p, const PointS3<FT>& q);

  bool         operator==(const Iso_cuboidS3<FT>& s) const;
  bool         operator!=(const Iso_cuboidS3<FT>& s) const;

  const PointS3<FT>&  min() const { return e0; }
  const PointS3<FT>&  max() const { return e1; }
  PointS3<FT>         vertex(int i) const;
  PointS3<FT>         operator[](int i) const { return vertex(i); }
  Iso_cuboidS3<FT>    transform(const Aff_transformationS3<FT>& t) const;

  Bounded_side bounded_side(const PointS3<FT>& p) const;
  bool         has_on(const PointS3<FT>& p) const;
  bool         has_on_boundary(const PointS3<FT>& p) const;
  bool         has_on_bounded_side(const PointS3<FT>& p) const;
  bool         has_on_unbounded_side(const PointS3<FT>& p) const;
  bool         is_degenerate() const;
  Bbox_3       bbox() const;
  const FT&    xmin() const;
  const FT&    ymin() const;
  const FT&    zmin() const;
  const FT&    xmax() const;
  const FT&    ymax() const;
  const FT&    zmax() const;

protected:
  PointS3<FT>  e0;
  PointS3<FT>  e1;
};

template < class FT >
CGAL_KERNEL_CTOR_LARGE_INLINE
Iso_cuboidS3<FT>::Iso_cuboidS3(const PointS3<FT>& p, const PointS3<FT>& q)
{
  FT minx, maxx, miny, maxy, minz, maxz;
  if (p.x() < q.x()) 
  { minx = p.x(); maxx = q.x(); }
  else               
  { minx = q.x(); maxx = p.x(); }

  if (p.y() < q.y()) 
  { miny = p.y(); maxy = q.y(); }
  else               
  { miny = q.y(); maxy = p.y(); }

  if (p.z() < q.z()) 
  { minz = p.z(); maxz = q.z(); }
  else               
  { minz = q.z(); maxz = p.z(); }

  e0 = PointS3<FT>(minx, miny, minz);
  e1 = PointS3<FT>(maxx, maxy, maxz);
}

template < class FT >
CGAL_KERNEL_INLINE
bool
Iso_cuboidS3<FT>::operator==(const Iso_cuboidS3<FT>& r) const
{ return  (min() == r.min()) && (max() == r.max()); }

template < class FT >
inline
bool
Iso_cuboidS3<FT>::operator!=(const Iso_cuboidS3<FT>& r) const
{ return !(*this == r); }

template < class FT >
inline
const FT&
Iso_cuboidS3<FT>::xmin() const
{ return min().x(); }

template < class FT >
inline
const FT&
Iso_cuboidS3<FT>::ymin() const
{ return min().y(); }

template < class FT >
inline
const FT&
Iso_cuboidS3<FT>::zmin() const
{ return min().z(); }

template < class FT >
inline
const FT&
Iso_cuboidS3<FT>::xmax() const
{ return max().x(); }

template < class FT >
inline
const FT&
Iso_cuboidS3<FT>::ymax() const
{ return max().y(); }

template < class FT >
inline
const FT&
Iso_cuboidS3<FT>::zmax() const
{ return max().z(); }

template < class FT >
CGAL_KERNEL_LARGE_INLINE
PointS3<FT>
Iso_cuboidS3<FT>::vertex(int i) const
{
  switch (i%8)
  {
    case 0: return min();
    case 1: return PointS3<FT>(e1.x(), e0.y(), e0.z());
    case 2: return PointS3<FT>(e1.x(), e1.y(), e0.z());
    case 3: return PointS3<FT>(e0.x(), e1.y(), e0.z());
    case 4: return PointS3<FT>(e0.x(), e1.y(), e1.z());
    case 5: return PointS3<FT>(e0.x(), e0.y(), e1.z());
    case 6: return PointS3<FT>(e1.x(), e0.y(), e1.z());
    case 7: return max();
  }
  return PointS3<FT>();
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Bounded_side
Iso_cuboidS3<FT>::bounded_side(const PointS3<FT>& p) const
{
  if (   ( p.x() < e0.x() )
       ||( e1.x() < p.x() )
       ||( p.y() < e0.y() )
       ||( e1.y() < p.y() )
       ||( p.z() < e0.z() )
       ||( e1.z() < p.z() ) )
  { return ON_UNBOUNDED_SIDE; }
  if (   ( p.x() == e0.x() )
       ||( e1.x() == p.x() )
       ||( p.y() == e0.y() )
       ||( e1.y() == p.y() )
       ||( p.z() == e0.z() )
       ||( e1.z() == p.z() ) )
  { return ON_BOUNDARY; }
  else
  { return ON_BOUNDED_SIDE; }
}


template < class FT >
inline
bool
Iso_cuboidS3<FT>::has_on_boundary(const PointS3<FT>& p) const
{ return ( bounded_side(p) == ON_BOUNDARY ); }

template < class FT >
inline
bool
Iso_cuboidS3<FT>::has_on(const PointS3<FT>& p) const
{ return ( bounded_side(p) == ON_BOUNDARY ); }

template < class FT >
inline
bool
Iso_cuboidS3<FT>::has_on_bounded_side(const PointS3<FT>& p) const
{ return ( bounded_side(p) == ON_BOUNDED_SIDE ); }

template < class FT >
CGAL_KERNEL_INLINE
bool
Iso_cuboidS3<FT>::has_on_unbounded_side(const PointS3<FT>& p) const
{ return ( bounded_side(p) == ON_UNBOUNDED_SIDE ); }

template < class FT >
CGAL_KERNEL_INLINE
bool
Iso_cuboidS3<FT>::is_degenerate() const
{
  return ( (e0.x() == e1.x())||(e0.y() == e1.y())||(e0.z() == e1.z()) );
}

template < class FT >
inline
Bbox_3
Iso_cuboidS3<FT>::bbox() const
{ return  min().bbox() + max().bbox(); }

template < class FT >
CGAL_KERNEL_INLINE
Iso_cuboidS3<FT>
Iso_cuboidS3<FT>::transform(const Aff_transformationS3<FT>&t) const
{ return Iso_cuboidS3<FT>(t.transform(e0), t.transform(e1) ); }

#ifndef CGAL_NO_OSTREAM_INSERT_ISO_CUBOIDS3
template < class FT >
std::ostream& 
operator<<(std::ostream& os, const Iso_cuboidS3<FT>& r)
{
  switch(os.iword(IO::mode)) 
  {
    case IO::ASCII :
      return os << min() << ' ' << max();
    case IO::BINARY :
      return os << min() << max();
    default:
      return os << "Iso_cuboidS3(" << min() << ", " << max() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_ISO_CUBOIDS3

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOIDS3
template < class FT >
std::istream& 
operator>>(std::istream& is, Iso_cuboidS3<FT>& r)
{
  PointS3<FT> p, q;
  is >> p >> q;
  r = Iso_cuboidS3<FT>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOIDS3

CGAL_END_NAMESPACE

#endif // CGAL_ISO_CUBOIDS3_H
