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
// file          : include/CGAL/SegmentC2.h
// package       : C2 (1.3)
// source        : web/SegmentC2.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1997/12/18 18:10:59 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SEGMENTC2_H
#define CGAL_SEGMENTC2_H

#include <CGAL/LineC2.h>

template < class FT >
class CGAL_SegmentC2 : public CGAL_Handle
{
public:
                       CGAL_SegmentC2();
                       CGAL_SegmentC2(const CGAL_SegmentC2<FT>  &s);
                       CGAL_SegmentC2(const CGAL_PointC2<FT> &sp,
                                      const CGAL_PointC2<FT> &ep);

                       ~CGAL_SegmentC2();

  CGAL_SegmentC2<FT>   &operator=(const CGAL_SegmentC2<FT> &s);

  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 has_on(const CGAL_PointC2<FT> &p) const;
  bool                 collinear_has_on(const CGAL_PointC2<FT> &p) const;

  bool                 operator==(const CGAL_SegmentC2<FT> &s) const;
  bool                 operator!=(const CGAL_SegmentC2<FT> &s) const;
  int                  id() const;

  CGAL_PointC2<FT>     start() const;
  CGAL_PointC2<FT>     end() const;

  CGAL_PointC2<FT>     source() const;
  CGAL_PointC2<FT>     target() const;

  CGAL_PointC2<FT>     min() const;
  CGAL_PointC2<FT>     max() const;
  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     point(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  FT                   squared_length() const;

  CGAL_DirectionC2<FT> direction() const;
  CGAL_LineC2<FT>      supporting_line() const;
  CGAL_SegmentC2<FT>   opposite() const;
  CGAL_SegmentC2<FT>   transform(const CGAL_Aff_transformationC2<FT> &t) const;

  bool                 is_degenerate() const;
  CGAL_Bbox_2          bbox() const;

private:
  CGAL__Twotuple< CGAL_PointC2<FT> >*   ptr() const
  {
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
  }
};


template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentC2<FT>::CGAL_SegmentC2()
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentC2<FT>::CGAL_SegmentC2(const CGAL_SegmentC2<FT>  &s) :
  CGAL_Handle((CGAL_Handle&)s)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentC2<FT>::CGAL_SegmentC2(const CGAL_PointC2<FT> &sp,
                                 const CGAL_PointC2<FT> &ep)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, ep);
}

template < class FT >
inline
CGAL_SegmentC2<FT>::~CGAL_SegmentC2()
{}

#ifdef  CGAL_TO_DOUBLE
template < class FT >
CGAL_SegmentC2<FT>::operator CGAL_SegmentC2<double>() const
{
  return CGAL_SegmentC2<double>(source(), target());
}
#endif // CGAL_TO_DOUBLE

template < class FT >
inline
CGAL_SegmentC2<FT> &CGAL_SegmentC2<FT>::operator=(const CGAL_SegmentC2<FT> &s)
{
  CGAL_Handle::operator=(s);
  return *this;
}
template < class FT >
inline
bool  CGAL_SegmentC2<FT>::operator==(const CGAL_SegmentC2<FT> &s) const
{
  return ( (source() == s.source())  && (target() == s.target()) );
}

template < class FT >
inline
bool  CGAL_SegmentC2<FT>::operator!=(const CGAL_SegmentC2<FT> &s) const
{
  return !(*this == s);
}

template < class FT >
inline
int CGAL_SegmentC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
inline
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::start() const
{
  return ptr()->e0;
}

template < class FT >
inline
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::end() const
{
  return ptr()->e1;
}


template < class FT >
inline
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
inline
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::target() const
{
  return ptr()->e1;
}


template < class FT >
CGAL_KERNEL_INLINE
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::min() const
{
  return (CGAL_lexicographically_xy_smaller(source(),target())) ? source()
                                                                : target();
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::max() const
{
  return (CGAL_lexicographically_xy_smaller(source(),target())) ? target()
                                                                : source();
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_PointC2<FT> CGAL_SegmentC2<FT>::vertex(int i) const
{

  if(i%2 == 0) {
  return source();
  }
  return target();
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_PointC2<FT> CGAL_SegmentC2<FT>::point(int i) const
{

  if(i%2 == 0) {
  return source();
  }
  return target();
}

template < class FT >
inline
CGAL_PointC2<FT> CGAL_SegmentC2<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
CGAL_KERNEL_INLINE
FT CGAL_SegmentC2<FT>::squared_length() const
{
  return  ( (target() - source()) * (target() - source()));
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_DirectionC2<FT> CGAL_SegmentC2<FT>::direction() const
{
  return CGAL_DirectionC2<FT>( target() - source() );
}

template < class FT >
inline
CGAL_LineC2<FT> CGAL_SegmentC2<FT>::supporting_line() const
{
  return CGAL_LineC2<FT>(*this);
}

template < class FT >
inline
CGAL_SegmentC2<FT> CGAL_SegmentC2<FT>::opposite() const
{
  return CGAL_SegmentC2<FT>(target(), source());
}

template < class FT >
inline
CGAL_SegmentC2<FT> CGAL_SegmentC2<FT>::transform(
                               const CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_SegmentC2<FT>(t.transform(source()),
                            t.transform(target()));
}

template < class FT >
CGAL_KERNEL_INLINE
CGAL_Bbox_2 CGAL_SegmentC2<FT>::bbox() const
{
  return source().bbox() + target().bbox();
}

template < class FT >
inline
bool  CGAL_SegmentC2<FT>::is_degenerate() const
{
  return (source() == target());
}


#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENTC2
template < class FT >
ostream &operator<<(ostream &os, const CGAL_SegmentC2<FT> &s)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << s.source() << ' ' << s.target();
    case CGAL_IO::BINARY :
        return os << s.source() << s.target();
    default:
        return os << "SegmentC2(" << s.source() <<  ", " << s.target() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENTC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENTC2
template < class FT >
istream &operator>>(istream &is, CGAL_SegmentC2<FT> &s)
{
    CGAL_PointC2<FT> p, q;

    is >> p >> q;

    s = CGAL_SegmentC2<FT>(p, q);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENTC2

template < class FT >
CGAL_KERNEL_INLINE
bool CGAL_SegmentC2<FT>::is_horizontal() const
{
  return (source().y() == target().y());
}

template < class FT >
CGAL_KERNEL_INLINE
bool CGAL_SegmentC2<FT>::is_vertical() const
{

  return (source().x() == target().x());
}

template < class FT >
CGAL_KERNEL_INLINE
bool CGAL_SegmentC2<FT>::has_on(const CGAL_PointC2<FT> &p) const
{
  return(( p == source() )
         || ( p == target() )
         || ( CGAL_collinear(source(), p, target())
              &&( CGAL_DirectionC2<FT>(p - source())
                  !=
                  CGAL_DirectionC2<FT> (p - target()))
             )
         );
}


template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool CGAL_SegmentC2<FT>::collinear_has_on(const CGAL_PointC2<FT> &p)
const
{
    CGAL_kernel_exactness_precondition( CGAL_collinear(source(), p, target()) );
    if (CGAL_abs(target().x()-source().x())
        > CGAL_abs(target().y()-source().y())) {
        if (p.x() < source().x())
            return (p.x() >= target().x());
        if (p.x() <= target().x())
            return true;
        return (p.x() == source().x());
    } else {
        if (p.y() < source().y())
            return (p.y() >= target().y());
        if (p.y() <= target().y())
            return true;
        return (p.y() == source().y());
    }
}


#endif
