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
// file          : include/CGAL/SegmentC2.h
// package       : C2 (2.1.4)
// source        : web/SegmentC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:33 $
// author(s)     : Andreas.Fabri
//                 Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SEGMENTC2_H
#define CGAL_SEGMENTC2_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H
#ifndef CGAL_LINEC2_H
#include <CGAL/LineC2.h>
#endif // CGAL_LINEC2_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class SegmentC2 : public Handle
{
public:
                  SegmentC2();
                  SegmentC2(const SegmentC2<FT>  &s);
                  SegmentC2(const PointC2<FT> &sp,
                            const PointC2<FT> &ep);
                  ~SegmentC2();

  SegmentC2<FT>   &operator=(const SegmentC2<FT> &s);

  bool            is_horizontal() const;
  bool            is_vertical() const;
  bool            has_on(const PointC2<FT> &p) const;
  bool            collinear_has_on(const PointC2<FT> &p) const;

  bool            operator==(const SegmentC2<FT> &s) const;
  bool            operator!=(const SegmentC2<FT> &s) const;
  int             id() const;

  PointC2<FT>     start() const;
  PointC2<FT>     end() const;

  PointC2<FT>     source() const;
  PointC2<FT>     target() const;

  PointC2<FT>     min() const;
  PointC2<FT>     max() const;
  PointC2<FT>     vertex(int i) const;
  PointC2<FT>     point(int i) const;
  PointC2<FT>     operator[](int i) const;

  FT              squared_length() const;

  DirectionC2<FT> direction() const;
  LineC2<FT>      supporting_line() const;
  SegmentC2<FT>   opposite() const;
  SegmentC2<FT>   transform(const Aff_transformationC2<FT> &t) const;

  bool            is_degenerate() const;
  Bbox_2          bbox() const;

private:
  _Twotuple< PointC2<FT> >*   ptr() const
  {
  return (_Twotuple< PointC2<FT> >*)PTR;
  }
};

template < class FT >
CGAL_KERNEL_CTOR_INLINE
SegmentC2<FT>::SegmentC2()
{
  PTR = new _Twotuple< PointC2<FT> >;
}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
SegmentC2<FT>::SegmentC2(const SegmentC2<FT>  &s) :
  Handle((Handle&)s)
{}

template < class FT >
CGAL_KERNEL_CTOR_INLINE
SegmentC2<FT>::SegmentC2(const PointC2<FT> &sp,
                         const PointC2<FT> &ep)
{
  PTR = new _Twotuple< PointC2<FT> >(sp, ep);
}

template < class FT >
inline
SegmentC2<FT>::~SegmentC2()
{}

#ifdef  CGAL_TO_DOUBLE
template < class FT >
SegmentC2<FT>::operator SegmentC2<double>() const
{
  return SegmentC2<double>(source(), target());
}
#endif // CGAL_TO_DOUBLE

template < class FT >
inline
SegmentC2<FT> &SegmentC2<FT>::operator=(const SegmentC2<FT> &s)
{
  Handle::operator=(s);
  return *this;
}
template < class FT >
inline
bool  SegmentC2<FT>::operator==(const SegmentC2<FT> &s) const
{
  return ( (source() == s.source())  && (target() == s.target()) );
}

template < class FT >
inline
bool  SegmentC2<FT>::operator!=(const SegmentC2<FT> &s) const
{
  return !(*this == s);
}

template < class FT >
inline
int SegmentC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
inline
PointC2<FT>  SegmentC2<FT>::start() const
{
  return ptr()->e0;
}

template < class FT >
inline
PointC2<FT>  SegmentC2<FT>::end() const
{
  return ptr()->e1;
}


template < class FT >
inline
PointC2<FT>  SegmentC2<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
inline
PointC2<FT>  SegmentC2<FT>::target() const
{
  return ptr()->e1;
}


template < class FT >
CGAL_KERNEL_INLINE
PointC2<FT>  SegmentC2<FT>::min() const
{
  return (lexicographically_xy_smaller(source(),target())) ? source()
                                                           : target();
}

template < class FT >
CGAL_KERNEL_INLINE
PointC2<FT>  SegmentC2<FT>::max() const
{
  return (lexicographically_xy_smaller(source(),target())) ? target()
                                                           : source();
}

template < class FT >
CGAL_KERNEL_INLINE
PointC2<FT> SegmentC2<FT>::vertex(int i) const
{
  return (i%2 ==0) ? source() : target();
}

template < class FT >
CGAL_KERNEL_INLINE
PointC2<FT> SegmentC2<FT>::point(int i) const
{
  return (i%2 ==0) ? source() : target();
}

template < class FT >
inline
PointC2<FT> SegmentC2<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
CGAL_KERNEL_INLINE
FT SegmentC2<FT>::squared_length() const
{
  return squared_distance(source(), target());
}

template < class FT >
CGAL_KERNEL_INLINE
DirectionC2<FT> SegmentC2<FT>::direction() const
{
  return DirectionC2<FT>( target() - source() );
}

template < class FT >
inline
LineC2<FT> SegmentC2<FT>::supporting_line() const
{
  return LineC2<FT>(*this);
}

template < class FT >
inline
SegmentC2<FT> SegmentC2<FT>::opposite() const
{
  return SegmentC2<FT>(target(), source());
}

template < class FT >
inline
SegmentC2<FT> SegmentC2<FT>::transform( const Aff_transformationC2<FT> &t) const
{
  return SegmentC2<FT>(t.transform(source()), t.transform(target()));
}

template < class FT >
CGAL_KERNEL_INLINE
Bbox_2 SegmentC2<FT>::bbox() const
{
  return source().bbox() + target().bbox();
}

template < class FT >
inline
bool  SegmentC2<FT>::is_degenerate() const
{
  return (source() == target());
}


#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENTC2
template < class FT >
ostream &operator<<(ostream &os, const SegmentC2<FT> &s)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << s.source() << ' ' << s.target();
    case IO::BINARY :
        return os << s.source() << s.target();
    default:
        return os << "SegmentC2(" << s.source() <<  ", " << s.target() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENTC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENTC2
template < class FT >
istream &operator>>(istream &is, SegmentC2<FT> &s)
{
    PointC2<FT> p, q;

    is >> p >> q;

    s = SegmentC2<FT>(p, q);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENTC2

template < class FT >
CGAL_KERNEL_INLINE
bool SegmentC2<FT>::is_horizontal() const
{
  return source().y() == target().y();
}

template < class FT >
CGAL_KERNEL_INLINE
bool SegmentC2<FT>::is_vertical() const
{
  return source().x() == target().x();
}

template < class FT >
CGAL_KERNEL_INLINE
bool SegmentC2<FT>::has_on(const PointC2<FT> &p) const
{
  return(( p == source() )
         || ( p == target() )
         || ( collinear(source(), p, target())
              &&( DirectionC2<FT>(p - source())
                  !=
                  DirectionC2<FT>(p - target()))
             )
         );
}


template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool SegmentC2<FT>::collinear_has_on(const PointC2<FT> &p)
const
{
    CGAL_kernel_exactness_precondition( collinear(source(), p, target()) );
    if (abs(target().x()-source().x())
      > abs(target().y()-source().y())) {
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


CGAL_END_NAMESPACE

#endif
