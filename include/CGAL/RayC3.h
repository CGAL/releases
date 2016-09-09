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
// file          : include/CGAL/RayC3.h
// package       : C3 (2.1.5)
// source        : web/RayC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:37 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================



#ifndef CGAL_RAYC3_H
#define CGAL_RAYC3_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H
#ifndef CGAL_LINEC3_H
#include <CGAL/LineC3.h>
#endif // CGAL_LINEC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class RayC3 : public Handle
{
public:
                  RayC3();
                  RayC3(const RayC3<FT> &r);
                  RayC3(const PointC3<FT> &sp, const PointC3<FT> &secondp);
                  RayC3(const PointC3<FT> &sp, const DirectionC3<FT> &d);
                  ~RayC3();

  RayC3<FT>       &operator=(const RayC3<FT> &r);

  bool            operator==(const RayC3<FT> &r) const;
  bool            operator!=(const RayC3<FT> &r) const;
  long            id() const;

  PointC3<FT>     start() const;
  PointC3<FT>     source() const;
  PointC3<FT>     second_point() const;
  PointC3<FT>     point(int i) const;

  DirectionC3<FT> direction() const;
  LineC3<FT>      supporting_line() const;
  RayC3           opposite() const;

  RayC3           transform(const Aff_transformationC3<FT> &t) const;

  bool            is_degenerate() const;
  bool            has_on(const PointC3<FT> &p) const;
  bool            collinear_has_on(const PointC3<FT> &p) const;

private:
_Twotuple< PointC3<FT> > *ptr() const;
};

template < class FT >
_Twotuple< PointC3<FT> > *RayC3<FT>::ptr() const
{
  return (_Twotuple< PointC3<FT> >*)PTR;
}

template < class FT >
RayC3<FT>::RayC3()
{
  PTR = new _Twotuple< PointC3<FT> >;
}

template < class FT >
RayC3<FT>::RayC3(const RayC3<FT>  &r) :
  Handle((Handle&)r)
{}

template < class FT >
RayC3<FT>::RayC3(const PointC3<FT> &sp, const PointC3<FT> &secondp)
{
  PTR = new _Twotuple< PointC3<FT> >(sp,secondp);
}


template < class FT >
RayC3<FT>::RayC3(const PointC3<FT> &sp, const DirectionC3<FT> &d)
{
  PTR = new _Twotuple< PointC3<FT> >(sp, sp + d.vector());
}


template < class FT >
inline RayC3<FT>::~RayC3()
{}


template < class FT >
RayC3<FT> &RayC3<FT>::operator=(const RayC3<FT> &r)
{
  Handle::operator=(r);
  return *this;
}
template < class FT >
inline bool RayC3<FT>::operator==(const RayC3<FT> &r) const
{
  return (source() == r.source()) && (direction() == r.direction());
}


template < class FT >
inline bool RayC3<FT>::operator!=(const RayC3<FT> &r) const
{
  return !(*this == r);
}


template < class FT >
long RayC3<FT>::id() const
{
  return (long) PTR;
}
template < class FT >
PointC3<FT>  RayC3<FT>::start() const
{
  return ptr()->e0;
}


template < class FT >
PointC3<FT>  RayC3<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
PointC3<FT>  RayC3<FT>::second_point() const
{
  return ptr()->e1;
}


template < class FT >
PointC3<FT>  RayC3<FT>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  if (i == 0)
    return ptr()->e0;

  if (i == 1)
    return ptr()->e1;

  return source() + FT(i) * (second_point() - source());
}


template < class FT >
inline
DirectionC3<FT>
RayC3<FT>::direction() const
{
  return DirectionC3<FT>( second_point() - source() );
}


template < class FT >
inline
LineC3<FT>
RayC3<FT>::supporting_line() const
{
  return LineC3<FT>(*this);
}


template < class FT >
inline
RayC3<FT>
RayC3<FT>::opposite() const
{
  return RayC3<FT>( source(), - direction() );
}


template < class FT >
inline
RayC3<FT>
RayC3<FT>::transform(const Aff_transformationC3<FT> &t) const
{
  return RayC3<FT>(t.transform(source()), t.transform(second_point()));
}


template < class FT >
bool
RayC3<FT>::has_on(const PointC3<FT> &p) const
{
  return (p == source()) ||
         ( collinear(source(), p, second_point())
           && ( DirectionC3<FT>(p - source()) == direction() ));
}


template < class FT >
inline
bool
RayC3<FT>::is_degenerate() const
{
  return source() == second_point();
}


template < class FT >
inline
bool
RayC3<FT>::collinear_has_on(const PointC3<FT> &p) const
{
  CGAL_kernel_exactness_precondition( collinear(source(), p, second_point()) );

  Comparison_result cx = compare_x(source(), second_point());
  if (cx != EQUAL)
    return cx != compare_x(p, source());

  Comparison_result cy = compare_y(source(), second_point());
  if (cy != EQUAL)
    return cy != compare_y(p, source());

  Comparison_result cz = compare_z(source(), second_point());
  if (cz != EQUAL)
    return cz != compare_z(p, source());

  return true; // p == source()
}


#ifndef CGAL_NO_OSTREAM_INSERT_RAYC3
template < class FT >
ostream &operator<<(ostream &os, const RayC3<FT> &r)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << r.start() << ' ' << r.direction();
    case IO::BINARY :
        return os<< r.start() << r.direction();
    default:
        return os << "RayC3(" << r.start() <<  ", " << r.direction() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYC3
template < class FT >
istream &operator>>(istream &is, RayC3<FT> &r)
{
    PointC3<FT> p;
    DirectionC3<FT> d;

    is >> p >> d;

    r = RayC3<FT>(p, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYC3


CGAL_END_NAMESPACE

#endif
