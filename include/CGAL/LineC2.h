// Source: LineC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_LINEC2_H
#define CGAL_LINEC2_H

#include <CGAL/Threetuple.h>
#include <CGAL/OrdertypeC2.h>
#include <CGAL/SegmentC2.h>
#include <CGAL/RayC2.h>

template < class FT >
class CGAL_LineC2 : public handle_base
{
public:
                       CGAL_LineC2();
                       CGAL_LineC2(const CGAL_LineC2  &l);
                       CGAL_LineC2(const CGAL_PointC2<FT> &p,
                                   const CGAL_PointC2<FT> &q);
                       CGAL_LineC2(const FT &a, const FT &b, const FT &c);
                       CGAL_LineC2(const CGAL_SegmentC2<FT> &s);
                       CGAL_LineC2(const CGAL_RayC2<FT> &r);
                       CGAL_LineC2(const CGAL_PointC2<FT> &p,
                                   const CGAL_DirectionC2<FT> &d);
                       ~CGAL_LineC2();
                       operator CGAL_LineC2<double>() const;

  CGAL_LineC2<FT>      &operator=(const CGAL_LineC2<FT> &l);

  bool                 operator==(const CGAL_LineC2<FT> &l) const;
  bool                 operator!=(const CGAL_LineC2<FT> &l) const;
  bool                 identical(const CGAL_LineC2<FT> &l) const;

  FT                   a() const;
  FT                   b() const;
  FT                   c() const;

  FT                   x_at_y(const FT &y) const;
  FT                   y_at_x(const FT &x) const;

  CGAL_LineC2<FT>      perpendicular(const CGAL_PointC2<FT> &p) const;
  CGAL_LineC2<FT>      opposite() const;
  CGAL_PointC2<FT>     point() const;

  CGAL_PointC2<FT>     projection(const CGAL_PointC2<FT> &p) const;

  CGAL_DirectionC2<FT> direction() const;

  bool                 is_on(const CGAL_PointC2<FT> &p) const;
  CGAL_Side            where_is(const CGAL_PointC2<FT> &p) const;
  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 is_degenerate() const;

  CGAL_LineC2          transform(const CGAL_Aff_transformation_baseC2<FT> &t) const;

#ifdef CGAL_KERNEL_PRECONDITION
  bool                 is_defined() const
  {
    return (PTR == NULL) ? false : true;
  }
#endif // CGAL_KERNEL_PRECONDITION

private:
  CGAL__Threetuple<FT>* ptr() const;
  void                 new_rep(const CGAL_PointC2<FT> &p,
                               const CGAL_PointC2<FT> &q);
  void                 new_rep(const FT &a, const FT &b, const FT &c);

};



template < class FT >
inline CGAL__Threetuple<FT>* CGAL_LineC2<FT>::ptr() const
{
  return (CGAL__Threetuple<FT>*)PTR;
}

template < class FT >
inline void CGAL_LineC2<FT>::new_rep(const CGAL_PointC2<FT> &p, const CGAL_PointC2<FT> &q)
{
  CGAL_kernel_precondition(p != q);

  PTR = new CGAL__Threetuple<FT> (p.y() - q.y(),
                                  q.x() - p.x(),
                                  p.x()*q.y() - p.y()*q.x());
}

template < class FT >
inline void CGAL_LineC2<FT>::new_rep(const FT &a, const FT &b, const FT &c)
{
  CGAL_kernel_precondition((a != FT(0.0)) || (b != FT(0.0)) || (c != FT(0.0)));

  PTR = new CGAL__Threetuple<FT> (a, b, c);
}


template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2()
{
#ifdef CGAL_KERNEL_PRECONDITION
  PTR = NULL;
#else
  PTR = new CGAL__Threetuple<FT>;
#endif // CGAL_KERNEL_PRECONDITION
}

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_LineC2<FT>  &l) :
  handle_base(l)
{}

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_PointC2<FT> &p, const CGAL_PointC2<FT> &q)
{
  new_rep(p, q);
}

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2(const FT &a, const FT &b, const FT &c)
{
  new_rep(a, b, c);
}

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_SegmentC2<FT> &s)
{
  new_rep(s.start(), s.end());
}

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_RayC2<FT> &r)
{
  new_rep(r.start(), r.second_point());
}

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_PointC2<FT> &p, const CGAL_DirectionC2<FT> &d)
{
  new_rep(-d.y(), d.x(), -d.x()* p.y()  + d.y() * p.x());
}


template < class FT >
inline CGAL_LineC2<FT>::~CGAL_LineC2()
{}

template < class FT >
CGAL_LineC2<FT>::operator CGAL_LineC2<double>() const
{
  return CGAL_LineC2<double>(a(), b(), c());
}

template < class FT >
CGAL_LineC2<FT> &CGAL_LineC2<FT>::operator=(const CGAL_LineC2<FT> &l)
{
  handle_base::operator=(l);
  return *this;
}
template < class FT >
bool CGAL_LineC2<FT>::operator==(const CGAL_LineC2<FT> &l) const
{
  if (  (a() * l.c() != l.a() * c())
      ||(b() * l.c() != l.b() * c()) )
    {
      return false;
    }
  int sc  = CGAL_sign(c());
  int slc = CGAL_sign(l.c());
  if ( sc == slc )
    {
      return (sc == 0) ?  ( a()*l.b() ==  b()*l.a() )
                          && (CGAL_sign(a() ) == CGAL_sign( l.a() ))
                          && (CGAL_sign(b() ) == CGAL_sign( l.b() ))
                       : true;
    }
  else
    {
      return false;
    }
}

template < class FT >
inline bool CGAL_LineC2<FT>::operator!=(const CGAL_LineC2<FT> &l) const
{
  return !(*this == l);
}

template < class FT >
bool CGAL_LineC2<FT>::identical(const CGAL_LineC2<FT> &l) const
{
  return ( PTR == l.PTR );
}
template < class FT >
FT CGAL_LineC2<FT>::a() const
{
  return ptr()->e0;
}

template < class FT >
FT CGAL_LineC2<FT>::b() const
{
  return ptr()->e1;
}

template < class FT >
FT CGAL_LineC2<FT>::c() const
{
  return ptr()->e2;
}

template < class FT >
inline FT CGAL_LineC2<FT>::x_at_y(const FT &y) const
{
  CGAL_kernel_precondition( a() != FT(0.0) );
  return ( -b()*y - c() ) / a();
}

template < class FT >
inline FT CGAL_LineC2<FT>::y_at_x(const FT &x) const
{
  CGAL_kernel_precondition( b() != FT(0.0) );
  return ( -a()*x - c() ) / b();
}

template < class FT >
inline CGAL_LineC2<FT> CGAL_LineC2<FT>::perpendicular(const CGAL_PointC2<FT> &p) const
{
  return CGAL_LineC2<FT>( -b() , a() , b() * p.x() - a() * p.y()  );
}

template < class FT >
inline CGAL_LineC2<FT> CGAL_LineC2<FT>::opposite() const
{
  return CGAL_LineC2<FT>( -a(), -b(), -c() );
}

template < class FT >
CGAL_PointC2<FT> CGAL_LineC2<FT>::point() const
{
  return is_vertical() ? CGAL_PointC2<FT>( (-b()-c())/a(), FT(1.0) )
                       : CGAL_PointC2<FT>( FT(1.0), -(a()+c())/b());
}

template < class FT >
CGAL_PointC2<FT> CGAL_LineC2<FT>::projection(const CGAL_PointC2<FT> &p) const
{
  if (is_horizontal())
    {
      return CGAL_PointC2<FT>(p.x(), -c()/b());
    }

  if (is_vertical())
    {
      return CGAL_PointC2<FT>( -c()/a(), p.y());
    }
  FT ab = a()/b(), ba = b()/a(), ca = c()/a();
  FT y = ( -p.x() + ab*p.y() - ca ) / ( ba + ab );
  return CGAL_PointC2<FT>(-ba * y - ca, y);
}

template < class FT >
inline CGAL_DirectionC2<FT> CGAL_LineC2<FT>::direction() const
{
  return CGAL_DirectionC2<FT>( b(), -a() );
}

template < class FT >
inline bool CGAL_LineC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()) == FT(0.0);
}

template < class FT >
inline CGAL_Side CGAL_LineC2<FT>::where_is(const CGAL_PointC2<FT> &p) const
{
  FT n = a()*p.x() + b()*p.y() + c();
  return (n == FT(0.0)) ? CGAL_ON : ( (n > FT(0.0)) ? CGAL_LEFT : CGAL_RIGHT);
}

template < class FT >
inline bool CGAL_LineC2<FT>::is_horizontal() const
{
  return a() == FT(0.0) ;
}

template < class FT >
inline bool CGAL_LineC2<FT>::is_vertical() const
{
  return b() == FT(0.0) ;
}

template < class FT >
bool CGAL_LineC2<FT>::is_degenerate() const
{
  return (a() == FT(0.0)) && (b() == FT(0.0)) ;
}

template < class FT >
inline CGAL_LineC2<FT> CGAL_LineC2<FT>::transform(const CGAL_Aff_transformation_baseC2<FT> &t) const
{
  return CGAL_LineC2<FT>( t.transform(point() ),
                          t.transform(direction() ));
}



#ifdef CGAL_IO

#include <stream.h>

template < class FT >
ostream &operator<<(ostream &os, CGAL_LineC2<FT> &l)
{
  os << "LineC2(" << l.a() << ", "<< l.b() << ", " << l.c() << ")";
  return os;
}

#endif


#endif
