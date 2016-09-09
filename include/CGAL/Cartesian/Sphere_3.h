// ======================================================================
//
// Copyright (c) 1997  The CGAL Consortium

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
// patch         : 1
// patch_date    : 2000, December 11
//
// file          : include/CGAL/Cartesian/Sphere_3.h
// package       : C3 (5.6)
// revision      : $Revision: 1.18 $
// revision_date : $Date: 2000/11/02 15:18:13 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis 
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_SPHERE_3_H
#define CGAL_CARTESIAN_SPHERE_3_H

#include <CGAL/Cartesian/redefine_names_3.h>
#include <CGAL/Cartesian/Sphere_rep_3.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class SphereC3 CGAL_ADVANCED_KERNEL_PARTIAL_SPEC
  : public Handle_for< Sphere_repC3<R_> >
{
public:
  typedef R_                                    R;
  typedef typename R::FT                        FT;
  typedef typename R::RT                        RT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef SphereC3<R CGAL_CTAG>                 Self;
  typedef typename R::Point_3                   Point_3;
  typedef typename R::Aff_transformation_3      Aff_transformation_3;
#else
  typedef SphereC3<R>                           Self;
  typedef typename R::Point_3_base              Point_3;
  typedef typename R::Aff_transformation_3_base Aff_transformation_3;
#endif

  SphereC3();
  SphereC3(const Self &s);

  // Sphere with center p, squared radius s, orientation o
  SphereC3(const Point_3 &p, const FT &s,
           const Orientation &o = COUNTERCLOCKWISE)
  {
    CGAL_kernel_precondition( ( s >= FT(0) ) && ( o != COLLINEAR) );

    new ( static_cast< void*>(ptr)) Sphere_repC3<R>(p, s, o);
  }

  // Sphere passing through p,q,r,s, oriented by p, q, r, s
  SphereC3(const Point_3 &p, const Point_3 &q,
           const Point_3 &r, const Point_3 &s);

  // Sphere with great circle passing through p,q,r, oriented by o
  SphereC3(const Point_3 &p, const Point_3 &q, const Point_3 &r,
	   const Orientation &o = COUNTERCLOCKWISE);

  // Sphere with diameter pq and orientation o
  SphereC3(const Point_3 & p, const Point_3 & q,
           const Orientation &o = COUNTERCLOCKWISE);

  // Sphere centered at p, radius 0, orientation o
  SphereC3(const Point_3 & p,
           const Orientation& o = COUNTERCLOCKWISE);

  ~SphereC3() {}

  bool operator==(const Self &) const;
  bool operator!=(const Self &) const;

  Point_3 center() const
  {
      return ptr->center;
  }
  FT squared_radius() const
  {
      // Returns the square of the radius (instead of the radius itself,
      // which would require square roots)
      return ptr->squared_radius;
  }
  Orientation orientation() const
  {
      return ptr->orient;
  }

  Self   orthogonal_transform(const Aff_transformation_3 &t) const;
  //! precond: t.is_orthogonal() (*UNDEFINED*)
  // Returns the image of c by t. Since t is orthogonal, the image is
  // always a circle

  bool   is_degenerate() const;
  // A circle is degenerate if its (squared) radius is null or negative
  Self   opposite() const;
  // Returns a circle with opposite orientation

  Oriented_side  oriented_side(const Point_3 &p) const;
  //! precond: ! x.is_degenerate() (when available)
  // Returns R::ON_POSITIVE_SIDE, R::ON_ORIENTED_BOUNDARY or
  // R::ON_NEGATIVE_SIDE
  bool has_on_boundary(const Point_3 &p) const;
  bool has_on_positive_side(const Point_3 &p) const;
  bool has_on_negative_side(const Point_3 &p) const;

  Bounded_side   bounded_side(const Point_3 &p) const;
  //! precond: ! x.is_degenerate() (when available)
  // Returns R::ON_BOUNDED_SIDE, R::ON_BOUNDARY or R::ON_UNBOUNDED_SIDE
  bool has_on_bounded_side(const Point_3 &p) const;
  bool has_on_unbounded_side(const Point_3 &p) const;

  Bbox_3 bbox() const;
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template < class R >
CGAL_KERNEL_CTOR_INLINE
SphereC3<R CGAL_CTAG>::SphereC3()
{
  new ( static_cast< void*>(ptr)) Sphere_repC3<R>;
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
SphereC3<R CGAL_CTAG>::SphereC3(const SphereC3<R CGAL_CTAG> &s)
  : Handle_for< Sphere_repC3<R> > (s)
{}

template < class R >
CGAL_KERNEL_CTOR_INLINE
SphereC3<R CGAL_CTAG>::
SphereC3(const typename SphereC3<R CGAL_CTAG>::Point_3 &p,
         const Orientation &o)
{
  CGAL_kernel_precondition( o != COLLINEAR );

  new ( static_cast< void*>(ptr)) Sphere_repC3<R>(p, FT(0), o);
}

template < class R >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
SphereC3<R CGAL_CTAG>::
SphereC3(const typename SphereC3<R CGAL_CTAG>::Point_3 &p,
         const typename SphereC3<R CGAL_CTAG>::Point_3 &q,
         const Orientation &o)
{
  CGAL_kernel_precondition( o != COLLINEAR);

  SphereC3<R CGAL_CTAG>::Point_3 center = midpoint(p,q);
  SphereC3<R CGAL_CTAG>::FT      squared_radius = squared_distance(p,center);

  new ( static_cast< void*>(ptr))
      Sphere_repC3<R>( center, squared_radius, o);
}

template < class R >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
SphereC3<R CGAL_CTAG>::
SphereC3(const typename SphereC3<R CGAL_CTAG>::Point_3 &p,
         const typename SphereC3<R CGAL_CTAG>::Point_3 &q,
         const typename SphereC3<R CGAL_CTAG>::Point_3 &r,
         const Orientation &o)
{
  CGAL_kernel_precondition( o != COLLINEAR);

  Point_3 center = circumcenter(p,q,r);
  FT      squared_radius = squared_distance(p,center);

  new ( static_cast< void*>(ptr))
      Sphere_repC3<R>(center, squared_radius, o);
}

template < class R >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
SphereC3<R CGAL_CTAG>::
SphereC3(const typename SphereC3<R CGAL_CTAG>::Point_3 &p,
         const typename SphereC3<R CGAL_CTAG>::Point_3 &q,
         const typename SphereC3<R CGAL_CTAG>::Point_3 &r,
         const typename SphereC3<R CGAL_CTAG>::Point_3 &s)
{
  Orientation o = CGAL::orientation(p,q,r,s);
  Point_3 center = circumcenter(p,q,r,s);
  FT      squared_radius = squared_distance(p,center);

  new ( static_cast< void*>(ptr))
      Sphere_repC3<R>(center, squared_radius, o);
}

template < class R >
CGAL_KERNEL_INLINE
bool
SphereC3<R CGAL_CTAG>::
operator==(const SphereC3<R CGAL_CTAG> &t) const
{
  if ( identical(t) ) return true;
  return center() == t.center() &&
         squared_radius() == t.squared_radius() &&
         orientation() == t.orientation();
}

template < class R >
inline
bool
SphereC3<R CGAL_CTAG>::
operator!=(const SphereC3<R CGAL_CTAG> &t) const
{
  return !(*this == t);
}

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
Oriented_side
SphereC3<R CGAL_CTAG>::
oriented_side(const typename SphereC3<R CGAL_CTAG>::Point_3 &p) const
{
  return Oriented_side(bounded_side(p) * orientation());
}

template < class R >
CGAL_KERNEL_INLINE
Bounded_side
SphereC3<R CGAL_CTAG>::
bounded_side(const typename SphereC3<R CGAL_CTAG>::Point_3 &p) const
{
  return Bounded_side(CGAL_NTS compare(squared_radius(),
                                       squared_distance(center(),p)));
}

template < class R >
inline
bool
SphereC3<R CGAL_CTAG>::
has_on_boundary(const typename SphereC3<R CGAL_CTAG>::Point_3 &p) const
{
  return squared_distance(center(),p) == squared_radius();
  // NB: J'ai aussi trouve ailleurs :
  // return oriented_side(p)==ON_ORIENTED_BOUNDARY;
  // a voir...
}

template < class R >
CGAL_KERNEL_INLINE
bool
SphereC3<R CGAL_CTAG>::
has_on_negative_side(const typename SphereC3<R CGAL_CTAG>::Point_3 &p) const
{
  if (orientation() == COUNTERCLOCKWISE)
    return has_on_unbounded_side(p);
  return has_on_bounded_side(p);
  // NB: J'ai aussi trouve ailleurs :
  // return oriented_side(p)==ON_NEGATIVE_SIDE;
}

template < class R >
CGAL_KERNEL_INLINE
bool
SphereC3<R CGAL_CTAG>::
has_on_positive_side(const typename SphereC3<R CGAL_CTAG>::Point_3 &p) const
{
  if (orientation() == COUNTERCLOCKWISE)
    return has_on_bounded_side(p);
  return has_on_unbounded_side(p);
  // NB: J'ai aussi trouve ailleurs :
  // return oriented_side(p)==ON_POSITIVE_SIDE;
}

template < class R >
inline
bool
SphereC3<R CGAL_CTAG>::
has_on_bounded_side(const typename SphereC3<R CGAL_CTAG>::Point_3 &p) const
{
  return squared_distance(center(),p) < squared_radius();
  // NB: J'ai aussi trouve ailleurs :
  // return bounded_side(p)==ON_BOUNDED_SIDE;
}

template < class R >
inline
bool
SphereC3<R CGAL_CTAG>::
has_on_unbounded_side(const typename SphereC3<R CGAL_CTAG>::Point_3 &p) const
{
  return squared_distance(center(),p) > squared_radius();
  // NB: J'ai aussi trouve ailleurs :
  // return bounded_side(p)==ON_UNBOUNDED_SIDE;
}

template < class R >
inline
bool
SphereC3<R CGAL_CTAG>::
is_degenerate() const
{
  return CGAL_NTS is_zero(squared_radius());
}

template < class R >
inline
SphereC3<R CGAL_CTAG> SphereC3<R CGAL_CTAG>::
opposite() const
{
  return SphereC3<R CGAL_CTAG>(center(), squared_radius(),
                               CGAL::opposite(orientation()) );
}

template < class R >
CGAL_KERNEL_INLINE
Bbox_3
SphereC3<R CGAL_CTAG>::bbox() const
{
  double cx = CGAL::to_double(center().x());
  double cy = CGAL::to_double(center().y());
  double cz = CGAL::to_double(center().z());
  double radius = CGAL::sqrt(CGAL::to_double(squared_radius()));

  return Bbox_3(cx - radius, cy - radius, cz - radius,
                cx + radius, cy + radius, cz + radius);
}

template < class R >
CGAL_KERNEL_INLINE
SphereC3<R CGAL_CTAG>
SphereC3<R CGAL_CTAG>::orthogonal_transform
  (const typename SphereC3<R CGAL_CTAG>::Aff_transformation_3 &t) const
{
  typename SphereC3<R CGAL_CTAG>::Vector_3 vec(FT(1), FT(0) );   // unit vector
  vec = vec.transform(t);             // transformed
  FT sq_scale = vec.squared_length();       // squared scaling factor

  return SphereC3<R CGAL_CTAG>(t.transform(center()),
                      sq_scale * squared_radius(),
                      t.is_even() ? orientation()
                                  : CGAL::opposite(orientation()));
}

/*
template < class R >
inline
EllipseC3<SphereC3<R CGAL_CTAG>::FT> SphereC3<R CGAL_CTAG>::i
transform(const Aff_transformationC3<SphereC3<R CGAL_CTAG>::FT> &t) const
{
  return SphereC3<R CGAL_CTAG>(t.transform(center()),
                      squared_radius(),
                      orientation());
}
*/

#ifndef CGAL_NO_OSTREAM_INSERT_SPHEREC3
template < class R >
CGAL_KERNEL_INLINE
std::ostream &
operator<<(std::ostream &os, const SphereC3<R CGAL_CTAG> &c)
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
        os << "SphereC3(" << c.center() <<  ", " << c.squared_radius();
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
#endif // CGAL_NO_OSTREAM_INSERT_SPHEREC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_SPHEREC3
template < class R >
CGAL_KERNEL_INLINE
std::istream &
operator>>(std::istream &is, SphereC3<R CGAL_CTAG> &c)
{
    typename SphereC3<R CGAL_CTAG>::Point_3 center;
    typename R::FT squared_radius;
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
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;
    }
    c = SphereC3<R CGAL_CTAG>(center, squared_radius, (Orientation)o);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SPHEREC3

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_SPHERE_3_H
