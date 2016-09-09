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
// file          : include/CGAL/DirectionC2.h
// package       : C2 (2.1.4)
// source        : web/DirectionC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:31 $
// author(s)     : Andreas.Fabri
//                 Herve Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DIRECTIONC2_H
#define CGAL_DIRECTIONC2_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H
#ifndef CGAL_VECTORC2_H
#include <CGAL/VectorC2.h>
#endif // CGAL_VECTORC2_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class DirectionC2 : public Handle
{
public:
                  DirectionC2();
                  DirectionC2(const DirectionC2<FT> &d);
                  DirectionC2(const VectorC2<FT> &v);
                  DirectionC2(const FT &x,
                              const FT &y);
                  ~DirectionC2();

  DirectionC2<FT> &operator=(const DirectionC2<FT> &d);

  bool            operator==(const DirectionC2<FT> &d) const;
  bool            operator!=(const DirectionC2<FT> &d) const;
  bool            operator>=(const DirectionC2<FT> &d) const;
  bool            operator<=(const DirectionC2<FT> &d) const;
  bool            operator>(const DirectionC2<FT> &d) const;
  bool            operator<(const DirectionC2<FT> &d) const;
  bool            counterclockwise_in_between(
                               const DirectionC2<FT> &d1,
                               const DirectionC2<FT> &d2) const;
  int             id() const;

  VectorC2<FT>    vector() const;

  DirectionC2<FT> perpendicular(const Orientation &o) const;
  DirectionC2<FT> transform(const Aff_transformationC2<FT> &t) const;

  DirectionC2<FT> operator-() const;

  FT              delta(int i) const;
  FT              dx() const;
  FT              dy() const;

private:
  _Twotuple<FT>*   ptr() const;
};

template < class FT >
inline
_Twotuple<FT>*
DirectionC2<FT>::ptr() const
{
  return (_Twotuple<FT>*)PTR;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
DirectionC2<FT>::DirectionC2()
{
  PTR = new _Twotuple<FT>();
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
DirectionC2<FT>::DirectionC2(const DirectionC2<FT> &d) :
  Handle((Handle&)d)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
DirectionC2<FT>::DirectionC2(const VectorC2<FT> &v) :
  Handle((Handle&)v)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
DirectionC2<FT>::DirectionC2(const FT &x, const FT &y)
{
  PTR = new _Twotuple<FT>(x, y);
}

template < class FT >
inline DirectionC2<FT>:: ~DirectionC2()
{}

template < class FT >
CGAL_KERNEL_INLINE
DirectionC2<FT> &DirectionC2<FT>::operator=(const DirectionC2<FT> &d)
{
  Handle::operator=(d);
  return *this;
}
template < class FT >
bool
DirectionC2<FT>::operator==(const DirectionC2<FT> &d) const
{
// Use a C2 predicate for that ?
    return (CGAL::sign(dx()) == CGAL::sign(d.dx()))
        && (CGAL::sign(dy()) == CGAL::sign(d.dy()))
        && (dy()*d.dx() == d.dy()*dx());
}

template < class FT >
inline
bool
DirectionC2<FT>::operator!=(const DirectionC2<FT> &d) const
{
  return !( *this == d );
}

template < class FT >
inline
int
DirectionC2<FT>::id() const
{
  return (int)PTR;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
DirectionC2<FT>::operator<(const DirectionC2<FT> &d) const
{
  int quadrant_this = (dx() >= FT(0)) ? ((dy() >= FT(0))?1:4)
                                      : ((dy() >= FT(0))?2:3);
  int quadrant_d    = (d.dx() >= FT(0)) ? ((d.dy() >= FT(0))?1:4)
                                        : ((d.dy() >= FT(0))?2:3);

  if(quadrant_this < quadrant_d)
    return true;
  else if (quadrant_this > quadrant_d)
    return false;
  else
    return dy() * d.dx() < d.dy() * dx();
}

template < class FT >
CGAL_KERNEL_INLINE
bool
DirectionC2<FT>::operator>(const DirectionC2<FT> &d) const
{
  return d < *this ;
}

template < class FT >
CGAL_KERNEL_INLINE
bool
DirectionC2<FT>::operator>=(const DirectionC2<FT> &d) const
{
  return (d < *this) || (d == *this) ;
}

template < class FT >
CGAL_KERNEL_INLINE
bool
DirectionC2<FT>::operator<=(const DirectionC2<FT> &d) const
{
  return (*this < d) || (d == *this) ;
}

template < class FT >
CGAL_KERNEL_INLINE
bool
DirectionC2<FT>::counterclockwise_in_between(const DirectionC2<FT> &d1,
                                             const DirectionC2<FT> &d2) const
{
  return (d2 > *this) && (*this > d1) ;
}
template < class FT >
inline
VectorC2<FT>
DirectionC2<FT>::vector() const
{
  return VectorC2<FT>(*this);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
DirectionC2<FT>
DirectionC2<FT>::perpendicular(const Orientation &o) const
{
  CGAL_kernel_precondition(o != COLLINEAR);
  if (o == COUNTERCLOCKWISE)
    return DirectionC2<FT>(-dy(), dx());
  else
    return DirectionC2<FT>(dy(), -dx());
}

template < class FT >
CGAL_KERNEL_INLINE
DirectionC2<FT> DirectionC2<FT>::transform(
                                const Aff_transformationC2<FT> &t) const
{
  return t.transform(*this);
}

template < class FT >
inline
DirectionC2<FT> DirectionC2<FT>::operator-() const
{
  return DirectionC2<FT>(-dx(), -dy());
}



template < class FT >
CGAL_KERNEL_INLINE
FT
DirectionC2<FT>::delta(int i) const
{
  CGAL_kernel_precondition( ( i == 0 ) || ( i == 1 ) );
  return (i==0) ? dx() : dy();
}


template < class FT >
inline
FT
DirectionC2<FT>::dx() const
{
  return ptr()->e0;
}

template < class FT >
inline
FT
DirectionC2<FT>::dy() const
{
  return ptr()->e1;
}


#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTIONC2
template < class FT >
ostream
&operator<<(ostream &os, const DirectionC2<FT> &d)
{
    VectorC2<FT> v = d.vector();
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << v.x() << ' ' << v.y();
    case IO::BINARY :
        write(os, v.x());
        write(os, v.y());
        return os;
    default:
        return os << "DirectionC2(" << v.x() << ", " << v.y() << ')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTIONC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTIONC2

template < class FT >
istream
&operator>>(istream &is, DirectionC2<FT> &p)
{
    FT x, y;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> x >> y;
        break;
    case IO::BINARY :
        read(is, x);
        read(is, y);
        break;
    default:
        cerr << endl << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = DirectionC2<FT>(x, y);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTIONC2



CGAL_END_NAMESPACE

#endif
