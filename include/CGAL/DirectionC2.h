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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/DirectionC2.h
// package       : C2 (1.7)
// source        : web/DirectionC2.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/01/04 06:54:12 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DIRECTIONC2_H
#define CGAL_DIRECTIONC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/VectorC2.h>

template < class FT >
class CGAL_DirectionC2 : public CGAL_Handle
{
public:
                       CGAL_DirectionC2();
                       CGAL_DirectionC2(const CGAL_DirectionC2<FT> &d);
                       CGAL_DirectionC2(const CGAL_VectorC2<FT> &v);
                       CGAL_DirectionC2(const FT &x,
                                        const FT &y);
                       ~CGAL_DirectionC2();

  CGAL_DirectionC2<FT> &operator=(const CGAL_DirectionC2<FT> &d);

  bool                 operator==(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator!=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator>=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator<=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator>(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator<(const CGAL_DirectionC2<FT> &d) const;
  bool                 counterclockwise_in_between(
                                         const CGAL_DirectionC2<FT> &d1,
                                         const CGAL_DirectionC2<FT> &d2) const;
  int                  id() const;

  CGAL_VectorC2<FT>    vector() const;

  CGAL_DirectionC2<FT> perpendicular(const CGAL_Orientation &o) const;
  CGAL_DirectionC2<FT> transform(const CGAL_Aff_transformationC2<FT> &t) const;

  CGAL_DirectionC2<FT> operator-() const;

  FT                   delta(int i) const;
  FT                   dx() const;
  FT                   dy() const;

private:
  CGAL__Twotuple<FT>*   ptr() const;
};


template < class FT >
inline CGAL__Twotuple<FT>*   CGAL_DirectionC2<FT>::ptr() const
{
  return (CGAL__Twotuple<FT>*)PTR;
}


template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionC2<FT>::CGAL_DirectionC2()
{
  PTR = new CGAL__Twotuple<FT>();
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionC2<FT>::CGAL_DirectionC2(const CGAL_DirectionC2<FT> &d) :
  CGAL_Handle((CGAL_Handle&)d)
{

}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionC2<FT>::CGAL_DirectionC2(const CGAL_VectorC2<FT> &v) :
  CGAL_Handle((CGAL_Handle&)v)
{

}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionC2<FT>::CGAL_DirectionC2(const FT &x, const FT &y)
{
  PTR = new CGAL__Twotuple<FT>(x, y);
}

template < class FT >
inline CGAL_DirectionC2<FT>:: ~CGAL_DirectionC2()
{}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_DirectionC2<FT> &CGAL_DirectionC2<FT>::operator=(
                                               const CGAL_DirectionC2<FT> &d)
{
  CGAL_Handle::operator=(d);
  return *this;
}
template < class FT >
bool  CGAL_DirectionC2<FT>::operator==(const CGAL_DirectionC2<FT> &d) const
{
    return (CGAL_sign(dx()) == CGAL_sign(d.dx()))
           && (CGAL_sign(dy()) == CGAL_sign(d.dy()))
           && (dy()*d.dx() == d.dy()*dx());
}

template < class FT >
inline bool  CGAL_DirectionC2<FT>::operator!=(
                                        const CGAL_DirectionC2<FT> &d) const
{
  return !( *this == d );
}

template < class FT >
inline int CGAL_DirectionC2<FT>::id() const
{
  return (int)PTR;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool  CGAL_DirectionC2<FT>::operator<(const CGAL_DirectionC2<FT> &d) const
{
  int quadrant_this = (dx() >= FT(0)) ? ((dy() >= FT(0))?1:4)
                                       : ((dy() >= FT(0))?2:3);
  int quadrant_d    = (d.dx() >= FT(0)) ? ((d.dy() >= FT(0))?1:4)
                                         : ((d.dy() >= FT(0))?2:3);

  if(quadrant_this < quadrant_d) {
    return true;
  } else if (quadrant_this > quadrant_d){
    return false;
  }else {
    return dy() * d.dx() < d.dy() * dx();
  }
}

template < class FT >
CGAL_KERNEL_INLINE
bool  CGAL_DirectionC2<FT>::operator>(const CGAL_DirectionC2<FT> &d) const
{
  return d < *this ;
}

template < class FT >
CGAL_KERNEL_INLINE
bool  CGAL_DirectionC2<FT>::operator>=(const CGAL_DirectionC2<FT> &d) const
{
  return (d < *this) || (d == *this) ;
}

template < class FT >
CGAL_KERNEL_INLINE
bool  CGAL_DirectionC2<FT>::operator<=(const CGAL_DirectionC2<FT> &d) const
{
  return (*this < d) || (d == *this) ;
}

template < class FT >
CGAL_KERNEL_INLINE
bool  CGAL_DirectionC2<FT>::counterclockwise_in_between(
                                        const CGAL_DirectionC2<FT> &d1,
                                        const CGAL_DirectionC2<FT> &d2) const
{
  return (d2 > *this) && (*this > d1) ;
}
template < class FT >
inline
CGAL_VectorC2<FT> CGAL_DirectionC2<FT>::vector() const
{
  return CGAL_VectorC2<FT>(*this);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_DirectionC2<FT> CGAL_DirectionC2<FT>::perpendicular(
                                                const CGAL_Orientation &o) const
{
  CGAL_kernel_precondition(o != CGAL_COLLINEAR);
  if(o == CGAL_COUNTERCLOCKWISE){
    return CGAL_DirectionC2<FT>(-dy(), dx());
  }else{
    return CGAL_DirectionC2<FT>(dy(), -dx());
  }
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_DirectionC2<FT> CGAL_DirectionC2<FT>::transform(
                                const CGAL_Aff_transformationC2<FT> &t) const
{
  return t.transform(*this);
}

template < class FT >
inline
CGAL_DirectionC2<FT> CGAL_DirectionC2<FT>::operator-() const
{
  return CGAL_DirectionC2<FT>(-dx(), -dy());
}



template < class FT >
CGAL_KERNEL_INLINE
FT CGAL_DirectionC2<FT>::delta(int i) const
{
  CGAL_kernel_precondition( ( i == 0 ) || ( i == 1 ) );
  if(i == 0) {
    return dx();
  }
  return dy();
}


template < class FT >
inline
FT CGAL_DirectionC2<FT>::dx() const
{
  return ptr()->e0;
}

template < class FT >
inline
FT CGAL_DirectionC2<FT>::dy() const
{
  return ptr()->e1;
}


#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTIONC2
template < class FT >
ostream &operator<<(ostream &os, const CGAL_DirectionC2<FT> &d)
{
    CGAL_VectorC2<FT> v = d.vector();
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << v.x() << ' ' << v.y();
    case CGAL_IO::BINARY :
        CGAL_write(os, v.x());
        CGAL_write(os, v.y());
        return os;
    default:
        return os << "DirectionC2(" << v.x() << ", " << v.y() << ')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTIONC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTIONC2

template < class FT >
istream &operator>>(istream &is, CGAL_DirectionC2<FT> &p)
{
    FT x, y;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> x >> y;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, x);
        CGAL_read(is, y);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = CGAL_DirectionC2<FT>(x, y);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTIONC2



#endif
