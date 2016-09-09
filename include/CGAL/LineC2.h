// ======================================================================
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
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/LineC2.h
// package       : C2 (1.3)
// source        : web/LineC2.fw
// revision      : $Revision: 1.9 $
// revision_date : $Date: 1997/12/15 11:11:26 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_LINEC2_H
#define CGAL_LINEC2_H

#include <CGAL/Threetuple.h>
#include <CGAL/predicates_on_pointsC2.h>


template < class FT >
class CGAL_LineC2 : public CGAL_Handle
{
public:
                       CGAL_LineC2();
                       CGAL_LineC2(const CGAL_LineC2<FT>  &l);
                       CGAL_LineC2(const CGAL_PointC2<FT> &p,
                                   const CGAL_PointC2<FT> &q);
                       CGAL_LineC2(const FT &a, const FT &b, const FT &c);
                       CGAL_LineC2(const CGAL_SegmentC2<FT> &s);
                       CGAL_LineC2(const CGAL_RayC2<FT> &r);
                       CGAL_LineC2(const CGAL_PointC2<FT> &p,
                                   const CGAL_DirectionC2<FT> &d);
                       ~CGAL_LineC2();

  CGAL_LineC2<FT>      &operator=(const CGAL_LineC2<FT> &l);

  bool                 operator==(const CGAL_LineC2<FT> &l) const;
  bool                 operator!=(const CGAL_LineC2<FT> &l) const;
  int                  id() const;

  FT                   a() const;
  FT                   b() const;
  FT                   c() const;

  FT                   x_at_y(const FT &y) const;
  FT                   y_at_x(const FT &x) const;

  CGAL_LineC2<FT>      perpendicular(const CGAL_PointC2<FT> &p) const;
  CGAL_LineC2<FT>      opposite() const;
  CGAL_PointC2<FT>     point(int i) const;

  CGAL_PointC2<FT>     point() const;
  CGAL_PointC2<FT>     projection(const CGAL_PointC2<FT> &p) const;

  CGAL_DirectionC2<FT> direction() const;

  CGAL_Oriented_side   oriented_side(const CGAL_PointC2<FT> &p) const;
  bool                 has_on_boundary(const CGAL_PointC2<FT> &p) const;
  bool                 has_on_positive_side(const CGAL_PointC2<FT> &p) const;
  bool                 has_on_negative_side(const CGAL_PointC2<FT> &p) const;

  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 is_degenerate() const;

  CGAL_LineC2<FT>      transform(const CGAL_Aff_transformationC2<FT> &t) const;

private:
  CGAL__Threetuple<FT>* ptr() const;
  void                 new_rep(const CGAL_PointC2<FT> &p,
                               const CGAL_PointC2<FT> &q);
  void                 new_rep(const FT &a, const FT &b, const FT &c);

};



template < class FT >
inline
CGAL__Threetuple<FT>* CGAL_LineC2<FT>::ptr() const
{
  return (CGAL__Threetuple<FT>*)PTR;
}

template < class FT >
CGAL_KERNEL_INLINE
void CGAL_LineC2<FT>::new_rep(const CGAL_PointC2<FT> &p,
                                     const CGAL_PointC2<FT> &q)
{
  PTR = new CGAL__Threetuple<FT> (p.y() - q.y(),
                                  q.x() - p.x(),
                                  p.x()*q.y() - p.y()*q.x());
}

template < class FT >
CGAL_KERNEL_INLINE
void CGAL_LineC2<FT>::new_rep(const FT &a, const FT &b, const FT &c)
{
  PTR = new CGAL__Threetuple<FT> (a, b, c);
}


#include <CGAL/SegmentC2.h>
#include <CGAL/RayC2.h>

template < class FT >
inline
CGAL_LineC2<FT>::CGAL_LineC2()
{
  PTR = new CGAL__Threetuple<FT>;
}

template < class FT >
inline
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_LineC2<FT>  &l) :
  CGAL_Handle((CGAL_Handle&)l)
{}

template < class FT >
inline
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_PointC2<FT> &p,
                             const CGAL_PointC2<FT> &q)
{
  new_rep(p, q);
}

template < class FT >
inline
CGAL_LineC2<FT>::CGAL_LineC2(const FT &a, const FT &b, const FT &c)
{
  new_rep(a, b, c);
}

template < class FT >
inline
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_SegmentC2<FT> &s)
{
  new_rep(s.start(), s.end());
}

template < class FT >
inline
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_RayC2<FT> &r)
{
  new_rep(r.start(), r.second_point());
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_LineC2<FT>::CGAL_LineC2(const CGAL_PointC2<FT> &p,
                             const CGAL_DirectionC2<FT> &d)
{
  new_rep(-d.dy(), d.dx(), -d.dx()* p.y()  + d.dy() * p.x());
}


template < class FT >
inline
CGAL_LineC2<FT>::~CGAL_LineC2()
{}


template < class FT >
CGAL_KERNEL_INLINE
CGAL_LineC2<FT> &CGAL_LineC2<FT>::operator=(const CGAL_LineC2<FT> &l)
{

  CGAL_Handle::operator=(l);
  return *this;
}
template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
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
inline
bool CGAL_LineC2<FT>::operator!=(const CGAL_LineC2<FT> &l) const
{
  return !(*this == l);
}

template < class FT >
inline
int CGAL_LineC2<FT>::id() const
{
  return (int) PTR;
}
template < class FT >
inline
FT CGAL_LineC2<FT>::a() const
{
  return ptr()->e0;
}

template < class FT >
inline
FT CGAL_LineC2<FT>::b() const
{
  return ptr()->e1;
}

template < class FT >
inline
FT CGAL_LineC2<FT>::c() const
{
  return ptr()->e2;
}

template < class FT >
CGAL_KERNEL_INLINE
FT CGAL_LineC2<FT>::x_at_y(const FT &y) const
{
  CGAL_kernel_precondition_msg( (a() != FT(0)),
               "Line::x_at_y(const FT &y) is undefined for horizontal line" );
  return ( -b()*y - c() ) / a();
}

template < class FT >
CGAL_KERNEL_INLINE
FT CGAL_LineC2<FT>::y_at_x(const FT &x) const
{
  CGAL_kernel_precondition_msg( (b() != FT(0)),
              "Line::x_at_y(const FT &y) is undefined for vertical line");
  return ( ( (-a()*x) - c() ) / b()) ;
}

template < class FT >
inline
CGAL_LineC2<FT> CGAL_LineC2<FT>::perpendicular(const CGAL_PointC2<FT> &p) const
{
  return CGAL_LineC2<FT>( -b() , a() , b() * p.x() - a() * p.y()  );
}


template < class FT >
inline
CGAL_LineC2<FT> CGAL_LineC2<FT>::opposite() const
{

  return CGAL_LineC2<FT>( -a(), -b(), -c() );
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_PointC2<FT> CGAL_LineC2<FT>::point(int i) const
{

  if (i == 0){
  return is_vertical() ? CGAL_PointC2<FT>( (-b()-c())/a(), FT(1) )
                       : CGAL_PointC2<FT>( FT(1), -(a()+c())/b());
  }
  if (i == 1){
  return is_vertical() ? CGAL_PointC2<FT>( (-b()-c())/a() + b(),
                                           FT(1) - a() )
                       : CGAL_PointC2<FT>( FT(1) + b(),
                                           -(a()+c())/b() - a() );
  }
  // we add i times the direction
  if(is_vertical()){
    return CGAL_PointC2<FT>( (-b()-c())/a() + FT(i)*b(),
                             FT(1) - FT(i)*a() );
  }
  return CGAL_PointC2<FT>( FT(1) + FT(i)*b(),
                           -(a()+c())/b() - FT(i)*a() );
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_PointC2<FT> CGAL_LineC2<FT>::point() const
{
  return is_vertical() ? CGAL_PointC2<FT>( (-b()-c())/a(), FT(1) )
                       : CGAL_PointC2<FT>( FT(1), -(a()+c())/b());
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
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
inline
CGAL_DirectionC2<FT> CGAL_LineC2<FT>::direction() const
{
  return CGAL_DirectionC2<FT>( b(), -a() );
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_Oriented_side CGAL_LineC2<FT>::oriented_side(
                                             const CGAL_PointC2<FT> &p) const
{
  FT n = a()*p.x() + b()*p.y() + c();
  return (n == FT(0)) ? CGAL_ON_ORIENTED_BOUNDARY
                      : ( (n > FT(0)) ? CGAL_ON_POSITIVE_SIDE
                                      : CGAL_ON_NEGATIVE_SIDE);
}

template < class FT >
inline
bool CGAL_LineC2<FT>::has_on_boundary(const CGAL_PointC2<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()) == FT(0);
}

template < class FT >
inline
bool CGAL_LineC2<FT>::has_on_positive_side(
                                             const CGAL_PointC2<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()) >  FT(0);
}

template < class FT >
CGAL_KERNEL_INLINE
bool CGAL_LineC2<FT>::has_on_negative_side(
                                             const CGAL_PointC2<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()) <  FT(0);
}

template < class FT >
inline
bool CGAL_LineC2<FT>::is_horizontal() const
{

  return a() == FT(0) ;
}

template < class FT >
inline
bool CGAL_LineC2<FT>::is_vertical() const
{

  return b() == FT(0) ;
}

template < class FT >
inline
bool CGAL_LineC2<FT>::is_degenerate() const
{
  return (a() == FT(0)) && (b() == FT(0)) ;
}

template < class FT >
inline
CGAL_LineC2<FT> CGAL_LineC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_LineC2<FT>( t.transform(point(0) ),
                          t.transform(direction() ));
}



#ifndef CGAL_NO_OSTREAM_INSERT_LINEC2
template < class FT >
ostream &operator<<(ostream &os, const CGAL_LineC2<FT> &l)
{

    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << l.a() << ' ' << l.b() << ' ' << l.c();
    case CGAL_IO::BINARY :
        CGAL_write(os, l.a());
        CGAL_write(os, l.b());
        CGAL_write(os, l.c());
        return os;
    default:
        return os << "LineC2(" << l.a() << ", " << l.b() << ", " << l.c() <<')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_LINEC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINEC2
template < class FT >
istream &operator>>(istream &is, CGAL_LineC2<FT> &p)
{
    FT a, b, c;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> a >> b >> c;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, a);
        CGAL_read(is, b);
        CGAL_read(is, c);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = CGAL_LineC2<FT>(a, b, c);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINEC2




#endif // CGAL_LINEC2_H
