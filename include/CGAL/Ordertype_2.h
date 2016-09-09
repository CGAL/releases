// Source: Ordertype_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_ORDERTYPE_2_H
#define CGAL_ORDERTYPE_2_H

#include <CGAL/OrdertypeC2.h>
#include <CGAL/Point_2.h>

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
   return CGAL_leftturn(R::Point_2(p), R::Point_2(q), R::Point_2(r));
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
  assert(0); // not implemented
  return CGAL_ON;
}


#endif
