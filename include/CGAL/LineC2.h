// Source: LineC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_LINEC2_H
#define CGAL_LINEC2_H

#include <CGAL/Threetuple.h>
#include <CGAL/OrdertypeC2.h>


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
#ifdef CGAL_TO_DOUBLE
                       operator CGAL_LineC2<double>() const;
#endif // CGAL_TO_DOUBLE

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

  CGAL_LineC2<FT>      transform(const CGAL_Aff_transformationC2<FT> &t) const;

#ifdef CGAL_CHECK_PRECONDITIONS
  bool                 is_defined() const
  {
    return (PTR == NULL) ? false : true;
  }
#endif // CGAL_CHECK_PRECONDITIONS

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
inline void CGAL_LineC2<FT>::new_rep(const CGAL_PointC2<FT> &p, 
                                     const CGAL_PointC2<FT> &q)
{
  CGAL_kernel_precondition( p.is_defined() && q.is_defined() );
  PTR = new CGAL__Threetuple<FT> (p.y() - q.y(),
                                  q.x() - p.x(),
                                  p.x()*q.y() - p.y()*q.x());

  CGAL_nondegeneracy_assertion;
}

template < class FT >
inline void CGAL_LineC2<FT>::new_rep(const FT &a, const FT &b, const FT &c)
{
  PTR = new CGAL__Threetuple<FT> (a, b, c);

  CGAL_nondegeneracy_assertion;
}


#include <CGAL/SegmentC2.h>
#include <CGAL/RayC2.h>

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Threetuple<FT>;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_LineC2<FT>  &l) :
  handle_base((handle_base&)l)
{}

template < class FT >
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_PointC2<FT> &p, 
                             const CGAL_PointC2<FT> &q)
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
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_PointC2<FT> &p, 
                             const CGAL_DirectionC2<FT> &d)
{
  new_rep(-d.y(), d.x(), -d.x()* p.y()  + d.y() * p.x());
}


template < class FT >
CGAL_LineC2<FT>::~CGAL_LineC2()
{}

#ifdef CGAL_TO_DOUBLE
// This leads to lots of ambiguities for the GNU compiler g++-2.7.0

template < class FT >
CGAL_LineC2<FT>::operator CGAL_LineC2<double>() const
{
  return CGAL_LineC2<double>(a(), b(), c());
}
#endif // CGAL_TO_DOUBLE

template < class FT >
CGAL_LineC2<FT> &CGAL_LineC2<FT>::operator=(const CGAL_LineC2<FT> &l)
{
  CGAL_kernel_precondition(l.is_defined());
  handle_base::operator=(l);
  return *this;
}
template < class FT >
bool CGAL_LineC2<FT>::operator==(const CGAL_LineC2<FT> &l) const
{
  CGAL_kernel_precondition(is_defined() && l.is_defined());
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
bool CGAL_LineC2<FT>::operator!=(const CGAL_LineC2<FT> &l) const
{
  CGAL_kernel_precondition(is_defined() && l.is_defined());
  return !(*this == l);
}

template < class FT >
bool CGAL_LineC2<FT>::identical(const CGAL_LineC2<FT> &l) const
{
  CGAL_kernel_precondition(is_defined() && l.is_defined());
  return ( PTR == l.PTR );
}
template < class FT >
FT CGAL_LineC2<FT>::a() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e0;
}

template < class FT >
FT CGAL_LineC2<FT>::b() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e1;
}

template < class FT >
FT CGAL_LineC2<FT>::c() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e2;
}

template < class FT >
FT CGAL_LineC2<FT>::x_at_y(const FT &y) const
{
  CGAL_kernel_precondition( is_defined() && (a() != FT(0.0)) );
  return ( -b()*y - c() ) / a();
}

template < class FT >
FT CGAL_LineC2<FT>::y_at_x(const FT &x) const
{
  CGAL_kernel_precondition( is_defined() && (b() != FT(0.0)) );
  return ( -a()*x - c() ) / b();
}

template < class FT >
CGAL_LineC2<FT> CGAL_LineC2<FT>::perpendicular(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  return CGAL_LineC2<FT>( -b() , a() , b() * p.x() - a() * p.y()  );
}

template < class FT >
CGAL_LineC2<FT> CGAL_LineC2<FT>::opposite() const
{
  CGAL_kernel_precondition( is_defined() );
  return CGAL_LineC2<FT>( -a(), -b(), -c() );
}

template < class FT >
CGAL_PointC2<FT> CGAL_LineC2<FT>::point() const
{
  CGAL_kernel_precondition( is_defined() );
  return is_vertical() ? CGAL_PointC2<FT>( (-b()-c())/a(), FT(1.0) )
                       : CGAL_PointC2<FT>( FT(1.0), -(a()+c())/b());
}

template < class FT >
CGAL_PointC2<FT> CGAL_LineC2<FT>::projection(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined());
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
CGAL_DirectionC2<FT> CGAL_LineC2<FT>::direction() const
{
  CGAL_kernel_precondition( is_defined() );
  return CGAL_DirectionC2<FT>( b(), -a() );
}

template < class FT >
bool CGAL_LineC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  return (a()*p.x() + b()*p.y() + c()) == FT(0.0);
}

template < class FT >
CGAL_Side CGAL_LineC2<FT>::where_is(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  FT n = a()*p.x() + b()*p.y() + c();
  return (n == FT(0.0)) ? CGAL_ON : ( (n > FT(0.0)) ? CGAL_LEFT : CGAL_RIGHT);
}

template < class FT >
bool CGAL_LineC2<FT>::is_horizontal() const
{
  CGAL_kernel_precondition( is_defined() );
  return a() == FT(0.0) ;
}

template < class FT >
bool CGAL_LineC2<FT>::is_vertical() const
{
  CGAL_kernel_precondition( is_defined() );
  return b() == FT(0.0) ;
}

template < class FT >
bool CGAL_LineC2<FT>::is_degenerate() const
{
  CGAL_kernel_precondition( is_defined() );
  return (a() == FT(0.0)) && (b() == FT(0.0)) ;
}

template < class FT >
CGAL_LineC2<FT> CGAL_LineC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
  return CGAL_LineC2<FT>( t.transform(point() ),
                          t.transform(direction() ));
}




#ifdef CGAL_IO

template < class FT >
ostream &operator<<(ostream &os, CGAL_LineC2<FT> &l)
{
  CGAL_kernel_precondition( l.is_defined() );
  os << "LineC2(" << l.a() << ", "<< l.b() << ", " << l.c() << ")";
  return os;
}

#endif


#endif
