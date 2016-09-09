// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// source        : SegmentH2.fw
// file          : include/CGAL/SegmentH2.h
// package       : H2 (1.2.1)
// revision      : 1.2.1
// revision_date : 15 Jan 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SEGMENTH2_H
#define CGAL_SEGMENTH2_H

#ifndef CGAL_POINTH2_H
#include <CGAL/PointH2.h>
#endif // CGAL_POINTH2_H
#ifndef CGAL_LINEH2_H
#include <CGAL/LineH2.h>
#endif // CGAL_LINEH2_H


template < class FT, class RT >
class CGAL__Segment_repH2 : public CGAL_Rep
{
public:
            CGAL__Segment_repH2();
            CGAL__Segment_repH2(const CGAL_PointH2<FT,RT>& sp,
                                const CGAL_PointH2<FT,RT>& ep);
            ~CGAL__Segment_repH2(){}

    CGAL_PointH2<FT,RT>  start;
    CGAL_PointH2<FT,RT>  end;

};

template < class FT, class RT >
class CGAL_SegmentH2 : public CGAL_Handle
{
public:
            CGAL_SegmentH2();
            CGAL_SegmentH2( const CGAL_SegmentH2<FT,RT>& s);
            CGAL_SegmentH2( const CGAL_PointH2<FT,RT>& sp,
                            const CGAL_PointH2<FT,RT>& ep);
            CGAL_SegmentH2(const RT& sw, const RT& sx, const RT& sy,
                           const RT& ew, const RT& ex, const RT& ey);
            ~CGAL_SegmentH2();
    CGAL_SegmentH2<FT,RT>&
            operator=(const CGAL_SegmentH2<FT,RT>& s);

    bool    operator==(const CGAL_SegmentH2<FT,RT>& s) const;
    bool    operator!=(const CGAL_SegmentH2<FT,RT>& s) const;
    bool    identical (const CGAL_SegmentH2<FT,RT>& s) const;
    int     id() const;

    CGAL_PointH2<FT,RT>  source() const;
    CGAL_PointH2<FT,RT>  target() const;
    CGAL_PointH2<FT,RT>  start() const;
    CGAL_PointH2<FT,RT>  end()   const;
    CGAL_PointH2<FT,RT>  vertex(int i) const;
    CGAL_PointH2<FT,RT>  point(int i) const;
    CGAL_PointH2<FT,RT>  operator[](int i) const;
    CGAL_PointH2<FT,RT>  min()   const;
    CGAL_PointH2<FT,RT>  max()   const;
    CGAL_PointH2<FT,RT>  other_vertex(const CGAL_PointH2<FT,RT>& p) const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    has_on(const CGAL_PointH2<FT,RT>& p) const;
    bool    collinear_has_on(const CGAL_PointH2<FT,RT>& p) const;
    bool    is_degenerate() const;

    FT      squared_length() const;

    CGAL_DirectionH2<FT,RT> direction() const;
    CGAL_LineH2<FT,RT>      supporting_line() const;
    CGAL_SegmentH2<FT,RT>   opposite() const;
    CGAL_Bbox_2             bbox() const;

    CGAL_SegmentH2<FT,RT>
            transform( const CGAL_Aff_transformationH2<FT,RT> & t) const;

protected:
    CGAL__Segment_repH2<FT,RT>*   ptr() const;
};

template < class FT, class RT >
inline
CGAL__Segment_repH2<FT,RT>*
CGAL_SegmentH2<FT,RT>::ptr() const
{ return (CGAL__Segment_repH2<FT,RT>*)PTR; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL__Segment_repH2<FT,RT>::CGAL__Segment_repH2()
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL__Segment_repH2<FT,RT>::
CGAL__Segment_repH2(const CGAL_PointH2<FT,RT>& sp,
                    const CGAL_PointH2<FT,RT>& ep) : start(sp), end(ep)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentH2<FT,RT>::CGAL_SegmentH2()
{ PTR = new CGAL__Segment_repH2<FT,RT>; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentH2<FT,RT>::CGAL_SegmentH2(const CGAL_SegmentH2<FT,RT>& s)
  : CGAL_Handle( (CGAL_Handle&) s)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentH2<FT,RT>::CGAL_SegmentH2( const CGAL_PointH2<FT,RT>& sp,
                                       const CGAL_PointH2<FT,RT>& ep)
{ PTR = new CGAL__Segment_repH2<FT,RT>(sp,ep); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentH2<FT,RT>::CGAL_SegmentH2(const RT& sx, const RT& sy, const RT& sw,
                                      const RT& ex, const RT& ey, const RT& ew)
{
  PTR = new CGAL__Segment_repH2<FT,RT> (CGAL_PointH2<FT,RT>(sx,sy,sw),
                                        CGAL_PointH2<FT,RT>(ex,ey,ew) );
}

template < class FT, class RT >
inline
CGAL_SegmentH2<FT,RT>::~CGAL_SegmentH2()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_SegmentH2<FT,RT>&
CGAL_SegmentH2<FT,RT>::operator=(const CGAL_SegmentH2<FT,RT>& s)
{
  CGAL_Handle::operator=(s);
  return *this;
}
template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::source() const
{ return ptr()->start; }

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::start() const
{ return ptr()->start; }

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::target() const
{ return ptr()->end; }

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::end() const
{ return ptr()->end; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::min() const
{
  return
  CGAL_lexicographically_xy_smaller_or_equal(start(),end()) ? start() : end();
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::max() const
{
  return
  CGAL_lexicographically_xy_smaller_or_equal(start(),end()) ? end() : start();
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::other_vertex(const CGAL_PointH2<FT,RT>& p) const
{
  CGAL_kernel_precondition( (p == end()) || (p == start()) );
  return ( p == start() ) ? end() : start() ;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::vertex(int i) const
{
  switch (i%2)
  {
    case 0:  return ptr()->start;
    case 1:  return ptr()->end;
  };
  return CGAL_PointH2<FT,RT>(); // otherwise the SGI compiler complains
}

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::point(int i) const
{ return vertex(i); }

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::operator[](int i) const
{ return vertex(i); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_SegmentH2<FT,RT>::squared_length() const
{ return  (ptr()->end - ptr()->start) * (ptr()->end - ptr()->start); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_DirectionH2<FT,RT>
CGAL_SegmentH2<FT,RT>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return CGAL_DirectionH2<FT,RT>( ptr()->end - ptr()->start );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_LineH2<FT,RT>
CGAL_SegmentH2<FT,RT>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return CGAL_LineH2<FT,RT>(ptr()->start, ptr()->end);
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_SegmentH2<FT,RT>
CGAL_SegmentH2<FT,RT>::opposite() const
{ return CGAL_SegmentH2<FT,RT>(ptr()->end, ptr()->start); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_SegmentH2<FT,RT>
CGAL_SegmentH2<FT,RT>::
transform(const CGAL_Aff_transformationH2<FT,RT>& t) const
{
  return CGAL_SegmentH2<FT,RT>(t.transform(ptr()->start),
                               t.transform(ptr()->end)   );
}

template < class FT, class RT >
inline
CGAL_Bbox_2
CGAL_SegmentH2<FT,RT>::bbox() const
{ return start().bbox() + end().bbox(); }

#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENTH2
template < class FT, class RT >
ostream &
operator<<(ostream &os, const CGAL_SegmentH2<FT,RT> &s)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << s.source() << ' ' << s.target();
    case CGAL_IO::BINARY :
        return os << s.source() << s.target();
    default:
        return os << "SegmentH2(" << s.source() <<  ", " << s.target() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENTH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENTH2
template < class FT, class RT >
istream &
operator>>(istream &is, CGAL_SegmentH2<FT,RT> &s)
{
  CGAL_PointH2<FT,RT> p, q;
  is >> p >> q;
  s = CGAL_SegmentH2<FT,RT>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENTH2
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH2<FT,RT>::is_horizontal() const
{
  return (    ptr()->start.hy() * ptr()->end.hw()
           == ptr()->end.hy() * ptr()->start.hw() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH2<FT,RT>::is_vertical() const
{
  return (    ptr()->start.hx() * ptr()->end.hw()
           == ptr()->end.hx() * ptr()->start.hw() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH2<FT,RT>::is_degenerate() const
{ return (start() == end()); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH2<FT,RT>::has_on(const CGAL_PointH2<FT,RT>& p) const
{
  if ( CGAL_collinear(ptr()->start, p, ptr()->end ) )
  {
      return collinear_has_on(p);
  }
  else
  {
      return false;
  }
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH2<FT,RT>::collinear_has_on(const CGAL_PointH2<FT,RT>& p) const
{
  return (  CGAL_lexicographically_xy_smaller_or_equal(p, max() )
         && CGAL_lexicographically_xy_smaller_or_equal(min(),p) );
}
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH2<FT,RT>::operator==(const CGAL_SegmentH2<FT,RT>& s) const
{
  return (  (start() == s.start() )
          &&(end()   == s.end()   ) );
}

template < class FT, class RT >
inline
bool
CGAL_SegmentH2<FT,RT>::operator!=(const CGAL_SegmentH2<FT,RT>& s) const
{ return ( !operator==(s) ); }  /* XXX */

template < class FT, class RT >
inline
bool
CGAL_SegmentH2<FT,RT>::identical(const CGAL_SegmentH2<FT,RT>& s) const
{ return  PTR == s.PTR; }

template < class FT, class RT >
inline
int
CGAL_SegmentH2<FT,RT>::id() const
{ return (int)PTR; }


#endif // CGAL_SEGMENTH2_H
