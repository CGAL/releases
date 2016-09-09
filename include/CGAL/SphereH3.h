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
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : SphereH3.fw
// file          : include/CGAL/SphereH3.h
// package       : H3 (2.12)
// revision      : 2.12
// revision_date : 16 Aug 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_SPHEREH3_H
#define CGAL_SPHEREH3_H

#include <CGAL/basic.h>
#include <CGAL/PointH3.h>
#include <CGAL/predicates_on_pointsH3.h>
#include <CGAL/basic_constructionsH3.h>

CGAL_BEGIN_NAMESPACE

template <class FT, class RT>
class Sphere_repH3 : public Ref_counted
{
  public:
    friend class SphereH3<FT,RT>;

            Sphere_repH3()
            {}

            Sphere_repH3(const PointH3<FT,RT> p,
                         const FT sq_rad,
                         const Orientation& or)
             : center(p), squared_radius(sq_rad), orientation_(or)
            {}

  protected:
            PointH3<FT,RT>   center;
            FT               squared_radius;
            Orientation      orientation_;
};


template <class FT, class RT>
class SphereH3 : public Handle_for< Sphere_repH3<FT,RT> >
{
  public:
      SphereH3();

      SphereH3(const PointH3<FT,RT>& p, const FT& sq_rad,
               const Orientation& o = COUNTERCLOCKWISE);

      SphereH3(const PointH3<FT,RT>& p, const PointH3<FT,RT>& q,
               const PointH3<FT,RT>& r, const PointH3<FT,RT>& u);

      SphereH3(const PointH3<FT,RT>& p, const PointH3<FT,RT>& q,
               const PointH3<FT,RT>& r,
               const Orientation& o = COUNTERCLOCKWISE);

      SphereH3(const PointH3<FT,RT>&  p, const PointH3<FT,RT>&  q,
               const Orientation& o = COUNTERCLOCKWISE);

      SphereH3(const PointH3<FT,RT>&  p,
               const Orientation& o = COUNTERCLOCKWISE);

      bool
      operator==(const SphereH3<FT,RT>&) const;

      bool
      operator!=(const SphereH3<FT,RT>& s) const
      { return !(*this == s); }

      PointH3<FT,RT>
      center() const;

      FT
      squared_radius() const;

      Orientation
      orientation() const;

      SphereH3<FT,RT>
      orthogonal_transform(const Aff_transformationH3<FT,RT>& t) const;

      bool
      is_degenerate() const;

      SphereH3<FT,RT>
      opposite() const;

      Bbox_3
      bbox() const;

      Oriented_side
      oriented_side(const PointH3<FT,RT>& p) const;

      bool
      has_on_boundary(const PointH3<FT,RT>& p) const
      { return oriented_side(p)==ON_ORIENTED_BOUNDARY; }

      bool
      has_on_positive_side(const PointH3<FT,RT>& p) const
      { return oriented_side(p)==ON_POSITIVE_SIDE; }

      bool
      has_on_negative_side(const PointH3<FT,RT>& p) const
      { return oriented_side(p)==ON_NEGATIVE_SIDE; }

      Bounded_side
      bounded_side(const PointH3<FT,RT>& p) const;

      bool
      has_on_bounded_side(const PointH3<FT,RT>& p) const
      { return bounded_side(p)==ON_BOUNDED_SIDE; }

      bool
      has_on_unbounded_side(const PointH3<FT,RT>& p) const
      { return bounded_side(p)==ON_UNBOUNDED_SIDE; }

};


template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SphereH3<FT,RT>::SphereH3()
 : Handle_for< Sphere_repH3<FT,RT> >()
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SphereH3<FT,RT>::SphereH3(const PointH3<FT,RT>& center,
                          const FT& squared_radius,
                          const Orientation& o = COUNTERCLOCKWISE)
{
  CGAL_kernel_precondition( !( squared_radius < FT(0))
                          &&( o != COLLINEAR) );
  initialize_with( Sphere_repH3<FT,RT>(center, squared_radius, o));
}

template <class FT, class RT>
CGAL_KERNEL_CTOR_INLINE
SphereH3<FT,RT>::SphereH3(const PointH3<FT,RT>& center,
                          const Orientation& o = COUNTERCLOCKWISE)
{
  CGAL_kernel_precondition( ( o != COLLINEAR) );
  initialize_with( Sphere_repH3<FT,RT>(center, FT(0), o));
}

template <class FT, class RT>
CGAL_KERNEL_CTOR_MEDIUM_INLINE
SphereH3<FT,RT>::SphereH3(const PointH3<FT,RT>& p,
                          const PointH3<FT,RT>& q,
                          const Orientation& o = COUNTERCLOCKWISE)
{
  CGAL_kernel_precondition( o != COLLINEAR);
  PointH3<FT,RT> center = midpoint(p,q);
  FT     squared_radius = squared_distance(p,center);
  initialize_with(Sphere_repH3<FT,RT>(center, squared_radius, o));
}

template <class FT, class RT>
CGAL_KERNEL_CTOR_MEDIUM_INLINE
SphereH3<FT,RT>::SphereH3(const PointH3<FT,RT>& p,
                          const PointH3<FT,RT>& q,
                          const PointH3<FT,RT>& r,
                          const Orientation& o = COUNTERCLOCKWISE)
{
  CGAL_kernel_precondition( o != COLLINEAR);
  PointH3<FT,RT> center = circumcenter(p,q,r);
  FT     squared_radius = squared_distance(p,center);
  initialize_with(Sphere_repH3<FT,RT>(center, squared_radius, o));
}

template <class FT, class RT>
CGAL_KERNEL_CTOR_MEDIUM_INLINE
SphereH3<FT,RT>::SphereH3(const PointH3<FT,RT>& p,
                          const PointH3<FT,RT>& q,
                          const PointH3<FT,RT>& r,
                          const PointH3<FT,RT>& s)
{
  Orientation o = CGAL::orientation(p,q,r,s);
  CGAL_kernel_precondition( o != COLLINEAR);
  PointH3<FT,RT> center = circumcenter(p,q,r,s);
  FT     squared_radius = squared_distance(p,center);
  initialize_with(Sphere_repH3<FT,RT>(center, squared_radius, o));
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
bool
SphereH3<FT,RT>::operator==(const SphereH3<FT,RT>& s) const
{
   return    ( orientation() == s.orientation())
          && ( center() == s.center())
          && ( squared_radius() == s.squared_radius());
}

template <class FT, class RT>
inline
PointH3<FT,RT>
SphereH3<FT,RT>::center() const
{ return ptr->center; }

template <class FT, class RT>
inline
FT
SphereH3<FT,RT>::squared_radius() const
{ return ptr->squared_radius; }

template <class FT, class RT>
inline
Orientation
SphereH3<FT,RT>::orientation() const
{ return ptr->orientation_; }

template <class FT, class RT>
inline
bool
SphereH3<FT,RT>::is_degenerate() const
{ return ptr->squared_radius <= FT(0) ; }

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Oriented_side
SphereH3<FT,RT>::oriented_side(const PointH3<FT,RT>& p) const
{ return Oriented_side(bounded_side(p) * orientation()); }

template <class FT, class RT>
CGAL_KERNEL_INLINE
Bounded_side
SphereH3<FT,RT>::bounded_side(const PointH3<FT,RT>& p) const
{
  return Bounded_side(CGAL::compare(squared_radius(),
                                    squared_distance(center(),p)));
}
template <class FT, class RT>
inline
SphereH3<FT,RT>
SphereH3<FT,RT>::opposite() const
{
  return SphereH3<FT,RT>(center(), squared_radius(),
                         CGAL::opposite(orientation()) );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
Bbox_3
SphereH3<FT,RT>::bbox() const
{
  double eps  = double(1.0) /(double(1<<26) * double(1<<26));
  double hxd  = CGAL::to_double( center().hx() );
  double hyd  = CGAL::to_double( center().hy() );
  double hzd  = CGAL::to_double( center().hz() );
  double hwd  = CGAL::to_double( center().hw() );
  double xmin = ( hxd - eps*hxd ) / ( hwd + eps*hwd );
  double xmax = ( hxd + eps*hxd ) / ( hwd - eps*hwd );
  double ymin = ( hyd - eps*hyd ) / ( hwd + eps*hwd );
  double ymax = ( hyd + eps*hyd ) / ( hwd - eps*hwd );
  double zmin = ( hzd - eps*hyd ) / ( hwd + eps*hwd );
  double zmax = ( hzd + eps*hyd ) / ( hwd - eps*hwd );
  if ( center().hx() < RT(0)   )
  { std::swap(xmin, xmax); }
  if ( center().hy() < RT(0)   )
  { std::swap(ymin, ymax); }
  if ( center().hz() < RT(0)   )
  { std::swap(zmin, zmax); }
  double sqradd = CGAL::to_double( squared_radius() );
  sqradd += sqradd*eps;
  sqradd = sqrt(sqradd);
  sqradd += sqradd*eps;
  xmin -= sqradd;
  xmax += sqradd;
  xmin -= xmin*eps;
  xmax += xmax*eps;
  ymin -= sqradd;
  ymax += sqradd;
  ymin -= ymin*eps;
  ymax += ymax*eps;
  zmin -= sqradd;
  zmax += sqradd;
  zmin -= ymin*eps;
  zmax += ymax*eps;
  return Bbox_3(xmin, ymin, zmin, xmax, ymax, zmax);
}


CGAL_END_NAMESPACE

#endif // CGAL_SPHEREH3_H
