// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/predicates_on_pointsC3.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_PREDICATES_ON_POINTSC3_H
#define CGAL_PREDICATES_ON_POINTSC3_H

#include <CGAL/PointC3.h>

template < class FT >
CGAL_Comparison_result CGAL_compare_lexicographically_xyz(
                                                     const CGAL_PointC3<FT> &p,
                                                     const CGAL_PointC3<FT> &q)
{
  if (p.x() < q.x()){
    return CGAL_SMALLER;
  }

  if (p.x() == q.x()){
    if (p.y() < q.y()){
      return CGAL_SMALLER;
    }
    //-----
    if (p.y() == q.y()){
      if (p.z() < q.z()){
        return CGAL_SMALLER;
      }

      if (p.z() == q.z()){
        return CGAL_EQUAL;
      }
    }
  }
  return CGAL_LARGER;
}


template < class FT >
bool CGAL_lexicographically_xyz_smaller_or_equal(const CGAL_PointC3<FT> &p,
                                                 const CGAL_PointC3<FT> &q)
{
  return ( !( CGAL_compare_lexicographically_xyz(p,q) == CGAL_LARGER ) );
}

template < class FT >
bool CGAL_lexicographically_xyz_smaller(const CGAL_PointC3<FT> &p,
                                        const CGAL_PointC3<FT> &q)
{
  return CGAL_compare_lexicographically_xyz(p,q) == CGAL_SMALLER ;
}


template < class FT >
inline
bool CGAL_x_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.x() == q.x();
}


template < class FT >
inline
bool CGAL_y_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.y() == q.y();
}

template < class FT >
inline
bool CGAL_z_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.z() == q.z();
}


template < class FT >
inline
CGAL_Comparison_result CGAL_compare_x(const CGAL_PointC3<FT> &p,
                                      const CGAL_PointC3<FT> &q)
{
  return CGAL_compare(p.x(), q.x());
}


template < class FT >
inline
CGAL_Comparison_result CGAL_compare_y(const CGAL_PointC3<FT> &p,
                                      const CGAL_PointC3<FT> &q)
{
 return CGAL_compare(p.y(), q.y());
}


template < class FT >
inline
CGAL_Comparison_result CGAL_compare_z(const CGAL_PointC3<FT> &p,
                                      const CGAL_PointC3<FT> &q)
{
 return CGAL_compare(p.z(), q.z());
}


template < class FT >
CGAL_Orientation CGAL_orientation(const FT &px, const FT &py, const FT &pz,
                                  const FT &qx, const FT &qy, const FT &qz,
                                  const FT &rx, const FT &ry, const FT &rz,
                                  const FT &sx, const FT &sy, const FT &sz)
{
  FT FT0(0);
  FT t0 = ry*sz;
  FT t1 = rz*sy;
  FT t2 = qz*sy;
  FT t3 = qy*rz;
  FT t4 = qz*ry;
  FT t5 = py*sz - pz*sy;
  FT t6 = py*rz - pz*ry ;
  FT t7 = py*qz - pz*qy;


FT det =   (  qx*( t0 - t1 )
                    - rx*( qy*sz - t2 )
                    + sx*( t3 - t4 ) )
          - (  px*( t0 - t1 )
                    - rx* t5
                    + sx* t6  )
          + (  px*( qy*sz - t2 )
                    - qx* t5
                    + sx* t7  )
          - (  px*( t3 - t4 )
                    - qx* t6
                    + rx* t7  ) ;


  // these intermediary steps are necessary for SGI C++ 4.0
  CGAL_Orientation orientation = (det == FT0) ? CGAL_COPLANAR : CGAL_NEGATIVE;
  CGAL_Orientation result = (det > FT0) ? CGAL_POSITIVE : orientation;

  return result;
}


template < class FT >
inline bool CGAL_coplanar(const CGAL_PointC3<FT> &p,
                          const CGAL_PointC3<FT> &q,
                          const CGAL_PointC3<FT> &r,
                          const CGAL_PointC3<FT> &s)
{
  return (CGAL_orientation(p, q, r, s) == CGAL_COLLINEAR);
}

template < class FT >
bool CGAL_collinear(const CGAL_PointC3<FT> &p,
                    const CGAL_PointC3<FT> &q,
                    const CGAL_PointC3<FT> &r)
{
  if ( (p == q) || (r == q) ){
    return true;
  } else {
    CGAL_DirectionC3<FT> dir_pq = (p - q).direction();
    CGAL_DirectionC3<FT> dir_rq = (r - q).direction();


    return ( dir_pq == dir_rq ) || (dir_pq == -dir_rq);
  }
}

template < class FT >
inline bool CGAL_are_ordered_along_line(const CGAL_PointC3<FT> &p,
                         const CGAL_PointC3<FT> &q,
                         const CGAL_PointC3<FT> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }

  return CGAL_collinear_are_ordered_along_line(p, q, r);
}

template < class FT >
inline bool CGAL_collinear_are_ordered_along_line(const CGAL_PointC3<FT> &p,
                                   const CGAL_PointC3<FT> &q,
                                   const CGAL_PointC3<FT> &r)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  if (p.x() != q.x())
    {
      return ((p.x() <= r.x()) && r.x() <= q.x()) ||
             ((q.x() <= r.x()) && r.x() <= p.x());
    }
  if (p.y() != q.y())
    {
      return ((p.y() <= r.y()) && r.y() <= q.y()) ||
             ((q.y() <= r.y()) && r.y() <= p.y());
    }
  return ((p.z() <= r.z()) && r.z() <= q.z()) ||
         ((q.z() <= r.z()) && r.z() <= p.z());

}


template < class FT >
inline CGAL_Orientation CGAL_orientation(const CGAL_PointC3<FT> &p,
                                         const CGAL_PointC3<FT>&q,
                                         const CGAL_PointC3<FT> &r,
                                         const CGAL_PointC3<FT> &s)
{
  return CGAL_orientation(p.x(), p.y(), p.z(), q.x(), q.y(), q.z(),
                        r.x(), r.y(), r.z(), s.x(), s.y(), s.z());
}

template <class FT >
CGAL_Bounded_side CGAL_side_of_bounded_sphere(
                         const CGAL_PointC3<FT> &p, const CGAL_PointC3<FT> &q,
                         const CGAL_PointC3<FT> &r, const CGAL_PointC3<FT> &s,
                         const CGAL_PointC3<FT> &test)
{
  assert(0); // not implemented
  return CGAL_ON_BOUNDED_SIDE;
}

template <class FT >
CGAL_Oriented_side CGAL_side_of_oriented_sphere(
                         const CGAL_PointC3<FT> &p0,
                         const CGAL_PointC3<FT> &p1,
                         const CGAL_PointC3<FT> &p2,
                         const CGAL_PointC3<FT> &p3,
                         const CGAL_PointC3<FT> &test)
{
  CGAL_VectorC3<FT> v0 = p0-test;
  CGAL_VectorC3<FT> v1 = p1-test;
  CGAL_VectorC3<FT> v2 = p2-test;
  CGAL_VectorC3<FT> v3 = p3-test;
  CGAL_VectorC3<FT> v01 = CGAL_cross_product(v0, v1);
  CGAL_VectorC3<FT> v23 = CGAL_cross_product(v2, v3);

  FT det = - (v0 * v0) * ( v1 * v23)
           + (v1 * v1) * ( v0 * v23)
           - (v2 * v2) * ( v01 * v3)
           + (v3 * v3) * ( v01 * v2);

  // these intermediary steps are necessary for SGI C++ 4.0
  CGAL_Oriented_side orientation = (det == FT0) ? CGAL_ON_ORIENTED_BOUNDARY
                                                : CGAL_ON_NEGATIVE_SIDE;
  CGAL_Oriented_side result = (det > FT0) ? CGAL_ON_POSITIVE_SIDE
                                          : orientation;

  return result;
}


#endif // CGAL_PREDICATES_ON_POINTSC3_H
