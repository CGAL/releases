 
// Source: predicates_on_pointsC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#define CGAL_PREDICATES_ON_POINTSC2_H
#include <CGAL/cartesian_classes.h>
#include <CGAL/PointC2.h>

 
template < class FT >
bool CGAL_x_equal(const CGAL_PointC2<FT> &p,
                  const CGAL_PointC2<FT> &q)
{
  return p.x() == q.x();
}

template < class FT >
bool CGAL_y_equal(const CGAL_PointC2<FT> &p,
                  const CGAL_PointC2<FT> &q)
{
  return p.y() == q.y();
}
 


 
template < class FT >
CGAL_Comparison_result CGAL_compare_lexicographically_xy(
                                                    const CGAL_PointC2<FT> &p,
                                                    const CGAL_PointC2<FT> &q)
{
  CGAL_kernel_precondition( p.is_defined() && q.is_defined() );

  if (p.x() < q.x()){
    return CGAL_SMALLER;
  }

 if (p.x() == q.x()){
   if (p.y() < q.y()){
     return CGAL_SMALLER;
   }
   if (p.y() == q.y()){
     return CGAL_EQUAL;
   }
 }
 return CGAL_LARGER;
}


template < class FT >
bool CGAL_lexicographically_xy_smaller_or_equal(const CGAL_PointC2<FT> &p,
                                                const CGAL_PointC2<FT> &q)
{
  CGAL_kernel_precondition( p.is_defined() && q.is_defined() );
  return ( !( CGAL_compare_lexicographically_xy(p,q) == CGAL_LARGER ) );
}

template < class FT >
bool CGAL_lexicographically_xy_smaller(const CGAL_PointC2<FT> &p,
                                       const CGAL_PointC2<FT> &q)
{
  CGAL_kernel_precondition( p.is_defined() && q.is_defined() );
  return CGAL_compare_lexicographically_xy(p,q) == CGAL_SMALLER ;
}
 


 
template < class FT >
CGAL_Ordertype CGAL_ordertype(const FT &px, const FT &py,
                              const FT &qx, const FT &qy,
                              const FT &rx, const FT &ry)
{
  FT det = px * qy - py * qx +
           py * rx - px * ry +
           qx * ry - rx * qy ;
  return  (det == FT(0)) ? CGAL_COLLINEAR
                           : ((det > FT(0))? CGAL_LEFTTURN : CGAL_RIGHTTURN);
}

template < class FT >
FT CGAL_area2(const FT &px, const FT &py,
              const FT &qx, const FT &qy,
              const FT &rx, const FT &ry)
{
  return  px * qy - py * qx +
          py * rx - px * ry +
          qx * ry - rx * qy ;
}
 


 
template < class FT >
bool CGAL_collinear(const CGAL_PointC2<FT> &p,
                    const CGAL_PointC2<FT> &q,
                    const CGAL_PointC2<FT> &r)
{
  return (CGAL_ordertype(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
          == CGAL_COLLINEAR);
}

template < class FT >
bool CGAL_between(const CGAL_PointC2<FT> &p,
                  const CGAL_PointC2<FT> &q,
                  const CGAL_PointC2<FT> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }
  return CGAL_collinear_between(p, q, r);

}

template < class FT >
inline bool CGAL_collinear_between(const CGAL_PointC2<FT> &p,
                                   const CGAL_PointC2<FT> &q,
                                   const CGAL_PointC2<FT> &r)
{
  CGAL_exactness_precondition( CGAL_collinear(p, q, r) );

  if (p.x() != r.x())
    {
      return ((p.x() <= q.x()) && q.x() <= r.x()) ||
             ((r.x() <= q.x()) && q.x() <= p.x());
    }
  return ((p.y() <= q.y()) && q.y() <= r.y()) ||
         ((r.y() <= q.y()) && q.y() <= p.y());

}

template < class FT >
inline bool CGAL_leftturn(const CGAL_PointC2<FT> &p,
                          const CGAL_PointC2<FT> &q,
                          const CGAL_PointC2<FT> &r)
{
  return (CGAL_ordertype(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
          == CGAL_LEFTTURN );
}

template < class FT >
inline bool CGAL_rightturn(const CGAL_PointC2<FT> &p,
                           const CGAL_PointC2<FT> &q,
                           const CGAL_PointC2<FT> &r)
{
   return (CGAL_ordertype(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
           == CGAL_RIGHTTURN);
}

template < class FT >
inline CGAL_Ordertype CGAL_ordertype(const CGAL_PointC2<FT> &p,
                                     const CGAL_PointC2<FT>&q,
                                     const CGAL_PointC2<FT> &r)
{
  return CGAL_ordertype(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template < class FT >
inline FT CGAL_area2(const CGAL_PointC2<FT> &p,
                     const CGAL_PointC2<FT> &q,
                     const CGAL_PointC2<FT> &r)
{
  return CGAL_area2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}
template <class FT >
CGAL_Side CGAL_in_circle(const CGAL_PointC2<FT> &p,
                         const CGAL_PointC2<FT> &q,
                         const CGAL_PointC2<FT> &r,
                         const CGAL_PointC2<FT> &test)
{
  const FT &px = p.x();
  const FT &py = p.y();
  const FT &qx = q.x();
  const FT &qy = q.y();
  const FT &rx = r.x();
  const FT &ry = r.y();
  const FT &tx = test.x();
  const FT &ty = test.y();
     
  FT det = CGAL_det4x4_by_formula(px, py, px*px + py*py, FT(1),
                                  qx, qy, qx*qx + qy*qy, FT(1),
                                  rx, ry, rx*rx + ry*ry, FT(1),
                                  tx, ty, tx*tx + ty*ty, FT(1));

  if (CGAL_ordertype(px, py, qx, qy, rx, ry) == CGAL_LEFTTURN )
    {
      det = -det;
    }
  
  return (det==0) ? CGAL_ON : ((det<0) ? CGAL_INSIDE : CGAL_OUTSIDE);
}
 


#endif  // CGAL_PREDICATES_ON_POINTSC2_H
