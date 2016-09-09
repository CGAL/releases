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
// file          : include/CGAL/RayC2.h
// package       : C2 (2.1.4)
// source        : web/RayC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:32 $
// author(s)     : Andreas.Fabri
//                 Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_RAYC2_H
#define CGAL_RAYC2_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H
#ifndef CGAL_POINTC2_H
#include<CGAL/PointC2.h>
#endif // CGAL_POINTC2_H
#ifndef CGAL_LINEC2_H
#include <CGAL/LineC2.h>
#endif // CGAL_LINEC2_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class RayC2 : public Handle
{
public:
                  RayC2();
                  RayC2(const RayC2<FT> &r);
                  RayC2(const PointC2<FT> &sp,
                        const PointC2<FT> &secondp);
                  RayC2(const PointC2<FT> &sp,
                        const DirectionC2<FT> &d);
                  ~RayC2();



  RayC2<FT>       &operator=(const RayC2<FT> &r);

  bool            operator==(const RayC2<FT> &r) const;
  bool            operator!=(const RayC2<FT> &r) const;
  int             id() const;

  PointC2<FT>     start() const;
  PointC2<FT>     source() const;
  PointC2<FT>     point(int i) const;
  PointC2<FT>     second_point() const;

  DirectionC2<FT> direction() const;
  LineC2<FT>      supporting_line() const;
  RayC2<FT>       opposite() const;

  RayC2<FT>       transform(const Aff_transformationC2<FT> &t) const;

  bool            is_horizontal() const;
  bool            is_vertical() const;
  bool            is_degenerate() const;
  bool            has_on(const PointC2<FT> &p) const;
  bool            collinear_has_on(const PointC2<FT> &p) const;

private:
  _Twotuple< PointC2<FT> > *ptr() const
  {
    return (_Twotuple< PointC2<FT> >*)PTR;
  }
};

template < class FT >
CGAL_KERNEL_CTOR_INLINE
RayC2<FT>::RayC2()
{
  PTR = new _Twotuple< PointC2<FT> >;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
RayC2<FT>::RayC2(const RayC2<FT>  &r) :
  Handle((Handle&)r)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
RayC2<FT>::RayC2(const PointC2<FT> &sp, const PointC2<FT> &secondp)
{
  PTR = new _Twotuple< PointC2<FT> >(sp, secondp);
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
RayC2<FT>::RayC2(const PointC2<FT> &sp, const DirectionC2<FT> &d)
{
  PTR = new _Twotuple< PointC2<FT> >(sp, sp + d.vector());
}

template < class FT >
inline
RayC2<FT>::~RayC2()
{}


template < class FT >
inline
RayC2<FT> &RayC2<FT>::operator=(const RayC2<FT> &r)
{
  Handle::operator=(r);
  return *this;
}
template < class FT >
CGAL_KERNEL_INLINE
bool RayC2<FT>::operator==(const RayC2<FT> &r) const
{
  return ((source() == r.source()) && (direction() == r.direction()) );
}

template < class FT >
bool RayC2<FT>::operator!=(const RayC2<FT> &r) const
{
  return !(*this == r);
}

template < class FT >
inline
int RayC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
inline
PointC2<FT>  RayC2<FT>::start() const
{
  return ptr()->e0;
}

template < class FT >
inline
PointC2<FT>  RayC2<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
inline
PointC2<FT>  RayC2<FT>::second_point() const
{
  return ptr()->e1;
}

template < class FT >
CGAL_KERNEL_INLINE
PointC2<FT>  RayC2<FT>::point(int i) const
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
DirectionC2<FT> RayC2<FT>::direction() const
{
  return DirectionC2<FT>(  second_point() - source() );
}

template < class FT >
inline
LineC2<FT> RayC2<FT>::supporting_line() const
{
  return LineC2<FT>(*this);
}

template < class FT >
inline
RayC2<FT> RayC2<FT>::opposite() const
{
  return RayC2<FT>( source(), - direction() );
}


template < class FT >
CGAL_KERNEL_INLINE
RayC2<FT> RayC2<FT>::transform(const Aff_transformationC2<FT> &t) const
{
  return RayC2<FT>(t.transform(source()), t.transform(second_point()));
}


template < class FT >
CGAL_KERNEL_INLINE
bool RayC2<FT>::is_horizontal() const
{
  return (source().y() ==  second_point().y());
}

template < class FT >
CGAL_KERNEL_INLINE
bool RayC2<FT>::is_vertical() const
{
  return  (source().x() == second_point().x());
}

template < class FT >
CGAL_KERNEL_INLINE
bool RayC2<FT>::is_degenerate() const
{
  return (source() == second_point());
}

template < class FT >
CGAL_KERNEL_INLINE
bool RayC2<FT>::has_on(const PointC2<FT> &p) const
{
  return ( p == source()
           || ( collinear(source(), p, second_point())
           && ( DirectionC2<FT>(p - source()) == direction() )));

}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool RayC2<FT>::collinear_has_on(const PointC2<FT> &p) const
{
    switch(compare_x(source(), second_point())){
    case SMALLER:
        return compare_x(source(), p) != LARGER;
    case LARGER:
        return compare_x(p, source()) != LARGER;
    default:
        switch(compare_y(source(), second_point())){
        case SMALLER:
            return compare_y(source(), p) != LARGER;
        case LARGER:
            return compare_y(p, source()) != LARGER;
        default:
            return true; // p == source()
        }
    }
}


#ifndef CGAL_NO_OSTREAM_INSERT_RAYC2
template < class FT >
ostream &operator<<(ostream &os, const RayC2<FT> &r)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << r.source() << ' ' << r.direction();
    case IO::BINARY :
        return os << r.source() << r.direction();
    default:
        return os << "RayC2(" << r.source() <<  ", " << r.direction() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYC2
template < class FT >
istream &operator>>(istream &is, RayC2<FT> &r)
{
    PointC2<FT> p;
    DirectionC2<FT> d;

    is >> p >> d;

    r = RayC2<FT>(p, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYC2



CGAL_END_NAMESPACE

#endif
