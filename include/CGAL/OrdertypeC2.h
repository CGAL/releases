// Source: OrdertypeC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_ORDERTYPEC2_H
#define CGAL_ORDERTYPEC2_H

#include <CGAL/PointC2.h>

template < class FT >
CGAL_Ordertype CGAL_ordertype(const FT &px, const FT &py,
                              const FT &qx, const FT &qy,
                              const FT &rx, const FT &ry)
{
  FT det = px * qy - py * qx +
           py * rx - px * ry +
           qx * ry - rx * qy ;
  return  (det == FT(0.0)) ? CGAL_COLLINEAR 
                           : ((det > FT(0.0))? CGAL_LEFTTURN : CGAL_RIGHTTURN);
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
  assert( CGAL_collinear(p, q, r) );

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
  assert(0); // not implemented
  return CGAL_ON;
}


#endif
