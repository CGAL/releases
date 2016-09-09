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
// file          : include/CGAL/LineC3.h
// package       : C3 (2.1.5)
// source        : web/LineC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:37 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_LINEC3_H
#define CGAL_LINEC3_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H
#ifndef CGAL_PREDICATES_ON_POINTSC3_H
#include <CGAL/predicates_on_pointsC3.h>
#endif // CGAL_PREDICATES_ON_POINTSC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class LineC3 : public Handle
{
public:
                  LineC3();
                  LineC3(const LineC3<FT>  &l);
                  LineC3(const PointC3<FT> &p,
                         const PointC3<FT> &q);
                  LineC3(const SegmentC3<FT> &s);
                  LineC3(const RayC3<FT> &r);
                  LineC3(const PointC3<FT> &p,
                         const DirectionC3<FT> &d);
                  ~LineC3();

  LineC3<FT>      &operator=(const LineC3<FT> &l);

  bool            operator==(const LineC3<FT> &l) const;
  bool            operator!=(const LineC3<FT> &l) const;
  long            id() const;

  PlaneC3<FT>     perpendicular_plane(const PointC3<FT> &p) const;
  LineC3<FT>      opposite() const;

  PointC3<FT>     point() const;
  PointC3<FT>     point(int i) const;

  PointC3<FT>     projection(const PointC3<FT> &p) const;

  DirectionC3<FT> direction() const;

  bool            has_on(const PointC3<FT> &p) const;
  bool            is_degenerate() const;

  LineC3<FT>      transform(const Aff_transformationC3<FT> &t) const;


private:
  _Twotuple< PointC3<FT> >* ptr() const;
  void            new_rep(const PointC3<FT> &p,
                          const VectorC3<FT> &v);
};

template < class FT >
inline _Twotuple< PointC3<FT> >* LineC3<FT>::ptr() const
{
  return (_Twotuple< PointC3<FT> >*)PTR;
}


template < class FT >
inline void LineC3<FT>::new_rep(const PointC3<FT> &p, const VectorC3<FT> &v)
{
  // CGAL_kernel_precondition(  v != NULL_VECTOR );
  PTR = new _Twotuple< PointC3<FT> > (p, ORIGIN+v);
}


CGAL_END_NAMESPACE

#ifndef CGAL_SEGMENTC3_H
#include <CGAL/SegmentC3.h>
#endif // CGAL_SEGMENTC3_H
#ifndef CGAL_RAYC3_H
#include <CGAL/RayC3.h>
#endif // CGAL_RAYC3_H
#ifndef CGAL_PLANEC3_H
#include <CGAL/PlaneC3.h>
#endif // CGAL_PLANEC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
LineC3<FT>::LineC3()
{
  PTR = new _Twotuple<FT>();
}

template < class FT >
LineC3<FT>::LineC3(const LineC3<FT>  &l) :
  Handle((Handle&)l)
{}

template < class FT >
LineC3<FT>::LineC3(const PointC3<FT> &p, const PointC3<FT> &q)
{
  new_rep(p, q-p);
}

template < class FT >
LineC3<FT>::LineC3(const SegmentC3<FT> &s)
{
  new_rep(s.start(), s.end() - s.start());
}

template < class FT >
LineC3<FT>::LineC3(const RayC3<FT> &r)
{
  new_rep(r.start(), r.second_point() - r.start());
}

template < class FT >
LineC3<FT>::LineC3(const PointC3<FT> &p, const DirectionC3<FT> &d)
{
  new_rep(p, d.vector());
}

template < class FT >
LineC3<FT>::~LineC3()
{}


template < class FT >
LineC3<FT> &LineC3<FT>::operator=(const LineC3<FT> &l)
{
  Handle::operator=(l);
  return *this;
}
template < class FT >
bool LineC3<FT>::operator==(const LineC3<FT> &l) const
{
  return has_on(l.point()) && (direction() == l.direction());
}

template < class FT >
inline bool LineC3<FT>::operator!=(const LineC3<FT> &l) const
{
  return !(*this == l);
}

template < class FT >
long LineC3<FT>::id() const
{
  return (long) PTR ;
}

template < class FT >
PointC3<FT> LineC3<FT>::point() const
{
  return ptr()->e0;
}

template < class FT >
DirectionC3<FT> LineC3<FT>::direction() const
{
  return ((ptr()->e1) - ORIGIN).direction();
}


template < class FT >
PointC3<FT> LineC3<FT>::point(int i) const
{
  return PointC3<FT>(point() + FT(i) * ((ptr()->e1) - ORIGIN));
}

template < class FT >
PlaneC3<FT> LineC3<FT>::perpendicular_plane(const PointC3<FT> &p) const
{
  return PlaneC3<FT>(p, direction().vector());
}

template < class FT >
LineC3<FT> LineC3<FT>::opposite() const
{
  return LineC3<FT>(point(), -direction());
}

template < class FT >
PointC3<FT> LineC3<FT>::projection(const PointC3<FT> &p) const
{
  return point() + ( ((direction().vector() * (p - point())) /
                      (direction().vector() * direction().vector()))
                     * direction().vector() );
}


template < class FT >
bool LineC3<FT>::has_on(const PointC3<FT> &p) const
{
  return collinear(point(), point()+direction().vector(), p);
}


template < class FT >
bool LineC3<FT>::is_degenerate() const
{
  return direction() == DirectionC3<FT>(0,0,0);
}


template < class FT >
inline
LineC3<FT> LineC3<FT>::transform(const Aff_transformationC3<FT> &t) const
{
  return LineC3<FT>( t.transform(point()), t.transform(direction()));
}


#ifndef CGAL_NO_OSTREAM_INSERT_LINEC3
template < class FT >
ostream &operator<<(ostream &os, const LineC3<FT> &l)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << l.point(0) << ' ' << l.point(1);
    case IO::BINARY :
        return os << l.point(0) <<  l.point(1);
    default:
        return  os << "LineC3(" << l.point(0) << ", " << l.point(1) << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_LINEC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINEC3
template < class FT >
istream &operator>>(istream &is, LineC3<FT> &l)
{
    PointC3<FT> p, q;
    is >> p >> q;
    l = LineC3<FT>(p, q);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINEC3


CGAL_END_NAMESPACE

#endif // CGAL_LINEC3_H
