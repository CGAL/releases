 
// Source: predicates_on_points_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#define CGAL_PREDICATES_ON_POINTS_2_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/predicates_on_pointsC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>
 
template < class R >
bool CGAL_x_equal(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q)
{
  return CGAL_x_equal(R::Point_2(p), R::Point_2(q));
}

template < class R >
bool CGAL_y_equal(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q)
{
  return CGAL_y_equal(R::Point_2(p), R::Point_2(q));
}
 


 
template < class R >
bool CGAL_lexicographically_xy_smaller_or_equal(const CGAL_Point_2<R>& p,
                                           const CGAL_Point_2<R>& q)
{
  CGAL_kernel_precondition(p.is_defined() && q.is_defined() );
  return ( !( CGAL_compare_lexicographically_xy(R::Point_2(p),R::Point_2(q))
              == CGAL_LARGER ) );
}

template < class R >
bool CGAL_lexicographically_xy_smaller(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
 CGAL_kernel_precondition(p.is_defined() && q.is_defined() );
 return ( CGAL_compare_lexicographically_xy(R::Point_2(p),R::Point_2(q))
             == CGAL_SMALLER );
}
 


 
template < class R >
bool CGAL_collinear(const CGAL_Point_2<R> &p,
                    const CGAL_Point_2<R> &q,
                    const CGAL_Point_2<R> &r)
{
  return (CGAL_collinear(R::Point_2(p), R::Point_2(q), R::Point_2(r)));
}

template < class R >
bool CGAL_between(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q,
                  const CGAL_Point_2<R> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }
  return CGAL_collinear_between(p, q, r);

}

template < class R >
inline bool CGAL_collinear_between(const CGAL_Point_2<R> &p,
                                   const CGAL_Point_2<R> &q,
                                   const CGAL_Point_2<R> &r)
{
  return (CGAL_collinear_between(R::Point_2(p), R::Point_2(q), R::Point_2(r)));
}

template < class R >
inline bool CGAL_leftturn(const CGAL_Point_2<R> &p,
                          const CGAL_Point_2<R> &q,
                          const CGAL_Point_2<R> &r)
{
  return CGAL_leftturn(R::Point_2(p), R::Point_2(q), R::Point_2(r));
}

template < class R >
inline bool CGAL_rightturn(const CGAL_Point_2<R> &p,
                           const CGAL_Point_2<R> &q,
                           const CGAL_Point_2<R> &r)
{
   return CGAL_rightturn(R::Point_2(p), R::Point_2(q), R::Point_2(r));
}

template < class R >
inline CGAL_Ordertype CGAL_ordertype(const CGAL_Point_2<R> &p,
                                     const CGAL_Point_2<R>&q,
                                     const CGAL_Point_2<R> &r)
{
  return CGAL_ordertype(R::Point_2(p), R::Point_2(q), R::Point_2(r));
}
/*
template < class RT, class R >
inline RT CGAL_area2(const CGAL_Point_2<R> &p,
                     const CGAL_Point_2<R> &q,
                     const CGAL_Point_2<R> &r)
{
  return CGAL_area2(R::Point_2(p), R::Point_2(q), R::Point_2(r));
}
*/
template <class R >
CGAL_Side CGAL_in_circle(const CGAL_Point_2<R> &p, const CGAL_Point_2<R> &q,
                         const CGAL_Point_2<R> &r, const CGAL_Point_2<R> &test)
{
  return CGAL_in_circle(R::Point_2(p),
                        R::Point_2(q),
                        R::Point_2(r),
                        R::Point_2(test));
}
 


#endif  // CGAL_PREDICATES_ON_POINTS_2_H
