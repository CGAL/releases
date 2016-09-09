// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/LineC2.h
// package       : C2 (2.1.4)
// source        : web/LineC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:31 $
// author(s)     : Andreas.Fabri
//                 Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_LINEC2_H
#define CGAL_LINEC2_H

#ifndef CGAL_THREETUPLE_H
#include <CGAL/Threetuple.h>
#endif // CGAL_THREETUPLE_H
#ifndef CGAL_SEGMENTC2_H
#include <CGAL/SegmentC2.h>
#endif // CGAL_SEGMENTC2_H
#ifndef CGAL_RAYC2_H
#include <CGAL/RayC2.h>
#endif // CGAL_RAYC2_H
#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#include <CGAL/predicates_on_pointsC2.h>
#endif // CGAL_PREDICATES_ON_POINTSC2_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class LineC2 : public Handle
{
public:
                  LineC2();
                  LineC2(const LineC2<FT>  &l);
                  LineC2(const PointC2<FT> &p,
                         const PointC2<FT> &q);
                  LineC2(const FT &a, const FT &b, const FT &c);
                  LineC2(const SegmentC2<FT> &s);
                  LineC2(const RayC2<FT> &r);
                  LineC2(const PointC2<FT> &p,
                         const DirectionC2<FT> &d);
                  ~LineC2();

  LineC2<FT>      &operator=(const LineC2<FT> &l);

  bool            operator==(const LineC2<FT> &l) const;
  bool            operator!=(const LineC2<FT> &l) const;
  int             id() const;

  FT              a() const;
  FT              b() const;
  FT              c() const;

  FT              x_at_y(const FT &y) const;
  FT              y_at_x(const FT &x) const;

  LineC2<FT>      perpendicular(const PointC2<FT> &p) const;
  LineC2<FT>      opposite() const;
  PointC2<FT>     point(int i) const;

  PointC2<FT>     point() const;
  PointC2<FT>     projection(const PointC2<FT> &p) const;

  DirectionC2<FT> direction() const;

  Oriented_side   oriented_side(const PointC2<FT> &p) const;
  bool            has_on_boundary(const PointC2<FT> &p) const;
  bool            has_on_positive_side(const PointC2<FT> &p) const;
  bool            has_on_negative_side(const PointC2<FT> &p) const;

  bool            is_horizontal() const;
  bool            is_vertical() const;
  bool            is_degenerate() const;

  LineC2<FT>      transform(const Aff_transformationC2<FT> &t) const;

private:
  _Threetuple<FT>* ptr() const;
  void            new_rep(const PointC2<FT> &p, const PointC2<FT> &q);
  void            new_rep(const FT &a, const FT &b, const FT &c);

};


template < class FT >
inline
_Threetuple<FT>* LineC2<FT>::ptr() const
{
  return (_Threetuple<FT>*)PTR;
}

template < class FT >
CGAL_KERNEL_INLINE
void LineC2<FT>::new_rep(const PointC2<FT> &p, const PointC2<FT> &q)
{
  PTR = new _Threetuple<FT> (p.y() - q.y(),
                             q.x() - p.x(),
                             p.x()*q.y() - p.y()*q.x());
}

template < class FT >
CGAL_KERNEL_INLINE
void LineC2<FT>::new_rep(const FT &a, const FT &b, const FT &c)
{
  PTR = new _Threetuple<FT> (a, b, c);
}

template < class FT >
inline
LineC2<FT>::LineC2()
{
  PTR = new _Threetuple<FT>;
}

template < class FT >
inline
LineC2<FT>::LineC2(const LineC2<FT>  &l) :
  Handle((Handle&)l)
{}

template < class FT >
inline
LineC2<FT>::LineC2(const PointC2<FT> &p, const PointC2<FT> &q)
{
  new_rep(p, q);
}

template < class FT >
inline
LineC2<FT>::LineC2(const FT &a, const FT &b, const FT &c)
{
  new_rep(a, b, c);
}

template < class FT >
inline
LineC2<FT>::LineC2(const SegmentC2<FT> &s)
{
  new_rep(s.start(), s.end());
}

template < class FT >
inline
LineC2<FT>::LineC2(const RayC2<FT> &r)
{
  new_rep(r.start(), r.second_point());
}

template < class FT >
CGAL_KERNEL_INLINE
LineC2<FT>::LineC2(const PointC2<FT> &p, const DirectionC2<FT> &d)
{
  new_rep(-d.dy(), d.dx(), -d.dx()* p.y()  + d.dy() * p.x());
}


template < class FT >
inline
LineC2<FT>::~LineC2()
{}


template < class FT >
CGAL_KERNEL_INLINE
LineC2<FT> &LineC2<FT>::operator=(const LineC2<FT> &l)
{

  Handle::operator=(l);
  return *this;
}
template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool LineC2<FT>::operator==(const LineC2<FT> &l) const
{
  if (  (a() * l.c() != l.a() * c())
      ||(b() * l.c() != l.b() * c()) )
      return false;
  int sc  = sign(c());
  int slc = sign(l.c());
  if ( sc == slc )
      return (sc == 0) ?  ( a()*l.b() ==  b()*l.a() )
                          && (sign(a() ) == sign( l.a() ))
                          && (sign(b() ) == sign( l.b() ))
                       : true;
  return false;
}

template < class FT >
inline
bool LineC2<FT>::operator!=(const LineC2<FT> &l) const
{
  return !(*this == l);
}

template < class FT >
inline
int LineC2<FT>::id() const
{
  return (int) PTR;
}
template < class FT >
inline
FT LineC2<FT>::a() const
{
  return ptr()->e0;
}

template < class FT >
inline
FT LineC2<FT>::b() const
{
  return ptr()->e1;
}

template < class FT >
inline
FT LineC2<FT>::c() const
{
  return ptr()->e2;
}

template < class FT >
CGAL_KERNEL_INLINE
FT LineC2<FT>::x_at_y(const FT &y) const
{
  CGAL_kernel_precondition_msg( (a() != FT(0)),
               "Line::x_at_y(const FT &y) is undefined for horizontal line" );
  return ( -b()*y - c() ) / a();
}

template < class FT >
CGAL_KERNEL_INLINE
FT LineC2<FT>::y_at_x(const FT &x) const
{
  CGAL_kernel_precondition_msg( (b() != FT(0)),
              "Line::x_at_y(const FT &y) is undefined for vertical line");
  return ( -a()*x - c() ) / b();
}

template < class FT >
inline
LineC2<FT> LineC2<FT>::perpendicular(const PointC2<FT> &p) const
{
  return LineC2<FT>( -b() , a() , b() * p.x() - a() * p.y()  );
}


template < class FT >
inline
LineC2<FT> LineC2<FT>::opposite() const
{

  return LineC2<FT>( -a(), -b(), -c() );
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
PointC2<FT> LineC2<FT>::point(int i) const
{

  if (i == 0)
    return is_vertical() ? PointC2<FT>( (-b()-c())/a(), FT(1) )
                         : PointC2<FT>( FT(1), -(a()+c())/b());
  if (i == 1)
    return is_vertical() ? PointC2<FT>( (-b()-c())/a() + b(), FT(1) - a() )
                         : PointC2<FT>( FT(1) + b(), -(a()+c())/b() - a() );
  // we add i times the direction
  if (is_vertical())
    return PointC2<FT>( (-b()-c())/a() + FT(i)*b(), FT(1) - FT(i)*a() );
  return PointC2<FT>( FT(1) + FT(i)*b(), -(a()+c())/b() - FT(i)*a() );
}

template < class FT >
CGAL_KERNEL_INLINE
PointC2<FT> LineC2<FT>::point() const
{
  return is_vertical() ? PointC2<FT>( (-b()-c())/a(), FT(1) )
                       : PointC2<FT>( FT(1), -(a()+c())/b());
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
PointC2<FT> LineC2<FT>::projection(const PointC2<FT> &p) const
{
  if (is_horizontal())
      return PointC2<FT>(p.x(), -c()/b());

  if (is_vertical())
      return PointC2<FT>( -c()/a(), p.y());

  FT ab = a()/b(), ba = b()/a(), ca = c()/a();
  FT y = ( -p.x() + ab*p.y() - ca ) / ( ba + ab );
  return PointC2<FT>(-ba * y - ca, y);
}

template < class FT >
inline
DirectionC2<FT> LineC2<FT>::direction() const
{
  return DirectionC2<FT>( b(), -a() );
}

template < class FT >
CGAL_KERNEL_INLINE
Oriented_side LineC2<FT>::oriented_side(const PointC2<FT> &p) const
{
  return Oriented_side(sign(a()*p.x() + b()*p.y() + c()));
}

template < class FT >
inline
bool LineC2<FT>::has_on_boundary(const PointC2<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()) == FT(0);
}

template < class FT >
inline
bool LineC2<FT>::has_on_positive_side(const PointC2<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()) >  FT(0);
}

template < class FT >
CGAL_KERNEL_INLINE
bool LineC2<FT>::has_on_negative_side(const PointC2<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()) <  FT(0);
}

template < class FT >
inline
bool LineC2<FT>::is_horizontal() const
{
  return a() == FT(0) ;
}

template < class FT >
inline
bool LineC2<FT>::is_vertical() const
{
  return b() == FT(0) ;
}

template < class FT >
inline
bool LineC2<FT>::is_degenerate() const
{
  return (a() == FT(0)) && (b() == FT(0)) ;
}

template < class FT >
inline
LineC2<FT> LineC2<FT>::transform(const Aff_transformationC2<FT> &t) const
{
  return LineC2<FT>( t.transform(point(0) ), t.transform(direction() ));
}



#ifndef CGAL_NO_OSTREAM_INSERT_LINEC2
template < class FT >
ostream &operator<<(ostream &os, const LineC2<FT> &l)
{

    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << l.a() << ' ' << l.b() << ' ' << l.c();
    case IO::BINARY :
        write(os, l.a());
        write(os, l.b());
        write(os, l.c());
        return os;
    default:
        return os << "LineC2(" << l.a() << ", " << l.b() << ", " << l.c() <<')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_LINEC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINEC2
template < class FT >
istream &operator>>(istream &is, LineC2<FT> &p)
{
    FT a, b, c;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> a >> b >> c;
        break;
    case IO::BINARY :
        read(is, a);
        read(is, b);
        read(is, c);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = LineC2<FT>(a, b, c);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINEC2



CGAL_END_NAMESPACE

#endif // CGAL_LINEC2_H
