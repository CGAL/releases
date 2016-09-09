// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : SegmentH2.fw
// file          : include/CGAL/SegmentH2.h
// package       : H2 (2.4.8)
// revision      : 2.4.8
// revision_date : 10 Dec 1999 
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

CGAL_BEGIN_NAMESPACE


template < class FT, class RT >
class _Segment_repH2 : public Rep
{
public:
            _Segment_repH2();
            _Segment_repH2(const PointH2<FT,RT>& sp,
                                const PointH2<FT,RT>& ep);
            ~_Segment_repH2(){}

    PointH2<FT,RT>  start;
    PointH2<FT,RT>  end;

};

template < class FT, class RT >
class SegmentH2 : public Handle
{
public:
            SegmentH2();
            SegmentH2( const SegmentH2<FT,RT>& s);
            SegmentH2( const PointH2<FT,RT>& sp,
                            const PointH2<FT,RT>& ep);
            SegmentH2(const RT& sw, const RT& sx, const RT& sy,
                           const RT& ew, const RT& ex, const RT& ey);
            ~SegmentH2();
    SegmentH2<FT,RT>&
            operator=(const SegmentH2<FT,RT>& s);

    bool    operator==(const SegmentH2<FT,RT>& s) const;
    bool    operator!=(const SegmentH2<FT,RT>& s) const;
    bool    identical (const SegmentH2<FT,RT>& s) const;
    int     id() const;

    PointH2<FT,RT>  source() const;
    PointH2<FT,RT>  target() const;
    PointH2<FT,RT>  start() const;
    PointH2<FT,RT>  end()   const;
    PointH2<FT,RT>  vertex(int i) const;
    PointH2<FT,RT>  point(int i) const;
    PointH2<FT,RT>  operator[](int i) const;
    PointH2<FT,RT>  min()   const;
    PointH2<FT,RT>  max()   const;
    PointH2<FT,RT>  other_vertex(const PointH2<FT,RT>& p) const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    has_on(const PointH2<FT,RT>& p) const;
    bool    collinear_has_on(const PointH2<FT,RT>& p) const;
    bool    is_degenerate() const;

    FT      squared_length() const;

    DirectionH2<FT,RT> direction() const;
    LineH2<FT,RT>      supporting_line() const;
    SegmentH2<FT,RT>   opposite() const;
    Bbox_2             bbox() const;

    SegmentH2<FT,RT>
            transform( const Aff_transformationH2<FT,RT> & t) const;

protected:
    _Segment_repH2<FT,RT>*   ptr() const;
};

template < class FT, class RT >
inline
_Segment_repH2<FT,RT>*
SegmentH2<FT,RT>::ptr() const
{ return (_Segment_repH2<FT,RT>*)PTR; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
_Segment_repH2<FT,RT>::_Segment_repH2()
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
_Segment_repH2<FT,RT>::
_Segment_repH2(const PointH2<FT,RT>& sp,
                    const PointH2<FT,RT>& ep) : start(sp), end(ep)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SegmentH2<FT,RT>::SegmentH2()
{ PTR = new _Segment_repH2<FT,RT>; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SegmentH2<FT,RT>::SegmentH2(const SegmentH2<FT,RT>& s)
  : Handle( (Handle&) s)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SegmentH2<FT,RT>::SegmentH2( const PointH2<FT,RT>& sp,
                                       const PointH2<FT,RT>& ep)
{ PTR = new _Segment_repH2<FT,RT>(sp,ep); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SegmentH2<FT,RT>::SegmentH2(const RT& sx, const RT& sy, const RT& sw,
                                      const RT& ex, const RT& ey, const RT& ew)
{
  PTR = new _Segment_repH2<FT,RT> (PointH2<FT,RT>(sx,sy,sw),
                                        PointH2<FT,RT>(ex,ey,ew) );
}

template < class FT, class RT >
inline
SegmentH2<FT,RT>::~SegmentH2()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
SegmentH2<FT,RT>&
SegmentH2<FT,RT>::operator=(const SegmentH2<FT,RT>& s)
{
  Handle::operator=(s);
  return *this;
}
template < class FT, class RT >
inline
PointH2<FT,RT>
SegmentH2<FT,RT>::source() const
{ return ptr()->start; }

template < class FT, class RT >
inline
PointH2<FT,RT>
SegmentH2<FT,RT>::start() const
{ return ptr()->start; }

template < class FT, class RT >
inline
PointH2<FT,RT>
SegmentH2<FT,RT>::target() const
{ return ptr()->end; }

template < class FT, class RT >
inline
PointH2<FT,RT>
SegmentH2<FT,RT>::end() const
{ return ptr()->end; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
SegmentH2<FT,RT>::min() const
{
  return
  lexicographically_xy_smaller_or_equal(start(),end()) ? start() : end();
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
SegmentH2<FT,RT>::max() const
{
  return
  lexicographically_xy_smaller_or_equal(start(),end()) ? end() : start();
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
SegmentH2<FT,RT>::other_vertex(const PointH2<FT,RT>& p) const
{
  CGAL_kernel_precondition( (p == end()) || (p == start()) );
  return ( p == start() ) ? end() : start() ;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
SegmentH2<FT,RT>::vertex(int i) const
{
  switch (i%2)
  {
    case 0:  return ptr()->start;
    case 1:  return ptr()->end;
  };
  return PointH2<FT,RT>(); // otherwise the SGI compiler complains
}

template < class FT, class RT >
inline
PointH2<FT,RT>
SegmentH2<FT,RT>::point(int i) const
{ return vertex(i); }

template < class FT, class RT >
inline
PointH2<FT,RT>
SegmentH2<FT,RT>::operator[](int i) const
{ return vertex(i); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
SegmentH2<FT,RT>::squared_length() const
{ return  (ptr()->end - ptr()->start) * (ptr()->end - ptr()->start); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
DirectionH2<FT,RT>
SegmentH2<FT,RT>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return DirectionH2<FT,RT>( ptr()->end - ptr()->start );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
LineH2<FT,RT>
SegmentH2<FT,RT>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return LineH2<FT,RT>(ptr()->start, ptr()->end);
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
SegmentH2<FT,RT>
SegmentH2<FT,RT>::opposite() const
{ return SegmentH2<FT,RT>(ptr()->end, ptr()->start); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
SegmentH2<FT,RT>
SegmentH2<FT,RT>::
transform(const Aff_transformationH2<FT,RT>& t) const
{
  return SegmentH2<FT,RT>(t.transform(ptr()->start),
                               t.transform(ptr()->end)   );
}

template < class FT, class RT >
inline
Bbox_2
SegmentH2<FT,RT>::bbox() const
{ return start().bbox() + end().bbox(); }

#ifndef NO_OSTREAM_INSERT_SEGMENTH2
template < class FT, class RT >
std::ostream &
operator<<(std::ostream &os, const SegmentH2<FT,RT> &s)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << s.source() << ' ' << s.target();
    case IO::BINARY :
        return os << s.source() << s.target();
    default:
        return os << "SegmentH2(" << s.source() <<  ", " << s.target() << ")";
  }
}
#endif // NO_OSTREAM_INSERT_SEGMENTH2

#ifndef NO_ISTREAM_EXTRACT_SEGMENTH2
template < class FT, class RT >
std::istream &
operator>>(std::istream &is, SegmentH2<FT,RT> &s)
{
  PointH2<FT,RT> p, q;
  is >> p >> q;
  s = SegmentH2<FT,RT>(p, q);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_SEGMENTH2
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
SegmentH2<FT,RT>::is_horizontal() const
{
  return (    ptr()->start.hy() * ptr()->end.hw()
           == ptr()->end.hy() * ptr()->start.hw() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
SegmentH2<FT,RT>::is_vertical() const
{
  return (    ptr()->start.hx() * ptr()->end.hw()
           == ptr()->end.hx() * ptr()->start.hw() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
SegmentH2<FT,RT>::is_degenerate() const
{ return (start() == end()); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
SegmentH2<FT,RT>::has_on(const PointH2<FT,RT>& p) const
{
  if ( collinear(ptr()->start, p, ptr()->end ) )
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
SegmentH2<FT,RT>::collinear_has_on(const PointH2<FT,RT>& p) const
{
  return (  lexicographically_xy_smaller_or_equal(p, max() )
         && lexicographically_xy_smaller_or_equal(min(),p) );
}
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
SegmentH2<FT,RT>::operator==(const SegmentH2<FT,RT>& s) const
{
  return (  (start() == s.start() )
          &&(end()   == s.end()   ) );
}

template < class FT, class RT >
inline
bool
SegmentH2<FT,RT>::operator!=(const SegmentH2<FT,RT>& s) const
{ return ( !operator==(s) ); }  /* XXX */

template < class FT, class RT >
inline
bool
SegmentH2<FT,RT>::identical(const SegmentH2<FT,RT>& s) const
{ return  PTR == s.PTR; }

template < class FT, class RT >
inline
int
SegmentH2<FT,RT>::id() const
{ return (int)PTR; }

CGAL_END_NAMESPACE


#endif // CGAL_SEGMENTH2_H
