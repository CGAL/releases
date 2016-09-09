// ============================================================================
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/SegmentC3.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_SEGMENTC3_H
#define CGAL_SEGMENTC3_H

#include <CGAL/LineC3.h>

template < class FT >
class CGAL_SegmentC3 : public CGAL_Handle
{
public:
                       CGAL_SegmentC3();
                       CGAL_SegmentC3(const CGAL_SegmentC3<FT>  &s);
                       CGAL_SegmentC3(const CGAL_PointC3<FT> &sp,
                                      const CGAL_PointC3<FT> &ep);

                       ~CGAL_SegmentC3();

  CGAL_SegmentC3<FT>   &operator=(const CGAL_SegmentC3<FT> &s);

  bool                 has_on(const CGAL_PointC3<FT> &p) const;
  bool                 collinear_has_on(const CGAL_PointC3<FT> &p) const;

  bool                 operator==(const CGAL_SegmentC3<FT> &s) const;
  bool                 operator!=(const CGAL_SegmentC3<FT> &s) const;
  int                  id() const;

  CGAL_PointC3<FT>     start() const;
  CGAL_PointC3<FT>     end() const;

  CGAL_PointC3<FT>     source() const;
  CGAL_PointC3<FT>     target() const;

  CGAL_PointC3<FT>     min() const;
  CGAL_PointC3<FT>     max() const;
  CGAL_PointC3<FT>     vertex(int i) const;
  CGAL_PointC3<FT>     point(int i) const;
  CGAL_PointC3<FT>     operator[](int i) const;

  FT                   squared_length() const;

  CGAL_DirectionC3<FT> direction() const;
  CGAL_LineC3<FT>      supporting_line() const;
  CGAL_SegmentC3       opposite() const;
  CGAL_SegmentC3       transform(const CGAL_Aff_transformationC3<FT> &t) const;

  bool                 is_degenerate() const;
  CGAL_Bbox_3          bbox() const;

private:
  CGAL__Twotuple< CGAL_PointC3<FT> >*   ptr() const;
};


template < class FT >
inline CGAL__Twotuple< CGAL_PointC3<FT> > *CGAL_SegmentC3<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC3<FT> >*)PTR;
}


template < class FT >
CGAL_SegmentC3<FT>::CGAL_SegmentC3()
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >;
}


template < class FT >
CGAL_SegmentC3<FT>::CGAL_SegmentC3(const CGAL_SegmentC3<FT>  &s) :
  CGAL_Handle((CGAL_Handle&)s)
{}

template < class FT >
CGAL_SegmentC3<FT>::CGAL_SegmentC3(const CGAL_PointC3<FT> &sp,
                                   const CGAL_PointC3<FT> &ep)
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >(sp, ep);
}


template < class FT >
inline CGAL_SegmentC3<FT>::~CGAL_SegmentC3()
{}


template < class FT >
CGAL_SegmentC3<FT> &CGAL_SegmentC3<FT>::operator=(const CGAL_SegmentC3<FT> &s)
{
  CGAL_Handle::operator=(s);
  return *this;
}
template < class FT >
inline bool  CGAL_SegmentC3<FT>::operator==(const CGAL_SegmentC3<FT> &s) const
{
  return ( (source() == s.source())  && (target() == s.target()) );
}


template < class FT >
inline bool  CGAL_SegmentC3<FT>::operator!=(const CGAL_SegmentC3<FT> &s) const
{
  return !(*this == s);
}


template < class FT >
int  CGAL_SegmentC3<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::start() const
{
  return ptr()->e0;
}


template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::end() const
{
  return ptr()->e1;
}


template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::source() const
{
  return ptr()->e0;
}


template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::target() const
{
  return ptr()->e1;
}


template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::min() const
{
  return (CGAL_lexicographically_xyz_smaller(source(),target())) ? source()
                                                                 : target();
}


template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::max() const
{
  return (CGAL_lexicographically_xyz_smaller(source(),target())) ? target()
                                                                 : source();
}


template < class FT >
inline CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::vertex(int i) const
{
  if (i%2 == 0) {
    return source();
  }
  return target();
}


template < class FT >
inline CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::point(int i) const
{
  if (i%2 == 0) {
    return source();
  }
  return target();
}


template < class FT >
inline CGAL_PointC3<FT> CGAL_SegmentC3<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
inline FT CGAL_SegmentC3<FT>::squared_length() const
{
  return  ( (target() - source()) * (target() - source()));
}


template < class FT >
inline CGAL_DirectionC3<FT> CGAL_SegmentC3<FT>::direction() const
{
  return CGAL_DirectionC3<FT>( target() - source() );
}


template < class FT >
inline CGAL_LineC3<FT> CGAL_SegmentC3<FT>::supporting_line() const
{
  return CGAL_LineC3<FT>(*this);
}


template < class FT >
inline CGAL_SegmentC3<FT> CGAL_SegmentC3<FT>::opposite() const
{
  return CGAL_SegmentC3<FT>(target(), source());
}


template < class FT >
inline CGAL_SegmentC3<FT> CGAL_SegmentC3<FT>::transform(
                                const CGAL_Aff_transformationC3<FT> &t) const
{
  return CGAL_SegmentC3<FT>(t.transform(source()),
                            t.transform(target()));
}


template < class FT >
bool  CGAL_SegmentC3<FT>::is_degenerate() const
{
  return (source() == target());
}


template < class FT >
CGAL_Bbox_3 CGAL_SegmentC3<FT>::bbox() const
{
  return source().bbox() + target().bbox();
}


#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENTC3
template < class FT >
ostream &operator<<(ostream &os, const CGAL_SegmentC3<FT> &s)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << s.source() << ' ' << s.target();
    case CGAL_IO::BINARY :
        return os << s.source() << s.target();
    default:
        return os << "SegmentC3(" << s.source() <<  ", " << s.target() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENTC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENTC3
template < class FT >
istream &operator>>(istream &is, CGAL_SegmentC3<FT> &s)
{
    CGAL_PointC3<FT> p, q;

    is >> p >> q;

    s = CGAL_SegmentC3<FT>(p, q);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENTC3
template < class FT >
bool CGAL_SegmentC3<FT>::has_on(const CGAL_PointC3<FT> &p) const
{
  return(( p == source() )
         || ( p == target() )
         || ( CGAL_collinear(source(), p, target())
              &&( CGAL_DirectionC3<FT>(p - source())
                  !=
                  CGAL_DirectionC3<FT> (p - target()))
             )
         );
}

template < class FT >
inline bool CGAL_SegmentC3<FT>::collinear_has_on(
                                             const CGAL_PointC3<FT> &p) const
{
  CGAL_kernel_exactness_precondition(
        CGAL_collinear(source(), p, target()) );
  return(( p == source() )
         || ( p == target() )
         || ( CGAL_DirectionC3<FT>(p - source())
              !=
              CGAL_DirectionC3<FT> (p - target())) );
}


#endif
