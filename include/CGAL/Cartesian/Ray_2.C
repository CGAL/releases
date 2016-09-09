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
// file          : include/CGAL/Cartesian/Ray_2.C
// package       : C2 (4.4)
// revision      : $Revision: 1.20 $
// revision_date : $Date: 2000/08/23 13:45:36 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_RAY_2_C
#define CGAL_CARTESIAN_RAY_2_C

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_2_H
#define CGAL_CTAG
#endif

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
CGAL_KERNEL_CTOR_INLINE
RayC2<R CGAL_CTAG>::RayC2()
{
  new ( static_cast< void*>(ptr)) Twotuple<Point_2>();
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
RayC2<R CGAL_CTAG>::RayC2(const RayC2<R CGAL_CTAG>  &r)
  : Handle_for<Twotuple<typename R::Point_2> >(r)
{}

template < class R >
CGAL_KERNEL_CTOR_INLINE
RayC2<R CGAL_CTAG>::RayC2(const typename RayC2<R CGAL_CTAG>::Point_2 &sp,
                          const typename RayC2<R CGAL_CTAG>::Point_2 &secondp)
{
  new ( static_cast< void*>(ptr)) Twotuple<Point_2>(sp, secondp);
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
RayC2<R CGAL_CTAG>::RayC2(const typename RayC2<R CGAL_CTAG>::Point_2 &sp,
                          const typename RayC2<R CGAL_CTAG>::Direction_2 &d)
{
  new ( static_cast< void*>(ptr)) Twotuple<Point_2>(sp, sp + d.to_vector());
}

template < class R >
inline
RayC2<R CGAL_CTAG>::~RayC2()
{}

template < class R >
CGAL_KERNEL_INLINE
bool
RayC2<R CGAL_CTAG>::operator==(const RayC2<R CGAL_CTAG> &r) const
{
  return source() == r.source() && direction() == r.direction();
}

template < class R >
inline
bool
RayC2<R CGAL_CTAG>::operator!=(const RayC2<R CGAL_CTAG> &r) const
{
  return !(*this == r);
}

template < class R >
inline
typename RayC2<R CGAL_CTAG>::Point_2
RayC2<R CGAL_CTAG>::source() const
{
  return ptr->e0;
}

template < class R >
inline
typename RayC2<R CGAL_CTAG>::Point_2
RayC2<R CGAL_CTAG>::start() const
{
  return source();
}

template < class R >
inline
typename RayC2<R CGAL_CTAG>::Point_2
RayC2<R CGAL_CTAG>::second_point() const
{
  return ptr->e1;
}

template < class R >
CGAL_KERNEL_INLINE
typename RayC2<R CGAL_CTAG>::Point_2
RayC2<R CGAL_CTAG>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  if (i == 0) return source();
  if (i == 1) return second_point();
  return source() + (second_point() - source()) * FT(i);
}

template < class R >
inline
typename RayC2<R CGAL_CTAG>::Direction_2
RayC2<R CGAL_CTAG>::direction() const
{
  return Direction_2( second_point() - source() );
}

template < class R >
inline
typename RayC2<R CGAL_CTAG>::Line_2
RayC2<R CGAL_CTAG>::supporting_line() const
{
  return Line_2(*this);
}

template < class R >
inline
RayC2<R CGAL_CTAG>
RayC2<R CGAL_CTAG>::opposite() const
{
  return RayC2<R CGAL_CTAG>( source(), - direction() );
}

template < class R >
CGAL_KERNEL_INLINE
RayC2<R CGAL_CTAG>
RayC2<R CGAL_CTAG>::
transform(const typename RayC2<R CGAL_CTAG>::Aff_transformation_2 &t) const
{
  return RayC2<R CGAL_CTAG>(t.transform(source()), 
			    t.transform(second_point()));
}

template < class R >
CGAL_KERNEL_INLINE
bool RayC2<R CGAL_CTAG>::is_horizontal() const
{
  return y_equal(source(), second_point());
}

template < class R >
CGAL_KERNEL_INLINE
bool RayC2<R CGAL_CTAG>::is_vertical() const
{
  return x_equal(source(), second_point());
}

template < class R >
CGAL_KERNEL_INLINE
bool RayC2<R CGAL_CTAG>::is_degenerate() const
{
  return source() == second_point();
}

template < class R >
CGAL_KERNEL_INLINE
bool
RayC2<R CGAL_CTAG>::has_on(const typename RayC2<R CGAL_CTAG>::Point_2 &p) const
{
  return p == source()
      || collinear(source(), p, second_point())
      && Direction_2(p - source()) == direction();
}

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
bool
RayC2<R CGAL_CTAG>::
collinear_has_on(const typename RayC2<R CGAL_CTAG>::Point_2 &p) const
{
    switch(compare_x(source(), second_point())){
    case SMALLER:
        return compare_x(source(), p) != LARGER;
    case LARGER:
        return compare_x(p, source()) != LARGER;
    default:
        switch(compare_y(source(), second_point())){
        case SMALLER:
            return compare_y(source(), p) != LARGER;
        case LARGER:
            return compare_y(p, source()) != LARGER;
        default:
            return true; // p == source()
        }
    }
}

#ifndef CGAL_NO_OSTREAM_INSERTR_AYC2
template < class R >
std::ostream &
operator<<(std::ostream &os, const RayC2<R CGAL_CTAG> &r)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << r.source() << ' ' << r.direction();
    case IO::BINARY :
        return os << r.source() << r.direction();
    default:
        return os << "RayC2(" << r.source() <<  ", " << r.direction() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERTR_AYC2

#ifndef CGAL_NO_ISTREAM_EXTRACTR_AYC2
template < class R >
std::istream &
operator>>(std::istream &is, RayC2<R CGAL_CTAG> &r)
{
    typename RayC2<R CGAL_CTAG>::Point_2 p;
    typename RayC2<R CGAL_CTAG>::Direction_2 d;

    is >> p >> d;

    r = RayC2<R CGAL_CTAG>(p, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACTR_AYC2

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

#endif // CGAL_CARTESIAN_RAY_2_C
