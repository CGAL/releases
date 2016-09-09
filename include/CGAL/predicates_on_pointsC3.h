//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: predicates_on_pointsC3.h
// Author: Andreas.Fabri@sophia.inria.fr

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
bool CGAL_x_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.x() == q.x();
}

template < class FT >
bool CGAL_y_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.y() == q.y();
}

template < class FT >
bool CGAL_z_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.z() == q.z();
}


template < class FT >
CGAL_Orientation CGAL_orientation(const FT &px, const FT &py, const FT &pz,
                                  const FT &qx, const FT &qy, const FT &qz,
                                  const FT &rx, const FT &ry, const FT &rz,
                                  const FT &sx, const FT &sy, const FT &sz)
{
  /*
  FT t1 = px*ry;
  FT t2 = px*sy;
  FT t3 = qx*py;
  FT t4 = qx*ry;
  FT t5 = qx*sy;
  FT t6 = t0*rz-t0*sz-t1*qz+t1*sz+t2*qz-t2*rz-t3*rz+
          t3*sz+t4*pz-t4*sz-t5*pz+t5*rz;
  t0 = rx*py;
  t1 = rx*qy;
  t2 = rx*sy;
  t3 = sx*py;
  t4 = sx*qy;
  t6 = sx*ry;
  FT det = t6 + t0*qz-t0*sz-t1*pz+t1*sz+t2*pz-t2*qz-t3*qz+
           t3*rz+t4*pz-t4*rz-t6*pz+t6*qz;
           */
  FT t0 = ry*sz;
  FT t1 = rz*sy;
  FT t2 = qz*sy;
  FT t3 = qy*rz;
  FT t4 = qz*ry;
  FT t5 = py*sz - pz*sy;
  FT t6 = py*rz - pz*ry ;
  FT t7 = py*qz - pz*qy;

FT det =   (  qx*( ry*sz - rz*sy )
                    - rx*( qy*sz - qz*sy )
                    + sx*( qy*rz - qz*ry ) )
          - (  px*( ry*sz - rz*sy )
                    - rx*( py*sz - pz*sy )
                    + sx*( py*rz - pz*ry ) )
          + (  px*( qy*sz - qz*sy )
                    - qx*( py*sz - pz*sy )
                    + sx*( py*qz - pz*qy ) )
          - (  px*( qy*rz - qz*ry )
                    - qx*( py*rz - pz*ry )
                    + rx*( py*qz - pz*qy ) ) ;

FT det2 =   (  qx*( t0 - t1 )
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

assert(det == det2);

  return  (det == FT(0))? CGAL_COPLANAR : ((det > FT(0)) ? CGAL_POSITIVE
                                                         : CGAL_NEGATIVE);
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
inline bool CGAL_between(const CGAL_PointC3<FT> &p,
                         const CGAL_PointC3<FT> &q,
                         const CGAL_PointC3<FT> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }

  return CGAL_collinear_between(p, q, r);
}

template < class FT >
inline bool CGAL_collinear_between(const CGAL_PointC3<FT> &p,
                                   const CGAL_PointC3<FT> &q,
                                   const CGAL_PointC3<FT> &r)
{
  CGAL_exactness_precondition( CGAL_collinear(p, q, r) );
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


#endif // CGAL_PREDICATES_ON_POINTSC3_H
