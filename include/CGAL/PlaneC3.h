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
// file          : include/CGAL/PlaneC3.h
// package       : C3 (2.1.5)
// source        : web/PlaneC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:37 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PLANEC3_H
#define CGAL_PLANEC3_H

#ifndef CGAL_FOURTUPLE_H
#include <CGAL/Fourtuple.h>
#endif // CGAL_FOURTUPLE_H
#ifndef CGAL_SOLVEC3_H
#include <CGAL/solveC3.h>
#endif // CGAL_SOLVEC3_H
#ifndef CGAL_BASIC_CONSTRUCTIONSC3_H
#include <CGAL/basic_constructionsC3.h>
#endif // CGAL_BASIC_CONSTRUCTIONSC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class PlaneC3 : public Handle
{
public:
                   PlaneC3();
                   PlaneC3(const PlaneC3<FT> &p);
                   PlaneC3(const PointC3<FT> &p,
                           const PointC3<FT> &q,
                           const PointC3<FT> &r);
                   PlaneC3(const PointC3<FT> &p,
                           const DirectionC3<FT> &d);
                   PlaneC3(const PointC3<FT> &p,
                           const VectorC3<FT> &v);
                   PlaneC3(const FT &a, const FT &b,
                           const FT &c, const FT &d);
                   PlaneC3(const LineC3<FT> &l,
                           const PointC3<FT> &p);
                   PlaneC3(const SegmentC3<FT> &s,
                           const PointC3<FT> &p);
                   PlaneC3(RayC3<FT> &r,
                           const PointC3<FT> &p);
                   ~PlaneC3();
  PlaneC3<FT>       &operator=(const PlaneC3<FT> &p);

  bool             operator==(const PlaneC3<FT> &p) const;
  bool             operator!=(const PlaneC3<FT> &p) const;
  long             id() const;

  FT               a() const;
  FT               b() const;
  FT               c() const;
  FT               d() const;

  LineC3<FT>       perpendicular_line(const PointC3<FT> &p) const;
  PlaneC3          opposite() const;

  PointC3<FT>      point() const;
  PointC3<FT>      projection(const PointC3<FT> &p) const;
  VectorC3<FT>     orthogonal_vector() const;
  DirectionC3<FT>  orthogonal_direction() const;
  VectorC3<FT>     base1() const;
  VectorC3<FT>     base2() const;

  PointC3<FT>      to_plane_basis(const PointC3<FT> &p) const;

  PointC2<FT>      to_2d(const PointC3<FT> &p) const;
  PointC3<FT>      to_3d(const PointC2<FT> &p) const;

  PlaneC3          transform(const Aff_transformationC3<FT> &t) const;


  Oriented_side    oriented_side(const PointC3<FT> &p) const;
  bool             has_on_boundary(const PointC3<FT> &p) const;
  bool             has_on_boundary(const LineC3<FT> &p) const;
  bool             has_on_positive_side(const PointC3<FT> &l) const;
  bool             has_on_negative_side(const PointC3<FT> &l) const;

  bool             is_degenerate() const;

private:
  _Fourtuple<FT>*   ptr() const;
  void              new_rep(const PointC3<FT> &p,
                            const PointC3<FT> &q,
                            const PointC3<FT> &r);
  void              new_rep(const FT &a, const FT &b,
                            const FT &c, const FT &d);
};

template < class FT >
inline _Fourtuple<FT>* PlaneC3<FT>::ptr() const
{
    return (_Fourtuple<FT>*)PTR;
}

template < class FT >
inline
void
PlaneC3<FT>::new_rep(const FT &a, const FT &b, const FT &c, const FT &d)
{
  PTR = new _Fourtuple<FT>(a, b, c, d);
}

template < class FT >
inline
void
PlaneC3<FT>::new_rep(const PointC3<FT> &p,
                     const PointC3<FT> &q,
                     const PointC3<FT> &r)
{
  FT rpx = p.x()-r.x();
  FT rpy = p.y()-r.y();
  FT rpz = p.z()-r.z();
  FT rqx = q.x()-r.x();
  FT rqy = q.y()-r.y();
  FT rqz = q.z()-r.z();
  // Cross product rp * rq.
  FT A = rpy*rqz - rqy*rpz;
  FT B = rpz*rqx - rqz*rpx;
  FT C = rpx*rqy - rqx*rpy;
  FT D = - A*r.x() - B*r.y() - C*r.z();
  PTR = new _Fourtuple<FT>(A, B, C, D);
}


CGAL_END_NAMESPACE

#ifndef CGAL_LINEC3_H
#include <CGAL/LineC3.h>
#endif // CGAL_LINEC3_H

CGAL_BEGIN_NAMESPACE


template < class FT >
PlaneC3<FT>::PlaneC3()
{
  PTR = new _Fourtuple<FT>();
}

template < class FT >
PlaneC3<FT>::PlaneC3(const PlaneC3<FT> &p) :
  Handle(p)
{}

template < class FT >
PlaneC3<FT>::PlaneC3(const PointC3<FT> &p,
                     const PointC3<FT> &q,
                     const PointC3<FT> &r)
{
  new_rep(p, q, r);
}

template < class FT >
PlaneC3<FT>::PlaneC3(const PointC3<FT> &p, const DirectionC3<FT> &d)
{
  new_rep(d.dx(), d.dy(),
          d.dz(),
          -d.dx() * p.x() - d.dy() * p.y() - d.dz() * p.z());
}

template < class FT >
PlaneC3<FT>::PlaneC3(const PointC3<FT> &p, const VectorC3<FT> &v)
{
  new_rep(v.x(), v.y(), v.z(), -v.x() * p.x() - v.y() * p.y() - v.z() * p.z());
}

template < class FT >
PlaneC3<FT>::PlaneC3(const FT &a, const FT &b, const FT &c, const FT &d)
{
  new_rep(a, b, c, d);
}

template < class FT >
PlaneC3<FT>::PlaneC3(const LineC3<FT> &l, const PointC3<FT> &p)
{
  new_rep(l.point(), l.point()+l.direction().vector(), p);
}

template < class FT >
PlaneC3<FT>::PlaneC3(const SegmentC3<FT> &s, const PointC3<FT> &p)
{
  new_rep(s.start(), s.end(), p);
}

template < class FT >
PlaneC3<FT>::PlaneC3(RayC3<FT> &r, const PointC3<FT> &p)
{
  new_rep(r.start(), r.second_point(), p);
}

template < class FT >
PlaneC3<FT>::~PlaneC3()
{}

template < class FT >
PlaneC3<FT> &PlaneC3<FT>::operator=(const PlaneC3<FT> &p)
{

  Handle::operator=(p);
  return *this;
}

template < class FT >
bool PlaneC3<FT>::operator==(const PlaneC3<FT> &p) const
{
  return has_on_boundary(p.point()) &&
         (orthogonal_direction() == p.orthogonal_direction());

}

template < class FT >
bool PlaneC3<FT>::operator!=(const PlaneC3<FT> &p) const
{
  return !(*this == p);
}

template < class FT >
long PlaneC3<FT>::id() const
{
  return (long) PTR;
}
template < class FT >
FT PlaneC3<FT>::a() const
{
  return ptr()->e0;
}

template < class FT >
FT PlaneC3<FT>::b() const
{
  return ptr()->e1;
}

template < class FT >
FT PlaneC3<FT>::c() const
{
  return ptr()->e2;
}

template < class FT >
FT PlaneC3<FT>::d() const
{
  return ptr()->e3;
}
template < class FT >
PointC3<FT>  PlaneC3<FT>::point() const
{
  if (a() != FT(0)) // not parallel to x-axis
    return PointC3<FT>(-d()/a(), FT(0), FT(0));
  if (b() != FT(0)) // not parallel to y-axis
    return PointC3<FT>(FT(0), -d()/b(), FT(0));
  // parallel to xy-plane => intersects z-axis
  return PointC3<FT>(FT(0), FT(0), -d()/c());
}

template < class FT >
PointC3<FT>
PlaneC3<FT>::projection(const PointC3<FT> &p) const
{
  return CGAL::projection(p, *this);
}

template < class FT >
VectorC3<FT> PlaneC3<FT>::orthogonal_vector() const
{
  return VectorC3<FT>(a(), b(), c());
}


template < class FT >
DirectionC3<FT> PlaneC3<FT>::orthogonal_direction() const
{
  return DirectionC3<FT>(a(), b(), c());
}

template < class FT >
VectorC3<FT> PlaneC3<FT>::base1() const
{
  if( a() == FT(0) )  // parallel to x-axis
      return VectorC3<FT>(FT(1), FT(0), FT(0));

  if( b() == FT(0) )  // parallel to y-axis
      return VectorC3<FT>(FT(0), FT(1), FT(0));

  if (c() == FT(0) )  // parallel to z-axis
      return VectorC3<FT>(FT(0), FT(0), FT(1));

  return VectorC3<FT>(-b(), a(), FT(0));
}


template < class FT >
VectorC3<FT> PlaneC3<FT>::base2() const
{
  if ( a() == FT(0) ) // parallel to x-axis  x-axis already returned in base1
    {
      if (b() == FT(0) )  // parallel to y-axis
          return VectorC3<FT>(FT(0), FT(1), FT(0));

      if (c() == FT(0) ) // parallel to z-axis
          return VectorC3<FT>(FT(0), FT(0), FT(1));

      return VectorC3<FT>(FT(0), -b(), c());
    }
  if (b() == FT(0) )
      return VectorC3<FT>(c(), FT(0), -a());

  if (c() == FT(0) )
      return VectorC3<FT>(-b(), a(), FT(0));

  return VectorC3<FT>(FT(0), -c(), b());
}
template < class FT >
PointC3<FT> PlaneC3<FT>::to_plane_basis(const PointC3<FT> &p) const
{
  const VectorC3<FT> &e1 = base1();
  const VectorC3<FT> &e2 = base2();
  FT alpha, beta, gamma;

  solve(e1, e2, orthogonal_vector(), p - point(), alpha, beta, gamma);

  return PointC3<FT>(alpha, beta, gamma);
}

template < class FT >
PointC2<FT> PlaneC3<FT>::to_2d(const PointC3<FT> &p) const
{
  const VectorC3<FT> &e1 = base1();
  const VectorC3<FT> &e2 = base2();
  FT alpha, beta, gamma;

  solve(e1, e2, orthogonal_vector(), p - point(), alpha, beta, gamma);

  return PointC2<FT>(alpha, beta);
}


template < class FT >
PointC3<FT> PlaneC3<FT>::to_3d(const PointC2<FT> &p) const
{
  VectorC3<FT> e1 = base1(),
               e2 = base2();
  return point() + p.x() * e1 + p.y() * e2;
}

template < class FT >
LineC3<FT> PlaneC3<FT>::perpendicular_line(const PointC3<FT> &p) const
{
  return LineC3<FT>(p, orthogonal_direction());
}


template < class FT >
PlaneC3<FT> PlaneC3<FT>::opposite() const
{
  return PlaneC3<FT>(-a(),-b(),-c(),-d());
}


template < class FT >
PlaneC3<FT> PlaneC3<FT>::transform(const Aff_transformationC3<FT>& t) const
{
  return PlaneC3<FT>( t.transform(point()), (t.is_even())
           ?   t.transpose().inverse().transform(orthogonal_direction())
           : - t.transpose().inverse().transform(orthogonal_direction()) );
}


template < class FT >
Oriented_side PlaneC3<FT>::oriented_side(const PointC3<FT> &p) const
{
  return Oriented_side(CGAL::sign(a()*p.x() + b()*p.y() + c()*p.z() +d()));
}

template < class FT >
bool PlaneC3<FT>::has_on_boundary(const  PointC3<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()*p.z() +d()) == FT(0);
}

template < class FT >
bool PlaneC3<FT>::has_on_boundary(const  LineC3<FT> &l) const
{
  return has_on_boundary(l.point())
         &&  has_on_boundary(l.point() + l.direction().vector());
}

template < class FT >
bool PlaneC3<FT>::has_on_positive_side(const  PointC3<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()*p.z() +d()) > FT(0);
}

template < class FT >
bool PlaneC3<FT>::has_on_negative_side(const  PointC3<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()*p.z() +d()) < FT(0);
}


template < class FT >
bool PlaneC3<FT>::is_degenerate() const
{
  return (a() == FT(0)) && (b() == FT(0)) && (c() == FT(0));
}


#ifndef CGAL_NO_OSTREAM_INSERT_PLANEC3
template < class FT >
ostream &operator<<(ostream &os, const PlaneC3<FT> &p)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << p.a() << ' ' << p.b() <<  ' ' << p.c() << ' ' << p.d();
    case IO::BINARY :
        write(os, p.a());
        write(os, p.b());
        write(os, p.c());
        write(os, p.d());
        return os;
        default:
            os << "PlaneC3(" << p.a() <<  ", " << p.b() <<   ", ";
            os << p.c() << ", " << p.d() <<")";
            return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_PLANEC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_PLANEC3
template < class FT >
istream &operator>>(istream &is, PlaneC3<FT> &p)
{
    FT a, b, c, d;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> a >> b >> c >> d;
        break;
    case IO::BINARY :
        read(is, a);
        read(is, b);
        read(is, c);
        read(is, d);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = PlaneC3<FT>(a, b, c, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_PLANEC3


CGAL_END_NAMESPACE

#endif  // CGAL_PLANEC3_H
